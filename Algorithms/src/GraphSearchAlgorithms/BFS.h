#pragma once

#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace GraphSearchAlgorithms
{
/**
 * Breadth-First Search (BFS)
 * Time/space complexity: O(V+E)
 */
namespace BFS
{
Path Search(const Graph& inGraph, const Node inStartNode, const Node inGoalNode);
} // namespace BFS
} // namespace GraphSearchAlgorithms
