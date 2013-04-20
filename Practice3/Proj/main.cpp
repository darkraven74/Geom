#include <gtest/gtest.h>
#include <iostream>
#include <gmpxx.h>
#include "cg/primitives/point.h"
#include "cg/primitives/range.h"
#include "cg/primitives/segment.h"
#include <cg/operations/orientation.h>
using namespace cg;
using namespace std;

template <class Scalar>
bool between(point_2t<Scalar> const& a, point_2t<Scalar> const& b,
             point_2t<Scalar> const& c)
{
    if (b == a)
    {
        return (c == a);
    }
    Scalar t = (c.x - a.x) / (b.x - a.x);
    return ((t <= 1) && (t >= 0)) ? true : false;
}


template <class Scalar>
bool intersect(segment_2t<Scalar> const& a, segment_2t<Scalar> const& b)
{
    point_2t<Scalar> p1 = a[0];
    point_2t<Scalar> p2 = a[1];
    point_2t<Scalar> p3 = b[0];
    point_2t<Scalar> p4 = b[1];

    if (!between(p1, p2, p3) && !between(p1, p2, p4))
    {
        return false;
    }

    if (between(p1, p2, p4))
    {
        swap(p4, p3);
    }

    int temp = orientation(p1, p2, p3);

    if (temp == 0)
    {
        return true;
    }

    if ((orientation(p1, p2, p4) != temp) && (orientation(p3, p2, p4) != temp)
            && ((orientation(p3, p1, p4) == temp) || (orientation(p3, p1, p4) == 0)))
    {
            return true;
    }
    return false;
}


TEST(test_intersect, 1)
{
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(10, 10), point_2t<double>(10, -10));
    EXPECT_FALSE(intersect(s1, s2));
}

TEST(test_intersect, 2)
{
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(3, 10), point_2t<double>(3, -10));
    EXPECT_TRUE(intersect(s1, s2));
}

TEST(test_intersect, 3)
{
    segment_2t<double> s1(point_2t<double>(3, 3), point_2t<double>(1, 1));
    segment_2t<double> s2(point_2t<double>(5, 5), point_2t<double>(4, 4));
    EXPECT_FALSE(intersect(s1, s2));
}

TEST(test_intersect, 4)
{
    segment_2t<double> s1(point_2t<double>(3, 3), point_2t<double>(1, 1));
    segment_2t<double> s2(point_2t<double>(2, 2), point_2t<double>(4, 4));
   EXPECT_TRUE(intersect(s1, s2));
}

TEST(test_intersect, 5)
{
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(5, 5));
    segment_2t<double> s2(point_2t<double>(4, 4), point_2t<double>(3, -7));
    EXPECT_TRUE(intersect(s1, s2));
}

TEST(test_intersect, 6)
{
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(3, 7), point_2t<double>(3, 10));
    EXPECT_FALSE(intersect(s1, s2));
}

TEST(test_intersect, 7)
{
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(7, 7), point_2t<double>(10, 10));
    EXPECT_FALSE(intersect(s1, s2));
}

TEST(test_intersect, 8)
{
    segment_2t<double> s1(point_2t<double>(1, 0), point_2t<double>(5, 0));
    segment_2t<double> s2(point_2t<double>(5, 0), point_2t<double>(5, 10));
    EXPECT_TRUE(intersect(s1, s2));
}

TEST(test_intersect, 9)
{
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(5, 5));
    segment_2t<double> s2(point_2t<double>(7, 7), point_2t<double>(7, 7));
    EXPECT_FALSE(intersect(s1, s2));
}

TEST(test_intersect, 10)
{
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(5, 5));
    segment_2t<double> s2(point_2t<double>(4, 4), point_2t<double>(4, 4));
    EXPECT_TRUE(intersect(s1, s2));
}

TEST(test_intersect, 11)
{
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(1, 1));
    segment_2t<double> s2(point_2t<double>(1, 1), point_2t<double>(1, 1));
    EXPECT_TRUE(intersect(s1, s2));
}

TEST(test_intersect, 12)
{
    segment_2t<double> s1(point_2t<double>(1, 1), point_2t<double>(3, 3));
    segment_2t<double> s2(point_2t<double>(100, 100), point_2t<double>(100, 1));
    EXPECT_FALSE(intersect(s1, s2));
}

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

