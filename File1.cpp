#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Student
{
	char name[100];
	int year, group, physics, math, informatics, chem;
	float averageMark;
};

void InputInt(int &, int = INT_MIN, int = INT_MAX, string = "", string = "");
int Select(const string *, int, string = "");
void ShowStudentInfo(Student, int);
void ChangeStudentInfo(Student &, int);

int main()
{
	system("chcp 1251");
	system("cls");
Start:
	int n, input;
	float groupAverageMark = 0;
	Student *students;
	string variants[][100] = { { "Да", "Нет" }, { 	"Прочесть файл", "Записать новый", } };
	ifstream fin("Structures.txt", ios::binary);
	fin.seekg(0, ios::end);
	if ((int)fin.tellg() > 0 && Select(variants[1], 2) == 1)
	{
		n = (int)fin.tellg() / sizeof(Student);
		fin.seekg(0, ios::beg);
		students = new Student[n]{};
		fin.read((char*)students, sizeof(*students) * n);
		for (int i = 0; i < n; i++) ShowStudentInfo(students[i], i);
		while (1)
		{
			if (n > 0 && Select(variants[0], 2, "Изменить файл?") == 1)
			{
				InputInt(input, 1, 100, "Какой номер?\n", "\n");
				ChangeStudentInfo(students[input - 1], input - 1);
			}
			else break;
		}
	}
	else
	{
		InputInt(n, 1, 100, "Количество студентов\n", "\n");
		students = new Student[n]{};
		for (int i = 0; i < n; i++) ChangeStudentInfo(students[i], i);
	}
	ofstream fout("Structures.txt", ios::binary);
	fout.write((char*)students, sizeof(*students) * n);
	InputInt(input, 0, 10, "Введите нужную группу\n", "\n");
	int KolSt = 0;
	for (int i = 0; i < n; i++) if(students[i].group == input)  KolSt = KolSt+1;
	for (int i = 0; i < n; i++) if(students[i].group == input) groupAverageMark += students[i].averageMark / KolSt;
	cout << "\n" << "Средний балл студентов группы " << input << ": " << groupAverageMark << "\n\n";
	cout << "\n" << "Студенты группы "  << input << " со средним баллом больше общего среднего балла:\n\n";
	for (int i = 0, j = 0; i < n; i++)
	{
		if (students[i].averageMark > groupAverageMark && students[i].group == input)
		{
			cout << (j == 1 ? ", " : "") << students[i].name;
			j = 1;
		}
		if (i == n - 1 && j == 1) cout << "\n\n";
	}
	goto Start;
}

void InputInt(int &n, int minValue, int maxValue, string text1, string text2)
{
	cout << text1;
	while (!(cin >> n) || n < minValue || n > maxValue)
	{
		cout << "Введите корректное значение\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << text2;
}

int Select(const string *variants, int count, string question)
{
	int choice;
	if (question != "") cout << question << "\n";
	for (int i = 0; i < count; i++) cout << i + 1 << " - " << variants[i] << "\n";
	InputInt(choice, 1, count, "", "\n");
	return choice;
}

void ShowStudentInfo(Student student, int n)
{
	cout << "Студент номер " << n + 1 << ":\n";
	cout << "Имя: " << student.name << "\n";
	cout << "Год рождения: " << student.year << "\n";
	cout << "Номер группы: " << student.group << "\n";
	cout << "Оценка за семестр по физике: " << student.physics << "\n";
	cout << "Оценка за семестр по математике: " << student.math << "\n";
	cout << "Оценка за семестр по информатике: " << student.informatics << "\n";
	cout << "Оценка за семестр по химии: " << student.chem << "\n";
	cout << "Средний балл: " << student.averageMark << "\n\n";
}

void ChangeStudentInfo(Student &student, int n)
{
	cout << "Студент номер " << n + 1 << ":\n";
	cout << "Имя: ";
	cin >> student.name;
	InputInt(student.year, 0, 2010, "Год рождения: ");
	InputInt(student.group, 0, 10, "Номер группы: ");
	InputInt(student.physics, 0, 10, "Оценка за семестр по физике: ");
	InputInt(student.math, 0, 10, "Оценка за семестр по математике: ");
	InputInt(student.informatics, 0, 10, "Оценка за семестр по информатике: ");
	InputInt(student.chem, 0, 10, "Оценка за семестр по химии: ");
	student.averageMark = (student.physics + student.math + student.informatics + student.chem) / 4.0f;
	cout << "Средний балл " << student.averageMark << "\n\n";
}
