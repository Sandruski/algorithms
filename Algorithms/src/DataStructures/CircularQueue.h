#pragma once

#include <vector>

namespace DataStructures
{
class CircularQueue
{
public:
    CircularQueue(const int inSize);

    bool EnQueue(const int inValue);
    bool DeQueue();

    int Front() const;
    int Rear() const;

    bool IsEmpty() const;
    bool IsFull() const;

private:
    std::vector<int> mData;
    int              mHead = -1;
    int              mTail = -1;
};
} // namespace DataStructures

namespace DataStructures
{
inline bool CircularQueue::IsEmpty() const
{
    return (mHead == -1) && (mTail == -1);
}

inline bool CircularQueue::IsFull() const
{
    return ((mTail + 1) % mData.size()) == mHead;
}
} // namespace DataStructures
