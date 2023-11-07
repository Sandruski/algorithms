#include "GraphSearchAlgorithms/Helpers/Graph.h"

Connection::Connection(const Node inFromNode, const Node inToNode, const float inCost)
    : mFromNode(inFromNode), mToNode(inToNode), mCost(inCost)
{
}
