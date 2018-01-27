//
// Created by Maximilian Franz on 07.01.18.
//

#include "ReLUActivationLayer.h"


ReLUActivationLayer::ReLUActivationLayer(std::vector<int> &inputDimension) : ActivationLayer(inputDimension) {
    this->type = ACTIVATION_RELU;
    this->outputDimensions = calcOutputDimensions();
    init(); // TODO never call virtual functions in constructor

}
