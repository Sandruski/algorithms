#include <vector>

/**
 * Quick Sort
 * Time complexity: O(nlogn)
 * Uses divide and conquer (D&Q)
 * Uses recursion
 */
namespace QuickSort
{
std::vector<int> Sort(const std::vector<int>& inNums)
{
    // Base case
    const std::size_t NumsSize = inNums.size();
    if (NumsSize <= 1)
    {
        return inNums;
    }

    // Recursive case
    const std::size_t PivotIndex = NumsSize / 2;
    const int         Pivot      = inNums[PivotIndex];
    std::vector<int>  LesserNums;
    std::vector<int>  GreaterNums;
    for (std::size_t i = 0; i < NumsSize; ++i)
    {
        if (i == PivotIndex)
        {
            continue;
        }

        const int Num = inNums[i];
        if (Num <= Pivot)
        {
            LesserNums.emplace_back(Num);
        }
        else
        {
            GreaterNums.emplace_back(Num);
        }
    }

    std::vector<int>       SortedLesserNums  = Sort(LesserNums);
    const std::vector<int> SortedGreaterNums = Sort(GreaterNums);
    SortedLesserNums.emplace_back(Pivot);
    SortedLesserNums.insert(SortedLesserNums.end(), SortedGreaterNums.begin(), SortedGreaterNums.end());
    return SortedLesserNums;
}
} // namespace QuickSort

TEST(QuickSortTest, VectorIsSorted)
{
    const std::vector<int> InNums = {5, 1, 1, 2, 0, 0};
    const std::vector<int> OuNums = {0, 0, 1, 1, 2, 5};
    EXPECT_EQ(QuickSort::Sort(InNums), OuNums);
}
