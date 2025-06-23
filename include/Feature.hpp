#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <Eigen/Dense>

class Feature
{
public:
  virtual ~Feature() = default;

  // Pure virtual method to add features to the design matrix
  virtual void addFeature(Eigen::MatrixXd &designMatrix) const = 0;
};

#endif // FEATURE_HPP