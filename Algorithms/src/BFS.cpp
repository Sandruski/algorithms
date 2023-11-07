#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Breadth First Search (BFS)
 * Simplest graph search algorithm
 * Greedy algorithm
 * Explores equally in all directions
 * Useful for flow field pathfinding and map analysis
 * Time complexity: O(V+E)
 * Uses an unweighted graph
 * Uses a queue
 */
namespace BFS
{
using Graph = std::unordered_map<std::string, std::vector<std::string>>;
using Path  = std::vector<std::string>;

std::vector<std::string> Search(const Graph& inGraph, const std::string& inOrigin, const std::string& inDestination)
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

class BFSTest : public testing::Test
{
protected:
    void SetUp() override
    {
        mInGraph.reserve(4);
        mInGraph["you"]    = {"alice", "bob", "claire"};
        mInGraph["bob"]    = {"anuj", "peggy"};
        mInGraph["alice"]  = {"peggy"};
        mInGraph["claire"] = {"thom", "jonny"};
    }

    BFS::Graph mInGraph;
};

TEST_F(BFSTest, PathExists)
{
    const std::string InOrigin      = "you";
    const std::string InDestination = "thom";
    const BFS::Path   OutPath       = {"you", "claire", "thom"};
    EXPECT_EQ(BFS::Search(mInGraph, InOrigin, InDestination), OutPath);
}

TEST_F(BFSTest, PathDoesNotExist)
{
    const std::string InOrigin      = "bob";
    const std::string InDestination = "thom";
    const BFS::Path   OutPath       = {};
    EXPECT_EQ(BFS::Search(mInGraph, InOrigin, InDestination), OutPath);
}
