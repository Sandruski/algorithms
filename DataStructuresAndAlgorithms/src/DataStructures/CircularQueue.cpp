#include "DataStructures/CircularQueue.h"

namespace DataStructures
{
CircularQueue::CircularQueue(const int inSize)
{
    mData.resize(inSize);
}

bool CircularQueue::EnQueue(const int inValue)
{
    if (IsFull())
    {
        return false;
    }

    if (IsEmpty())
    {
        mHead = 0;
        mTail = 0;
    }
    else
    {
        mTail = (mTail + 1) % mData.size();
    }

    mData[mTail] = inValue;

    return true;
}

bool CircularQueue::DeQueue()
{
    if (IsEmpty())
    {
        return false;
    }

    if (mHead == mTail)
    {
        mHead = -1;
        mTail = -1;
    }
    else
    {
        mHead = (mHead + 1) % mData.size();
    }

    return true;
}

int CircularQueue::Front() const
{
    if (IsEmpty())
    {
        return -1;
    }

    return mData[mHead];
}

int CircularQueue::Rear() const
{
    if (IsEmpty())
    {
        return -1;
    }

    return mData[mTail];
}
} // namespace DataStructures