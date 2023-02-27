#include "Mylib.h"

struct Student {
	string name, surname;
	int* grades = 0;
	int g = 0;
	int exam = 0;
	float final = 0;
};
int N=1; //Struct array size

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
		if (temp.g != 0) {			//checks if there are values in "grades"
			float sum = 0;
			for (int i = 0; i < temp.g; i++) { sum += temp.grades[i]; }
			avg = (float) sum / temp.g;
		}
		else { avg = 0; }			//if there are no grades, average is equal 0
		
		temp.final = (float) (0.4 * avg) + (0.6 * temp.exam);
	} //calculates average
	else {
		float median = 0;
		if (temp.g != 0) {			//checks if there are values in "grades"
			sort(temp.grades, temp.grades + temp.g);
			if (temp.g % 2 == 0) { median = (float) (temp.grades[temp.g / 2] + temp.grades[temp.g / 2 - 1]) / 2.0; }
			else { median = temp.grades[temp.g / 2]; };
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
				int n = 1, p = 0; //n is for the size of an array, p is for position in the array
				int* a = new int[n];
				
				while (cin >> grade) {
					if (n == 1)	{							//initiated one time, used to create new slot for new data
						while (true) {
							if (grade >= 0 && grade <= 10) {
								a[p] = grade;
								n++;						//adds new slot to array							
								int* b = new int[n];	//new bigger array is created
								copy_n(a, 1, b);			//old array is copied to new bigger array
								delete[]a;					//old array is emptied
								a = b;						//old pointer "a" points to new array
								b = NULL;					//useless pointer "b" is deleted

								break;
							}
							else {
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "Wrong value. Please enter number from 0 to 10" << endl;
								cin >> grade;
							};
						}
					}
					else {
						while (true) {					//used to extend array as much as needed and fill it
							if (grade >= 0 && grade <= 10) {
								n++;
								p++;					//moving to next "a" array slot
								a[p] = grade;
								int* b = new int[n];
								copy(a, a + (n - 1), b);
								delete[]a;
								a = b;
								b = NULL;

								break;
							}
							else {
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "Wrong value. Please enter number from 0 to 10" << endl;
								cin >> grade;
							};
						}
					}
				}
				
				temp.grades = a;			//all student's grades are stored in struct
				temp.g = n-1;				//how many grades are stored

				a = NULL;					//useless pointer is cleared
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

				cout << "Enter how many values you want to generate or symbol to continue" << endl;
				cin >> temp.g;
				temp.grades = new int[temp.g];												//defining grade array size
				for (int i = 0; i < temp.g; i++) { temp.grades[i] = (rand() % 10) + 1; }	//filling array with random values
				
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				char answer;
				cout << "Do you want to generate exam grade? (y/n)" << endl;
				cin >> answer;
				if ((answer != 'y' && answer != 'Y') && (answer != 'n' && answer != 'N')) {
					cout << "There is no such answer. Y/y - generate exam grade, N/n - continue." << endl;
					cin >> answer;
				}
				else if (answer == 'y' || answer == 'Y') {	temp.exam = (rand() % 10) + 1;	}

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
	for (int i = 0; i < temp.g; i++) { cout << temp.grades[i] << " "; }
	cout << endl << "Exam: " << temp.exam << endl;

	CalcData(temp);
}

void PrintData(Student& temp) {
	cout << left << setw(20) << temp.name << left << setw(20) << temp.surname << left << setw(10) << fixed << setprecision(2) << temp.final << endl;
}

int main()
{
	Student* Group;								//pointer to struct array
	int p = 0;									//p - position in array
	char answer;
	Group = new Student[N];
	do {										//used to extend struct array and fill every struct with data
		GatherData(Group[p]);
		N++;
		p++;
		Student *temp = new Student[N];			//new struct array slot
		copy(Group, Group + (N - 1), temp);		//old array copied to new extended array
		delete[]Group;
		Group = temp;
		temp = NULL;

		cout << "Add new student? (y/n)" << endl;
		cin >> answer;
		while ((answer != 'y' && answer != 'Y') && (answer != 'n' && answer != 'N')) {
			cout << "There is no such answer. Y/y - add student, N/n - continue." << endl;
			cin >> answer;
		};
	} while (answer == 'y' || answer == 'Y');
	
	N--; //since the last array slot is empty, the value N is not accurate and we need to reduce the value by 1
	cout << left << setw(20) << "Name" << left << setw(20) << "Surname" << left << setw(10) << "Final grade" << endl;
	cout << "----------------------------------------------------" << endl;
	for (int i = 0; i < N; i++) { PrintData(Group[i]); }
}
