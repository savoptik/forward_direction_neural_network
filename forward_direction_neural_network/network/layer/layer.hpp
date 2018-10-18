//
//  layer.hpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 18/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#ifndef layer_hpp
#define layer_hpp

#include <stdio.h>
#include "../neuron/neuron.hpp"

class example {
public:
    example() {} // конструктор бес параметров
    example(const int number, const int size, const int af, const int a, const int b = 0); // конструктор, принимающий количество нейронов, которые нужно создать для этого примера, и создающий это количество неййронов.
    /**
     Доступ к вектору нейронов

     @return ссылку на вектор нейронов
     */
    std::vector<neuron>& accessToTheNeuronVector();
    /**
     доступ к вектору выходных значений

     @return ссылку на вектор выходных значений
     */
    std::vector<double*>& AccessToTheOutputVector();
    /**
     Доступ к вектору локальных градиентов

     @return ссылку на вектор локальных градиентов
     */
    std::vector<double*>& accessToTheLocalGradientVector();
    /**
     Доступ к вектору ошибок

     @return ссылку на вектор ошибок
     */
    std::vector<double*>& AccessToTheErrorVector();
    /**
     Получить ошибку слоя

     @return ошибку
     */
    double getError();
private:
    std::vector<neuron> neurons; // набор нейронов
    std::vector<double *> outputValues; // вектор указателй на выходные значения
    std::vector<double *> localGradients; // вектор указателей на локальные градиенты
    std::vector<double *> errors; // вектор указателей на компоненты вектора ошибок.
    double error; // Ошибка
};

#endif /* layer_hpp */
