#include "SortingAlgorithms/BubbleSort.h"

#include <vector>

namespace SortingAlgorithms
{
namespace BubbleSort
{
std::vector<int> Sort(std::vector<int> inNums)
{
    std::vector<int> SortedNums = inNums;
    const int        NumsSize   = static_cast<int>(inNums.size());

    bool HasSwapped = false;
    for (int i = 0; i < NumsSize - 1; ++i)
    {
        HasSwapped = false;

        for (int j = 0; j < NumsSize - 1 - i; ++j)
        {
            const int Left  = SortedNums[j];
            const int Right = SortedNums[j + 1];
            if (Left > Right)
            {
                SortedNums[j]     = Right;
                SortedNums[j + 1] = Left;
                HasSwapped        = true;
            }
        }

        if (!HasSwapped)
        {
            break;
        }
    }

    return SortedNums;
}
} // namespace BubbleSort
} // namespace SortingAlgorithms
