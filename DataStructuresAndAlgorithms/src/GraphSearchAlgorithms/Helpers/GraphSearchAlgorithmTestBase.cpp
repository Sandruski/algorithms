#include "GraphSearchAlgorithms/Helpers/GraphSearchAlgorithmTestBase.h"

namespace GraphSearchAlgorithms
{
void GraphSearchAlgorithmTestBase::SetUp()
{
    mGraph.AddConnection(m0To1Connection);
    mGraph.AddConnection(m0To2Connection);
    mGraph.AddConnection(m1To3Connection);
    mGraph.AddConnection(m2To1Connection);
    mGraph.AddConnection(m2To3Connection);
}
} // namespace GraphSearchAlgorithms
