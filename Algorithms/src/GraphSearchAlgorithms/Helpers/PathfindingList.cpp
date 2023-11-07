#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

namespace Pathfinding
{
NodeRecord::NodeRecord(const Node inNode) : mNode(inNode)
{
}

NodeRecord::NodeRecord(const Node inNode, const Connection* inConnection) : mNode(inNode), mConnection(inConnection)
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
