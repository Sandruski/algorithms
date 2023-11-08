#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace GraphSearchAlgorithms;

/**
 * Breadth-First Search (BFS)
 * Time complexity: O(V+E)
 * Space complexity: O(V+E)
 */

namespace BFS
{
Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode)
{
    std::queue<NodeRecord> NodesToProcess;
    NodesToProcess.emplace(NodeRecord(inStartNode));

    // TODO salvarez Rename this list to something that is not pathfinding. Should it be an unordered set instead?
    PathfindingList ProcessedNodes;

    const NodeRecord* CurrentNodeRecord = nullptr;

    while (!NodesToProcess.empty())
    {
        CurrentNodeRecord = &NodesToProcess.front();
        NodesToProcess.pop();

        const Node CurrentNode = CurrentNodeRecord->GetNode();

        // If it is the goal node, terminate
        if (CurrentNode == inGoalNode)
        {
            break;
        }

        const Neighbors* Neighbors = inGraph.FindNeighbors(CurrentNode);
        if (!Neighbors)
        {
            continue;
        }

        for (const Connection& Neighbor : *Neighbors)
        {
            // Skip if this node is a wall

            const Node NeighborNode = Neighbor.GetToNode();

            // Skip this node if it is processed
            if (FindNodeRecord(ProcessedNodes, NeighborNode))
            {
                continue;
            }

            NodesToProcess.emplace(NodeRecord(NeighborNode, &Neighbor));
        }

        ProcessedNodes.emplace_back(*CurrentNodeRecord);
    }

    return ReconstructPath(*CurrentNodeRecord, ProcessedNodes, inStartNode, inGoalNode);
}
} // namespace BFS

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
