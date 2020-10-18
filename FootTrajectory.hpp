/**
 * @file Trajectory.hpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_FOOTTRAJECTORY_HPP
#define SPOTMICROCPP_FOOTTRAJECTORY_HPP


#include "Vector3d.hpp"

class FootTrajectory {
    public:
        [[nodiscard]] virtual Vector3d getPos(double progress) const = 0;

        virtual ~FootTrajectory() = default;
};


#endif //SPOTMICROCPP_FOOTTRAJECTORY_HPP
