//
//  layer.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 18/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "layer.hpp"
using namespace std;

double example::getError() { 
    return error;
}

std::vector<double *> &example::AccessToTheErrorVector() { 
    return errors;
}

std::vector<double *> &example::accessToTheLocalGradientVector() { 
    return localGradients;
}

std::vector<double *> &example::AccessToTheOutputVector() { 
    return outputValues;
}

std::vector<neuron> &example::accessToTheNeuronVector() { 
    return neurons;
}

example::example(const int number, const int size, const int af, const int a, const int b) {
    for (int i = 0; i < number; i++) {
        neurons.push_back(neuron(size, af, a, b));
    }
    outputValues.resize(neurons.size());
    localGradients.resize(neurons.size());
    
    for (int i = 0; i < outputValues.size(); i++) {
        outputValues[i] = &neurons[i].getOutputValue();
        localGradients[i] = &neurons[i].getLocalGradient();
        errors[i] = &neurons[i].getE();
    }
}
