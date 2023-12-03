#pragma once

#include "GraphSearchAlgorithms/Helpers/GraphFwd.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingListFwd.h"

namespace GraphSearchAlgorithms
{
class NodeRecord
{
public:
    explicit NodeRecord(const Node inNode);
    explicit NodeRecord(const Node inNode, const Connection* inConnection);
    explicit NodeRecord(const Node inNode, const float inEstimatedTotalCost);

    bool operator==(const NodeRecord& inOther) const;

    void              Update(const float inCostSoFar, const Connection* inConnection);
    void              Update(const float inCostSoFar, const float inEstimatedTotalCost, const Connection* inConnection);
    const Connection* GetConnection() const;
    Node              GetNode() const;
    float             GetCostSoFar() const;
    float             GetEstimatedTotalCost() const;

private:
    const Connection* mConnection         = nullptr;
    Node              mNode               = 0;
    float             mCostSoFar          = 0;
    float             mEstimatedTotalCost = 0.f;
};

inline bool NodeRecord::operator==(const NodeRecord& inOther) const
{
    return ((mNode == inOther.mNode) && (mCostSoFar == inOther.mCostSoFar) && (mConnection == inOther.mConnection));
}

inline void NodeRecord::Update(const float inCostSoFar, const Connection* inConnection)
{
    mCostSoFar  = inCostSoFar;
    mConnection = inConnection;
}

inline void NodeRecord::Update(const float inCostSoFar, const float inEstimatedTotalCost, const Connection* inConnection)
{
    Update(inCostSoFar, inConnection);
    mEstimatedTotalCost = inEstimatedTotalCost;
}

inline const Connection* NodeRecord::GetConnection() const
{
    return mConnection;
}

inline Node NodeRecord::GetNode() const
{
    return mNode;
}

inline float NodeRecord::GetCostSoFar() const
{
    return mCostSoFar;
}

inline float NodeRecord::GetEstimatedTotalCost() const
{
    return mEstimatedTotalCost;
}
} // namespace GraphSearchAlgorithms
