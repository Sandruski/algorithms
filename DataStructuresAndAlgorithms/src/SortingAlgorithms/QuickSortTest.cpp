#include "SortingAlgorithms/QuickSort.h"
#include "SortingAlgorithms/Helpers/SortingAlgorithmTestBase.h"

namespace SortingAlgorithms
{
namespace QuickSort
{
class QuickSortTest : public SortingAlgorithmTestBase
{
};

TEST_F(QuickSortTest, VectorIsSorted)
{
    std::vector<int>       InNums      = GetNums();
    const int              InLowIndex  = 0;
    const int              InHighIndex = static_cast<int>(InNums.size()) - 1;
    const std::vector<int> OutNums     = {0, 0, 1, 1, 2, 5};
    QuickSort::Sort(InNums, InLowIndex, InHighIndex);
    EXPECT_EQ(InNums, OutNums);
}
} // namespace QuickSort
} // namespace SortingAlgorithms
