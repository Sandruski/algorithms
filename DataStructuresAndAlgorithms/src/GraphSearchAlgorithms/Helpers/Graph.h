#pragma once

#include "GraphSearchAlgorithms/Helpers/GraphFwd.h"

#include <unordered_map>

namespace GraphSearchAlgorithms
{
/**
 * Vertex
 * Pair of nodes
 */
class Connection
{
public:
    explicit Connection(const Node inFromNode, const Node inToNode, const float inCost);

    bool operator==(const Connection& inOther) const;

    Node  GetFromNode() const;
    Node  GetToNode() const;
    float GetCost() const;

private:
    Node mFromNode = 0;
    Node mToNode   = 0;

    // Non-negative weight (e.g. in a pathfinding graph, time or distance)
    float mCost = 0.f;
};

/**
 * Pathfinding graph
 * Directed non-negative weighted graph
 * Acyclic by definition
 * Set of connections
 */
class Graph
{
public:
    void             AddConnection(const Connection& inConnection);
    const Neighbors* FindNeighbors(const Node inNode) const;

private:
    // Node to its neighbors
    std::unordered_map<Node, Neighbors> mConnections;
};

inline bool Connection::operator==(const Connection& inOther) const
{
    return ((mFromNode == inOther.mFromNode) && (mToNode == inOther.mToNode) && (mCost == inOther.mCost));
}

inline Node Connection::GetFromNode() const
{
    return mFromNode;
}

inline Node Connection::GetToNode() const
{
    return mToNode;
}

inline float Connection::GetCost() const
{
    return mCost;
}

inline void Graph::AddConnection(const Connection& inConnection)
{
    const Node FromNode = inConnection.GetFromNode();
    mConnections[FromNode].emplace_back(inConnection);
}

inline const Neighbors* Graph::FindNeighbors(const Node inNode) const
{
    const auto It = mConnections.find(inNode);
    return ((It != mConnections.end()) ? &It->second : nullptr);
}
} // namespace GraphSearchAlgorithms
