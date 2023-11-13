#pragma once

#include "GraphSearchAlgorithms/Helpers/GraphFwd.h"

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
