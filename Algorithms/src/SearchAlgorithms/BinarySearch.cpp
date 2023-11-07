#include <vector>

// Binary Search
// Time complexity: O(log2n)
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
} // namespace BinarySearch

class BinarySearchTest : public testing::Test
{
protected:
    const std::vector<int> mInNums = {-1, 0, 3, 5, 9, 12};
};

TEST_F(BinarySearchTest, ItemExists)
{
    const int InItem   = 9;
    const int OutIndex = 4;
    EXPECT_EQ(BinarySearch::Search(mInNums, InItem), OutIndex);
}

TEST_F(BinarySearchTest, ItemDoesNotExist)
{
    const int InItem   = 2;
    const int OutIndex = -1;
    EXPECT_EQ(BinarySearch::Search(mInNums, InItem), OutIndex);
}
