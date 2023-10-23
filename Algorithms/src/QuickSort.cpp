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
    if (NumsSize < 2)
    {
        return inNums;
    }

    // Recursive case
    const std::size_t PivotIndex = NumsSize / 2;
    const int         Pivot      = inNums[PivotIndex];
    std::vector<int>  Lesser;
    std::vector<int>  Greater;
    for (std::size_t i = 0; i < NumsSize; ++i)
    {
        if (i == PivotIndex)
        {
            continue;
        }

        const int Num = inNums[i];
        if (Num <= Pivot)
        {
            Lesser.emplace_back(Num);
        }
        else // Num > Pivot
        {
            Greater.emplace_back(Num);
        }
    }

    std::vector<int> SortedLesser  = Sort(Lesser);
    std::vector<int> SortedGreater = Sort(Greater);
    SortedLesser.emplace_back(Pivot);
    SortedLesser.insert(SortedLesser.end(), SortedGreater.begin(), SortedGreater.end());
    return SortedLesser;
}
} // namespace QuickSort

TEST(QuickSortTest, VectorIsSorted)
{
    const std::vector<int> InNums = {5, 1, 1, 2, 0, 0};
    const std::vector<int> OuNums = {0, 0, 1, 1, 2, 5};
    EXPECT_EQ(QuickSort::Sort(InNums), OuNums);
}
