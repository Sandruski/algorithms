#include "Helpers/PathfindingList.h"

namespace Pathfinding
{
NodeRecord::NodeRecord(const Node inNode) : mNode(inNode)
{
}

NodeRecord* FindNodeRecord(PathfindingList& inPathfindingList, const Node inNode)
{
    for (NodeRecord& NodeRecord : inPathfindingList)
    {
        const Node Node = NodeRecord.GetNode();
        if (Node == inNode)
        {
            return &NodeRecord;
        }
    }

    return nullptr;
}
} // namespace Pathfinding
