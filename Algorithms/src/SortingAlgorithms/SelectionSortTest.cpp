#include "SortingAlgorithms/SelectionSort.h"
#include "SortingAlgorithms/Helpers/SortingAlgorithmTestBase.h"

namespace SortingAlgorithms
{
namespace SelectionSort
{
class SelectionSortTest : public SortingAlgorithmTestBase
{
};

TEST_F(SelectionSortTest, VectorIsSorted)
{
    const std::vector<int>& InNums  = GetNums();
    const std::vector<int>  OutNums = {0, 0, 1, 1, 2, 5};
    EXPECT_EQ(SelectionSort::Sort(InNums), OutNums);
}
} // namespace SelectionSort
} // namespace SortingAlgorithms
