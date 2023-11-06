#pragma once

#include <list>

namespace Pathfinding
{
class NodeRecord;

using PathfindingList = std::list<NodeRecord>;

NodeRecord* FindNodeRecord(PathfindingList& inPathfindingList, const Node inNode);
} // namespace Pathfinding
