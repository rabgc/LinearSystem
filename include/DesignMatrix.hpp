#ifndef DESIGNMATRIX_HPP
#define DESIGNMATRIX_HPP

#include <Eigen/Dense>
#include <vector>
#include <memory>
#include "Feature.hpp"

class DesignMatrix
{
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
      bool equate_targets, bool observe_rates);

  // New: Construct from an initial matrix (e.g., bias features)
  DesignMatrix(const Eigen::MatrixXd& initial, bool equate_targets)
    : matrix_(initial), equate_targets_(equate_targets) {}

  // New: Add a feature (column) to the matrix
  void addFeature(const Feature& feature) {
    if (!equate_targets_) {
      throw std::logic_error("Feature addition only allowed when equate_targets=true.");
    }
    feature.addFeature(matrix_);
  }

  // New: Access the underlying matrix
  const Eigen::MatrixXd& getMatrix() const { return matrix_; }

private:
  Eigen::MatrixXd matrix_;
  bool equate_targets_;

};
#endif // DESIGNMATRIX_HPP