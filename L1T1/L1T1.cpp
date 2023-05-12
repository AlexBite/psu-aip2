#include <iostream>
#include <fstream>
#include <string>

const int MAX_SUBJECTS = 5;

using namespace std;

struct Subject {
    string name;
    int grade;
};

struct Student {
    string fullName;
    string faculty;
    string group;
    Subject subjects[MAX_SUBJECTS];
};

void writeStudentsToFile(Student students[], int numStudents, const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cerr << "Не удалось открыть файл: " << fileName << endl;
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        outputFile << "ФИО: " << students[i].fullName << endl;
        outputFile << "Факультет: " << students[i].faculty << endl;
        outputFile << "Группа: " << students[i].group << endl;

        for (auto& subject : students[i].subjects)
        {
            outputFile << "Предмет: " << subject.name << ", Оценка: " << subject.grade << endl;
        }

        outputFile << endl;
    }

    outputFile.close();
}

void displayStudentsWithGpaGreaterThan(Student students[], int numStudents, int minGpa) {
    for (int i = 0; i < numStudents; i++) {
        int totalGrades = 0;
        for (auto& subject : students[i].subjects)
        {
            totalGrades += subject.grade;
        }

        double gpa = static_cast<double>(totalGrades) / MAX_SUBJECTS;
        if (gpa > minGpa) {
            cout << "ФИО: " << students[i].fullName << endl;
            cout << "Факультет: " << students[i].faculty << endl;
            cout << "Группа: " << students[i].group << endl;
            cout << "Средний балл: " << gpa << endl;
            cout << endl;
        }
    }
}

int main()
{
    system("chcp 65001");
    const int numStudents = 4;
    Student students[numStudents];
    
    students[0].fullName = "Иванов Иван Иванович";
    students[0].faculty = "Инженерный";
    students[0].group = "А";
    students[0].subjects[0] = { "Математика", 85 };
    students[0].subjects[1] = { "Физика", 78 };
    students[0].subjects[2] = { "Химия", 92 };
    students[0].subjects[3] = { "Английский", 70 };
    students[0].subjects[4] = { "История", 88 };

    students[1].fullName = "Васильев Василий Васильевич";
    students[1].faculty = "Научный";
    students[1].group = "В";
    students[1].subjects[0] = { "Биология", 79 };
    students[1].subjects[1] = { "Физика", 82 };
    students[1].subjects[2] = { "Химия", 91 };
    students[1].subjects[3] = { "Английский", 85 };
    students[1].subjects[4] = { "История", 68 };

    students[2].fullName = "Смирнова Алиса Александровна";
    students[2].faculty = "Искусств";
    students[2].group= "С";
    students[2].subjects[0] = { "Литература", 88 };
    students[2].subjects[1] = { "История", 76 };
    students[2].subjects[2] = { "Английский", 82 };
    students[2].subjects[3] = { "Математика", 79 };
    students[2].subjects[4] = { "Музыка", 90 };

    students[3].fullName = "Сидоров Сергей Семёнович";
    students[3].faculty = "Строительный";
    students[3].group= "А";
    students[3].subjects[0] = { "Черчение", 50 };
    students[3].subjects[1] = { "Филосовия", 20 };
    students[3].subjects[2] = { "Английский", 25 };
    students[3].subjects[3] = { "Математика", 50 };
    students[3].subjects[4] = { "Физика", 23 };
    
    // Записать студентов в файл
    writeStudentsToFile(students, numStudents, "students.txt");

    // Отобразить студентов с GPA больше 41
    const int minGpa = 41;
    displayStudentsWithGpaGreaterThan(students, numStudents, minGpa);

    return 0;
}
