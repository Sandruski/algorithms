#include "SortingAlgorithms/QuickSort.h"

#include <vector>

namespace SortingAlgorithms
{
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
} // namespace SortingAlgorithms
