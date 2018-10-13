//
//  neuron.hpp
//  forward_direction_neural_network
//
//  Created by Admin on 11/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#ifndef neuron_hpp
#define neuron_hpp

#include <stdio.h>
#include <vector>

class neuron {
public:
    neuron() {}
    neuron(std::vector<double>& inputSignalVector, const int acFunc);
    /**
     вектор весов

     @return ссылку на вектор весов
     */
    std::vector<double>& getVectorOfWeights();
    /**
     номер функции активации для этого нейрона

     @return номер функции активации
     */
    int getActivationFunction();
    /**
     локальный градиент

     @return локальный градиент
     */
    double getLocalGradient();
    /**
     выходное значение

     @return выходное значение
     */
    double getOutputValue();
    std::vector<double>& getInputVector();
private:
    std::vector<double> vectorOfWeights; // вектор весов
    std::vector<double> inSignal;
    int activationFunction; // номер функции активации
    double localGradient; // локальный градиент
    double outputValue; // выходное значение
};

#endif /* neuron_hpp */
