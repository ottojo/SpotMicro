/**
 * @file expect.hpp
 * @author jonas
 * @date 9/23/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_EXPECT_HPP
#define SPOTMICROCPP_EXPECT_HPP

#include <string>  // for string

#define ExpectM(E, M) expect(E,M,__LINE__, __FILE__)

void expect(bool e, const std::string &message, int line, const std::string &file);


#endif //SPOTMICROCPP_EXPECT_HPP
