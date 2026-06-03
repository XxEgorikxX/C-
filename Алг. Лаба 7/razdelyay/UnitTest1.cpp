#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "C:\\Users\\work\\OneDrive\\Рабочий стол\\Дезе 7\\razdelyay\\qweqweqwe\\qweqweqwe.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest666
{
    TEST_CLASS(UnitTest666)
    {
    public:

        TEST_METHOD(Test_SingleElement_Found)
        {
            vector<int> a = { 5 };
            Assert::AreEqual(0, firstOccurrence(a, 5));
            Assert::AreEqual(0, lastOccurrence(a, 5));
        }

        TEST_METHOD(Test_SingleElement_NotFound)
        {
            vector<int> a = { 5 };
            Assert::AreEqual(-1, firstOccurrence(a, 10));
            Assert::AreEqual(-1, lastOccurrence(a, 10));
        }

        TEST_METHOD(Test_MultipleOccurrences)
        {
            vector<int> a = { 1, 2, 2, 2, 3 };
            Assert::AreEqual(1, firstOccurrence(a, 2));
            Assert::AreEqual(3, lastOccurrence(a, 2));
        }

        TEST_METHOD(Test_NoOccurrences)
        {
            vector<int> a = { 1, 2, 3, 4, 5 };
            Assert::AreEqual(-1, firstOccurrence(a, 10));
            Assert::AreEqual(-1, lastOccurrence(a, 10));
        }

        TEST_METHOD(Test_AllSameElements)
        {
            vector<int> a = { 7, 7, 7, 7, 7 };
            Assert::AreEqual(0, firstOccurrence(a, 7));
            Assert::AreEqual(4, lastOccurrence(a, 7));
        }

        TEST_METHOD(Test_TargetAtEdges)
        {
            vector<int> a = { 10, 20, 30, 40, 50 };
            Assert::AreEqual(0, firstOccurrence(a, 10));
            Assert::AreEqual(4, lastOccurrence(a, 50));
        }

        TEST_METHOD(Test_NegativeNumbers)
        {
            vector<int> a = { -5, -3, -3, 0, 2 };
            Assert::AreEqual(1, firstOccurrence(a, -3));
            Assert::AreEqual(2, lastOccurrence(a, -3));
        }
    };
}