#include "GraphSearchAlgorithms/BFS.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"

namespace GraphSearchAlgorithms
{
namespace BFS
{
class BFSTest : public GraphSearchAlgorithmTestBase
{
};

TEST_F(BFSTest, PathExists)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 0;
    const Node   InGoalNode  = 3;
    const Path   OutPath     = {Get0To1Connection(), Get1To3Connection()};
    EXPECT_EQ(BFS::Search(InGraph, InStartNode, InGoalNode), OutPath);
}

TEST_F(BFSTest, PathDoesNotExist)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 3;
    const Node   InGoalNode  = 0;
    const Path   OutPath     = {};
    EXPECT_EQ(BFS::Search(InGraph, InStartNode, InGoalNode), OutPath);
}
} // namespace BFS
} // namespace GraphSearchAlgorithms
