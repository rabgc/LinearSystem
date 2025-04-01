#ifndef DESIGNMATRIX_HPP
#define DESIGNMATRIX_HPP

#include <Eigen/Dense>

class DesignMatrix {
public:
    /**
     * @brief Create the design matrix for a linear system
     * @param physical_dim Num of physical dimensions (e.g., 3 for x, y, z)
     * @param system_order Sys dynamics order (e.g., 1 for pos, 2 for pos & vel)
     * @param num_targets Number of targets in the system
     * @param equate_targets Whether to equate targets in the design matrix
     * @param observe_rates  Include rates (e.g., velocity) in design matrix
     * @return Eigen::MatrixXd The design matrix
     */
    static Eigen::MatrixXd create(
        int physical_dim, int system_order, int num_targets, 
        bool equate_targets, bool observe_rates
    );
};

#endif // DESIGNMATRIX_HPP