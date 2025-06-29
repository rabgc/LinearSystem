#include "DesignMatrix.hpp"

Eigen::MatrixXd DesignMatrix::create(
    int physical_dim, int system_order, int num_targets,
    bool equate_targets, bool observe_rates)
{
  
  if (!observe_rates && !equate_targets)
  {
    return Eigen::MatrixXd::Identity(
        physical_dim * num_targets, physical_dim * system_order);
  }
  
  if (observe_rates && !equate_targets)
  {
    int rows = 2 * physical_dim * num_targets;
    int cols = physical_dim * system_order;
    Eigen::MatrixXd F_ = Eigen::MatrixXd::Zero(rows, cols);
    Eigen::MatrixXd Eye = Eigen::MatrixXd::Identity(cols, cols);

    for (int t = 0; t < num_targets; ++t) {
        // Each block gets a physical_dim position tuple and velocity tuple
        int row_offset = t * 2 * physical_dim;
        F_.block(row_offset, 0, 2 * physical_dim, cols) = Eye;
    }
    return F_;
  }

  // Placeholder for other cases (to be implemented later)
  return Eigen::MatrixXd::Zero(1, 1); // Temporary return for unsupported cases
}