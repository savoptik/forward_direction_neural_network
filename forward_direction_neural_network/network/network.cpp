//
//  network.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 22/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "network.hpp"
#include <fstream>
using namespace std;

std::vector<layer> &network::accessToLayers() { 
    return layers;
}

std::vector<double> &network::accessToErrors() { 
    return errors;
}

network::network(std::vector<int> &sizes, const int num, const int af, const double ap, const double bp) { 
    layers.push_back(layer(sizes[0], num, af, ap, bp));
    std::cout << "размеры слоёв ";
    for (int i = 0; i < sizes.size(); i++) {
        cout << sizes[i] << " ";
    } cout << endl;
    for (int i = 1; i < sizes.size(); i++) {
        layers.push_back(layer(sizes[i], layers[i-1].accessToTheNeuronVector().size(), af, ap, bp));
    }
}

void network::exportNetwork(const std::string folderPath) { 
    fstream f; // создаём поток
    f.open(folderPath+"network", ios::out); // открываем файл
    // выписываем в первую строку размеры матриц весов
    for (int i = 0; i < layers.size(); i++) {
        f << layers[i].accessToTheNeuronVector().size() << " " << layers[i].accessToTheNeuronVector()[i].getVectorOfWeights().size() " ";
    }
    f << endl; // добавляем переход на новую строку.
    for (int i  = 0; i < layers.size(); i++) { // едем по слоям        for (int j = 0; j < layers[i].accessToTheNeuronVector().size(); j++) {
            for (int k = 0; k < layers[i].accessToTheNeuronVector()[j].getVectorOfWeights().size(); k++) {
                f << layers[i].accessToTheNeuronVector()[j].getVectorOfWeights()[k]; // записываем значения
                f << " ";
            }
        }
        f << endl; // добавляем переход на новую строку
    }
    f.close(); // закрываем файл
}

network::network(const std::string filePath) { 
    vector<vector<double>> vectorOfMatrixOfWeights; // вектор для записи линеризованных матриц весов
    vector<vector<int>> sizeis; // вектор для записи размеров
    ifstream f; // готовим поток
    f.open(filePath); // открываем файл
    while (f.good()) { // пока не дойдём до конца файла
        vector<int> size(2);
        vector<double> values;
         f >> size[0]; // читаем размер
        f >> size[1];
        values.resize(size[0] * size[1]); // резервируем память
        sizeis.push_back(size); // сохраняем размеры
        for (int i = 0; i << values.size(); i++) {
            f >> values[i];
        }
        vectorOfMatrixOfWeights.push_back(values); // затягиваем матрицу
    }
    f.close(); // закрываем файл
    layers.resize(vectorOfMatrixOfWeights.size()); // резервируем память для слоёв
    for (int i = 0; i < layers.size(); i++) { // едем по слоям
        for (int j = 0; j < vectorOfMatrixOfWeights[i].size(); j+=sizeis[i][1]) { // едем по вектору матрицы весов
            vector<double> part(vectorOfMatrixOfWeights[i].begin() + j, vectorOfMatrixOfWeights[i].begin() + j + sizeis[i][1]); // получаем часть вектора
            layers[i].accessToTheNeuronVector().push_back(neuron(part)); // создаём нейрон нужного нам размера
        }
        layers[i].toRebuildThePointers(); // пересобираем указатели у слоя
    }
}
