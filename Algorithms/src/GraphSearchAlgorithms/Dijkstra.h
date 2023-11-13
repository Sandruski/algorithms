#pragma once

#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <algorithm>

namespace GraphSearchAlgorithms
{
/**
 * Dijkstra
 * Time/space complexity: O(nm) (n = number of nodes whose total cost so far is less than that of the goal node, m = average number of outgoing
 * connections from each node)
 */
namespace Dijkstra
{
Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode);
} // namespace Dijkstra
} // namespace GraphSearchAlgorithms
