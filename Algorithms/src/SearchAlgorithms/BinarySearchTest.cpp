#include "SearchAlgorithms/BinarySearch.h"
#include "SearchAlgorithms/Helpers/SearchAlgorithmTestBase.h"

namespace SearchAlgorithms
{
namespace BinarySearch
{
class BinarySearchTest : public SearchAlgorithmTestBase
{
};

TEST_F(BinarySearchTest, ItemExists)
{
    const std::vector<int>& InNums   = GetNums();
    const int               InItem   = 9;
    const int               OutIndex = 4;
    EXPECT_EQ(BinarySearch::Search(InNums, InItem), OutIndex);
}

TEST_F(BinarySearchTest, ItemDoesNotExist)
{
    const std::vector<int>& InNums   = GetNums();
    const int               InItem   = 2;
    const int               OutIndex = -1;
    EXPECT_EQ(BinarySearch::Search(InNums, InItem), OutIndex);
}
} // namespace BinarySearch
} // namespace SearchAlgorithms
