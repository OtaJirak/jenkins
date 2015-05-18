#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

using namespace CppUnit;
class Math
{
public:
static int add(int a, int b)
{
  return a+b;
}
};
class MyTester : public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(MyTester);
CPPUNIT_TEST(test1);
CPPUNIT_TEST(test2);
CPPUNIT_TEST_SUITE_END();
void test1();
void test2();
};
CPPUNIT_TEST_SUITE_REGISTRATION(MyTester);
void MyTester::test1()
{
CPPUNIT_ASSERT(5==Math::add(2,3));
}

void MyTester::test2()
{
CPPUNIT_ASSERT(6==Math::add(3,3));
}

int main(int argc, char** argv)
{

 CPPUNIT_NS::TestResult testresult;

// register listener for collecting the test-results
CPPUNIT_NS::TestResultCollector collectedresults;
testresult.addListener (&collectedresults);

// register listener for per-test progress output
CPPUNIT_NS::BriefTestProgressListener progress;
testresult.addListener (&progress);

// insert test-suite at test-runner by registry
CPPUNIT_NS::TestRunner testrunner;
testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
testrunner.run(testresult);

// output results in compiler-format
CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
compileroutputter.write ();

// Output XML for Jenkins CPPunit plugin
std::ofstream xmlFileOut("MyResults.xml");
XmlOutputter xmlOut(&collectedresults, xmlFileOut);
xmlOut.write();

// return 0 if tests were successful
return collectedresults.wasSuccessful() ? 0 : 1;
}
