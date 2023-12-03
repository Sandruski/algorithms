#pragma once

#include "gtest/gtest.h"

#include <vector>

namespace SearchAlgorithms
{
class SearchAlgorithmTestBase : public testing::Test
{
protected:
    const std::vector<int>& GetNums() const;

private:
    std::vector<int> mNums = {-1, 0, 3, 5, 9, 12};
};

inline const std::vector<int>& SearchAlgorithmTestBase::GetNums() const
{
    return mNums;
}
} // namespace SearchAlgorithms
