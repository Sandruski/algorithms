#include "GraphSearchAlgorithms/Helpers/Graph.h"

namespace GraphSearchAlgorithms
{
Connection::Connection(const Node inFromNode, const Node inToNode, const float inCost) : mFromNode(inFromNode), mToNode(inToNode), mCost(inCost)
{
}
} // namespace GraphSearchAlgorithms
