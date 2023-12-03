#pragma once

#include <vector>

namespace SortingAlgorithms
{
/**
 * Quick Sort
 * Time complexity: O(nlogn). Depending on the pivot it can be O(n^2)
 */
namespace QuickSort
{
void Sort(std::vector<int>& inNums, const int inLowIndex, const int inHighIndex);
} // namespace QuickSort
} // namespace SortingAlgorithms
