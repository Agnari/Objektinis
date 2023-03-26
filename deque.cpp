#include "./headers/Mylib.h"
#include "./headers/DeStudent.h"

bool Compare(const Student &a, const Student &b)
{
    return a.finalA < b.finalA;
}

void CalcData(Student &tempDe)
{
    float avg = 0;
    if (!tempDe.grades.empty())
    {
        float sum = 0;
        for (int grade : tempDe.grades)
        {
            sum += grade;
        }
        avg = (float)sum / tempDe.grades.size();
    }
    else
    {
        avg = 0;
    }

    tempDe.finalA = (float)(0.4 * avg) + (0.6 * tempDe.exam);

    float median = 0;
    if (!tempDe.grades.empty())
    {
        std::sort(tempDe.grades.begin(), tempDe.grades.end());
        if (tempDe.grades.size() % 2 == 0)
        {
            int mid1 = tempDe.grades.size() / 2 - 1;
            int mid2 = tempDe.grades.size() / 2;
            median = (float)(tempDe.grades[mid1] + tempDe.grades[mid2]) / 2.0;
        }
        else
        {
            int mid = tempDe.grades.size() / 2;
            median = tempDe.grades[mid];
        }
    }
    else
    {
        median = 0;
    }

    tempDe.finalM = (0.4 * median) + (0.6 * tempDe.exam);
}

void FillStudentStruct(istringstream &line)
{
    line >> tempDe.name >> tempDe.surname;
    int grade = 0;
    for (int j = 0; j < 10; j++)
    {
        line >> grade;
        if (grade >= 1 && grade <= 10)
        {
            tempDe.grades.push_back(grade);
        }
        else
        {
            throw "Bad data format in file";
        }
    }

    int exam;
    line >> exam;
    if (exam >= 1 && exam <= 10)
    {
        tempDe.exam = exam;
    }
    else
    {
        throw "Data in file must contain name, surname, homework grades and exam grade. Please, check your file.";
    }

    CalcData(tempDe);
    Group.push_back(tempDe);
    tempDe.exam = NULL;
    tempDe.grades.clear();
}

void Read(int k)
{

    string filename = "C:\\Users\\Home\\OneDrive\\Documents\\GitHub\\Objektinis\\data\\" + to_string(k) + ".txt";
    string header;
    ifstream readf(filename);
    getline(readf, header);
    string line;

    while (getline(readf, line))
    {
        istringstream x(line);
        FillStudentStruct(x);
    }

    readf.close();
}

void TwoGroups()
{

    for (const auto &tempDe : Group)
    {
        if (tempDe.finalA > 5)
        {
            Smart.push_back(tempDe);
        }
        else
        {
            Stupid.push_back(tempDe);
        }
    }
}

int main()
{
    int k = 1000;
    for (int i = 0; i < 5; i++)
    {
        auto start1 = high_resolution_clock::now();
        Read(k);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        cout << "File " << k << ".txt read in: " << fixed << setprecision(4) << duration1.count() / 1000000.0 << " seconds" << endl;

        auto start2 = high_resolution_clock::now();
        sort(Group.begin(), Group.end(), Compare);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        cout << "File " << k << ".txt sorted by grade: " << fixed << setprecision(4) << duration1.count() / 1000000.0 << duration2.count() << " seconds" << endl;

        auto start3 = high_resolution_clock::now();
        TwoGroups();
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        cout << "File " << k << ".txt sorted into smart and stupid in: " << fixed << setprecision(4) << duration1.count() / 1000000.0 << duration3.count() << " seconds" << endl;

        Group.clear();

        k = k * 10;
    }
}