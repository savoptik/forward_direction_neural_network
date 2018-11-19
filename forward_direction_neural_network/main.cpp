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
#include "mnist-master/include/mnist/mnist_reader.hpp"
#include "mnist-master/include/mnist/mnist_utils.hpp"

int main(int argc, const char * argv[]) {
    parametrsStorage ps(argc, argv); // разбираем аргументы коммандной строки
    if (ps.operatingMode() == 0) { // если режим работы нулевой
        return 0; // выходим
    }
    if ((ps.operatingMode() == 1)) { // если режим работы 1
        std::cout << "Читаю базу МНИСТ…\n";
        auto ds = mnist::read_dataset();
        mnist::binarize_dataset(ds);
        // преобразуем вектор откликов к виду, в котором еденица означает число
        std::vector<std::vector<double>> convertResponse;
        convertResponse.resize(ds.training_labels.size()); // задаём размер
        for (long i = 0; i < convertResponse.size(); i++) { // обходим вектор
            convertResponse[i].resize(10); // задаём размер
            convertResponse[i][static_cast<int>(ds.training_labels[i])] = 1; // записываем на соответствующую позицию единицу
        }
        std::vector<std::vector<double>> trainData;
        for (int i  = 0; i < trainData.size(); i++) {
            trainData.resize(ds.training_images.size());
            for (int j = 0; j < trainData[i].size(); j++) {
                trainData[i][j] = static_cast<double>(ds.training_images[i][j]);
            }
        }
        std::cout << "Готовлю сеть…\n";
        ps.getNumberOfNeuronsInHiddenLayers().push_back(ps.getNumberOfClassesInTheOutputLayer()); // добавляем в количества нейронов скрытых слоёв количество нейронов на последнем слое
        network net(ps.getNumberOfNeuronsInHiddenLayers(), static_cast<int>(ds.training_images[0].size()), ps.getActivationFunction(), ps.getParametersOfTheActivationFunction()[0], ps.getParametersOfTheActivationFunction()[1]); // создаём сеть
        std::cout << "Учусь…\n";
        net.train(trainData, convertResponse, 0.01, ps.getLearningRate(), 100); // тренируем сеть
        std::cout << "Вываливаю сеть на диск.\n";
        net.exportNetwork(ps.getSavePath()); // выгружаем сеть
        std::cout << "Всё!\n";
    }
    if (ps.operatingMode() == 2) {
        network net(ps.getInputPath());
    }
    return 0;
}
