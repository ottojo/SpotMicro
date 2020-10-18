/**
 * @file StraightTrajectory.hpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_STRAIGHTTRAJECTORY_HPP
#define SPOTMICROCPP_STRAIGHTTRAJECTORY_HPP


#include "FootTrajectory.hpp"

class StraightTrajectory : public FootTrajectory {
    public:
        StraightTrajectory(Vector3d from, Vector3d to) :
                start{from},
                direction{to - from} {}

        [[nodiscard]] Vector3d getPos(double progress) const override;

    private:
        Vector3d start;
        Vector3d direction;
};


#endif //SPOTMICROCPP_STRAIGHTTRAJECTORY_HPP
