//
//  network.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 22/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "network.hpp"
#include <fstream>
using namespace std;

std::vector<layer> &network::accessToLayers() { 
    return layers;
}

std::vector<double> &network::accessToErrors() { 
    return errors;
}

network::network(std::vector<int> &sizes, const int num, const int af, const double ap, const double bp) { 
    layers.push_back(layer(sizes[0], num, af, ap, bp));
    for (int i = 1; i < sizes.size(); i++) {
        layers.push_back(layer(sizes[i], layers[i-1].accessToTheNeuronVector().size(), af, ap, bp));
    }
}

void network::exportNetwork(const std::string folderPath) { 
    fstream f;
    f.open(folderPath+"network", ios::out);
    for (int i  = 0; i < layers.size(); i++) {
        f << layers[i].accessToTheNeuronVector().size();
        f << layers[i].accessToTheNeuronVector()[0].getVectorOfWeights().size();
        for (int j = 0; j < layers[i].accessToTheNeuronVector().size(); j++) {
            for (int k = 0; k < layers[i].accessToTheNeuronVector()[j].getVectorOfWeights().size(); k++) {
                f << layers[i].accessToTheNeuronVector()[j].getVectorOfWeights()[k];
            }
        }
        f << endl;
    }
    f.close();
}

network::network(const std::string filePath) { 
    vector<vector<double>> vectorOfMatrixOfWeights;
    vector<vector<int>> sizeis;
    ifstream f;
    f.open(filePath);
    while (f.good()) {
        vector<int> size(2);
        vector<double> values;
         f >> size[0];
        f >> size[1];
        values.resize(size[0] * size[1]);
        sizeis.push_back(size);
        for (int i = 0; i << size[0] * size[1]; i++) {
            double t;
            f >> t;
            values[i] = t;
        }
        vectorOfMatrixOfWeights.push_back(values);
    }
    f.close();
    layers.resize(vectorOfMatrixOfWeights.size());
    for (int i = 0; i < layers.size(); i++) {
        for (int j = 0; j < vectorOfMatrixOfWeights[i].size(); j+=sizeis[i][1]) {
            vector<double> part(vectorOfMatrixOfWeights[i].begin() + j, vectorOfMatrixOfWeights[i].begin() + j + sizeis[i][1]);
            layers[i].accessToTheNeuronVector().push_back(neuron(part));
        }
        layers[i].toRebuildThePointers();
    }
}

