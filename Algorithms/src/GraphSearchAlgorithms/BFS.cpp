#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"

#include <algorithm>

/**
 * Breadth-First Search (BFS)
 * Time complexity: O(V+E)
 * Space complexity: O(V+E)
 */
/*
namespace BFS
{
Path Search(const Graph& inGraph, const std::string& inOrigin, const std::string& inDestination)
{
    const auto OriginNeighborsIt = inGraph.find(inOrigin);
    if (OriginNeighborsIt == inGraph.end())
    {
        return {};
    }

    std::queue<std::string>                      NodesToProcess;
    std::unordered_map<std::string, std::string> NodeParents;

    const std::vector<std::string>& OriginNeighbors = OriginNeighborsIt->second;
    for (const std::string& OriginNeighbor : OriginNeighbors)
    {
        NodesToProcess.push(OriginNeighbor);
        NodeParents[OriginNeighbor] = inOrigin;
    }

    std::unordered_set<std::string> ProcessedNodes;

    while (!NodesToProcess.empty())
    {
        const std::string NodeToProcess = NodesToProcess.front();
        NodesToProcess.pop();

        if (ProcessedNodes.contains(NodeToProcess))
        {
            continue;
        }

        if (NodeToProcess == inDestination)
        {
            break;
        }

        const auto NeighborsIt = inGraph.find(NodeToProcess);
        if (NeighborsIt == inGraph.end())
        {
            continue;
        }

        const std::vector<std::string>& Neighbors = NeighborsIt->second;
        for (const std::string& Neighbor : Neighbors)
        {
            NodesToProcess.push(Neighbor);
            NodeParents[Neighbor] = NodeToProcess;
        }

        ProcessedNodes.emplace(NodeToProcess);
    }

    // Build path
    Path Path;
    for (auto NodeParentIt = NodeParents.find(inDestination); NodeParentIt != NodeParents.end();
         NodeParentIt      = NodeParents.find(NodeParentIt->second))
    {
        const std::string& Node = NodeParentIt->first;
        Path.emplace_back(Node);
    }

    if (!Path.empty())
    {
        Path.emplace_back(inOrigin);
        std::reverse(Path.begin(), Path.end());
    }

    return Path;
}
} // namespace BFS

class BFSTest : public GraphSearchAlgorithmTest
{
};

TEST_F(GraphSearchAlgorithmTest, PathExists)
{
    const Node InStartNode = 0;
    const Node InGoalNode  = 3;
    const Path OutPath     = {m0To2Connection, m2To1Connection, m1To3Connection};
    EXPECT_EQ(BFS::Search(mInGraph, InStartNode, InGoalNode), OutPath);
}

TEST_F(GraphSearchAlgorithmTest, PathDoesNotExist)
{
    const Node InStartNode = 3;
    const Node InGoalNode  = 0;
    const Path OutPath     = {};
    EXPECT_EQ(BFS::Search(mInGraph, InStartNode, InGoalNode), OutPath);
}
*/