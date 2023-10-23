#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Dijkstra
 * Time complexity: O(V^2)
 * Uses a weighted, directed, acyclic graph
 * Positive weights
 */
namespace Dijkstra
{
using Graph = std::unordered_map<std::string, std::unordered_map<std::string, int>>;
using Path  = std::vector<std::string>;

std::vector<std::string> Search(const Graph& inGraph, const std::string& inOrigin, const std::string& inDestination)
{
    const auto OriginNeighborsIt = inGraph.find(inOrigin);
    if (OriginNeighborsIt == inGraph.end())
    {
        return {};
    }

    std::unordered_map<std::string, int>         NodeCosts;
    std::unordered_map<std::string, std::string> NodeParents;

    const std::unordered_map<std::string, int>& OriginNeighbors = OriginNeighborsIt->second;
    for (const std::pair<std::string, int>& OriginNeighbor : OriginNeighbors)
    {
        const std::string& Node = OriginNeighbor.first;
        const int          Cost = OriginNeighbor.second;
        NodeCosts[Node]         = Cost;
        NodeParents[Node]       = inOrigin;
    }

    std::unordered_set<std::string> ProcessedNodes;

    const auto FindLowestCostNodeLambda = [&]() -> std::pair<std::string, int> {
        std::pair<std::string, int> LowestCostNode;
        int&                        LowestCost = LowestCostNode.second;
        LowestCost                             = std::numeric_limits<int>::max();

        for (const std::pair<std::string, int>& NodeCost : NodeCosts)
        {
            const std::string& Node = NodeCost.first;
            if (ProcessedNodes.contains(Node))
            {
                continue;
            }

            const int Cost = NodeCost.second;
            if (Cost < LowestCost)
            {
                LowestCostNode = NodeCost;
            }
        }

        return LowestCostNode;
    };

    for (std::pair<std::string, int> NodeCostToProcess = FindLowestCostNodeLambda(); !NodeCostToProcess.first.empty();
         NodeCostToProcess                             = FindLowestCostNodeLambda())
    {
        const std::string& NodeToProcess = NodeCostToProcess.first;
        const auto         NeighborsIt   = inGraph.find(NodeToProcess);
        if (NeighborsIt != inGraph.end())
        {
            const int                                   NodeToProcessCostSoFar = NodeCostToProcess.second;
            const std::unordered_map<std::string, int>& Neighbors              = NeighborsIt->second;
            for (const std::pair<std::string, int>& Neighbor : Neighbors)
            {
                const int          NeighborCost         = Neighbor.second;
                const int          NewNeighborCostSoFar = NodeToProcessCostSoFar + NeighborCost;
                const std::string& NeighborNode         = Neighbor.first;

                const auto NeighborNodeCostIt = NodeCosts.find(NeighborNode);
                if (NeighborNodeCostIt == NodeCosts.end())
                {
                    NodeCosts[NeighborNode] = std::numeric_limits<int>::max();
                }

                int& NeighborCostSoFar = NodeCosts[NeighborNode];
                if (NewNeighborCostSoFar < NeighborCostSoFar)
                {
                    NeighborCostSoFar         = NewNeighborCostSoFar;
                    NodeParents[NeighborNode] = NodeToProcess;
                }
            }
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
} // namespace Dijkstra

class DijkstraTest : public testing::Test
{
protected:
    void SetUp() override
    {
        mInGraph.reserve(3);
        mInGraph["start"].reserve(2);
        mInGraph["start"]["a"] = 6;
        mInGraph["start"]["b"] = 2;
        mInGraph["a"].reserve(1);
        mInGraph["a"]["fin"] = 1;
        mInGraph["b"].reserve(2);
        mInGraph["b"]["a"]   = 3;
        mInGraph["b"]["fin"] = 5;
    }

    Dijkstra::Graph mInGraph;
};

TEST_F(DijkstraTest, PathExists)
{
    const std::string    InOrigin      = "start";
    const std::string    InDestination = "fin";
    const Dijkstra::Path OutPath       = {"start", "b", "a", "fin"};
    EXPECT_EQ(Dijkstra::Search(mInGraph, InOrigin, InDestination), OutPath);
}

TEST_F(DijkstraTest, PathDoesNotExist)
{
    const std::string    InOrigin      = "fin";
    const std::string    InDestination = "start";
    const Dijkstra::Path OutPath       = {};
    EXPECT_EQ(Dijkstra::Search(mInGraph, InOrigin, InDestination), OutPath);
}
