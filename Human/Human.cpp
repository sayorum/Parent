#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string name;
    int age;

    Student() : name(""), age(0) {}
    Student(const string& name, int age) : name(name), age(age) {}
};

class Parent {
public:
    vector<Student> students;

    Parent() {}
    Parent(const string& filename) {
        initializeFromFile(filename);
    }

    void initializeFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file: " << filename << endl;
            return;
        }

        string name;
        int age;
        while (file >> name >> age) {
            students.push_back(Student(name, age));
        }

        file.close();
    }

    void removeStudent(const string& name) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->name == name) {
                students.erase(it);
                return;
            }
        }
        cout << "Student with name " << name << " not found!" << endl;
    }

    void writeToOutputFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file: " << filename << endl;
            return;
        }

        for (const auto& student : students) {
            file << student.name << " " << student.age << endl;
        }

        file.close();
    }
};

class Child : public Parent {
public:
    Child(const string& filename) : Parent(filename) {}
};

int main() {
    Child child("students.txt");

    for (const auto& student : child.students) {
        cout << "Name: " << student.name << ", Age: " << student.age << endl;
    }

    child.removeStudent("Alice");

    for (const auto& student : child.students) {
        cout << "Name: " << student.name << ", Age: " << student.age << endl;
    }

    child.writeToOutputFile("updated_students.txt");

    return 0;
}
