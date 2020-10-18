/**
 * @file test.cpp
 * @author jonas
 * @date 9/18/20
 * Description here TODO
 */

#include <gtest/gtest.h>
#include <cfenv>

int main(int argc, char **argv) {
    feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
