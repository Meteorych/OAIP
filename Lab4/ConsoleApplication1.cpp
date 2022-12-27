#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct Table
{
	string destination;
	time_t time;
	time_t date;
	int count;
};

template<typename T = int>
void InputNumber(T&, string = "", T = numeric_limits<T>::min(), T = numeric_limits<T>::max());
int Select(const string*, int, string = "");
void ChangeTableInfo(Table&);
void ShowTableInfo(Table);
void ShowTablesInfo(Table[], int);
void InputDate(time_t&, string = "");
void ShowDate(time_t, string = "");
void InputTime(time_t&, string = "");
void ShowTime(time_t, string = "");
template<typename T = int>
void SelectionSort(Table[], int, T Table::* = &Table::count);
template<typename T = int>
void QuickSort(Table[], int, int, T Table::* = &Table::count);
template<typename T = int>
int LinearSearch(Table[], int, T, T Table::* = &Table::count);
template<typename T = int>
int BinarySearch(Table[], int, int, T, T Table::* = &Table::count);


int main()
{
	system("chcp 1251");
	system("cls");
Start:
	int n, input, result;
	Table* tables;
	int key;
	string variants[][100] = { { "Да", "Нет" }, { "Прочесть файл", "Записать новый" },
	{ "Задание", "Сортировка прямым выбором", "Быстрая сортировка", "Линейный поиск", "Двоичный поиск" } };
	ifstream fin("Structures.txt", ios::binary);
	fin.seekg(0, ios::end);
	if ((int)fin.tellg() > 0 && Select(variants[1], 2) == 1)
	{
		n = (int)fin.tellg() / sizeof(Table);
		fin.seekg(0, ios::beg);
		tables = new Table[n]{};
		fin.read((char*)tables, sizeof(*tables) * n);
		ShowTablesInfo(tables, n);
		while (1)
		{
			if (Select(variants[0], 2, "Изменить файл?") == 1)
			{
				InputNumber(input, "Какой номер (от 1)?\n", 1, n);
				cout << "\n";
				ChangeTableInfo(tables[input - 1]);
				ShowTablesInfo(tables, n);
			}
			else break;
		}
	}
	else
	{
		InputNumber(n, "Количество записей: ", 1);
		cout << "\n";
		tables = new Table[n]{};
		for (int i = 0; i < n; i++) ChangeTableInfo(tables[i]);
	}
	ofstream fout("Structures.txt", ios::binary);
	fout.write((char*)tables, sizeof(*tables) * n);
	fout.close();
	string N;
	int m;
	int k;
	int t;
	bool yes = false;
	switch (Select(variants[2], 5, "Выберите операцию:"))
	{
	case 1:
		cout << "Пункт назначения: ";
		getline(cin, N);
		InputNumber(m, "Число мест: ", 1);
		InputNumber(k, "День: ", 1, 31);
		InputNumber(t, "Час: ", 0, 23);
		cout << "\n";
		for (int i = 0; i < n; i++)
		{
			if (tables[i].destination == N && tables[i].count >= m)
			{
				tm date;
				localtime_s(&date, &tables[i].time);
				if (date.tm_mday == k && date.tm_hour <= t)
				{
					ShowTableInfo(tables[i]);
					yes = true;
				}
			}
		}
		if (!yes) cout << "Невозможно выполнить заказ\n\n";
		break;
	case 2:
		SelectionSort(tables, n);
		ShowTablesInfo(tables, n);
		break;
	case 3:
		QuickSort(tables, 0, n - 1);
		ShowTablesInfo(tables, n);
		break;
	case 4:
		InputNumber(key, "Нужное число свободных мест: ");
		cout << "\n";
		result = LinearSearch(tables, n, key);
		if (result >= 0) ShowTableInfo(tables[result]);
		else cout << "Элемент не найден\n\n";
		break;
	case 5:
		if (Select(variants[0], 2, "Массив будет отсортирован, продолжить?") != 1) break;
		QuickSort(tables, 0, n - 1);
		ShowTablesInfo(tables, n);
		InputNumber(key, "Нужное число свободных мест: ");
		cout << "\n";
		result = BinarySearch(tables, 0, n, key);
		if (result >= 0) ShowTableInfo(tables[result]);
		else cout << "Элемент не найден\n\n";
		break;
	}
	goto Start;
}

template<typename T>
void InputNumber(T& n, string text, T minVlaue, T maxValue)
{
	cout << text;
	while (!(cin >> n) || n < minVlaue || n > maxValue)
	{
		cout << "Введите корректное значение\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int Select(const string* variants, int count, string question)
{
	int choice;
	if (question != "") cout << question << "\n";
	for (int i = 0; i < count; i++) cout << i + 1 << " - " << variants[i] << "\n";
	InputNumber(choice, "", 1, count);
	cout << "\n";
	return choice;
}

void InputDate(time_t& time, string text)
{
	cout << text;
	tm date{};
	InputNumber(date.tm_mday, "День: ", 1, 31);
	InputNumber(date.tm_mon, "Месяц: ", 1, 12);
	InputNumber(date.tm_year, "Год: ", 1971);
	date.tm_year -= 1900;
	date.tm_mon--;
	int temp = date.tm_mday;
	time = mktime(&date);
	if (date.tm_mday != temp) ShowDate(time, "Дата исправлена: ");
}

void ShowDate(time_t time, string text)
{
	cout << text;
	tm date;
	localtime_s(&date, &time);
	cout << (date.tm_mday < 10 ? "0" : "") << date.tm_mday << "." <<
		(date.tm_mon + 1 < 10 ? "0" : "") << date.tm_mon + 1 << "." << date.tm_year + 1900;
}

void InputTime(time_t& time, string text)
{
	cout << text;
	tm tmTime;
	localtime_s(&tmTime, &time);
	InputNumber(tmTime.tm_hour, "Час: ", 0, 23);
	InputNumber(tmTime.tm_min, "Минута: ", 0, 59);
	time = mktime(&tmTime);
}

void ShowTime(time_t time, string text)
{
	cout << text;
	tm date;
	localtime_s(&date, &time);
	cout << (date.tm_hour < 10 ? "0" : "") << date.tm_hour <<
		":" << (date.tm_min < 10 ? "0" : "") << date.tm_min;
}

void ChangeTableInfo(Table& table)
{
	InputDate(table.date, "Дата выезда:\n");
	cout << "Пункт назначения: ";
	getline(cin, table.destination);
	table.time = table.date;
	InputTime(table.time, "Время отправления:\n");
	InputNumber(table.count, "Число свободных мест: ", 0);
	cout << "\n";
}

void ShowTableInfo(Table table)
{
	ShowDate(table.date, "Дата выезда: ");
	cout << "\n";
	cout << "Пункт назначения: " << table.destination << "\n";
	ShowTime(table.time, "Время отправления: ");
	cout << "\n";
	cout << "Число свободных мест: " << table.count << "\n\n";
}

void ShowTablesInfo(Table tables[], int n)
{
	for (int i = 0; i < n; i++) ShowTableInfo(tables[i]);
}

template<typename T>
void SelectionSort(Table array[], int n, T Table::* keyPtr)
{
	for (int i = 0; i < n - 1; i++)
	{
		int m = i;
		for (int j = i + 1; j < n; j++) if (array[i].*keyPtr > array[j].*keyPtr) m = j;
		if (m == i) continue;
		Table temp = array[i];
		array[i] = array[m];
		array[m] = temp;
	}
}

template<typename T>
void QuickSort(Table array[], int begin, int end, T Table::* keyPtr)
{
	int left = begin, right = end, middle = (left + right) / 2;
	do
	{
		while (array[left].*keyPtr < array[middle].*keyPtr) left++;
		while (array[right].*keyPtr > array[middle].*keyPtr) right--;
		if (left <= right)
		{
			Table temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			left++;
			right--;
		}
	} while (left <= right);
	if (begin < right) QuickSort(array, begin, right, keyPtr);
	if (left < end) QuickSort(array, left, end, keyPtr);
}

template<typename T>
int LinearSearch(Table array[], int n, T key, T Table::* keyPtr)
{
	int result = -1;
	for (int i = 0; i < n; i++) if (array[i].*keyPtr == key) result = i;
	return result;
}

template<typename T>
int BinarySearch(Table array[], int left, int right, T key, T Table::* keyPtr)
{
	if (left > right) return -1;
	int middle = (left + right) / 2;
	if (array[middle].*keyPtr > key) return BinarySearch(array, left, middle - 1, key, keyPtr);
	if (array[middle].*keyPtr < key) return BinarySearch(array, middle + 1, right, key, keyPtr);
	return middle;
}