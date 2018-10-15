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
#include <cmath>
using namespace std;

double& neuron::getOutputValue() {
    return outputValue;
}

double& neuron::getLocalGradient() {
    return localGradient;
}

int neuron::getActivationFunction() { 
    return activationFunction;
}

std::vector<double> &neuron::getVectorOfWeights() { 
    return vectorOfWeights;
}

neuron::neuron(int size, const int acFunc, const double afa, const double afb) {
    activationFunction = acFunc;
    mt19937_64 gen(static_cast<int>(time(0)));
    uniform_real_distribution<> urd(-0.8, 0.8);
    inSignal.resize(size);
    vectorOfWeights.resize(size);
    for (int i = 0; i < vectorOfWeights.size(); i++) {
        vectorOfWeights[i] = urd(gen);
    }
    a = afa;
    b = afb;
}

std::vector<double> &neuron::getInputVector() { 
    return inSignal;
}

void neuron::theCalculationOfTheOutputValue(std::vector<double> &signal) {
    inSignal.resize(signal.size());
    for (int i = 0; i < inSignal.size(); i++) {
        inSignal[i] = signal[i];
    }
    for (int i = 0; i < inSignal.size(); i++) {
        outputValue += inSignal[i] * vectorOfWeights[i];
    }
    switch (activationFunction) {
        case 1:
            outputValue = logistic(outputValue, a);
            break;
            
            case 2:
            outputValue = identiti(outputValue, a, b);
            break;
            
            case 3:
            outputValue = hyperbolicTangent(outputValue, a, b);
            break;
    }
}

double& neuron::getE() {
    return e;
}

double& neuron::theCalculationOfTheE(const double d) {
    e = d - outputValue;
    return e;
}

double &neuron::theCalculationOfTheLocalGradient() { 
    switch (activationFunction) {
        case 1:
            localGradient = e = Dlogistic(outputValue, a);
            break;
            
            case 2:
            localGradient = e * Didentiti(outputValue, a, b);
            break;
            
            case 3:
            localGradient = e * DhyperbolicTangent(outputValue, a, b);
            break;
    }
    return localGradient;
}




double logistic(double x, double a, double b) {
    return b * (1 / 1 + exp(-a * x));
}

double Dlogistic(double y, double a, double b) {
    return a * b * y * (1 - y);
}

double identiti(double x, double a, double b) {
    return a * x + b;
}

double Didentiti(double y, double a, double b) {
    return a;
}

double hyperbolicTangent(double x, double a, double b) {
    return a * ((exp(b * x) - exp(-b * x))/(exp(b * x) + exp(-b * x)));
}

double DhyperbolicTangent(double y, double a, double b) {
    return double(b / a) * ((a - y) * (a + y));
}
