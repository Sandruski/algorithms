#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <algorithm>

using namespace GraphSearchAlgorithms;

/**
 * AStar
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
                // Skip if this node is a wall

                const Node  NeighborNode         = Neighbor.GetToNode();
                const float NeighborCost         = Neighbor.GetCost();
                const float NewNeighborCostSoFar = CurrentCostSoFar + NeighborCost;
                float       NeighborHeuristic    = 0.f;

                if (const NodeRecord* NeighborNodeRecord = FindNodeRecord(ClosedList, NeighborNode))
                {
                    // Skip this node if it is closed and the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NewNeighborCostSoFar)
                    {
                        continue;
                    }

                    // Update its heuristic by using the existing record
                    const float NeighborEstimatedTotalCost = NeighborNodeRecord->GetEstimatedTotalCost();
                    NeighborHeuristic                      = NeighborEstimatedTotalCost - NeighborCostSoFar;

                    // Remove it from the closed list
                    ClosedList.erase(std::remove(ClosedList.begin(), ClosedList.end(), *NeighborNodeRecord));
                }

                NodeRecord* NeighborNodeRecord = FindNodeRecordMutable(OpenList, NeighborNode);
                if (NeighborNodeRecord)
                {
                    // Skip this node if it is open but the new route is worse
                    const float NeighborCostSoFar = NeighborNodeRecord->GetCostSoFar();
                    if (NeighborCostSoFar <= NewNeighborCostSoFar)
                    {
                        continue;
                    }

                    // Update its heuristic by using the existing record
                    const float NeighborEstimatedTotalCost = NeighborNodeRecord->GetEstimatedTotalCost();
                    NeighborHeuristic                      = NeighborEstimatedTotalCost - NeighborCostSoFar;
                }
                else
                {
                    // Open this node if it is unvisited
                    NeighborNodeRecord = &OpenList.emplace_back(NodeRecord(NeighborNode));

                    // Update its heuristic by calling the heuristic function
                    NeighborHeuristic = Heuristic.Estimate(NeighborNode);
                }

                // Update the cost and the connections of this node
                const float NeighborEstimatedTotalCost = NewNeighborCostSoFar + NeighborHeuristic;
                NeighborNodeRecord->Update(NewNeighborCostSoFar, NeighborEstimatedTotalCost, &Neighbor);
            }
        }

        // Move it from the open list to the closed list
        ClosedList.emplace_back(*CurrentNodeRecord);
        OpenList.erase(std::remove(OpenList.begin(), OpenList.end(), *CurrentNodeRecord));
    }

    return ReconstructPath(*CurrentNodeRecord, ClosedList, inStartNode, inGoalNode);
}

class AStarTest : public GraphSearchAlgorithmTestBase
{
};

TEST_F(AStarTest, PathExists)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 0;
    const Node   InGoalNode  = 3;
    const Path   OutPath     = {Get0To2Connection(), Get2To1Connection(), Get1To3Connection()};
    EXPECT_EQ(AStar::Search(InGraph, InStartNode, InGoalNode), OutPath);
}

TEST_F(AStarTest, PathDoesNotExist)
{
    const Graph& InGraph     = GetGraph();
    const Node   InStartNode = 3;
    const Node   InGoalNode  = 0;
    const Path   OutPath     = {};
    EXPECT_EQ(AStar::Search(InGraph, InStartNode, InGoalNode), OutPath);
}
} // namespace AStar
