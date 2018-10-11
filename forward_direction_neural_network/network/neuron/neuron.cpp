//
//  neuron.cpp
//  forward_direction_neural_network
//
//  Created by Admin on 11/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "neuron.hpp"
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
