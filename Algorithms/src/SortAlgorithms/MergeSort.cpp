#include <vector>

/**
 * Merge Sort
 * Time complexity: O(nlogn). Always the same
 * Uses divide and conquer (D&Q)
 * Uses recursion
 */
namespace MergeSort
{
void Merge(std::vector<int>& inNums, const std::vector<int>& inLeftNums, const std::vector<int>& inRightNums)
{
    std::size_t       WriteIndex     = 0;
    const std::size_t LeftNumsSize   = inLeftNums.size();
    std::size_t       LeftReadIndex  = 0;
    const std::size_t RightNumsSize  = inRightNums.size();
    std::size_t       RightReadIndex = 0;

    while (LeftReadIndex < LeftNumsSize && RightReadIndex < RightNumsSize)
    {
        const int LeftNum  = inLeftNums[LeftReadIndex];
        const int RightNum = inRightNums[RightReadIndex];
        if (LeftNum < RightNum)
        {
            inNums[WriteIndex] = LeftNum;
            ++LeftReadIndex;
        }
        else
        {
            inNums[WriteIndex] = RightNum;
            ++RightReadIndex;
        }

        ++WriteIndex;
    }

    while (LeftReadIndex < LeftNumsSize)
    {
        const int LeftNum  = inLeftNums[LeftReadIndex];
        inNums[WriteIndex] = LeftNum;
        ++LeftReadIndex;
        ++WriteIndex;
    }

    while (RightReadIndex < RightNumsSize)
    {
        const int RightNum = inRightNums[RightReadIndex];
        inNums[WriteIndex] = RightNum;
        ++RightReadIndex;
        ++WriteIndex;
    }
}

void Sort(std::vector<int>& inNums)
{
    // Base case
    const std::size_t NumsSize = inNums.size();
    if (NumsSize <= 1)
    {
        return;
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

    Sort(LeftNums);
    Sort(RightNums);
    Merge(inNums, LeftNums, RightNums);
}
} // namespace MergeSort

TEST(MergeSortTest, VectorIsSorted)
{
    std::vector<int>       InNums  = {5, 1, 1, 2, 0, 0};
    const std::vector<int> OutNums = {0, 0, 1, 1, 2, 5};
    MergeSort::Sort(InNums);
    EXPECT_EQ(InNums, OutNums);
}
