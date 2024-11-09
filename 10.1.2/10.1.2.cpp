#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum Kurs { I = 1, II, III, IV, V, VI };
enum Spec { ME, MF, FI, IN, KN };  


struct Student {
    union ThirdMark {
        int mark_prog;
        int mark_num_methods;
        int mark_pedagogy;
    };
    string prizv;        
    int kurs;               
    Spec spec;        
    int mark_physics;      
    int mark_math;          
    ThirdMark third_mark;  
};

void input_students(Student* students, int n) {
    for (int i = 0; i < n; ++i) {
        cout << "\nEnter details for student #" << (i + 1) << endl;
        cout << "Surname: ";
        cin >> students[i].prizv;

        cout << "Course (1-6): ";
        cin >> students[i].kurs;

        int spec;
        cout << "Speciality (0 - ME, 1 - MF, 2 - FI, 3 - IN, 4 - KN): ";
        cin >> spec;
        students[i].spec = static_cast<Spec>(spec);

        cout << "Physics mark: ";
        cin >> students[i].mark_physics;

        cout << "Math mark: ";
        cin >> students[i].mark_math;

        switch (students[i].spec) {
        case IN: 
            cout << "Numerical Methods mark: ";
            cin >> students[i].third_mark.mark_num_methods;
            break;
        case KN: 
            cout << "Programming mark: ";
            cin >> students[i].third_mark.mark_prog;
            break;
        default: 
            cout << "Pedagogy mark: ";
            cin >> students[i].third_mark.mark_pedagogy;
            break;
        }
    }
}

void print_table(const Student* students, int n) {
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "| ¹  |   Surname   | Course |      Spec.      | Physics | Math | Prog | NumMeth | Ped |" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(2) << (i + 1) << " | "
            << setw(10) << left << students[i].prizv << " | "
            << setw(6) << right << students[i].kurs << " | ";

        switch (students[i].spec) {
        case ME: cout << setw(15) << left << "Math & Econ"; break;
        case MF: cout << setw(15) << left << "Labour Ed"; break;
        case FI: cout << setw(15) << left << "Phys & Info"; break;
        case IN: cout << setw(15) << left << "Informatics"; break;
        case KN: cout << setw(15) << left << "Comp Sci"; break;
        }

        cout << " | " << setw(7) << right << students[i].mark_physics
            << " | " << setw(4) << students[i].mark_math;

        if (students[i].spec == KN) { 
            cout << " | " << setw(5) << students[i].third_mark.mark_prog << " |         |      |";
        }
        else if (students[i].spec == IN) {
            cout << " |       | " << setw(7) << students[i].third_mark.mark_num_methods << " |      |";
        }
        else {  
            cout << " |       |         | " << setw(5) << students[i].third_mark.mark_pedagogy << " |";
        }

        cout << endl;
    }

    cout << "--------------------------------------------------------------------------------------" << endl;
}

void count_prog_grades(const Student* students, int n, int& count5, int& count4, int& count3) {
    count5 = count4 = count3 = 0;
    for (int i = 0; i < n; ++i) {
        if (students[i].spec == KN) { 
            int mark = students[i].third_mark.mark_prog;
            if (mark == 5) count5++;
            else if (mark == 4) count4++;
            else if (mark == 3) count3++;
        }
    }
}

double percent_high_grades(const Student* students, const int N) {
    int k = 0; 
    int n = 0; 

    for (int i = 0; i < N; i++) {
        n++;

        if (students[i].mark_physics >= 4 && students[i].mark_math >= 4) {
            k++;
        }
    }

    return (n == 0) ? 0.0 : (100.0 * k / n);
}



int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student* students = new Student[n];

 
    input_students(students, n);
    print_table(students, n);

    int count5, count4, count3;
    count_prog_grades(students, n, count5, count4, count3);
    cout << "\nNumber of '5' grades in programming: " << count5 << endl;
    cout << "Number of '4' grades in programming: " << count4 << endl;
    cout << "Number of '3' grades in programming: " << count3 << endl;

    double percent = percent_high_grades(students, n);
    cout << "Percentage of students with grades '4' or '5' in physics and math: "
        << fixed << setprecision(2) << percent << "%" << endl;

    delete[] students;
    return 0;
}
