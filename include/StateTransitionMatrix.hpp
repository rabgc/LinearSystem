// StateTransitionMatrix.hpp
#ifndef STATETRANSITIONMATRIX_HPP
#define STATETRANSITIONMATRIX_HPP

#include <Eigen/Dense>

/**
 * @class StateTransitionMatrix
 * @brief Utility class to create state transition matrices for linear 
 * systems.
 */
class StateTransitionMatrix {
public:
    /**
     * @brief Create the state transition matrix for a linear system.
     * 
     * This method generates a state transition matrix using a truncated 
     * matrix exponential based on the system order, physical dimensions, 
     * and number of targets.
     * 
     * @param physical_dim Number of physical dimensions (e.g., 3 for x, y, z).
     * @param system_order Order of the system dynamics 
     * (e.g., 1 for dx/dt => position, 2 for dx2/dt2 => position and velocity).
     * @param num_targets Number of targets in the system.
     * @param dt Time step for the state transition matrix.
     * @return Eigen::MatrixXd The state transition matrix.
     */
    static Eigen::MatrixXd create(
        int physical_dim, int system_order, int num_targets, double dt
    );
};

#endif // STATETRANSITIONMATRIX_HPP