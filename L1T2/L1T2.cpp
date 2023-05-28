#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Проверка на простое число
bool isPrime(int num) {
    if (num < 2)
        return false;

    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

// Запись содержимого бинарного файла в текстовый файл
void writeBinaryFileToTextFile(const string& binaryFileName, const string& textFileName) {
    ifstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Не удалось открыть бинарный файл: " << binaryFileName << endl;
        return;
    }

    ofstream textFile(textFileName);
    if (!textFile) {
        cerr << "Не удалось открыть текстовый файл: " << textFileName << endl;
        binaryFile.close();
        return;
    }

    int num;
    while (binaryFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        textFile << num << endl;
    }

    binaryFile.close();
    textFile.close();
}

int main()
{
    system("chcp 65001");
    
    const string textFileName = "numbers.txt";
    const string binaryFileName = "numbers.bin";
    const string primeFileName = "prime.bin";
    const string compositeFileName = "composite.bin";
    
    ofstream textFile(textFileName);
    if (!textFile) {
        cerr << "Не удалось открыть текстовый файл: " << textFileName << endl;
        return 1;
    }

    cout << "Введите количество целочисенных значений: ";
    int numIntegers;
    cin >> numIntegers;

    cout << "Введите " << numIntegers << " целочисленных значений: " << endl;
    for (int i = 0; i < numIntegers; i++) {
        int num;
        cin >> num;
        textFile << num << endl;
    }

    textFile.close();

    // Конвертация текстового файла в бинарный файл
    ifstream inputFile(textFileName);
    if (!inputFile) {
        cerr << "Не удалось открыть текстовый файл: " << textFileName << endl;
        return 1;
    }

    ofstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Не удалось открыть бинарный файл: " << binaryFileName << endl;
        inputFile.close();
        return 1;
    }

    int num;
    while (inputFile >> num) {
        binaryFile.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }

    inputFile.close();
    binaryFile.close();

    // Прочитать и обновить бинарный файл
    cout << "Введите номер записи для редактирования (0 - " << numIntegers - 1 << "): ";
    int recordNumber;
    cin >> recordNumber;

    fstream binaryFileToUpdate(binaryFileName, ios::binary | ios::in | ios::out);
    if (!binaryFileToUpdate) {
        cerr << "Не удалось открыть бинарный файл: " << binaryFileName << endl;
        return 1;
    }

    binaryFileToUpdate.seekp(recordNumber * sizeof(int));
    cout<< "Введите новое значение: ";
    int newValue;
    cin >> newValue;
    binaryFileToUpdate.write(reinterpret_cast<const char*>(&newValue), sizeof(int));
    binaryFileToUpdate.close();

    // Создать два новых бинарных файла для простых и составных чисел
    ifstream binaryFileToRead(binaryFileName, ios::binary);
    if (!binaryFileToRead) {
        cerr << "Не удалось открыть бинарный файл: " << binaryFileName << endl;
        return 1;
    }

    ofstream primeFile(primeFileName, ios::binary);
    if (!primeFile) {
        cerr << "Не удалось открыть бинарный файл: " << primeFileName << endl;
        binaryFileToRead.close();
        return 1;
    }

    ofstream compositeFile(compositeFileName, ios::binary);
    if (!compositeFile) {
        cerr << "Не удалось открыть бинарный файл: " << compositeFileName << endl;
        binaryFileToRead.close();
        return 1;
    }

    while (binaryFileToRead.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        if (isPrime(num))
            primeFile.write(reinterpret_cast<const char*>(&num), sizeof(int));
        else
            compositeFile.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }

    binaryFileToRead.close();
    primeFile.close();
    compositeFile.close();

    // Вывод содержимого бинарного файла на экран
    auto outputBinaryFileContents = [](const string& fileName, ostream& output) {
        ifstream binaryFile(fileName, ios::binary);
        if (!binaryFile) {
            cerr << "Не удалось открыть бинарный файл: " << fileName << endl;
            return;
        }

        int num;
        while (binaryFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
            output << num << endl;
        }

        binaryFile.close();
    };

    // Запись содежимого из бинарных файлов в текстовые файлы
    writeBinaryFileToTextFile(primeFileName, "prime_numbers.txt");
    writeBinaryFileToTextFile(compositeFileName, "composite_numbers.txt");

    // Вывод содержимого бинарного файла на экран
    cout << "Простые числа:" << endl;
    outputBinaryFileContents(primeFileName, cout);
    cout << endl;

    cout << "Составные:" << endl;
    outputBinaryFileContents(compositeFileName, cout);
    cout << endl;

    return 0;
}