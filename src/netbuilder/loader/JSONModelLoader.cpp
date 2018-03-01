//
// Created by Maximilian Franz on 07.01.18.
//

#include "JSONModelLoader.h"
#include <fstream>


JSONModelLoader::JSONModelLoader(string path) : ModelLoader(path){
    this->init();
}

void JSONModelLoader::init() {
    //loads the json File as a string
    std::ifstream jsonFile(this->pathToJSON);
    std::ostringstream tmp;
    tmp<<jsonFile.rdbuf();
    std::string jsonString = tmp.str();

    this->model = json::parse(jsonString);
    this->layers = model["layers"];
}

string JSONModelLoader::getNetWorkName() {
    return ModelLoader::model["name"];
}

string JSONModelLoader::getNetWorkID() {
    return model["identifier"];
}

int JSONModelLoader::getRequiredDimension() {
    return model["requiredDimension"][1];
}

string JSONModelLoader::getLayerTypeByIndex(int index) {
    return layers[index]["layerType"];
}

/**
 * Creates the LayerConstructionParams struct with the parameters, that are retrieved from a json neural net
 * description file.
 *
 * @param index the index of the layer the LayerConstructionParams struct is to be created for
 * @return the LayerConstructionParams struct which contains all the needed information for layer creation
 */
LayerConstructionParams JSONModelLoader::getLayerConstructionParamsByIndex(int index) {
    json currentLayer = getLayerJSON(index);
    LayerConstructionParams lp;
    lp.type = currentLayer["layerType"];
    if (currentLayer.count("activationFct") != 0)
        lp.actFctType = currentLayer["activationFct"];

    if (currentLayer.count("inputSize") != 0)
        lp.inputSize = currentLayer["inputSize"];

    if (currentLayer.count("inputChannels") != 0)
        lp.inputChannels = currentLayer["inputChannels"];

    if (currentLayer.count("filterSize") != 0)
        lp.filterSize = currentLayer["filterSize"];

    if (currentLayer.count("kernels") != 0)
        lp.numFilters = currentLayer["kernels"];

    if (currentLayer.count("stride") != 0)
        lp.stride = currentLayer["stride"];

    if (currentLayer.count("padding") != 0)
        lp.paddingSize = currentLayer["padding"];

    if (currentLayer.count("outputSize") != 0)
        lp.outputSize = currentLayer["outputSize"];

    if (currentLayer.count("params") != 0)
        lp.normParams = currentLayer["params"];

    if (currentLayer.count("numGroups") != 0)
        lp.numGroups = currentLayer["numGroups"];

    return lp;
}

json JSONModelLoader::getLayerJSON(int index) {
    return layers[index];
}

bool JSONModelLoader::isValid() {
    if (model.count("name") == 0) {
        return false;
    }
    else if (model.count("identifier") == 0) {
        return false;
    }
    else if (model.count("requiredDimension") == 0) {
        return false;
    }
    else if (model.count("layers") == 0) {
        return false;
    }
    else {
        return true;
    }
}
