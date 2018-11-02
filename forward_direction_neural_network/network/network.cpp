//
//  network.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 22/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "network.hpp"
#include <fstream>
#include <cstring>
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
        layers.push_back(layer(sizes[i], static_cast<int>(layers[i-1].accessToTheNeuronVector().size()), af, ap, bp));
    }
}

void network::exportNetwork(const std::string folderPath) { 
    fstream f; // создаём поток
    f.open(folderPath+"network", ios::out); // открываем файл
    // выписываем в первую строку размеры матриц весов
    for (int i = 0; i < layers.size(); i++) {
        f << layers[i].accessToTheNeuronVector().size() << " " << layers[i].accessToTheNeuronVector()[0].getVectorOfWeights().size() << " ";
    }
    f << endl; // добавляем переход на новую строку.
    for (int i  = 0; i < layers.size(); i++) { // едем по слоям
        for (int j = 0; j < layers[i].accessToTheNeuronVector().size(); j++) {
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
    ifstream f; // готовим поток
    f.open(filePath); // открываем файл
    string s; // строка для строки с параметрами
    getline(f, s); // выдёргиваем первую строку
    // внимание, дальше будет много кода на сях, простите за дремучее легаси.
    char *cs = new char(s.size()); // сишная строка
    strcpy(cs, s.data()); // копируем строку из нормальной в дремучую.
    char* stime = strtok(cs, " "); // создаём маленькую строку и загоняем в неё первую лексему
    int num = atoi(stime); // по идее это количество нейронов на первом скрытом слое, по этому перекидуем эту строчку в инт.
    stime = strtok(cs, " "); // тащим следующую лексему
    int size = atoi(stime); // забираем размер вектора весов
    layers.push_back(layer(num, size)); // создаём первый слой.
    while (stime != NULL) { // пока не налетим на null
        // повторяем процедуру
        stime = strtok(cs, " ");
        num = atoi(stime);
        stime = strtok(cs, " ");
        size = atoi(stime);
        layers.push_back(layer(num, size));
    }
    // освобождаем память, мы же гуманнай народ.
    delete cs;
    delete stime;
    // выдохнули, код на сях кончился, возвращаемся к крестам
    // заполняем матрицы весов
    for (int i = 0; i < layers.size(); i++) { // едем по слоям
        for (int j = 0; j < layers[i].accessToTheNeuronVector().size(); j++) { // едем по нейронам
            for (int k = 0; k < layers[i].accessToTheNeuronVector()[j].getVectorOfWeights().size(); k++) { // едем по вектору весов
                f >> layers[i].accessToTheNeuronVector()[j].getVectorOfWeights()[k]; // тащим значение типа double
            }
        }
    }
    f.close(); // закрываем файл
}

void network::directPropagation(std::vector<double> &inputSignal) {
    layers[0].calculateTheOutputValuesByTheVectorOfTheInputSignals(inputSignal);
    for (int i = 1; i < layers.size(); i++) {
        layers[i].toCalculateTheOutputValuesForTheCurrentLayer(layers[i-1]);
    }
}

void network::backPropagation(std::vector<double> &responseVector, const double lg) {
    layers[layers.size()-1].toCalculateTheComponentOfTheVectorOfErrors(responseVector);
    layers[layers.size()-1].countTheWeightOnTheCurrentLayer(lg);
    layers[layers.size()-1].toCalculateTheError();
    errors.push_back(layers[layers.size()-1].getError());
    for (int i = static_cast<int>(layers.size()) - 2; i >= 0; i--) {
        layers[i].calculateLocalGradientsForTheCurrentLayer(layers[i+1]);
        layers[i].countTheWeightOnTheCurrentLayer(lg);
    }
}

void network::train(std::vector<std::vector<double> > &TrainingSample, std::vector<std::vector<double>> &response, const double epsErrorse, const double lg, const int MaximumNumberOfEpochs) {
    int era = 0;
    double currentError = 0, backError = 10.0;
    while ((era < MaximumNumberOfEpochs) && (currentError < backError)) {
        backError = currentError;
        currentError = 0;
        for (int i = 0; i < TrainingSample.size(); i++) {
            directPropagation(TrainingSample[i]);
            backPropagation(response[i], lg);
        }
        for (int j = 0; j < errors.size(); j++) {
            currentError += errors[j];
        }
                    currentError /= 2;
        errors.clear();
        era++;
    }
}

