/* File:   LinearSystem.cpp
 * Author: Rick.Bennett
 * Created on March 23, 2025, 7:00 AM
 */
#include "LinearSystem.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>


/**
 * @file LinearSystem.cpp
 * @brief Build the matrices of a linear system 
 */


LinearSystem::LinearSystem(
    const int num_targets, 
    const int physical_dim, 
    const int system_order, 
    const bool observe_rates,
    const bool equate_targets
) : num_targets_(num_targets), 
    physical_dim_(physical_dim), 
    system_order_(system_order), 
    observe_rates_(observe_rates),
    equate_targets_(equate_targets) {

        // Validate input parameters
        if (observe_rates_ && system_order_ < 2) {
            throw std::invalid_argument(
                "observe_rates=true is only valid if system_order >= 2"
            );
        }
        if (system_order_ < 1) {
            throw std::invalid_argument(
                "system_order must be at least 1"
            );
        }
        // Compute derived parameters
        target_state_len = physical_dim_ * system_order_;
        agglomerate_state_len = target_state_len * num_targets_;
        obs_scope = observe_rates_ ? physical_dim_ * 2 : physical_dim_;
        obs_len = physical_dim_ * obs_scope * num_targets_;
        
}

void LinearSystem::setStateTransMat(double dt) {
    // Delegate creation of state transition to StateTransitionMatrix
    S = StateTransitionMatrix::create(
        physical_dim_, system_order_, num_targets_, dt
    );
}


