//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include <wrapper/DataWrapper.h>
#include <wrapper/WeightWrapper.h>


enum LayerType {
    ACTIVATION_RELU,
    NORMALIZATION_LOCALRESPONSE,
    LOSS_SOFTMAX,
    POOLING_MAX,
    CONVOLUTION,
    FULLYCONNECTED,
    INPUT,
    CONCAT
};

/**
 * Abstract class Layer
 */
class Layer {
protected:

    Layer* previousLayer;
    Layer* nextLayer;
    bool computed;
    bool functionSet;

    std::string type;
    std::vector<int> inputDimensions;
    std::vector<int> outputDimensions;


public:
    /**
     * Dimension positions in the dimension vectors according to convention in 3D
     */
    const int D3_X_DIM = 2;
    const int D3_Y_DIM = 1;
    const int D3_Z_DIM = 0;


    /**
     * Computes the forward propagation given the input and writes results to the output!
     *
     * The Executor knows the size the output Wrapper needs by querying getOutputDimensions()
     *
     * @param input Wrapper holding the inputs to this layer
     * @param output Wrapper defining where to write the output.
     */
    virtual void forward(DataWrapper &input, DataWrapper &output) = 0;

    /**
     * Returns whether this Layer has been computed
     *
     * @return
     */
    virtual bool isComputed() = 0;

    /**
     * Sets the status of this Layer
     *
     * Is called from inside forward, when computation has worked succesfully.
     * TODO: Can this be private
     * @param status to which to set the layer
     * @return
     */
    virtual void setComputed(bool status) = 0;

    /**
     * Returns whether this Layer is ready to be computed.
     *
     * A Layer is ready iff the function has been set and previous layers are computed.
     *
     * @return
     */
    virtual bool readyToCompute() = 0;

    /**
     *
     * @return
     */
    virtual bool isLayerFunctionSet() = 0;

    /**
     * Resets the status of this layer, so that it can be reconfigured.
     */
    virtual void reset() = 0;

    /**
     * Initializes the default values of this layer
     *
     * This means: functionsSet is false
     *             computed is false
     *
     */
    virtual void init() = 0;

    /**
     * Set previous layer by giving a pointer
     *
     * @param previousLayer which to set as preceeding layer.
     */
    virtual void setPreviousLayer(Layer *previousLayer) = 0;

     /**
     * Set next layer by providing a pointer
     *
     * @param nextLayer which to append to this one.
     */
    virtual void setNextLayer(Layer *nextLayer) = 0;

    /**
     * Calculates the output dimensions of the layer given the inputDimensions of this instance and it's parameters.
     *
     * Different implementation for each layer type.
     *
     * @return the Dimensions the output Wrapper has to have.
     */
    virtual std::vector<int> calcOutputDimensions() = 0;

    /**
     * Returns the dimensions of the output wrapper.
     *
     * @return dimensions of the output Wrapper.
     */
    virtual std::vector<int> getOutputDimensions() = 0;

    virtual /**
     * Returns a pointer to the previous layer
     * @return a pointer to the previous layer.
     */
    Layer *getPreviousLayer() const;

    /**
     *
     * @return a pointer to the next Layer after this one.
     */
    Layer *getNextLayer() const;

    /**
     * Returns a string representation of the type of this layer.
     * @return string representation of the type.
     */
    const std::string &getType() const;

    /**
     *  Getter
     * @return dimensions of the inputWrapper to this
     */
    const std::vector<int> &getInputDimensions() const;

};

