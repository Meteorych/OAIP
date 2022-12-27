#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct ListElement
{
	ListElement* next = NULL;
	ListElement* prev = NULL;
	int value;
};

struct List
{
	ListElement* begin = NULL;
	ListElement* end = NULL;
};

void AddToBegin(List*, int);
void AddToEnd(List*, int);
void Delete(ListElement*, List*);
void DeleteList(List*);
void ShowFromBegin(List*);
void ShowFromEnd(List*);
template<typename T = int>
void InputNumber(T&, string = "", T = numeric_limits<T>::min(), T = numeric_limits<T>::max());
int Select(const string*, int, string = "");

int main()
{
	system("chcp 1251");
	system("cls");
	List* list = new List;
Start:
	int size, value, sizeRange = 5, elementRange = 20;
	srand(static_cast<unsigned int>(time(0)));
	string variants[][100] = { { "Да", "Нет" }, { "Создать", "Задание", "Добавить в начало", "Добавить в конец", "Просмотр с начала", "Просмотр с конца" } };
	switch (Select(variants[1], 6))
	{
	case 1:
	{
		DeleteList(list);
		cout << "Создать случайный список?" << "\n";
		if (Select(variants[0], 2) == 1)
		{
			size = 5 + rand() % sizeRange + 1;
			cout << "Размер списка: " << size << "\n\n";
			for (int i = 0; i < size; i++)
			{
				value = rand() % (elementRange * 2 + 1) - elementRange;
				cout << "[" << i << "]: " << value << "\n";
				AddToBegin(list, value);
			}
		}
		else
		{
			InputNumber(size, "Введите размер списка: ", 0);
			cout << "\n";
			for (int i = 0; i < size; i++)
			{
				InputNumber(value, "[" + to_string(i) + "]: ");
				AddToBegin(list, value);
			}
		}
		cout << "\nИтоговый вид:\n\n";
		ShowFromBegin(list);
		break;
	}
	case 2:
	{
		ListElement* maxElement = list->begin;
		for (ListElement* tempPointer = list->begin; tempPointer; tempPointer = tempPointer->next)
			if (tempPointer->value > maxElement->value) maxElement = tempPointer;
		Delete(maxElement, list);
		ShowFromBegin(list);
		break;
	}
	case 3:
		InputNumber(value, "Значение элемента: ");
		AddToBegin(list, value);
		break;
	case 4:
		InputNumber(value, "Значение элемента: ");
		AddToEnd(list, value);
		break;
	case 5:
		ShowFromBegin(list);
		break;
	case 6:
		ShowFromEnd(list);
		break;
	}
	cout << "\n";
	goto Start;
}

void AddToBegin(List* list, int value)
{
	ListElement* newElement = new ListElement;
	newElement->next = list->begin;
	newElement->value = value;
	if (list->begin) list->begin->prev = newElement;
	if (!list->end) list->end = newElement;
	list->begin = newElement;
}

void AddToEnd(List* list, int value)
{
	ListElement* newElement = new ListElement;
	newElement->prev = list->end;
	newElement->value = value;
	if (list->end) list->end->next = newElement;
	if (!list->begin) list->begin = newElement;
	list->end = newElement;
}

void Delete(ListElement* element, List* list)
{
	if (element == list->begin && element == list->end)
	{
		list->begin = list->end = NULL;
	}
	else if (element == list->begin)
	{
		list->begin = element->next;
		list->begin->prev = NULL;
	}
	else if (element == list->end)
	{
		list->end = element->prev;
		list->end->next = NULL;
	}
	else
	{
		element->next->prev = element->prev;
		element->prev->next = element->next;
	}
	delete element;
}

void DeleteList(List* list)
{
	while (list->begin) Delete(list->begin, list);
}

void ShowFromBegin(List* list)
{
	ListElement* tempPointer = list->begin;
	for (int i = 0; tempPointer; i++, tempPointer = tempPointer->next) cout << "[" << i << "]" << ": " << tempPointer->value << "\n";
}

void ShowFromEnd(List* list)
{
	ListElement* tempPointer = list->end;
	for (int i = 0; tempPointer; i++, tempPointer = tempPointer->prev) cout << "[" << i << "]" << ": " << tempPointer->value << "\n";
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