/**
 * @file mathTest.cpp
 * @author jonas
 * @date 9/26/20
 * Description here TODO
 */

#include <gtest/gtest.h>
#include "../MathUtil.hpp"

TEST(Math, CosineLawAngle) {
    EXPECT_DOUBLE_EQ(math::cosineLawAngle(4, 7, 5).getDegs(), 44.415308597192976);
}

TEST(Math, CosineLawSide) {
    EXPECT_DOUBLE_EQ(math::cosineLawSide(4, 7, Angle::fromDegs(44)), 4.9716165561148751);
}
