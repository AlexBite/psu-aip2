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
        cerr << "Failed to open the binary file: " << fileName << endl;
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
        cerr << "Failed to open the binary file: " << fileName << endl;
        return;
    }

    Student student{};
    while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        if (student.specialty == specialty)
        {
            cout << "Name: " << student.name << endl;
            cout << "Group: " << student.group << endl;
            cout << "Specialty: " << student.specialty << endl;
            cout << "Scholarship: " << student.scholarship << endl;
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
        cerr << "Failed to open the binary file: " << fileName << endl;
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

void displayBinaryFileContents(const string& fileName)
{
    ifstream inputFile(fileName, ios::binary);
    if (!inputFile)
    {
        cerr << "Failed to open the binary file: " << fileName << endl;
        return;
    }

    Student student;
    while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        cout << "Name: " << student.name << endl;
        cout << "Group: " << student.group << endl;
        cout << "Specialty: " << student.specialty << endl;
        cout << "Scholarship: " << student.scholarship << endl;
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
        {"Эмили Джонсон", "Группа Б", "химия", 1700},
        {"Элис Джонсон", "Группа С", "физика", 1600}
    };

    // Write the students to a binary file
    writeStudentsToFile("students.bin", students, numStudents);

    // Display the list of students of the specialty "physics" from the binary file
    cout << "Список физиков: " << endl;
    displayStudentsBySpecialty("students.bin", "физика");

    // Replace the scholarship for a specific student in the binary file
    int studentIndex = 1; // Index of the student to modify
    int newScholarship = 2000; // New scholarship value
    replaceStudentScholarship("students.bin", studentIndex, newScholarship);

    // Display the modified list of students from the binary file
    cout << "Файл после изменения: " << endl;
    displayBinaryFileContents("students.bin");

    return 0;
}
