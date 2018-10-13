//
//  neuron.cpp
//  forward_direction_neural_network
//
//  Created by Admin on 11/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "neuron.hpp"
#include <random>
#include <ctime>
using namespace std;

double neuron::getOutputValue() { 
    return outputValue;
}

double neuron::getLocalGradient() { 
    return localGradient;
}

int neuron::getActivationFunction() { 
    return activationFunction;
}

std::vector<double> &neuron::getVectorOfWeights() { 
    return vectorOfWeights;
}

neuron::neuron(std::vector<double> &inputSignalVector, const int acFunc) {
    activationFunction = acFunc;
    mt19937_64 gen(static_cast<int>(time(0)));
    uniform_real_distribution<> urd(-8.0, 8.0);
    inSignal = inputSignalVector;
    vectorOfWeights.resize(inSignal.size());
    for (int i = 0; i < vectorOfWeights.size(); i++) {
        vectorOfWeights[i] = urd(gen);
    }
}

std::vector<double> &neuron::getInputVector() { 
    return inSignal;
}
