//
//  network.hpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 22/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#ifndef network_hpp
#define network_hpp

#include <iostream>
#include "./layer/layer.hpp"

class network {
public:
    network(std::vector<int>& sizes, const int num, const int af, const double ap, const double bp=0);
    network(const std::string filePath);
    /**
     Доступ к вектору слоёв

     @return ссылку на верктор слоёв
     */
    std::vector<layer>& accessToLayers();
    /**
     Доступ к вектору ошибок

     @return ссылку на вектор ошибок
     */
    std::vector<double>& accessToErrors();
    /**
     метод экспортирует сеть в заданную папку

     @param folderPath путь к папке
     */
    void exportNetwork(const std::string folderPath);
    void directPropagation(std::vector<double> &inputSignal);
private:
    void backPropagation(std::vector<double> &responseVector, const double lg);
    std::vector<layer> layers;
    std::vector<double> errors;
};

#endif /* network_hpp */
