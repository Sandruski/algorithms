#include <vector>

/**
 * Quick Sort
 * Time complexity: O(nlogn). Depending on the pivot it can be O(n^2)
 * Uses divide and conquer (D&Q)
 * Uses recursion
 */
namespace QuickSort
{
int Partition(std::vector<int>& inNums, const int inLowIndex, const int inHighIndex)
{
    // Pivot is last element of the array
    const int Pivot = inNums[inHighIndex];

    int i = inLowIndex - 1;
    for (int j = inLowIndex; j <= inHighIndex; ++j)
    {
        const int Num = inNums[j];
        if (Num <= Pivot)
        {
            ++i;

            // Swap
            inNums[j] = inNums[i];
            inNums[i] = Num;
        }
    }

    return i;
}

void Sort(std::vector<int>& inNums, const int inLowIndex, const int inHighIndex)
{
    // Base case
    if (inLowIndex >= inHighIndex)
    {
        return;
    }

    // Recursive case
    const int i = Partition(inNums, inLowIndex, inHighIndex);
    Sort(inNums, inLowIndex, i - 1);
    Sort(inNums, i + 1, inHighIndex);
}
} // namespace QuickSort

TEST(QuickSortTest, VectorIsSorted)
{
    std::vector<int>       InNums      = {5, 1, 1, 2, 0, 0};
    const int              InLowIndex  = 0;
    const int              InHighIndex = static_cast<int>(InNums.size()) - 1;
    const std::vector<int> OutNums     = {0, 0, 1, 1, 2, 5};
    QuickSort::Sort(InNums, InLowIndex, InHighIndex);
    EXPECT_EQ(InNums, OutNums);
}
