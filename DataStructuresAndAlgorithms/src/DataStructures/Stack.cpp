#include "DataStructures/Stack.h"

namespace DataStructures
{
bool Stack::Pop()
{
    if (IsEmpty())
    {
        return false;
    }

    mData.pop_back();

    return true;
}
} // namespace DataStructures
