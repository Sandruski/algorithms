#include <vector>

/**
 * Merge Sort
 * Time complexity: O(nlogn)
 * Uses divide and conquer (D&Q)
 * Uses recursion
 */
namespace MergeSort
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
    const std::size_t MidIndex = NumsSize / 2;
    std::vector<int>  LeftNums;
    LeftNums.reserve(MidIndex);
    std::vector<int> RightNums;
    RightNums.reserve(MidIndex);

    for (std::size_t i = 0; i < MidIndex; ++i)
    {
        const int Num = inNums[i];
        LeftNums.emplace_back(Num);
    }

    for (std::size_t i = MidIndex; i < NumsSize; ++i)
    {
        const int Num = inNums[i];
        RightNums.emplace_back(Num);
    }

    std::vector<int> SortedNums;
    SortedNums.reserve(NumsSize);
    const std::vector<int> SortedLeftNums  = Sort(LeftNums);
    const std::size_t      LeftNumsSize    = SortedLeftNums.size();
    std::size_t            LeftReadIndex   = 0;
    const std::vector<int> SortedRightNums = Sort(RightNums);
    const std::size_t      RightNumsSize   = SortedRightNums.size();
    std::size_t            RightReadIndex  = 0;

    while (LeftReadIndex < LeftNumsSize && RightReadIndex < RightNumsSize)
    {
        const int SortedLeftNum  = SortedLeftNums[LeftReadIndex];
        const int SortedRightNum = SortedRightNums[RightReadIndex];
        if (SortedLeftNum < SortedRightNum)
        {
            SortedNums.emplace_back(SortedLeftNum);
            ++LeftReadIndex;
        }
        else
        {
            SortedNums.emplace_back(SortedRightNum);
            ++RightReadIndex;
        }
    }

    while (LeftReadIndex < LeftNumsSize)
    {
        const int sortedLeftNum = SortedLeftNums[LeftReadIndex];
        SortedNums.emplace_back(sortedLeftNum);
        ++LeftReadIndex;
    }

    while (RightReadIndex < RightNumsSize)
    {
        const int sortedRightNum = SortedRightNums[RightReadIndex];
        SortedNums.emplace_back(sortedRightNum);
        ++RightReadIndex;
    }

    return SortedNums;
}
} // namespace MergeSort

TEST(MergeSortTest, VectorIsSorted)
{
    const std::vector<int> InNums  = {5, 1, 1, 2, 0, 0};
    const std::vector<int> OutNums = {0, 0, 1, 1, 2, 5};
    EXPECT_EQ(MergeSort::Sort(InNums), OutNums);
}
