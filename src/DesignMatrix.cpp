#include "DesignMatrix.hpp"

Eigen::MatrixXd DesignMatrix::create(
    int physical_dim, int system_order, int num_targets,
    bool equate_targets, bool observe_rates)
{

  if (!observe_rates && !equate_targets)
  {

    int target_len = num_targets * physical_dim;
    int state_len = num_targets * physical_dim * system_order;
    Eigen::MatrixXd F = Eigen::MatrixXd::Zero(target_len, state_len);
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(physical_dim, physical_dim);

    for (int t = 0; t < num_targets; ++t)
    {
      int row = t * physical_dim;
      int col = t * physical_dim * system_order;
      F.block(row, col, physical_dim, physical_dim) = I;
    }
    return F;

  }

  if (observe_rates && !equate_targets)
  {
    int state_len = system_order * physical_dim * num_targets;
    return Eigen::MatrixXd::Identity(state_len, state_len);

  }

  // Placeholder for other cases (to be implemented later)
  return Eigen::MatrixXd::Zero(1, 1); // Temporary return for unsupported cases
}