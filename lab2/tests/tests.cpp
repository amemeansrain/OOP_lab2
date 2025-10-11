#include <gtest/gtest.h>
#include "../include/lab2.h"

TEST(HexTest, DefaultConstructor) {
    Hex hex;
    EXPECT_EQ(hex.size(), 1);
    EXPECT_EQ(hex.toString(), "0");
}

TEST(HexTest, SizeValueConstructor) {
    Hex hex(4, 10);
    EXPECT_EQ(hex.size(), 4);
    EXPECT_EQ(hex.toString(), "AAAA");
}

TEST(HexTest, SizeValueConstructorInvalidDigit) {
    EXPECT_THROW(Hex(3, 16), std::invalid_argument);
}

TEST(HexTest, SizeValueConstructorZeroSize) {
    EXPECT_THROW(Hex(0, 5), std::invalid_argument);
}

TEST(HexTest, StringConstructor) {
    Hex hex("1A3F");
    EXPECT_EQ(hex.size(), 4);
    EXPECT_EQ(hex.toString(), "1A3F");
}

TEST(HexTest, StringConstructorLowerCase) {
    Hex hex("1a3f");
    EXPECT_EQ(hex.toString(), "1A3F");
}

TEST(HexTest, StringConstructorEmpty) {
    Hex hex("");
    EXPECT_EQ(hex.toString(), "0");
}

TEST(HexTest, StringConstructorWithLeadingZeros) {
    Hex hex("000ABC");
    EXPECT_EQ(hex.toString(), "ABC");
}

TEST(HexTest, StringConstructorSingleZero) {
    Hex hex("0");
    EXPECT_EQ(hex.toString(), "0");
}

TEST(HexTest, StringConstructorInvalidChar) {
    EXPECT_THROW(Hex("1G3F"), std::invalid_argument);
}

TEST(HexTest, CopyConstructor) {
    Hex hex1("1A3F");
    Hex hex2(hex1);
    EXPECT_EQ(hex2.toString(), "1A3F");
    EXPECT_EQ(hex2.size(), 4);
}

TEST(HexTest, AddOperation) {
    Hex hex1("1A3F");
    Hex hex2("B2C");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "256B");
}

TEST(HexTest, AddOperationWithCarry) {
    Hex hex1("FFF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "1000");
}

TEST(HexTest, AddOperationZeros) {
    Hex hex1("0");
    Hex hex2("0");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "0");
}

TEST(HexTest, AddOperationLargeNumbers) {
    Hex hex1("FFFFFFFF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.toString(), "100000000");
}

TEST(HexTest, SubtractOperation) {
    Hex hex1("1A3F");
    Hex hex2("B2C");
    Hex result = hex1.sub(hex2);
    EXPECT_EQ(result.toString(), "F13");
}

TEST(HexTest, SubtractOperationEqual) {
    Hex hex1("ABC");
    Hex hex2("ABC");
    Hex result = hex1.sub(hex2);
    EXPECT_EQ(result.toString(), "0");
}

TEST(HexTest, SubtractOperationToZero) {
    Hex hex1("F");
    Hex hex2("F");
    Hex result = hex1.sub(hex2);
    EXPECT_EQ(result.toString(), "0");
}

TEST(HexTest, SubtractOperationInvalid) {
    Hex hex1("123");
    Hex hex2("124");
    EXPECT_THROW(hex1.sub(hex2), std::invalid_argument);
}

TEST(HexTest, CopyMethod) {
    Hex hex1("1A3F");
    Hex hex2 = hex1.copy();
    EXPECT_EQ(hex2.toString(), "1A3F");
    EXPECT_EQ(hex2.size(), 4);
}

TEST(HexTest, GreaterOperation) {
    Hex hex1("1A3F");
    Hex hex2("B2C");
    EXPECT_TRUE(hex1.gt(hex2));
    EXPECT_FALSE(hex2.gt(hex1));
}

TEST(HexTest, GreaterOperationEqual) {
    Hex hex1("1A3F");
    Hex hex2("1A3F");
    EXPECT_FALSE(hex1.gt(hex2));
}

TEST(HexTest, GreaterOperationDifferentLength) {
    Hex hex1("1000");
    Hex hex2("FFF");
    EXPECT_TRUE(hex1.gt(hex2));
}

TEST(HexTest, LessOperation) {
    Hex hex1("B2C");
    Hex hex2("1A3F");
    EXPECT_TRUE(hex1.lt(hex2));
    EXPECT_FALSE(hex2.lt(hex1));
}

TEST(HexTest, LessOperationEqual) {
    Hex hex1("1A3F");
    Hex hex2("1A3F");
    EXPECT_FALSE(hex1.lt(hex2));
}

TEST(HexTest, EqualsOperation) {
    Hex hex1("1A3F");
    Hex hex2("1A3F");
    Hex hex3("1A3E");
    EXPECT_TRUE(hex1.eq(hex2));
    EXPECT_FALSE(hex1.eq(hex3));
}

TEST(HexTest, EqualsOperationDifferentLength) {
    Hex hex1("ABC");
    Hex hex2("0ABC");
    EXPECT_TRUE(hex1.eq(hex2));
}

TEST(HexTest, SizeMethod) {
    Hex hex1("1A3F");
    Hex hex2("FFFFFFFF");
    Hex hex3("0");
    EXPECT_EQ(hex1.size(), 4);
    EXPECT_EQ(hex2.size(), 8);
    EXPECT_EQ(hex3.size(), 1);
}

TEST(HexTest, ToStringMethod) {
    Hex hex1("1a3f");
    Hex hex2("ABCDEF");
    Hex hex3("0");
    EXPECT_EQ(hex1.toString(), "1A3F");
    EXPECT_EQ(hex2.toString(), "ABCDEF");
    EXPECT_EQ(hex3.toString(), "0");
}

TEST(HexTest, ComplexOperations) {
    Hex hex1("123");
    Hex hex2("456");
    Hex hex3("789");
    
    Hex sum1 = hex1.add(hex2);
    Hex finalSum = sum1.add(hex3);
    
    EXPECT_EQ(finalSum.toString(), "D02");
}

TEST(HexTest, MultipleSubtractions) {
    Hex hex1("1000");
    Hex hex2("100");
    Hex hex3("10");
    
    Hex diff1 = hex1.sub(hex2);
    Hex finalDiff = diff1.sub(hex3);
    
    EXPECT_EQ(finalDiff.toString(), "EF0");
}

TEST(HexTest, Immutability) {
    Hex hex1("123");
    Hex hex2("456");
    
    Hex sum = hex1.add(hex2);
    Hex original = hex1.copy();
    
    EXPECT_TRUE(hex1.eq(original));
    EXPECT_EQ(hex1.toString(), "123");
    EXPECT_EQ(sum.toString(), "579");
}