#pragma once

#include <vector>

namespace DataStructures
{
class Stack
{
public:
    // Insert an element into the stack
    void Push(const int inValue);

    // Delete an element from the stack. Return true if the operation is successful
    bool Pop();

    // Get the top item from the stack
    int Top() const;

    // Checks whether the stack is empty or not
    bool IsEmpty() const;

private:
    std::vector<int> mData;
};
} // namespace DataStructures

namespace DataStructures
{
inline void Stack::Push(const int inValue)
{
    mData.emplace_back(inValue);
}

inline int Stack::Top() const
{
    return mData.back();
}

inline bool Stack::IsEmpty() const
{
    return mData.empty();
}
} // namespace DataStructures
