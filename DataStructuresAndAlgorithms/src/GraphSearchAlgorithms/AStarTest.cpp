#include "GraphSearchAlgorithms/AStar.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"

namespace GraphSearchAlgorithms
{
namespace AStar
{
class AStarTest : public GraphSearchAlgorithmTestBase
{
};

TEST_F(AStarTest, PathExists)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 0;
    const Node   InGoalNode  = 3;
    Heuristic    InHeuristic = Heuristic(InGoalNode);
    const Path   OutPath     = {Get0To2Connection(), Get2To1Connection(), Get1To3Connection()};
    EXPECT_EQ(AStar::Search(InGraph, InStartNode, InGoalNode, InHeuristic), OutPath);
}

TEST_F(AStarTest, PathDoesNotExist)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 3;
    const Node   InGoalNode  = 0;
    Heuristic    InHeuristic = Heuristic(InGoalNode);
    const Path   OutPath     = {};
    EXPECT_EQ(AStar::Search(InGraph, InStartNode, InGoalNode, InHeuristic), OutPath);
}
} // namespace AStar
} // namespace GraphSearchAlgorithms
