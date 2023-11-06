#include "Helpers/PathfindingGraph.h"
#include "Helpers/PathfindingList.h"

#include <algorithm>

using namespace Pathfinding;

/**
 * Dijkstra
 * Pathfinding algorithm: solves the mathematical problem of the shortest path
 * Uses a pathfinding graph
 * Finds the shortest path (lowest total cost) to the goal node (point-to-point pathfinding) from the start node
 * Useful for pathfinding and decision-making
 * Time complexity:
 * Space complexity:
 */
namespace AStar
{
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

float CalculateHeuristic(const Node inNode)
{
}

Path Search([[maybe_unused]] const Graph& inGraph, [[maybe_unused]] const Node inStartNode, [[maybe_unused]] const Node inGoalNode)
{
    PathfindingList OpenList = {NodeRecord(inStartNode)};
    PathfindingList ClosedList;

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
                const float NeighborNewCostSoFar = CurrentCostSoFar + NeighborCost;
                float       NeighborHeuristic    = 0.f;

                if (NodeRecord* NeighborNodeRecord = FindNodeRecord(ClosedList, NeighborNode))
                {
                    // Skip this node if it is closed and the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NeighborNewCostSoFar)
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
                    if (NeighborCostSoFar <= NeighborNewCostSoFar)
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
                    NeighborHeuristic = CalculateHeuristic(NeighborNode);
                }

                // Update the cost and the connections of this node
                const float NeighborEstimatedTotalCost = NeighborCost + NeighborHeuristic;
                NeighborNodeRecord->Update(NeighborNewCostSoFar, NeighborEstimatedTotalCost, &Neighbor);
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

TEST(AStarTest, PathExists)
{
}

TEST(AStarTest, PathDoesNotExist)
{
}
