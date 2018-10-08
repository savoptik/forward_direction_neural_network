//
//  parametrsStorage.hpp
//  forward_direction_neural_network
//
//  Created by Артём Семёнов on 08/10/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#ifndef parametrsStorage_hpp
#define parametrsStorage_hpp

#include <stdio.h>
#include <string>
#include <vector>

class parametrsStorage {
public:
    parametrsStorage(const int numArgv, const char** parametrs); // конструктор принимает параметры командной строки
    /**
     Режим работы приложения

     @return Целое число, номер режима работы приложения
     */
    int operatingMode();
    /**
     Функция активации

     @return возвращает номер функции активации
     */
    int getActivationFunction();
    /**
     скорость обучения

     @return возвращает скорость обучения
     */
    double getLearningRate();
    /**
     параметры функции активации

     @return ссылку на вектор с параметрами
     */
    std::vector<double>& getParametersOfTheActivationFunction();
    /**
     количество классов в выходном слое

     @return целое число, количество классов в выходном слое
     */
    int getNumberOfClassesInTheOutputLayer();
    /**
     вектор количеств нейронов на выходном слое

     @return указатель на вектор количества нейронов на выходном слое
     */
    std::vector<int>& getNumberOfNeuronsInHiddenLayers();
    /**
     путь к обучающей выборке или обученной сети

     @return строку с путём
     */
    std::string getInputPath();
    /**
     путь для сохранения обученной сети

     @return строку с путём
     */
    std::string getSavePath();
    /**
     путь к тестовой выборке

     @return строку с путём
     */
    std::string getTestPath();
private:
    /**
     Функция отображает справку по параметрам.
     */
    void help();
    int mode = 0; // режим работы сети
    double learningRate; // скорость обучения.
    int activationFunction; // функция активации
    std::vector<double> theParametersOfTheActivationFunction; // параметры функции активации
    int numberOfClassesInTheOutputLayer; // количество классов в выходном слое
    std::vector<int> numberOfNeuronsInHiddenLayers; // количества нейронов в скрытых слоях
    std::string inputPath; // путь либо к тренеровочной выборке либо к обученной сети
    std::string savePath; // путь для сохранения обученной сети.
    std::string testPath; // путь к тестовым объектам
    const std::string helpPath = "/Users/artemsemenov/Documents/GitHub/forward_direction_neural_network/forward_direction_neural_network/resursis/help/help.txt"; // путь к файлу справки
};

#endif /* parametrsStorage_hpp */
