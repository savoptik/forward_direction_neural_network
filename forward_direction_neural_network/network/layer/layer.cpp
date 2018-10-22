//
//  layer.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 18/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "layer.hpp"
#include <cmath>
using namespace std;

double layer::getError() { 
    return error;
}

std::vector<double *> &layer::AccessToTheErrorVector() { 
    return errors;
}

std::vector<double *> &layer::accessToTheLocalGradientVector() { 
    return localGradients;
}

std::vector<double *> &layer::AccessToTheOutputVector() { 
    return outputValues;
}

std::vector<neuron> &layer::accessToTheNeuronVector() { 
    return neurons;
}

layer::layer(const int number, const int size, const int af, const double a, const double b) {
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
    ap = a;
    bp = b;
}

void layer::toCalculateTheOutputValuesForTheCurrentLayer(layer &previousLayer) {
    for (int i = 0; i < neurons.size(); i++) {
        neurons[i].theCalculationOfTheOutputValue(previousLayer.AccessToTheOutputVector());
    }
}

void layer::calculateLocalGradientsForTheCurrentLayer(const double d) { 
    for (int i = 0; i < neurons.size(); i++) {
        neurons[i].theCalculationOfTheE(d);
        neurons[i].theCalculationOfTheLocalGradient();
    }
}

void layer::countTheWeightOnTheCurrentLayer(const double learningRate) { 
    for (int i = 0; i < neurons.size(); i++) {
        neurons[i].weightChangeCalculation(learningRate);
    }
}

void layer::calculateLocalGradientsForTheCurrentLayer(layer &previousLayer) { 
    for (int i = 0; i < localGradients.size(); i++) {
        double sum = 0;
        for (int k = 0; k < previousLayer.accessToTheLocalGradientVector().size(); k++) {
            sum += *previousLayer.accessToTheLocalGradientVector()[k] * neurons[i].getVectorOfWeights()[k];
        }
        switch (neurons[0].getActivationFunction()) {
            case 1:
                *localGradients[i] = Dlogistic(*outputValues[i], ap) * sum;
                break;
                
                case 2:
                *localGradients[i] = Didentiti(*outputValues[i], ap, bp) * sum;
                break;
                
                case 3:
                *localGradients[i] = DhyperbolicTangent(*outputValues[i]) * sum;
                break;
        }
    }
}

void layer::toCalculateTheError() {
    double sum = 0;
    for (int i = 0; i < errors.size(); i++) {
        sum += pow(*errors[i], 2);
    }
    error = sum / 2;
}
