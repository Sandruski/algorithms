#include "SearchAlgorithms/BinarySearch.h"

#include <vector>

namespace SearchAlgorithms
{
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
} // namespace SearchAlgorithms
