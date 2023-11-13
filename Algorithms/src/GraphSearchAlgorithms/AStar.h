#pragma once

#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <algorithm>

namespace GraphSearchAlgorithms
{
/**
 * AStar
 * Time/space complexity: O(lm) (l = number of nodes whose total estimated total cost is less than that of the goal node, m = average number of
 * outgoing connections from each node)
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
    explicit Heuristic(const Node inGoalNode);

    // Returns an estimated cost to reach the goal node from the given node
    float Estimate(MAYBE_UNUSED const Node inNode) const;

private:
    Node mGoalNode = 0;
};

Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode, const Heuristic& inHeuristic);

inline float Heuristic::Estimate(MAYBE_UNUSED const Node inNode) const
{
    return 1.f;
}
} // namespace AStar
} // namespace GraphSearchAlgorithms
