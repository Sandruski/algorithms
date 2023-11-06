#include "Helpers/PathfindingGraph.h"
#include "Helpers/PathfindingList.h"

#include <algorithm>

using namespace Pathfinding;

/**
 * AStar
 * Pathfinding algorithm: solves the mathematical problem of the shortest path
 * Uses a pathfinding graph
 * Finds the shortest path (lowest total cost) to the goal node (point-to-point pathfinding) from the start node
 * Useful for pathfinding and decision-making
 * Time complexity: O(lm) (l = number of nodes whose total estimated total cost is less than that of the goal node, m = average number of outgoing
 * connections from each node)
 * Space complexity: O(lm)
 */
namespace AStar
{
/**
 * Non-negative value
 * E.g. Manhattan Distance
 */
class Heuristic
{
public:
    explicit Heuristic(const Node inGoalNode) : mGoalNode(inGoalNode)
    {
    }

    // Returns an estimated cost to reach the goal node from the given node
    float Estimate(MAYBE_UNUSED const Node inNode)
    {
        return 1.f;
    }

private:
    Node mGoalNode = 0;
};

const NodeRecord* FindLowestEstimatedTotalCostNodeRecord(const PathfindingList& inPathfindingList)
{
    const NodeRecord* LowestEstimatedTotalCostNodeRecord = nullptr;

    float LowestEstimatedTotalCost = std::numeric_limits<float>::max();

    for (const NodeRecord& NodeRecord : inPathfindingList)
    {
        const float EstimatedTotalCost = NodeRecord.GetEstimatedTotalCost();
        if (EstimatedTotalCost < LowestEstimatedTotalCost)
        {
            LowestEstimatedTotalCostNodeRecord = &NodeRecord;

            LowestEstimatedTotalCost = EstimatedTotalCost;
        }
    }

    return LowestEstimatedTotalCostNodeRecord;
}

Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode)
{
    PathfindingList OpenList = {NodeRecord(inStartNode)};
    PathfindingList ClosedList;

    Heuristic Heuristic(inGoalNode);

    const NodeRecord* CurrentNodeRecord = nullptr;

    while (!OpenList.empty())
    {
        // Find the node with the lowest estimated total cost in the open list
        CurrentNodeRecord = FindLowestEstimatedTotalCostNodeRecord(OpenList);

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
                const Node  NeighborNode         = Neighbor.GetToNode();
                const float NeighborCost         = Neighbor.GetCost();
                const float NewNeighborCostSoFar = CurrentCostSoFar + NeighborCost;
                float       NeighborHeuristic    = 0.f;

                if (NodeRecord* NeighborNodeRecord = FindNodeRecord(ClosedList, NeighborNode))
                {
                    // Skip this node if it is closed and the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NewNeighborCostSoFar)
                    {
                        continue;
                    }

                    // Update its heuristic by using the existing record
                    NeighborHeuristic = NeighborCost - NeighborCostSoFar;

                    // Remove it from the closed list
                    ClosedList.erase(std::remove(ClosedList.begin(), ClosedList.end(), *NeighborNodeRecord));
                }

                NodeRecord* NeighborNodeRecord = FindNodeRecord(OpenList, NeighborNode);
                if (NeighborNodeRecord)
                {
                    // Skip this node if it is open but the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NewNeighborCostSoFar)
                    {
                        continue;
                    }

                    // Update its heuristic by using the existing record
                    NeighborHeuristic = NeighborCost - NeighborCostSoFar;
                }
                else
                {
                    // Open this node if it is unvisited
                    NeighborNodeRecord = &OpenList.emplace_back(NodeRecord(NeighborNode));

                    // Update its heuristic by calling the heuristic function
                    NeighborHeuristic = Heuristic.Estimate(NeighborNode);
                }

                // Update the cost and the connections of this node
                const float NeighborEstimatedTotalCost = NeighborCost + NeighborHeuristic;
                NeighborNodeRecord->Update(NewNeighborCostSoFar, NeighborEstimatedTotalCost, &Neighbor);
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
} // namespace AStar

class AStarTest : public testing::Test
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

TEST_F(AStarTest, PathExists)
{
    const Node InStartNode = 0;
    const Node InGoalNode  = 3;
    const Path OutPath     = {m0To2Connection, m2To1Connection, m1To3Connection};
    EXPECT_EQ(AStar::Search(mInGraph, InStartNode, InGoalNode), OutPath);
}

TEST_F(AStarTest, PathDoesNotExist)
{
    const Node InStartNode = 3;
    const Node InGoalNode  = 0;
    const Path OutPath     = {};
    EXPECT_EQ(AStar::Search(mInGraph, InStartNode, InGoalNode), OutPath);
}

/**
 * AIFG
 * https://www.redblobgames.com/pathfinding/a-star/introduction.html
 * https://www.redblobgames.com/pathfinding/a-star/implementation.html
 */
