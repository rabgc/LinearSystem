// ProcessNoiseCov.cpp
#include "ProcessNoiseCov.hpp"

Eigen::MatrixXd ProcessNoiseCov::create(int state_len, double noise_level) {
    Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(state_len, state_len);
    Q *= noise_level; // Scale by noise level
    return Q;
}