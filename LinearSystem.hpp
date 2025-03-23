#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include <Eigen/Dense>
#include <vector>
#include <string>

/**
 * @class LinearSystem
 * @brief Build a linear system, including standard design, state 
 * transition, and control input matrices. The mapping between features 
 * and targets is tracked for each matrix. 
 * 
 * The design matrix is instantiated as a biasonly, representing either the
 * state position or state posiiton and velocity, but additional features 
 * columns may be added to the design matrix which may be global or target 
 * specific.
 */
class LinearSystem {
public:
    // Constructorx
    LinearSystem(
        int physical_dim, int system_order, 
        int num_targets, bool observe_rates = false
    );

    // Methods to set matrices
    void SetStateTransMatrix(double dt);
    void SetDesignMatrix();  // bias only 

    void SetProcessNoiseCovMatrix(double w);
    void SetMeasurementNoiseCovMatrix(double sigma);
    
    void SetAPrioriStateCovMatrix(double sig0);
    void SetAPrioriStateEstimate(double x0);

    // Add features to the deign matrix 

    // Prints
    void PrintStateTransMatrix() const;
    void PrintDesignMatrix() const;
    void PrintProcessNoiseCovMatrix() const;
    void PrintMeasurementNoiseCovMatrix() const;
    void PrintAPrioriStateCovMatrix() const;
    void PrintAPrioriStateEstimate() const;

    void PrintStateToTargetMap() const;
    void PrintTargetToStateMap() const;
    void PrintObsToTargetMap() const;
    void PrintTargetToObsMap() const;
    void PrintObsToStateMap() const;
    void PrintStateToObsMap() const;

private:
    
    // Definitional parameters supplied by user
    int physical_dim_;          // Number of physical dims (e.g., 3 for x, y, z)
    int system_order_;          // Order of the system dynamics (1 or 2)
    int num_targets_;           // Number of targets in the system
    bool observe_rates_;        // True if rates are observed 

    // Derived parameters
    int agglomerate_state_len_; // Total length of the state vector
    int target_state_len_;      // Length of state vector for single target
    int obs_scope_;             // Scope of obs (1 for pos, 2 for pos and vel)
    int obs_len_;               // Length of the obs vector

    // System matrices
    Eigen::MatrixXd S;         // State transition matrix
    Eigen::MatrixXd F;         // Design matrix (features)
    Eigen::MatrixXd Q;         // Process noise covariance
    Eigen::MatrixXd R;         // Measurement noise covariance
    Eigen::MatrixXd P;         // A priori state covariance
    Eigen::VectorXd x;         // A priori state estimate

    // Parameter maps
    std::vector<std::string> StateToTargetMap; 
    std::vector<std::string> TargetToStateMap;
    std::vector<std::string> ObsToTargetMap;
    std::vector<std::string> TargetToObsMap;
    std::vector<std::string> ObsToStateMap;
    std::vector<std::string> StateToObsMap;
    
};

#endif // LINEARSYSTEM_HPP