#include "SearchAlgorithms/Helpers/SearchAlgorithmTestBase.h"

#include <vector>

using namespace SearchAlgorithms;

/**
 * Binary Search
 * Time complexity: O(logn)
 */
namespace BinarySearch
{
int Search(const std::vector<int>& inNums, const int inItem)
{
    int Low  = 0;
    int High = static_cast<int>(inNums.size()) - 1;

    while (Low <= High)
    {
        const int Mid   = (Low + High) / 2;
        const int Guess = inNums[Mid];
        if (Guess == inItem)
        {
            return Mid;
        }
        else if (Guess > inItem)
        {
            High = Mid - 1;
        }
        else // Guess < inItem
        {
            Low = Mid + 1;
        }
    }

    return -1;
}

class BinarySearchTest : public SearchAlgorithmTestBase
{
};

TEST_F(BinarySearchTest, ItemExists)
{
    const std::vector<int>& InNums   = GetNums();
    const int               InItem   = 9;
    const int               OutIndex = 4;
    EXPECT_EQ(BinarySearch::Search(InNums, InItem), OutIndex);
}

TEST_F(BinarySearchTest, ItemDoesNotExist)
{
    const std::vector<int>& InNums   = GetNums();
    const int               InItem   = 2;
    const int               OutIndex = -1;
    EXPECT_EQ(BinarySearch::Search(InNums, InItem), OutIndex);
}
} // namespace BinarySearch
