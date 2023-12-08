#include <iostream>
#include <map>

class Teacher; // Forward declaration

class Student {
    std::string name;
    std::map<std::string, std::string> grades;

public:
    Student(std::string studentName) : name(std::move(studentName)) {}

    void setGrade(const std::string& courseID, const std::string& grade) {
        grades[courseID] = grade;
    }

    void viewGrades() const {
        std::cout << "Grades for student " << name << ":\n";
        for (const auto& grade : grades) {
            std::cout << "Course: " << grade.first << ", Grade: " << grade.second << "\n";
        }
        std::cout << std::endl;
    }

    std::string getName() const { return name; }

    friend class Teacher;
};

class Teacher {
    Student* students[100];
    int numStudents;

public:
    Teacher() : numStudents(0) {}

    void addStudent(Student* student) {
        students[numStudents++] = student;
    }

    const Student* const* getStudents() const { return students; }

    int getNumStudents() const {
        return numStudents;
    }

    void searchStudentByName(const std::string& studentName) const {
        for (int i = 0; i < numStudents; i++) {
            if (students[i]->getName() == studentName) {
                std::cout << "Student " << studentName << " found.\n";
                return;
            }
        }
        std::cout << "Student " << studentName << " not found.\n";
    }

    void filterStudentsByGrade(const std::string& gradeStr, const std::string& courseID) const {
        for (int i = 0; i < numStudents; i++) {
            const Student* student = students[i];
            for (const auto& grade : student->grades) {
                if (grade.second == gradeStr && grade.first == courseID) {
                    std::cout << "Student " << student->getName() << " has grade " << gradeStr
                              << " in course " << courseID << "\n";
                }
            }
        }
    }

    void displayMenu() const {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View Student Grades\n";
        std::cout << "3. Search Student by Name\n";
        std::cout << "4. Filter Students by Grade\n";
        std::cout << "5. Exit\n";
    }
};

int main() {
    Teacher teacher;

    int choice;
    std::string studentName, courseID, gradeStr;
    Student* newStudent = nullptr; // Declare newStudent outside the switch statement

    do {
        teacher.displayMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter student name: ";
                std::cin >> studentName;
                newStudent = new Student(studentName);

                std::cout << "Enter course ID: ";
                std::cin >> courseID;
                std::cout << "Enter grade: ";
                std::cin >> gradeStr;
                newStudent->setGrade(courseID, gradeStr);

                teacher.addStudent(newStudent);
                std::cout << "Student added successfully.\n";
                break;

            case 2:
                std::cout << "Enter student name: ";
                std::cin >> studentName;
                {
                    const Student* const* students = teacher.getStudents();
                    for (int i = 0; i < teacher.getNumStudents(); i++) {
                        if (students[i]->getName() == studentName) {
                            students[i]->viewGrades();
                            break;
                        }
                    }
                }
                break;

            case 3:
                std::cout << "Enter student name: ";
                std::cin >> studentName;
                teacher.searchStudentByName(studentName);
                break;

            case 4:
                std::cout << "Enter grade: ";
                std::cin >> gradeStr;
                std::cout << "Enter course ID: ";
                std::cin >> courseID;
                teacher.filterStudentsByGrade(gradeStr, courseID);
                break;

            case 5:
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }

    } while (choice != 5);

    delete newStudent;

    return 0;
}
