#include "GraphSearchAlgorithms/Dijkstra.h"

#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <algorithm>

namespace GraphSearchAlgorithms
{
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
}

Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode)
{
    // Open list should be a priority queue
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
                // Skip if this node is a wall

                const Node NeighborNode = Neighbor.GetToNode();

                // Skip this node if it is closed
                if (FindNodeRecord(ClosedList, NeighborNode))
                {
                    continue;
                }

                const float NeighborCost         = Neighbor.GetCost();
                const float NeighborNewCostSoFar = CurrentCostSoFar + NeighborCost;

                NodeRecord* NeighborNodeRecord = FindNodeRecordMutable(OpenList, NeighborNode);
                if (NeighborNodeRecord)
                {
                    // Skip this node if it is open but the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NeighborNewCostSoFar)
                    {
                        continue;
                    }
                }
                else
                {
                    // Open this node if it is unvisited
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

    return ReconstructPath(*CurrentNodeRecord, ClosedList, inStartNode, inGoalNode);
}
} // namespace Dijkstra
} // namespace GraphSearchAlgorithms
