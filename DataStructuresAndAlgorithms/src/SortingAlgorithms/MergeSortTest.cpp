#include "SortingAlgorithms/MergeSort.h"
#include "SortingAlgorithms/Helpers/SortingAlgorithmTestBase.h"

namespace SortingAlgorithms
{
namespace MergeSort
{
class MergeSortTest : public SortingAlgorithmTestBase
{
};

TEST_F(MergeSortTest, VectorIsSorted)
{
    std::vector<int>       InNums  = GetNums();
    const std::vector<int> OutNums = {0, 0, 1, 1, 2, 5};
    MergeSort::Sort(InNums);
    EXPECT_EQ(InNums, OutNums);
}
} // namespace MergeSort
} // namespace SortingAlgorithms
