// RateFeature.hpp
#ifndef RATEFEATURE_HPP
#define RATEFEATURE_HPP

#include "Feature.hpp"
#include <Eigen/Dense>
#include <stdexcept>


class RateFeature : public Feature
{
public:
  void setEpochs(const Eigen::VectorXd& epochs) { obs_epoch_ = epochs; }
  void setPhysicalDim(int physical_dim) { physical_dim_ = physical_dim; }

  void addFeature(Eigen::MatrixXd &designMatrix) const override
  {
    if (physical_dim_ <= 0)
      throw std::logic_error("physical_dim must be set in RateFeature.");
    int rows = designMatrix.rows();
    int num_targets = rows / physical_dim_;
    if (obs_epoch_.size() != num_targets)
      throw std::logic_error("obs_epoch size must match number of targets.");

    Eigen::VectorXd delta = obs_epoch_ - Eigen::VectorXd::Constant(num_targets, obs_epoch_[0]);
    // Add one rate column per coordinate
    for (int d = 0; d < physical_dim_; ++d) {
      designMatrix.conservativeResize(rows, designMatrix.cols() + 1);
      for (int t = 0; t < num_targets; ++t) {
        int row = t * physical_dim_ + d;
        designMatrix(row, designMatrix.cols() - 1) = delta[t];
      }
    }
  }

private:
  Eigen::VectorXd obs_epoch_;
  int physical_dim_ = 0;
};

#endif // RATEFEATURE_HPP