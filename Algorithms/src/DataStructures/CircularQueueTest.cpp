#include "DataStructures/CircularQueue.h"
#include "DataStructures/Helpers/DataStructureTestBase.h"

namespace DataStructures
{
class CircularQueueTest : public DataStructureTestBase
{
};

TEST_F(CircularQueueTest, QueueOperations)
{
    CircularQueue CircularQueue(3);
    EXPECT_TRUE(CircularQueue.EnQueue(1));
    EXPECT_TRUE(CircularQueue.EnQueue(2));
    EXPECT_TRUE(CircularQueue.EnQueue(3));
    EXPECT_FALSE(CircularQueue.EnQueue(4));
    EXPECT_EQ(CircularQueue.Rear(), 3);
    EXPECT_TRUE(CircularQueue.IsFull());
    EXPECT_TRUE(CircularQueue.DeQueue());
    EXPECT_TRUE(CircularQueue.EnQueue(4));
    EXPECT_EQ(CircularQueue.Rear(), 4);
}
} // namespace DataStructures
