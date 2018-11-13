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
    parametrsStorage ps(argc, argv); // разбираем аргументы коммандной строки
    if (ps.operatingMode() == 0) { // если режим работы нулевой
        return 0; // выходим
    }
    if ((ps.operatingMode() == 1)) { // если режим работы 1
        std::vector<std::vector<double>> sample; // вектор премеров
        std::vector<double> response; // вектор откликов
        // заполняем тестовыми примерами для решения задачи xor.
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
        // преобразуем вектор откликов к виду, в котором еденица означает число
        std::vector<std::vector<double>> convertResponse;
        convertResponse.resize(response.size()); // задаём размер
        for (long i = 0; i < response.size(); i++) { // обходим вектор
            convertResponse[i].resize(10); // задаём размер
            convertResponse[i][static_cast<int>(response[i])] = 1; // записываем на соответствующую позицию единицу
        }
        ps.getNumberOfNeuronsInHiddenLayers().push_back(ps.getNumberOfClassesInTheOutputLayer()); // добавляем в количества нейронов скрытых слоёв количество нейронов на последнем слое
        network net(ps.getNumberOfNeuronsInHiddenLayers(), static_cast<int>(sample[0].size()), ps.getActivationFunction(), ps.getParametersOfTheActivationFunction()[0], ps.getParametersOfTheActivationFunction()[1]); // создаём сеть
        net.train(sample, convertResponse, 100, ps.getLearningRate(), 100); // тренируем сеть
        net.exportNetwork(ps.getSavePath()); // выгружаем сеть
    }
    return 0;
}
