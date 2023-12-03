#pragma once

#include <vector>

namespace DataStructures
{
class CircularQueue
{
public:
    CircularQueue(const int inSize);

    // Insert an element into the circular queue. Return true if the operation is successful
    bool EnQueue(const int inValue);

    // Delete an element from the circular queue. Return true if the operation is successful
    bool DeQueue();

    // Get the front item from the queue
    int Front() const;

    // Get the last item from the queue
    int Rear() const;

    // Checks whether the circular queue is empty or not
    bool IsEmpty() const;

    // Checks whether the circular queue is full or not
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
