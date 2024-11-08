#include <vector>
#include <gtest/gtest.h>

#include "helper.c"
#include "qsort.c"

// Test Suite Example
// ! this is a "Suite"
// * isNonDecreasingTest is a "Test"
TEST(SortTestSuite, isNonDecreasingTest)
{
    int i = 0;
    std::vector<int> anTestcase = {0, 1, 3, 3, 5};

    for(i = 1; i < 5; ++i)
    {
        ASSERT_LE(anTestcase[i - 1], anTestcase[i]);
    }
}

// *  isNonIncresingTest is a "Test" under SortTestSuite
TEST(SortTestSuite, isNonIncresingTest)
{
    int i = 0;
    std::vector<int> anTestcase = {5, 4, 3, 3, 1};

    for(i = 1; i < 5; ++i)
    {
        ASSERT_GE(anTestcase[i - 1], anTestcase[i]);
    }
}

// ! this is a test "fixture"
class SortTestFixture : public testing::Test
{
public:

    // Every time setyo a TEST_F, Setup() would be called
    void SetUp()
    {
        int i = 0;

        ASSERT_EQ(anTest.size(), anCorrect.size());
        nUnitTestNum = anTest.size();

        nTestArrSize = anTest[0].size();
        for(i = 0; i < nUnitTestNum; ++i)
        {
            ASSERT_EQ(anTest[i].size(), nTestArrSize);
        }
    }

    // Every time destoyed a TEST_F, TearDown() would be called
    // void TearDown() {}

    void unitTest();

    int getUnitTestNum() { return nUnitTestNum; };
    int getTestArrSize() { return nTestArrSize;};

    // Unit Test Data
    std::vector<std::vector<int>> anTest = {
        {0, 3, 1, 5, 2},
        {1000000, 0, 9999, -9999, -1000000},
        {5, 4, 3, 2, 1},
        {0, 0, 0, 0, 0},
        {-14, -14, -14, -14, -14},
        {1, 2, 3, 4, 5},
    };

    // 尽管每次创建创建是新的对象，但是 C++ 的类支持 静态成员变量和静态成员函数，
    // 静态成员变量是类的所有对象共享的，静态成员函数则是可以操作静态成员变量的。利用这一点，
    // 便可以在不同的 Test 之间进行数据的共享了。
    // static const double pi = 3.14;

private:

    // Unit Test Data variable
    int nUnitTestNum;
    int nTestArrSize;

    // Unit Test correct data
    std::vector<std::vector<int>> anCorrect = {
        {0, 1, 2, 3, 5},
        {-1000000, -9999, 0, 9999, 1000000},
        {1, 2, 3, 4, 5},
        {0, 0, 0, 0, 0},
        {-14, -14, -14, -14, -14},
        {1, 2, 3, 4, 5},
    };
};

void SortTestFixture::unitTest()
{
    int i = 0, j = 0;

    for(i = 0; i < nUnitTestNum; ++i)
    {
        for(j = 0; j < nTestArrSize; ++j)
        {
            EXPECT_EQ(anTest[i][j], anCorrect[i][j])
                << "Unit Test:" << i << " failed, at data:" << j;
        }
    }
}

TEST_F(SortTestFixture, quickSortIterativeTest)
{
    int i = 0;

    for(i = 0; i < getUnitTestNum(); ++i)
    {
        quickSortIterative(anTest[i].data(), getTestArrSize());
    }

    unitTest();
}

TEST_F(SortTestFixture, quickSortRecursiveTest)
{
    int i = 0;

    for(i = 0; i < getUnitTestNum(); ++i)
    {
        quickSortRecursive(anTest[i].data(), getTestArrSize());
    }

    unitTest();
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Start Running sortGUnitTesting" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}