#include "SortingAlgorithms/BubbleSort.h"
#include "SortingAlgorithms/Helpers/SortingAlgorithmTestBase.h"

namespace SortingAlgorithms
{
namespace BubbleSort
{
class BubbleSortTest : public SortingAlgorithmTestBase
{
};

TEST_F(BubbleSortTest, VectorIsSorted)
{
    const std::vector<int>& InNums  = GetNums();
    const std::vector<int>  OutNums = {0, 0, 1, 1, 2, 5};
    EXPECT_EQ(BubbleSort::Sort(InNums), OutNums);
}
} // namespace BubbleSort
} // namespace SortingAlgorithms
