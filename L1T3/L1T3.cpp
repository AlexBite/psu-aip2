#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student
{
    char name[40];
    char group[40];
    char specialty[40];
    int scholarship;
};

void writeStudentsToFile(const string& fileName, const Student* students, int numStudents)
{
    ofstream outputFile(fileName, ios::binary);
    if (!outputFile)
    {
        cerr << "Не удалось открыть бинарный файл: " << fileName << endl;
        return;
    }

    for (int i = 0; i < numStudents; ++i)
    {
        outputFile.write(reinterpret_cast<const char*>(&students[i]), sizeof(Student));
    }

    outputFile.close();
}

void displayStudentsBySpecialty(const string& fileName, const string& specialty)
{
    fstream inputFile(fileName, ios::binary | ios::in | ios::out);
    if (!inputFile)
    {
        cerr << "Не удалось открыть бинарный файл: " << fileName << endl;
        return;
    }

    Student student{};
    while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        if (student.specialty == specialty)
        {
            cout << "ФИО: " << student.name << endl;
            cout << "Группа: " << student.group << endl;
            cout << "Специальность: " << student.specialty << endl;
            cout << "Стипендия: " << student.scholarship << endl;
            cout << endl;
        }
    }

    inputFile.close();
}

void replaceStudentScholarship(const string& fileName, int index, int newScholarship)
{
    fstream file(fileName, ios::in | ios::out | ios::binary);
    if (!file)
    {
        cerr << "Не удалось открыть бинарный файл: " << fileName << endl;
        return;
    }

    file.seekg(index * sizeof(Student), ios::beg);
    Student student;
    if (file.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        student.scholarship = newScholarship;
        file.seekp(index * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }

    file.close();
}

// Вывод содержимого баинарного файла на экран
void displayBinaryFileContents(const string& fileName)
{
    ifstream inputFile(fileName, ios::binary);
    if (!inputFile)
    {
        cerr << "Не удалось открыть бинарный файл: " << fileName << endl;
        return;
    }

    Student student;
    while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        cout << "ФИО: " << student.name << endl;
        cout << "Группа: " << student.group << endl;
        cout << "Специальность: " << student.specialty << endl;
        cout << "Стипендия: " << student.scholarship << endl;
        cout << endl;
    }

    inputFile.close();
}

int main()
{
    system("chcp 65001");
    const int numStudents = 3;
    Student students[numStudents] = {
        {"Джон Смит", "Группа А", "физика", 1500},
        {"Эмили Джонсон", "Группа Б", "физика", 1700},
        {"Элис Джонсон", "Группа С", "химия", 1600}
    };

    // Записать студентов в бинарный файл
    writeStudentsToFile("students.bin", students, numStudents);

    // Вывод списка студентов со специальностью "физика" из бинрного файла
    cout << "Список физиков: " << endl;
    displayStudentsBySpecialty("students.bin", "физика");
    
    // Заменить стипендию для первого студента на 2000
    int studentIndex = 1;
    int newScholarship = 2000;
    replaceStudentScholarship("students.bin", studentIndex, newScholarship);

    // Вывести обновлённый список студентов из бинарного файла
    cout << "Файл после изменения: " << endl;
    displayBinaryFileContents("students.bin");

    return 0;
}
