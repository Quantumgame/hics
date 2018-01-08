//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "WeightWrapper.h"

class WeightLoader {
    enum class LayerIdentifier {
        CONV_1 = 0,
        CONV_2 = 1,
        CONV_3 = 2,
        CONV_4 = 3,
        CONV_5 = 4,
        FULLY_CON_1 = 10000,
        FULLY_CON_2 = 10001,
        FULLY_CON_3 = 10002
    };

private:

public:
    virtual WeightWrapper getWeights(LayerIdentifier layerId);
};
