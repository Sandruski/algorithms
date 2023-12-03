#pragma once

#include <list>
#include <queue>

namespace GraphSearchAlgorithms
{
class NodeRecord;

using PathfindingList = std::list<NodeRecord>;

const NodeRecord* FindNodeRecord(const PathfindingList& inPathfindingList, const Node inNode);
NodeRecord*       FindNodeRecordMutable(PathfindingList& inPathfindingList, const Node inNode);
} // namespace GraphSearchAlgorithms
