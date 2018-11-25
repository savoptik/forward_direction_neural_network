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

void convertingLabels(std::vector<u_char>& inLables, std::vector<std::vector<double>>& lables);
void imageConversion(std::vector<std::vector<u_char>>& charImages, std::vector<std::vector<double>>& outImages);
int theTransformationOfTheVectorOfOutputSignals(std::vector<double>& outputSignal);

int main(int argc, const char * argv[]) {
    parametrsStorage ps(argc, argv); // разбираем аргументы коммандной строки
    if (ps.operatingMode() == 0) { // если режим работы нулевой
        return 0; // выходим
    }
    if ((ps.operatingMode() == 1)) { // если режим работы 1
        std::cout << "Читаю базу МНИСТ…\n";
        auto ds = mnist::read_dataset();
    mnist::binarize_dataset(ds);
        std::cout << "прочитано " << ds.training_images.size() << " тренеровочных примеров, " << ds.training_labels.size() << " меток, " << ds.test_images.size() << " тестовых примеров и " << ds.test_labels.size() << " меток.\n";
        std::vector<std::vector<double>> convertResponse;
        std::vector<std::vector<double>> trainData;
        imageConversion(ds.training_images, trainData);
        convertingLabels(ds.training_labels, convertResponse);
        std::cout << "После преобразования " << trainData.size() << " примеров и " << convertResponse.size() << " меток.\n";
        std::cout << "Готовлю сеть…\n";
        ps.getNumberOfNeuronsInHiddenLayers().push_back(ps.getNumberOfClassesInTheOutputLayer()); // добавляем в количества нейронов скрытых слоёв количество нейронов на последнем слое
        network net(ps.getNumberOfNeuronsInHiddenLayers(), static_cast<int>(ds.training_images[0].size()), ps.getActivationFunction(), ps.getParametersOfTheActivationFunction()[0], ps.getParametersOfTheActivationFunction()[1]); // создаём сеть
        std::cout << "Учусь…\n";
        net.train(trainData, convertResponse, 0.1, ps.getLearningRate(), 100); // тренируем сеть
        std::cout << "Вываливаю сеть на диск.\n";
        net.exportNetwork(ps.getSavePath()); // выгружаем сеть
        std::cout << "Всё!\n";
    }
    if (ps.operatingMode() == 2) {
        network net(ps.getInputPath());
    }
    return 0;
}

void convertingLabels(std::vector<u_char>& inLables, std::vector<std::vector<double>>& lables) {
        // преобразуем вектор откликов к виду, в котором еденица означает число
    lables.resize(inLables.size());
    for (long i = 0; i < lables.size(); i++) { // обходим вектор
        lables[i].resize(10); // задаём размер
        lables[i][static_cast<int>(inLables[i])] = 1; // записываем на соответствующую позицию единицу
    }
}

void imageConversion(std::vector<std::vector<u_char>>& charImages, std::vector<std::vector<double>>& outImages) {
    outImages.resize(charImages.size());
    for (int i  = 0; i < outImages.size(); i++) {
        outImages[i].resize(charImages[i].size());
        for (int j = 0; j < outImages[i].size(); j++) {
            outImages[i][j] = static_cast<double>(charImages[i][j]);
        }
    }
}

int theTransformationOfTheVectorOfOutputSignals(std::vector<double>& outputSignal) {
    int result = 0;
    double max = 0;
    for (int i = 0; i < outputSignal.size(); i++) {
        if (outputSignal[i] > max) {
            max = outputSignal[i];
            result = i;
        }
        }
        return result;
}
