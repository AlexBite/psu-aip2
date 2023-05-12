#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
    string name;
    string group;
    string specialty;
    double scholarship;
};

void writeStudentsToBinaryFile(const vector<Student>& students, const string& fileName)
{
    ofstream outputFile(fileName, ios::binary);
    if (!outputFile)
    {
        cerr << "Failed to open the binary file: " << fileName << endl;
        return;
    }

    for (const Student& student : students)
    {
        outputFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }

    outputFile.close();
}

void displayPhysicsStudents(const string& fileName)
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
        if (student.specialty == "physics")
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

void updateScholarship(const string& fileName, int studentIndex, double newScholarship)
{
    fstream file(fileName, ios::binary | ios::in | ios::out);
    if (!file)
    {
        cerr << "Failed to open the binary file: " << fileName << endl;
        return;
    }

    Student student;
    file.seekp(studentIndex * sizeof(Student), ios::beg);
    if (file.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        student.scholarship = newScholarship;
        file.seekp(studentIndex * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }

    file.close();
}

void outputBinaryFileContents(const string& binaryFileName, const string& textFileName = "")
{
    ofstream outputFile;
    if (!textFileName.empty())
    {
        outputFile.open(textFileName);
        if (!outputFile)
        {
            cerr << "Failed to open the text file: " << textFileName << endl;
            return;
        }
    }

    ifstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile)
    {
        cerr << "Failed to open the binary file: " << binaryFileName << endl;
        return;
    }

    Student student;
    while (binaryFile.read(reinterpret_cast<char*>(&student), sizeof(Student)))
    {
        if (textFileName.empty())
        {
            cout << "Name: " << student.name << endl;
            cout << "Group: " << student.group << endl;
            cout << "Specialty: " << student.specialty << endl;
            cout << "Scholarship: " << student.scholarship << endl;
            cout << endl;
        }
        else
        {
            outputFile << "Name: " << student.name << endl;
            outputFile << "Group: " << student.group << endl;
            outputFile << "Specialty: " << student.specialty << endl;
            outputFile << "Scholarship: " << student.scholarship << endl;
            outputFile << endl;
        }
    }

    binaryFile.close();
    if (!textFileName.empty())
    {
        outputFile.close();
    }
}

int main()
{
    const string binaryFileName = "students.bin";
    // Create a list of students
    vector<Student> students;
    int numStudents;

    cout << "Enter the number of students: ";
    cin >> numStudents;

    cin.ignore(); // Ignore the newline character after entering the number

    for (int i = 0; i < numStudents; i++)
    {
        Student student;
        cout << "Enter the details for student " << i + 1 << ":" << endl;
        cout << "Name: ";
        getline(cin, student.name);
        cout << "Group: ";
        getline(cin, student.group);
        cout << "Specialty: ";
        getline(cin, student.specialty);
        cout << "Scholarship: ";
        cin >> student.scholarship;

        cin.ignore(); // Ignore the newline character after entering the scholarship

        students.push_back(student);
    }

    // Write students to binary file
    writeStudentsToBinaryFile(students, binaryFileName);

    // Display physics students
    cout << "Physics Students:" << endl;
    displayPhysicsStudents(binaryFileName);

    // Update scholarship for a student
    int studentIndex;
    double newScholarship;

    cout << "Enter the index of the student to update (0 to " << numStudents - 1 << "): ";
    cin >> studentIndex;
    cout << "Enter the new scholarship value: ";
    cin >> newScholarship;

    updateScholarship(binaryFileName, studentIndex, newScholarship);

    // Output binary file contents to text file and screen
    cout << "Binary File Contents:" << endl;
    outputBinaryFileContents(binaryFileName);

    cout << "Text File Contents:" << endl;
    outputBinaryFileContents(binaryFileName, "students.txt");

    return 0;
}
