// StateTransitionMatrix.hpp
#ifndef STATETRANSITIONMATRIX_HPP
#define STATETRANSITIONMATRIX_HPP

#include <Eigen/Dense>

class StateTransitionMatrix {
public:
    static Eigen::MatrixXd create(
        int physical_dim, int system_order, int num_targets, double dt);
};

#endif // STATETRANSITIONMATRIX_HPP