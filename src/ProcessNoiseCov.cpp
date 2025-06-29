#include "ProcessNoiseCov.hpp"
#include <Eigen/Dense>

Eigen::MatrixXd ProcessNoiseCov::create(int idim, double noise_level)
{
  Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(idim, idim) * noise_level;
  
  return Q;
}