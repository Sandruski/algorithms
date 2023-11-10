#pragma once

#include "gtest/gtest.h"

namespace SortingAlgorithms
{
class SortingAlgorithmTestBase : public testing::Test
{
protected:
    const std::vector<int>& GetNums() const;

private:
    std::vector<int> mNums = {5, 1, 1, 2, 0, 0};
};

inline const std::vector<int>& SortingAlgorithmTestBase::GetNums() const
{
    return mNums;
}
} // namespace GraphSearchAlgorithms
