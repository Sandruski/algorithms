#pragma once

#include <list>
#include <vector>

namespace Pathfinding
{
// List of connections (instead of nodes because two nodes could have multiple connections) from the start node to the goal node
using Path = std::vector<Connection>;

class NodeRecord
{
public:
    explicit NodeRecord(const Node inNode);

    bool operator==(const NodeRecord& inOther) const;

    Node              GetNode() const;
    void              Update(const float inCostSoFar, const Connection* inConnection);
    float             GetCostSoFar() const;
    const Connection* GetConnection() const;

private:
    Node              mNode       = 0;
    float             mCostSoFar  = 0;
    const Connection* mConnection = nullptr;
};

NodeRecord::NodeRecord(const Node inNode) : mNode(inNode)
{
}

bool NodeRecord::operator==(const NodeRecord& inOther) const
{
    return ((mNode == inOther.mNode) && (mCostSoFar == inOther.mCostSoFar) && (mConnection == inOther.mConnection));
}

Node NodeRecord::GetNode() const
{
    return mNode;
}

void NodeRecord::Update(const float inCostSoFar, const Connection* inConnection)
{
    mCostSoFar  = inCostSoFar;
    mConnection = inConnection;
}

float NodeRecord::GetCostSoFar() const
{
    return mCostSoFar;
}

const Connection* NodeRecord::GetConnection() const
{
    return mConnection;
}

using PathfindingList = std::list<NodeRecord>;
}
