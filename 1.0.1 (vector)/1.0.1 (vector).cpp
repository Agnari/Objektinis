#include "Mylib.h"

struct Student {
	string name, surname;
	vector<int> grades;
	int exam = 0;
	float final = 0;
};

void CalcData(Student& temp) {
	char answer;
	cout << "Do you want average or median as final grade? (a/m)";
	cin >> answer;
	while ((answer != 'a' && answer != 'A') && (answer != 'm' && answer != 'M')) {
		cout << "There is no such answer. A/a - for average, M/m - for median" << endl;
		cin >> answer;
	};

	if (answer == 'a' || answer == 'A') {
		float avg = 0;
		if (temp.grades.size() != 0) {			//checks if there are values in "grades"
			float sum = 0;
			for (int i = 0; i < temp.grades.size(); i++) { sum += temp.grades[i]; }
			avg = (float)sum / temp.grades.size();
		}
		else { avg = 0; }			//if there are no grades, average is equal 0

		temp.final = (float)(0.4 * avg) + (0.6 * temp.exam);
	} //calculates average
	else {
		float median = 0;
		if (temp.grades.size() != 0) {			//checks if there are values in "grades"
			sort(temp.grades.begin(), temp.grades.end());
			if (temp.grades.size() % 2 == 0) { median = (float)(temp.grades[temp.grades.size() / 2] + temp.grades[temp.grades.size() / 2 - 1]) / 2.0; }
			else { median = temp.grades[temp.grades.size() / 2]; };
		}
		else (median = 0);			//if there are no grades, median is equal 0

		temp.final = (0.4 * median) + (0.6 * temp.exam);
	}//calculates median
}

void GatherData(Student& temp) {
	cout << "Enter name and surname: " << endl;
	cin >> temp.name >> temp.surname;

	char answer;
	cout << "Manual input or random values? (m/r)" << endl;
	cin >> answer;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		if (answer == 'm' || answer == 'M') {
			cout << "Enter homework grades (0-10) or symbol to continue:" << endl;
			int grade = 0;

			while (cin >> grade) {
				if (grade >= 0 && grade <= 10) { temp.grades.push_back(grade); }
				else {
					while (grade < 0 || grade > 10)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Wrong value. Please enter number from 0 to 10" << endl;
						cin >> grade;
					}
					temp.grades.push_back(grade);
				};
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			int exam = 0;
			cout << "Enter exam grade: " << endl;
			cin >> exam;
			while (exam < 0 || exam > 10) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Re-enter your value. It must be from 0 to 10." << endl;
				cin >> exam;
			}
			temp.exam = exam;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else if (answer == 'r' || answer == 'R') {
			srand(time(NULL));

			int g = 0;
			cout << "Enter how many values you want to generate or symbol to continue" << endl;
			cin >> g;
			for (int i = 0; i < g; i++) { temp.grades.push_back((rand() % 10) + 1); }	//filling array with random values

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			char answer;
			cout << "Do you want to generate exam grade? (y/n)" << endl;
			cin >> answer;
			if ((answer != 'y' && answer != 'Y') && (answer != 'n' && answer != 'N')) {
				cout << "There is no such answer. Y/y - generate exam grade, N/n - continue." << endl;
				cin >> answer;
			}
			else if (answer == 'y' || answer == 'Y') { temp.exam = (rand() % 10) + 1; }

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else {
			cout << "There is no such answer. Choose manual or random input. (m/r)" << endl;
			cin >> answer;
		}
	};
	
	cout << "Grades: ";
	for (int i = 0; i < temp.grades.size(); i++) { cout << temp.grades[i] << " "; }
	cout << endl << "Exam: " << temp.exam << endl;
	CalcData(temp);
}

void PrintData(Student& temp) {
	cout << left << setw(20) << temp.name << left << setw(20) << temp.surname << left << setw(10) << fixed << setprecision(2) << temp.final << endl;
}

int main()
{
	vector<Student>Group;
	Student temp;
	char answer;
	do {
		GatherData(temp);
		Group.push_back(temp);
		temp.exam = NULL;
		temp.grades.clear();

		cout << "Add new student? (y/n)" << endl;
		cin >> answer;
		while ((answer != 'y' && answer != 'Y') && (answer != 'n' && answer != 'N')) {
			cout << "There is no such answer. Y/y - add student, N/n - continue." << endl;
			cin >> answer;
		};
	} while (answer == 'y' || answer == 'Y');

	cout << left << setw(20) << "Name" << left << setw(20) << "Surname" << left << setw(10) << "Final grade" << endl;
	cout << "----------------------------------------------------" << endl;
	for (int i = 0; i < Group.size(); i++) { PrintData(Group[i]); }
	Group.clear();
}
