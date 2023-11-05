#include "Helpers/PathfindingGraph.h"
#include "Helpers/PathfindingHelpers.h"

#include <algorithm>

using namespace Pathfinding;

/**
 * Dijkstra
 * Pathfinding algorithm: solves the mathematical problem of the shortest path
 * Uses a pathfinding graph
 * Finds the shortest paths to all nodes from a node
 * Returns the path from the start node to the goal node
 * Useful for tactical analysis
 * Time complexity: O(mn) (m = node, n = connection)
 * Space complexity: O(mn)
 */
namespace Dijkstra
{
const NodeRecord* FindLowestCostSoFarNodeRecord(const PathfindingList& inPathfindingList)
{
    const NodeRecord* LowestCostSoFarNodeRecord = nullptr;

    float LowestCostSoFar = std::numeric_limits<float>::max();

    for (const NodeRecord& NodeRecord : inPathfindingList)
    {
        const float CostSoFar = NodeRecord.GetCostSoFar();
        if (CostSoFar < LowestCostSoFar)
        {
            LowestCostSoFarNodeRecord = &NodeRecord;

            LowestCostSoFar = CostSoFar;
        }
    }

    return LowestCostSoFarNodeRecord;
};

NodeRecord* FindNodeRecord(PathfindingList& inPathfindingList, const Node inNode)
{
    for (NodeRecord& NodeRecord : inPathfindingList)
    {
        const Node Node = NodeRecord.GetNode();
        if (Node == inNode)
        {
            return &NodeRecord;
        }
    }

    return nullptr;
}

Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode)
{
    PathfindingList OpenList = {NodeRecord(inStartNode)};
    PathfindingList ClosedList;

    const NodeRecord* CurrentNodeRecord = nullptr;

    while (!OpenList.empty())
    {
        // Find the node with the lowest cost so far in the open list
        CurrentNodeRecord = FindLowestCostSoFarNodeRecord(OpenList);

        const Node CurrentNode = CurrentNodeRecord->GetNode();

        // If it is the goal node, terminate
        if (CurrentNode == inGoalNode)
        {
            break;
        }

        // Otherwise go through its neighbors
        if (const Neighbors* Neighbors = inGraph.FindNeighbors(CurrentNode))
        {
            const float CurrentCostSoFar = CurrentNodeRecord->GetCostSoFar();

            for (const Connection& Neighbor : *Neighbors)
            {
                const Node NeighborNode = Neighbor.GetToNode();

                // Skip this node if it is closed
                if (FindNodeRecord(ClosedList, NeighborNode))
                {
                    continue;
                }

                const float NeighborCost         = Neighbor.GetCost();
                const float NeighborNewCostSoFar = CurrentCostSoFar + NeighborCost;

                NodeRecord* NeighborNodeRecord = FindNodeRecord(OpenList, NeighborNode);
                if (NeighborNodeRecord)
                {
                    // Skip this node if it is open but the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NeighborNewCostSoFar)
                    {
                        continue;
                    }
                }
                else // Open this node if it is unvisited
                {
                    NeighborNodeRecord = &OpenList.emplace_back(NodeRecord(NeighborNode));
                }

                // Update the cost and the connections of this node
                NeighborNodeRecord->Update(NeighborNewCostSoFar, &Neighbor);
            }
        }

        // Move it from the open list to the closed list
        ClosedList.emplace_back(*CurrentNodeRecord);
        OpenList.erase(std::remove(OpenList.begin(), OpenList.end(), *CurrentNodeRecord));
    }

    // If the goal node is not found, terminate
    Node CurrentNode = CurrentNodeRecord->GetNode();
    if (CurrentNode != inGoalNode)
    {
        return {};
    }

    // Otherwise build its path
    Path Path;
    while (CurrentNode != inStartNode)
    {
        const Connection* Connection = CurrentNodeRecord->GetConnection();
        Path.emplace_back(*Connection);
        CurrentNode       = Connection->GetFromNode();
        CurrentNodeRecord = FindNodeRecord(ClosedList, CurrentNode);
    }

    std::reverse(Path.begin(), Path.end());

    return Path;
}
} // namespace Dijkstra

class DijkstraTest : public testing::Test
{
protected:
    void SetUp() override
    {
        mInGraph.AddConnection(m0To1Connection);
        mInGraph.AddConnection(m0To2Connection);
        mInGraph.AddConnection(m1To3Connection);
        mInGraph.AddConnection(m2To1Connection);
        mInGraph.AddConnection(m2To3Connection);
    }

    Graph      mInGraph;
    Connection m0To1Connection = Connection(0, 1, 6);
    Connection m0To2Connection = Connection(0, 2, 2);
    Connection m1To3Connection = Connection(1, 3, 1);
    Connection m2To1Connection = Connection(2, 1, 3);
    Connection m2To3Connection = Connection(2, 3, 5);
};

TEST_F(DijkstraTest, PathExists)
{
    const Node InStartNode = 0;
    const Node InGoalNode  = 3;
    const Path OutPath     = {m0To2Connection, m2To1Connection, m1To3Connection};
    EXPECT_EQ(Dijkstra::Search(mInGraph, InStartNode, InGoalNode), OutPath);
}

TEST_F(DijkstraTest, PathDoesNotExist)
{
    const Node InStartNode = 3;
    const Node InGoalNode  = 0;
    const Path OutPath     = {};
    EXPECT_EQ(Dijkstra::Search(mInGraph, InStartNode, InGoalNode), OutPath);
}
