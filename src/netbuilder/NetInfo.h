//
// Created by David Culley on 07.01.18.
//

#pragma once

#include <string>

class NetInfo {
private:

public:
    NetInfo(std::string name, int imageDimension);

    std::string getName();

    int getImageDimension();

    std::string getIdentifier();

};