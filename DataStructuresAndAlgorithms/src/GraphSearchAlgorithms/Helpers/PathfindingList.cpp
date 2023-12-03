#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

namespace GraphSearchAlgorithms
{
NodeRecord::NodeRecord(const Node inNode) : mNode(inNode)
{
}

NodeRecord::NodeRecord(const Node inNode, const Connection* inConnection) : mNode(inNode), mConnection(inConnection)
{
}

NodeRecord::NodeRecord(const Node inNode, const float inEstimatedTotalCost) : mNode(inNode), mEstimatedTotalCost(inEstimatedTotalCost)
{
}

const NodeRecord* FindNodeRecord(const PathfindingList& inPathfindingList, const Node inNode)
{
    for (const NodeRecord& NodeRecord : inPathfindingList)
    {
        const Node Node = NodeRecord.GetNode();
        if (Node == inNode)
        {
            return &NodeRecord;
        }
    }

    return nullptr;
}

NodeRecord* FindNodeRecordMutable(PathfindingList& inPathfindingList, const Node inNode)
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
} // namespace GraphSearchAlgorithms
