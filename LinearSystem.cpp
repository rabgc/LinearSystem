/* File:   LinearSystem.cpp
 * Author: Rick.Bennett
 * Created on March 23, 2025, 7:00 AM
 */
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>

# TODO make a header file for this class
#include "LinearSystem.hpp"

/**
 * @file LinearSystem.cpp
 * @brief Build the matrices of a linear system 
 */


LinearSystem(
    const int physical_dim, 
    const int system_order, 
    const int num_targets, 
    const bool observe_rates = false
) : physical_dim_(physical_dim), 
    system_order_(system_order), 
    num_targets_(num_targets), 
    observe_rates_(observe_rates_) {
    
    /**
     * Each target has a state vector withlegnth equal to the physical 
     * dimensions times the order of the system dynamics.
     */
    target_state_len_ = physical_dim_ * system_order_;

    /** The total length of the agglomerate state vector is equal to the 
     * number of targets times the length of each target state vector.
     */
    agglomerate_state_len_ = target_state_len_ * num_targets_;

    /**
     * obs_scope equlas 1 if observing position only (x,y,z), 
     * or 2 if observing position and velocity (x,y,z,u,v,w).
     */
    obs_scope_ = observe_rates_ ? physical_dim_ * 2 : physical_dim_;

    /**
     * The length of an observation vector is nominally equal to the physical 
     * dimensions of the system times the number of dimensions observed 
     * (scope), times the number of targets, e.g., for a 3 dimensional 
     * physical system, observe the positions of 2 targets for an observation 
     * vector of length 6. 
     */
    obs_len_ = physical_dim_ * obs_scope_ * num_targets_;
    
    }

void SetStateTransitionMatrix(double dt) {
    /**
     * The structure of the state transition matrix depends on the physical 
     * dimensions, the order of the system dynamics, and the number of 
     * targets. It is a square matrix of size equal to the total length of the 
     * agglomerate state vector.
     */
    Eigen::MatrixXd Seye = Eigen::MatrixXd::Identity(
        physical_dim_, physical_dim_
    );
    Eigen::MatrixXd S = Eigen::MatrixXd::Zero(
        agglomerate_state_len_, agglomerate_state_len_
    );

    for (int i = 0; i < num_targets_; i++) {
        // Starting index for the current target's state in the agglomerate 
        //  state vector
        int idx = i * target_state_len_; // 0, 6, 12, ...

        // Set identity for positions (position depends on previous position)
        S.block(idx, idx, physical_dim_, physical_dim_) = Seye;

        // Set rate terms (position depends on velocity, scaled by dt)
        if (observe_rates_) {
            S.block(
                idx, idx + physical_dim_, physical_dim_, physical_dim_
            ) = dt * Seye;
        }

        // Set identity for velocities (velocity depends on previous velocity)
        S.block(
            idx + physical_dim_, 
            idx + physical_dim_, physical_dim_, physical_dim_
        ) = Seye;
    }
    std::cout << "State Transition Matrix S:\n" << S << std::endl;
}
