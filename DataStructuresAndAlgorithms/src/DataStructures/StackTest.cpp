#include "DataStructures/Stack.h"
#include "DataStructures/Helpers/DataStructureTestBase.h"

namespace DataStructures
{
class StackTest : public DataStructureTestBase
{
};

TEST_F(StackTest, QueueOperations)
{
    Stack Stack;
    Stack.Push(1);
    Stack.Push(2);
    Stack.Push(3);
    EXPECT_EQ(Stack.Top(), 3);
    EXPECT_TRUE(Stack.Pop());
    EXPECT_TRUE(Stack.Pop());
    EXPECT_TRUE(Stack.Pop());
    EXPECT_FALSE(Stack.Pop());
    EXPECT_TRUE(Stack.IsEmpty());
}
} // namespace DataStructures
