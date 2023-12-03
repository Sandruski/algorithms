#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"

#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <algorithm>

namespace GraphSearchAlgorithms
{
Path ReconstructPath(const NodeRecord& inCurrentNodeRecord, const PathfindingList& inClosedList, const Node inStartNode, const Node inGoalNode)
{
    Path Path;

    // If the goal node is not found, return an empty path
    Node CurrentNode = inCurrentNodeRecord.GetNode();
    if (CurrentNode != inGoalNode)
    {
        return Path;
    }

    // Otherwise reconstruct the path by following the connections backwards from the goal node to the start node
    const NodeRecord* CurrentNodeRecord = &inCurrentNodeRecord;
    while (CurrentNode != inStartNode)
    {
        const Connection* Connection = CurrentNodeRecord->GetConnection();
        Path.emplace_back(*Connection);
        CurrentNode       = Connection->GetFromNode();
        CurrentNodeRecord = FindNodeRecord(inClosedList, CurrentNode);
    }

    // Optional
    //Path.emplace_back(NodeRecord(inStartNode));

    std::reverse(Path.begin(), Path.end());

    return Path;
}
} // namespace GraphSearchAlgorithms
