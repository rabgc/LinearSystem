// StateTransitionMatrix.cpp
#include "StateTransitionMatrix.hpp"

Eigen::MatrixXd StateTransitionMatrix::create(
    int physical_dim, int system_order, int num_targets, double dt
    ) {
    
    int target_state_len = physical_dim * system_order;
    int agglomerate_state_len = target_state_len * num_targets;

    Eigen::MatrixXd Seye = Eigen::MatrixXd::Identity(physical_dim, physical_dim);
    Eigen::MatrixXd S = Eigen::MatrixXd::Zero(agglomerate_state_len, agglomerate_state_len);

    for (int i = 0; i < num_targets; i++) {
        int idx = i * target_state_len;

        // Set identity for positions
        S.block(idx, idx, physical_dim, physical_dim) = Seye;

        // Set rate terms (position depends on velocity, scaled by dt)
        if (system_order == 2) {
            S.block(idx, idx + physical_dim, physical_dim, physical_dim) = dt * Seye;
        }

        // Set identity for velocities
        S.block(idx + physical_dim, idx + physical_dim, physical_dim, physical_dim) = Seye;
    }

    return S;
}