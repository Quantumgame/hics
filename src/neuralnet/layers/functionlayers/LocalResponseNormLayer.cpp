//
// Created by Maximilian Franz on 07.01.18.
//

#include "LocalResponseNormLayer.h"
#include "NotImplementedException.h"


LocalResponseNormLayer::LocalResponseNormLayer(std::vector<int> inputDimensions, float radius, float alpha, float beta,
                                               float bias)

        :
          radius(radius),
          alpha(alpha),
          beta(beta),
          bias(bias)
{
    this->inputDimensions = inputDimensions;
    this->outputDimensions = calcOutputDimensions();
    this->type = NORMALIZATION_LOCALRESPONSE;
    this->init();
}

float LocalResponseNormLayer::getRadius() const {
    return radius;
}

float LocalResponseNormLayer::getAlpha() const {
    return alpha;
}

float LocalResponseNormLayer::getBeta() const {
    return beta;
}

float LocalResponseNormLayer::getBias() const {
    return bias;
}

void LocalResponseNormLayer::setFunction(ResponseNormalizationFunction *function) {
    this->function = function;
    functionSet = true;
}

void LocalResponseNormLayer::forward() {
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, radius, alpha, beta, bias);
}
