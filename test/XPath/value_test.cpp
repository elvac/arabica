#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

using namespace Arabica::XPath;

class ValueTest : public TestCase
{
private:
  DOM::Node<std::string> dummy_;

public:
  ValueTest(std::string name) : TestCase(name)
  {
  } // ValueTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    XPathExpressionPtr b(new BoolValue(true));
    assertEquals(true, b->evaluateAsBool(dummy_));
    assertEquals(1.0, b->evaluateAsNumber(dummy_), 0.0);
    assertEquals("true", b->evaluateAsString(dummy_));
  }

  void test2()
  {
    XPathExpressionPtr b2(new BoolValue(false));
    assertEquals(false, b2->evaluateAsBool(dummy_));
    assertEquals(0.0, b2->evaluateAsNumber(dummy_), 0.0);
    assertEquals("false", b2->evaluateAsString(dummy_));
  } // test2

  void test3()
  {
    XPathExpressionPtr n(new NumericValue(99.5));
    assertEquals(true, n->evaluateAsBool(dummy_));
    assertEquals(99.5, n->evaluateAsNumber(dummy_), 0.0);
    assertEquals("99.5", n->evaluateAsString(dummy_));
  }

  void test4()
  {
    XPathExpressionPtr n(new NumericValue(0.0));
    assertEquals(false, n->evaluateAsBool(dummy_));
    assertEquals(0, n->evaluateAsNumber(dummy_), 0);
    assertEquals("0", n->evaluateAsString(dummy_));
  }

  void test5()
  {
    XPathExpressionPtr s(new StringValue("hello"));
    assertEquals(true, s->evaluateAsBool(dummy_));
    assertEquals("hello", s->evaluateAsString(dummy_));
  } // test5

  void test6()
  {
    XPathExpressionPtr s(new StringValue(""));
    assertEquals(false, s->evaluateAsBool(dummy_));
  }

  void test7()
  {
    XPathExpressionPtr s(new StringValue("100"));
    assertEquals(true, s->evaluateAsBool(dummy_));
    assertEquals(100.0, s->evaluateAsNumber(dummy_), 0.0);
    assertEquals("100", s->evaluateAsString(dummy_));
  } // test7

  void test8()
  {
    XPathExpressionPtr s(new StringValue("0"));
    assertEquals(true, s->evaluateAsBool(dummy_));
    assertEquals(0.0, s->evaluateAsNumber(dummy_), 0.0);
    assertEquals("0", s->evaluateAsString(dummy_));
  } // test8

  void test9()
  {
    XPathExpressionPtr bt(new BoolValue(true));
    XPathExpressionPtr st(new StringValue("true"));
    XPathExpressionPtr bf(new BoolValue(false));
    XPathExpressionPtr sf(new StringValue(""));

    assertTrue(areEqual(bt->evaluate(dummy_), (st->evaluate(dummy_))));
    assertTrue(areEqual(st->evaluate(dummy_), (bt->evaluate(dummy_))));

    assertTrue(areEqual(sf->evaluate(dummy_), (bf->evaluate(dummy_))));
    assertTrue(areEqual(bf->evaluate(dummy_), (sf->evaluate(dummy_))));

    assertTrue(areEqual(bt->evaluate(dummy_), (bt->evaluate(dummy_))));
    assertTrue(areEqual(bf->evaluate(dummy_), (bf->evaluate(dummy_))));
    assertTrue(areEqual(st->evaluate(dummy_), (st->evaluate(dummy_))));
    assertTrue(areEqual(sf->evaluate(dummy_), (sf->evaluate(dummy_))));
  } // test9

  void test10()
  {
    XPathExpressionPtr bt(new BoolValue(true));
    XPathExpressionPtr nt(new NumericValue(1.0));
    XPathExpressionPtr bf(new BoolValue(false));
    XPathExpressionPtr nf(new NumericValue(0.0));

    assertTrue(areEqual(bt->evaluate(dummy_), (nt->evaluate(dummy_))));
    assertTrue(areEqual(nt->evaluate(dummy_), (bt->evaluate(dummy_))));

    assertTrue(areEqual(bf->evaluate(dummy_), (nf->evaluate(dummy_))));
    assertTrue(areEqual(nf->evaluate(dummy_), (bf->evaluate(dummy_))));
  } // test10

  void test11()
  {
    XPathExpressionPtr nt(new NumericValue(1.0));
    XPathValuePtr ns = nt->evaluate(dummy_);

    assertTrue(areEqual(ns, (nt->evaluate(dummy_))));
  } // test11
}; // ValueTest

TestSuite* ValueTest_suite()
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ValueTest>("test1", &ValueTest::test1));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test2", &ValueTest::test2));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test3", &ValueTest::test3));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test4", &ValueTest::test4));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test5", &ValueTest::test5));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test6", &ValueTest::test6));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test7", &ValueTest::test7));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test8", &ValueTest::test8));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test9", &ValueTest::test9));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test10", &ValueTest::test10));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test11", &ValueTest::test11));

  return suiteOfTests;
} // ValueTest_suite
