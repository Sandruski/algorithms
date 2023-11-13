#include "GraphSearchAlgorithms/Dijkstra.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"

namespace GraphSearchAlgorithms
{
namespace Dijkstra
{
class DijkstraTest : public GraphSearchAlgorithmTestBase
{
};

TEST_F(DijkstraTest, PathExists)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 0;
    const Node   InGoalNode  = 3;
    const Path   OutPath     = {Get0To2Connection(), Get2To1Connection(), Get1To3Connection()};
    EXPECT_EQ(Dijkstra::Search(InGraph, InStartNode, InGoalNode), OutPath);
}

TEST_F(DijkstraTest, PathDoesNotExist)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 3;
    const Node   InGoalNode  = 0;
    const Path   OutPath     = {};
    EXPECT_EQ(Dijkstra::Search(InGraph, InStartNode, InGoalNode), OutPath);
}
} // namespace Dijkstra
} // namespace GraphSearchAlgorithms
