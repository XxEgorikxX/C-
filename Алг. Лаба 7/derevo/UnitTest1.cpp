#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "C:\\Users\\work\\OneDrive\\Рабочий стол\\Дезе 7\derevo\\UnitTest1\\tttttttttttt\\tttttttttttt.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(Test_SingleElement)
        {
            vector<int> tree = { 42 };
            int result = findMax(tree, 0);
            Assert::AreEqual(42, result);
        }

        TEST_METHOD(Test_MaxInLeftSubtree)
        {
            vector<int> tree = { 5, 100, 8, 1, 4 };
            int result = findMax(tree, 0);
            Assert::AreEqual(100, result);
        }

        TEST_METHOD(Test_MaxInRightSubtree)
        {
            vector<int> tree = { 5, 3, 200, 1, 4 };
            int result = findMax(tree, 0);
            Assert::AreEqual(200, result);
        }

        TEST_METHOD(Test_RootIsMax)
        {
            vector<int> tree = { 500, 3, 8, 1, 4 };
            int result = findMax(tree, 0);
            Assert::AreEqual(500, result);
        }
    };
}