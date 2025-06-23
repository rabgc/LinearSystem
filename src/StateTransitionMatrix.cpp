// StateTransitionMatrix.cpp
#include "StateTransitionMatrix.hpp"
#include <Eigen/Dense>
#include <iostream>

Eigen::MatrixXd StateTransitionMatrix::create(
    int physical_dim, int system_order, int num_targets, double dt)
{
  int target_state_len = physical_dim * system_order;
  int agglomerate_state_len = target_state_len * num_targets;

  // Initialize the state transition matrix S as a zero matrix
  Eigen::MatrixXd S =
      Eigen::MatrixXd::Zero(agglomerate_state_len, agglomerate_state_len);

  // Build the block matrix for a single target
  Eigen::MatrixXd A =
      Eigen::MatrixXd::Zero(target_state_len, target_state_len);

  // Fill the dynamics matrix A based on system_order
  for (int i = 0; i < system_order; ++i)
  {
    if (i + 1 < system_order)
    {
      A.block(i * physical_dim, (i + 1) * physical_dim,
              physical_dim, physical_dim) =
          dt * Eigen::MatrixXd::Identity(physical_dim, physical_dim);
    }
  }

  // Compute the matrix exponential using a truncated Taylor series
  Eigen::MatrixXd expA =
      Eigen::MatrixXd::Identity(target_state_len, target_state_len);
  Eigen::MatrixXd currentPower =
      Eigen::MatrixXd::Identity(target_state_len, target_state_len);

  for (int k = 1; k <= system_order + 1; ++k)
  {
    currentPower = currentPower * A / k; // Compute A^k / k!
    expA += currentPower;                // Add the term to the series
  }

  // Populate the full state transition matrix S for all targets
  for (int i = 0; i < num_targets; ++i)
  {
    int idx = i * target_state_len;
    S.block(idx, idx, target_state_len, target_state_len) = expA;
  }

  return S;
}
