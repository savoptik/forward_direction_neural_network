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
    std::vector<layer>& accessToLayers();
    std::vector<double>& accessToErrors();
    /**
     метод экспортирует сеть в заданную папку

     @param folderPath путь к папке
     */
    void exportNetwork(const std::string folderPath);
private:
    std::vector<layer> layers;
    std::vector<double> errors;
};

#endif /* network_hpp */
