#include "Helpers/PathfindingGraph.h"

namespace Pathfinding
{
Connection::Connection(const Node inFromNode, const Node inToNode, const float inCost)
    : mFromNode(inFromNode), mToNode(inToNode), mCost(inCost)
{
}
} // namespace Pathfinding
