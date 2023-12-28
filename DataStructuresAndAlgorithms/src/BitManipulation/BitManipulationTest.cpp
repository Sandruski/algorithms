#include <cmath>
#include <cstdint>
#include <string>

namespace
{
// You are given two 32-bit numbers, N and M, and two bit positions, i and j. Write a method to insert M into N such that M starts at bit j
// and ends at bit i. You can assume that the bits j through i have enough space to fit all of M. That is, if M = 10011, you can assume that there are
// at least 5 bits between j and i. You would not, for example, have j = 3 and i = 2, because M could not fully fit between bit 3 and bit 2.
std::int32_t Insertion(const std::int32_t inN, const std::int32_t inM, const std::int32_t ini, const std::int32_t inj)
{
    const std::int32_t LeftMask  = -1 << (inj + 1);      // 1110 0000
    const std::int32_t RightMask = (1 << ini) - 1;       // 0000 0111
    const std::int32_t Mask      = LeftMask | RightMask; // 1110 0111
    const std::int32_t MaskedN   = inN & Mask;           // 1110 0111
    const std::int32_t MaskedM   = inM << ini;           // 0001 1000
    const std::int32_t Result    = MaskedN | MaskedM;    // 1111 1111
    return Result;
}

// Given a real number between O and 1 (e.g., 0.72) that is passed in as a double, print the binary representation. If the number cannot be
// represented accurately in binary with at most 32 characters, print "ERROR".
std::string BinaryToString(const double inNumber)
{
    if (inNumber <= 0 || inNumber >= 1)
    {
        return "ERROR";
    }

    std::string Result = "0.";

    double Number = inNumber;
    while (Number > 0.0)
    {
        if (Result.length() >= 32)
        {
            break;
        }

        Number *= 2.0;

        const std::int32_t IntegerPart = static_cast<std::int32_t>(std::floor(Number));
        Result += std::to_string(IntegerPart);

        const double FractionalPart = Number - static_cast<double>(IntegerPart);
        Number                      = FractionalPart;
    }

    return Result;
}

// You have an integer and you can flip exactly one bit from a 0 to a 1. Write code to find the length of the longest sequence of 1s you could create.
int FlipBitToWin(const int inNumber)
{
    // Time complexity: 0(b)

    int MaxLength = 0;

    int CurrentLength  = 0;
    int PreviousLength = 0;

    // Cast to unsigned int to perform logical shift (insert 0s) instead of arithmetic shift (insert 1s), so the number eventually becomes 0
    for (unsigned int i = inNumber; i > 0; i >>= 1)
    {
        const int CurrentValue = i & 1;
        if (CurrentValue == 0)
        {
            const int NextValue = i & 2;
            PreviousLength      = (NextValue == 0) ? 0 : CurrentLength;

            CurrentLength = 0;
        }
        else
        {
            ++CurrentLength;
        }

        const int TotalLength = CurrentLength + PreviousLength + 1;
        if (TotalLength > MaxLength)
        {
            MaxLength = TotalLength;
        }
    }

    return MaxLength;
}
} // namespace

TEST(BitManipulationTest, Insertion)
{
    const std::int32_t InN  = 0b10011111110;
    const std::int32_t InM  = 0b10011;
    const std::int32_t Ini  = 2;
    const std::int32_t Inj  = 6;
    const std::int32_t OutN = 0b10011001110;
    EXPECT_EQ(Insertion(InN, InM, Ini, Inj), OutN);
}

TEST(BitManipulationTest, BinaryToString)
{
    const double      InNumber  = 0.375;
    const std::string OutString = "0.011";
    EXPECT_EQ(BinaryToString(InNumber), OutString);
}

TEST(BitManipulationTest, FlipBitToWin)
{
    const int InNumber     = 0b11011101111;
    const int OutMaxLength = 8;
    EXPECT_EQ(FlipBitToWin(InNumber), OutMaxLength);
}
