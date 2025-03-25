// ProcessNoiseCov.hpp
#ifndef PROCESSNOISECOV_HPP
#define PROCESSNOISECOV_HPP

#include <Eigen/Dense>

class ProcessNoiseCov {
public:
    static Eigen::MatrixXd create(int state_len, double noise_level);
};

#endif // PROCESSNOISECOV_HPP