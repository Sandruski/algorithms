#pragma once

#include "GraphSearchAlgorithms/Helpers/Graph.h"

#include "gtest/gtest.h"

namespace GraphSearchAlgorithms
{
class GraphSearchAlgorithmTestBase : public testing::Test
{
protected:
    void SetUp() override;

    const Graph&      GetGraph() const;
    const Connection& Get0To1Connection() const;
    const Connection& Get0To2Connection() const;
    const Connection& Get1To3Connection() const;
    const Connection& Get2To1Connection() const;
    const Connection& Get2To3Connection() const;

private:
    Graph      mGraph;
    Connection m0To1Connection = Connection(0, 1, 6);
    Connection m0To2Connection = Connection(0, 2, 2);
    Connection m1To3Connection = Connection(1, 3, 1);
    Connection m2To1Connection = Connection(2, 1, 3);
    Connection m2To3Connection = Connection(2, 3, 5);
};

inline const Graph& GraphSearchAlgorithmTestBase::GetGraph() const
{
    return mGraph;
}

inline const Connection& GraphSearchAlgorithmTestBase::Get0To1Connection() const
{
    return m0To1Connection;
}

inline const Connection& GraphSearchAlgorithmTestBase::Get0To2Connection() const
{
    return m0To2Connection;
}

inline const Connection& GraphSearchAlgorithmTestBase::Get1To3Connection() const
{
    return m1To3Connection;
}

inline const Connection& GraphSearchAlgorithmTestBase::Get2To1Connection() const
{
    return m2To1Connection;
}

inline const Connection& GraphSearchAlgorithmTestBase::Get2To3Connection() const
{
    return m2To3Connection;
}
} // namespace GraphSearchAlgorithms
