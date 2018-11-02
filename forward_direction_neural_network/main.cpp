//
//  main.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 08/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include <iostream>
#include "parametrsStorage/parametrsStorage.hpp"
#include "network/network.hpp"

int main(int argc, const char * argv[]) {
    parametrsStorage ps(argc, argv);
    if (ps.operatingMode() == 0) {
        return 0;
    }
    if ((ps.operatingMode() == 1)) {
        std::vector<std::vector<double>> sample;
        std::vector<double> response;
        sample.push_back({0.01, 0.25}); response.push_back(0);
        sample.push_back({0.7, 0.33}); response.push_back(1);
        sample.push_back({0.25, 0.4}); response.push_back(0);
        sample.push_back({0.1, 0.8}); response.push_back(1);
        sample.push_back({0.2, 0.7}); response.push_back(1);
        sample.push_back({0.8, 0.75}); response.push_back(0);
        sample.push_back({0, 0.93}); response.push_back(1);
        sample.push_back({0.49, 0.55}); response.push_back(1);
        sample.push_back({0.2, 0.37}); response.push_back(0);
        sample.push_back({0.47, 0.23}); response.push_back(0);
        ps.getNumberOfNeuronsInHiddenLayers().push_back(ps.getNumberOfClassesInTheOutputLayer());
        network net(ps.getNumberOfNeuronsInHiddenLayers(), sample[0].size(), ps.getActivationFunction(), ps.getParametersOfTheActivationFunction()[0], ps.getParametersOfTheActivationFunction()[1]);
        net.exportNetwork(ps.getSavePath());
    }
    return 0;
}
