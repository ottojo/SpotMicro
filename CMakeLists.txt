cmake_minimum_required(VERSION 3.13)
project(SpotMicroCPP)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt)
find_package(Microsoft.GSL CONFIG)
find_package(ottojo.I2C REQUIRED)

add_executable(SpotMicroCPP
        main.cpp
        Kinematics.cpp
        ServoController.cpp
        expect.cpp
        LegPose.cpp
        RobotHW.cpp
        RobotConfig.hpp
        StraightTrajectory.cpp
        TrajectoryRunner.cpp
        )

target_link_libraries(SpotMicroCPP PRIVATE ottojo.I2C::I2C Microsoft.GSL::GSL fmt::fmt pthread)

option(CLANG_TIDY OFF)
if (${CLANG_TIDY})
    set_target_properties(SpotMicroCPP PROPERTIES CXX_CLANG_TIDY "clang-tidy")
else ()
    message(WARNING "clang-tidy not enabled")
endif ()

option(IWYU OFF)
if (${IWYU})
    set_target_properties(SpotMicroCPP PROPERTIES
            CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--no_fwd_decls;-Xiwyu;--cxx17ns;-Xiwyu;--quoted_includes_first;-Xiwyu;--cxx17ns:")
else ()
    message(WARNING "include-what-you-use not enabled")
endif ()


target_compile_options(SpotMicroCPP PRIVATE $<IF:$<CONFIG:Debug>,-Og,-Ofast> -Wall -Wextra -Wpedantic -Werror -Wno-error=unused-function)

option(BUILD_TESTS OFF)
if (${BUILD_TESTS})
    if (${CMAKE_VERSION} VERSION_GREATER "3.16.0")
        include(FetchContent)
        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG release-1.10.0
        )
        FetchContent_MakeAvailable(googletest)
        add_executable(test test/testMain.cpp Kinematics.cpp expect.cpp test/kinematicsTest.cpp test/mathTest.cpp LegPose.cpp)
        target_include_directories(test PRIVATE external)
        target_link_libraries(test gtest fmt::fmt)
        include(GoogleTest)
        gtest_discover_tests(test)
    endif ()
endif ()
