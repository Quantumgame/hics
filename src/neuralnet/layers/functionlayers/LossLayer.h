/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <layerfunctions/loss/LossFunction.h>
#include "layers/Layer.h"

class LossLayer : public Layer {
protected:
    LossFunction* function;
public:

    /**
     * Calculates the output dimensions of the layer given the inputDimensions of this instance and it's parameters.
     *
     * @return the Dimensions the output Wrapper has to have.
     */
    std::vector<int> calcOutputDimensions() override;

    /**
     * Triggers the computation of the forward propagation. Takes input from inputWrapper and writes to outputWrapper.
     * The Executor knows the size the output Wrapper needs by querying getOutputDimensions()
     */
    void forward() override;

    /**
     * Set the platform to be used to create the function that performs the computations of the layer.
     *
     * @param platform      The platform to be used as a LayerFunction factory.
     */
    void setPlatform(Platform *platform) override;

    /**
     * Returns an approximation of the number of necessary computations in this layer, which indicates the difficulty of this layer.
     *
     * @return long value: difficulty of this layer
     */
    int getDifficulty() override;
};

