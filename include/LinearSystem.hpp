#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include <Eigen/Dense>
#include <vector>
#include <string>
#include "StateTransitionMatrix.hpp"

/**
 * @class LinearSystem
 * @brief Build a linear system. 
 * 
 */
class LinearSystem {
public:
    /**
     * @brief Constructor for the LinearSystem class.
     * 
     * @param num_targets Number of targets in the system.
     * @param physical_dim Number of physical dimensions (default is 1).
     * @param system_order Order of the system dynamics (default is 1).
     * @param observe_rates True if rates are observed (default is false).
     * @param equate_targets True if all targets share a common bias (default is false).
     */
    LinearSystem(
        int num_targets, 
        int physical_dim = 1, int system_order = 1,  
        bool observe_rates = false, bool equate_targets = false
    );

    /**
     * @brief Set the state transition matrix S based on the physical 
     * dimensions, system order, number of targets, and time step.
     * 
     * @param dt Time step for the state transition matrix.
     */
    void setStateTransMat(double dt);

    // Accessor methods 
    /**
     * @brief Get the length of the state vector for a single target.
     * @return int Length of the state vector for a single target.
     */
    int getTargetStateLen() const { return target_state_len; }
    
    /**
     * @brief Get the total length of the agglomerate state vector.
     * @return int Total length of the agglomerate state vector.
     */
    int getAgglomerateStateLen() const { return agglomerate_state_len; }


    int getNumTargets() const { return num_targets_; }
    int getPhysicalDim() const { return physical_dim_; }
    int getSystemOrder() const { return system_order_; }
    bool isObservingRates() const { return observe_rates_; }
    bool isEquatingTargets() const { return equate_targets_; }
    Eigen::MatrixXd getStateTransMatrix() const { return S; }

    
    
    // void setDesignMat();  // bias only 
    // void setProcessNoiseCovMat(double w);
    // void setObsNoiseCovMat(double sigma);
    // void setAprStateCovMat(double sig0);
    // void setAprStateVec(double x0);

    // Methods for adding features to the deign matrix 
    // void addFeature(const Feature& feature); // Accepts any derived Feature class

    // Methods for whitening the system 

    // Prints

    // Get mapping
    
    private:

    // Definitional parameters supplied by the user

    /**
     * @brief Number of targets in the system.
     */
    int num_targets_;

    /**
     * @brief Number of physical dimensions (e.g., 3 for x, y, z).
     */
    int physical_dim_;

    /**
     * @brief Order of the system dynamics (1 for position, 2 for position 
     * and velocity).
     */
    int system_order_;

    /**
     * @brief True if rates (e.g., velocities) are observed.
     */
    bool observe_rates_;

    /**
     * @brief True if all targets share a common bias.
     */
    bool equate_targets_;

    // Derived parameters

    /**
     * @brief Length of the state vector for a single target.
     * 
     * Each target has a state vector with length equal to the physical 
     * dimensions times the order of the system dynamics.
     */
    int target_state_len;

    /**
     * @brief Total length of the agglomerate state vector.
     * 
     * The total length of the agglomerate state vector is equal to the 
     * number of targets times the length of each target state vector.
     */
    int agglomerate_state_len;

    /**
     * @brief Scope of the observation vector.
     * 
     * `obs_scope` equals 3 if observing position only (x, y, z), 
     * or 6 if observing position and velocity (x, y, z, u, v, w).
     */
    int obs_scope;

    /**
     * @brief Length of the observation vector.
     * 
     * The length of an observation vector is nominally equal to the physical 
     * dimensions of the system times the number of dimensions observed 
     * (scope), times the number of targets. For example, for a 3-dimensional 
     * physical system, observing the positions of 2 targets results in an 
     * observation vector of length 6. For batch linear regression, 
     * equate_targets is set to true so the number of targets defines the 
     * number of data points, treated as redundant measurements of the same 
     * target variable.  
     */
    int obs_len;

    // System matrices

    /**
     * @brief State transition matrix.
     */
    Eigen::MatrixXd S;

    /**
     * @brief Design matrix (features).
     */
    Eigen::MatrixXd F;

    /**
     * @brief Process noise covariance matrix.
     */
    Eigen::MatrixXd Q;

    /**
     * @brief Measurement noise covariance matrix.
     */
    Eigen::MatrixXd R;

    /**
     * @brief A priori state covariance matrix.
     */
    Eigen::MatrixXd P;

    /**
     * @brief A priori state estimate vector.
     */
    Eigen::VectorXd x;
};

#endif // LINEARSYSTEM_HPP