//
//  parametrsStorage.cpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 08/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include "parametrsStorage.hpp"
#include <iostream>
#include <fstream>
using namespace std;

parametrsStorage::parametrsStorage(const int numArgv, const char **parametrs) {
    if (numArgv == 1) {
        cout << "Чтобы получить справку по параметрам используйте параметр -h\n";
        return;
    }
    if (numArgv == 2) { // если задан всего один параметр
        std::string p = parametrs[1]; // для удобства затаскиваем его в стринг
        if (p.find("-h") != string::npos) { // если это ключь помощи
            help(); // выводим справку
        } else cout << "Нет такой команды\n"; // выдаём ругательное сообщение
        return; // выходим из функции
    } else if (numArgv == 3) {
        cout << "Нет конфигурации с двумя параметрами\n"; // ругаемся
        return; // выходим из функции
    }
    mode = atoi(parametrs[1]); // подтягиваем режим работы
        if (mode == 1) { // если выбран режим обучения
        inputPath = parametrs[2]; // забираем путь к входной выборке
        savePath = parametrs[3]; // забираем путь для сохранения обученной сети
        learningRate = stod(parametrs[4]); // принимаем скорость обучения
        activationFunction = atoi(parametrs[5]); // принимаем тип функции активации
        if (activationFunction == 1) { // если функция логистическая
            theParametersOfTheActivationFunction.resize(1); // значит параметр у неё один
            theParametersOfTheActivationFunction[0] = stod(parametrs[6]); // забираем его
            numberOfClassesInTheOutputLayer = atoi(parametrs[7]); // принимаем количество классов в выходном слое
            int num = numArgv - 8; // вычисляем количество скрытых слоёв
            numberOfNeuronsInHiddenLayers.resize(num); // готовим вектор
            for (int i = 0; i < num; i++) { // перебираем параметры
                numberOfNeuronsInHiddenLayers[i] = atoi(parametrs[i+num]); // записываем в вектор количества нейронов на скрытых слоях.
            }
        } else { // если выбрана другая функция активации
            theParametersOfTheActivationFunction.resize(2); // у неё 2 параметра
            theParametersOfTheActivationFunction[0] = atoi(parametrs[6]); // забираем параметры
            theParametersOfTheActivationFunction[1] = atoi(parametrs[7]);
            numberOfClassesInTheOutputLayer = atoi(parametrs[8]); // принимаем количество нейронов в выходном слое
            int num = numArgv - 9; // вычисляем количество скрытых слоёв
            numberOfNeuronsInHiddenLayers.resize(num); // выделяем память
            for (int i = 0; i < num; i++) { // перебираем параметры
                numberOfNeuronsInHiddenLayers[i] = atoi(parametrs[i+num]); // забираем количества нейронов на скрытых слоях
            }
        }
    } else { // если выбран режим работы распознавания
        inputPath = parametrs[2]; // забираем путь, по которому лежит обученная сеть
        testPath = parametrs[3]; // передаём путь к папке с тестовыми объектами.
    }
}

int parametrsStorage::operatingMode() { 
    return mode;
}

void parametrsStorage::help() { 
    fstream f;
    f.open(helpPath); // открываем файл
    if (!f) {
        cout << "файл справки не найден\n";
        return;
    }
    string s;
    while (!f.eof()) { // пока не дойдём до конца файла
        getline(f, s); // читаем строку
        cout << s << endl; // выводим строку
    }
    f.close(); // закрываем файл справки
}

std::string parametrsStorage::getTestPath() { 
    if (mode == 2) { // проверяем режим работы
        return testPath; // возвращаем путь к тестовой выборке
    } else return NULL; // иначе возвращаем пустышку
}

std::string parametrsStorage::getSavePath() { 
    if (mode == 1) { // проверяем режим работы
        return savePath; // возвращаем путь
    } else return NULL; // иначе возвращаем пустышку
}

std::string parametrsStorage::getInputPath() { 
    return inputPath;
}

std::vector<int> &parametrsStorage::getNumberOfNeuronsInHiddenLayers() { 
    return numberOfNeuronsInHiddenLayers; // возвращаем ссылку
}

int parametrsStorage::getNumberOfClassesInTheOutputLayer() { 
    if (mode == 1) { // проверяем режим работы
        return numberOfClassesInTheOutputLayer; // возвращаем значение
    } else return NULL; // иначе возвращаем пустышку
}

std::vector<double> &parametrsStorage::getParametersOfTheActivationFunction() {
    return theParametersOfTheActivationFunction; // возвращаем ссылку
}

double parametrsStorage::getLearningRate() { 
    if (mode == 1) { // проверяяем режим работы
        return learningRate; // возвращаем значение
    } else return NULL; // иначе пустышка
}

int parametrsStorage::getActivationFunction() { 
    if (mode == 1) { // проверяем, допускает ли режим работы использование данного метода
        return activationFunction; // возвращаем значение
    } else return NULL; // иначе возвращаем пустышку
}


