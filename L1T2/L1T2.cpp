#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    if (num < 2)
        return false;

    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

// Function to write the contents of a binary file to a text file
void writeBinaryFileToTextFile(const string& binaryFileName, const string& textFileName) {
    ifstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Failed to open the binary file: " << binaryFileName << endl;
        return;
    }

    ofstream textFile(textFileName);
    if (!textFile) {
        cerr << "Failed to open the text file: " << textFileName << endl;
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

    // Write random integers to the text file
    ofstream textFile(textFileName);
    if (!textFile) {
        cerr << "Failed to create the text file: " << textFileName << endl;
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

    // Convert text file to binary file
    ifstream inputFile(textFileName);
    if (!inputFile) {
        cerr << "Failed to open the text file: " << textFileName << endl;
        return 1;
    }

    ofstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Failed to create the binary file: " << binaryFileName << endl;
        inputFile.close();
        return 1;
    }

    int num;
    while (inputFile >> num) {
        binaryFile.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }

    inputFile.close();
    binaryFile.close();

    // Read and update the binary file
    cout << "Введите номер записи для редактирования (0 - " << numIntegers - 1 << "): ";
    int recordNumber;
    cin >> recordNumber;

    fstream binaryFileToUpdate(binaryFileName, ios::binary | ios::in | ios::out);
    if (!binaryFileToUpdate) {
        cerr << "Failed to open the binary file: " << binaryFileName << endl;
        return 1;
    }

    binaryFileToUpdate.seekp(recordNumber * sizeof(int));
    cout<< "Введите новое значение: ";
    int newValue;
    cin >> newValue;
    binaryFileToUpdate.write(reinterpret_cast<const char*>(&newValue), sizeof(int));
    binaryFileToUpdate.close();

    // Create two new binary files for prime and composite numbers
    ifstream binaryFileToRead(binaryFileName, ios::binary);
    if (!binaryFileToRead) {
        cerr << "Failed to open the binary file: " << binaryFileName << endl;
        return 1;
    }

    ofstream primeFile(primeFileName, ios::binary);
    if (!primeFile) {
        cerr << "Failed to create the binary file: " << primeFileName << endl;
        binaryFileToRead.close();
        return 1;
    }

    ofstream compositeFile(compositeFileName, ios::binary);
    if (!compositeFile) {
        cerr << "Failed to create the binary file: " << compositeFileName << endl;
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

    // Function to output the contents of a binary file to a text file or screen
    auto outputBinaryFileContents = [](const string& fileName, ostream& output) {
        ifstream binaryFile(fileName, ios::binary);
        if (!binaryFile) {
            cerr << "Failed to open the binary file: " << fileName << endl;
            return;
        }

        int num;
        while (binaryFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
            output << num << endl;
        }

        binaryFile.close();
    };

    // Output binary file contents to text file
    writeBinaryFileToTextFile(primeFileName, "prime_numbers.txt");
    writeBinaryFileToTextFile(compositeFileName, "composite_numbers.txt");

    // Output binary file contents to screen
    cout << "Простые числа:" << endl;
    outputBinaryFileContents(primeFileName, cout);
    cout << endl;

    cout << "Составные:" << endl;
    outputBinaryFileContents(compositeFileName, cout);
    cout << endl;

    return 0;
}