#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include <Eigen/Dense>
#include <vector>
#include <string>
#include "StateTransitionMatrix.hpp"
#include "DesignMatrix.hpp"

/**
 * @class LinearSystem
 * @brief Build a linear system.
 *
 */
class LinearSystem
{
public:
  /**
   * @brief Constructor for the LinearSystem class.
   *
   * @param num_targets Number of targets
   * @param physical_dim Number of physical dimensions
   * @param system_order Dynamical system 
   * @param observe_rates True if rates are observed
   * @param equate_targets True if targets share a common bias
   */
  LinearSystem(int num_targets, int physical_dim = 1, int system_order = 1,
               bool observe_rates = false, bool equate_targets = false);
  
  void setStateTransMat(double dt);
  Eigen::MatrixXd getStateTransMat() const;
  
  void setDesignMat();
  Eigen::MatrixXd getDesignMat() const;

  void setProcessNoiseCov(double noise_level);
  void setProcessNoiseCov(const Eigen::MatrixXd& Q);
  Eigen::MatrixXd getProcessNoiseCov() const;

  // void setObsNoiseCovMat(double sigma);
  // void setAprStateCovMat(double sig0);
  // void setAprStateVec(double x0);


  int getTargetStateLen() const { return target_state_len; }
  int getAgglomerateStateLen() const { return agglomerate_state_len; }
  int getNumTargets() const;
  int getObsScope() const;
  int getPhysicalDim() const;
  int getSystemOrder() const;
  bool isObservingRates() const;
  bool isEquatingTargets() const;
  

  // Member functions
  //
  /**
   * extend the design matrix
   */
  // void addFeature(const Feature& feature); // Accepts any derived Feature class

  /**
   * Whiten the system
   */

  // Prints

  // Index maps

private:
  
  int num_targets_;     // Number of targets
  int physical_dim_;    // Number of physical dimensions 
  int system_order_;    // System order 
  bool observe_rates_;  // True if rates are observed
  bool equate_targets_; // True if targets share a common bias 

  int target_state_len;      // State vector length per target 
  int agglomerate_state_len; // Total state vector length
  int obs_scope;             // e.g., 3 (x, y, x), or 6 (x, y, z, u, v, w)
  
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

  Eigen::MatrixXd S; // State transition
  Eigen::MatrixXd F; // Design (features) matrix
  Eigen::MatrixXd Q; // Process noise covariance 
  Eigen::MatrixXd R; // Measurement noise covariance 
  Eigen::MatrixXd P; // State covariance 
  Eigen::VectorXd x; // state vector 

};

#endif // LINEARSYSTEM_HPP