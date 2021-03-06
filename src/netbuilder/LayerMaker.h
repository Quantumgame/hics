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

#include <layers/naive/InputLayer.h>
#include <layers/weightlayers/ConvolutionLayer.h>
#include <layers/functionlayers/MaxPoolingLayer.h>
#include <layers/functionlayers/LocalResponseNormLayer.h>
#include <layers/functionlayers/ReLUActivationLayer.h>
#include <layers/functionlayers/SoftMaxLossLayer.h>
#include <layers/weightlayers/FullyConnectedLayer.h>
#include "loader/ModelLoader.h"
#include "wrapper/WeightWrapper.h"



class LayerMaker {
private:

public:
    /**
     * Creates an input layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @return a pointer to a new InputLayer object
     */
    InputLayer* createInputLayer(LayerConstructionParams &lcp);

    /**
     * Creates a convolution layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     * @param weights a pointer to WeightWrapper object, that should be linked to the layer
     *
     * @return a pointer to a new ConvolutionLayer object
     */
    ConvolutionLayer* createConvLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims, WeightWrapper* weights);

    /**
     * Creates a max pooling layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new MaxPoolingLayer object
     */
    MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims);

    /**
     * Creates a local response normalization layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new LocalResponseNorm object
     */
    LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims);

    /**
     * Creates a rectified linear unit activation layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new ReLuActivationLayer object
     */
    ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims);

    /**
     * Creates a softmax loss layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new SoftmaxLossLayer object
     */
    SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims);

    /**
     * Creates a fully connected layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     * @param weights a pointer to WeightWrapper object, that should be linked to the layer
     *
     * @return a pointer to a new FCLayer object
     */
    FullyConnectedLayer* createFCLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims, WeightWrapper* weights);

};
