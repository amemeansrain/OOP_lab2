#include <gtest/gtest.h>
#include "../include/lab2.h"

TEST(HexTest, CreateEmpty) {
    Hex h;
    EXPECT_EQ(h.size(), 1);
    EXPECT_EQ(h.toStr(), "0");
}

TEST(HexTest, CreateFromString) {
    Hex h("1A3F");
    EXPECT_EQ(h.size(), 4);
    EXPECT_EQ(h.toStr(), "1A3F");
}

TEST(HexTest, CreateBad) {
    EXPECT_THROW(Hex("1G3F"), std::invalid_argument);
}

TEST(HexTest, Add) {
    Hex a("1A3F");
    Hex b("B2C");
    Hex c = a.plus(b);
    EXPECT_EQ(c.toStr(), "256B");
}

TEST(HexTest, AddCarry) {
    Hex a("FFF");
    Hex b("1");
    Hex c = a.plus(b);
    EXPECT_EQ(c.toStr(), "1000");
}

TEST(HexTest, Sub) {
    Hex a("1A3F");
    Hex b("B2C");
    Hex c = a.minus(b);
    EXPECT_EQ(c.toStr(), "F13");
}

TEST(HexTest, SubBad) {
    Hex a("123");
    Hex b("124");
    EXPECT_THROW(a.minus(b), std::invalid_argument);
}

TEST(HexTest, Compare) {
    Hex a("1A3F");
    Hex b("B2C");
    EXPECT_TRUE(a.more(b));
    EXPECT_TRUE(b.less(a));
    EXPECT_FALSE(a.same(b));
}

TEST(HexTest, Copy) {
    Hex a("1A3F");
    Hex b = a.dup();
    EXPECT_TRUE(a.same(b));
}

TEST(HexTest, BigAdd) {
    Hex a("FFFFFFFF");
    Hex b("1");
    Hex c = a.plus(b);
    EXPECT_EQ(c.toStr(), "100000000");
}

TEST(HexTest, RemoveZeros) {
    Hex a("000ABC");
    EXPECT_EQ(a.toStr(), "ABC");
}

TEST(HexTest, EqualWithZeros) {
    Hex a("ABC");
    Hex b("0ABC");
    EXPECT_TRUE(a.same(b));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}