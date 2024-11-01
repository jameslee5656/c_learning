#include <vector>
#include <gtest/gtest.h>

#include "helper.c"
#include "qsort.c"

class SortUnitTestSuite : public testing::Test
{
public:
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

void SortUnitTestSuite::unitTest()
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

TEST_F(SortUnitTestSuite, quickSortIterativeTest)
{
    int i = 0, j = 0;

    for(i = 0; i < getUnitTestNum(); ++i)
    {
        quickSortIterative(anTest[i].data(), getTestArrSize());
    }

    unitTest();
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Start Running sortGUnitTesting" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}