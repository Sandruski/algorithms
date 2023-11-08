#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmsHelpers.h"

#include "GraphSearchAlgorithms/Helpers/Graph.h"
#include "GraphSearchAlgorithms/Helpers/PathfindingList.h"

#include <algorithm>

namespace GraphSearchAlgorithms
{
Path BuildPath(const NodeRecord& inCurrentNodeRecord, const PathfindingList& inClosedList, const Node inStartNode, const Node inGoalNode)
{
    Path Path;

    // If the goal node is not found, terminate
    Node CurrentNode = inCurrentNodeRecord.GetNode();
    if (CurrentNode != inGoalNode)
    {
        return Path;
    }

    // Otherwise build its path
    const NodeRecord* CurrentNodeRecord = &inCurrentNodeRecord;
    while (CurrentNode != inStartNode)
    {
        const Connection* Connection = CurrentNodeRecord->GetConnection();
        Path.emplace_back(*Connection);
        CurrentNode       = Connection->GetFromNode();
        CurrentNodeRecord = FindNodeRecord(inClosedList, CurrentNode);
    }

    std::reverse(Path.begin(), Path.end());

    return Path;
}
} // namespace GraphSearchAlgorithms
