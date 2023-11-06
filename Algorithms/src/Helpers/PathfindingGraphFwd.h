#pragma once

#include <vector>

namespace Pathfinding
{
class Connection;
class Graph;

// Edge
using Node = unsigned int;

// List of outgoing connections from a node
using Neighbors = std::vector<Connection>;

// List of connections (instead of nodes because two nodes could have multiple connections) from the start node to the goal node
using Path = std::vector<Connection>;
} // namespace Pathfinding
