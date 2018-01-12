//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "Layer.h"

class LossLayer : Layer{
protected:
    LayerFunction* function;
public:
    void forward(DataWrapper &input, DataWrapper &output) override;

};

