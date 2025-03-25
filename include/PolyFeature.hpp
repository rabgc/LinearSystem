// PolyFeature.hpp
#ifndef POLYFEATURE_HPP
#define POLYFEATURE_HPP

#include "Feature.hpp"

class PolyFeature : public Feature {
public:
    PolyFeature(int order) : order_(order) {}

    void addFeature(Eigen::MatrixXd& designMatrix) const override {
        // Logic to add polynomial features to the design matrix
        // Example: Add columns for polynomial terms
        for (int i = 1; i <= order_; ++i) {
            Eigen::MatrixXd polyFeatures = designMatrix.array().pow(i);
            designMatrix.conservativeResize(designMatrix.rows(), designMatrix.cols() + 1);
            designMatrix.col(designMatrix.cols() - 1) = polyFeatures.col(0);
        }
    }

private:
    int order_;
};

#endif // POLYFEATURE_HPP