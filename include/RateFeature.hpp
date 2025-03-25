// RateFeature.hpp
#ifndef RATEFEATURE_HPP
#define RATEFEATURE_HPP

#include "Feature.hpp"

class RateFeature : public Feature {
public:
    void addFeature(Eigen::MatrixXd& designMatrix) const override {
        // Logic to add velocity features to the design matrix
        // Example: Add a column for velocity
        Eigen::MatrixXd rateFeatures = Eigen::MatrixXd::Random(designMatrix.rows(), 1);
        designMatrix.conservativeResize(designMatrix.rows(), designMatrix.cols() + 1);
        designMatrix.col(designMatrix.cols() - 1) = rateFeatures;
    }
};

#endif // RATEFEATURE_HPP