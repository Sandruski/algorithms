#include <vector>

/**
 * Merge Sort
 * Time complexity: O(nlogn)
 * Uses divide and conquer (D&Q)
 * Uses recursion
 */
namespace MergeSort
{
std::vector<int> Sort(std::vector<int> inNums)
{
    std::vector<int> SortedNums = inNums;

    // TODO salvarez

    return SortedNums;
}
} // namespace MergeSort

TEST(MergeSortTest, VectorIsSorted)
{
    const std::vector<int> InNums  = {5, 1, 1, 2, 0, 0};
    const std::vector<int> OutNums = {0, 0, 1, 1, 2, 5};
    EXPECT_EQ(MergeSort::Sort(InNums), OutNums);
}
