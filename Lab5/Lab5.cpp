#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Stack
{
	Stack* next;
	int value;
};

void Add(Stack*&, int);
void Delete(Stack*&);
void DeleteStack(Stack*&);
void Show(Stack*);
void SortAddress(Stack*&);
void SortValue(Stack*);
template<typename T = int>
void InputNumber(T&, string = "", T = numeric_limits<T>::min(), T = numeric_limits<T>::max());
int Select(const string*, int, string = "");

int main()
{
	system("chcp 1251");
	system("cls");
	Stack* stack = NULL;
Start:
	int size, value, sizeRange = 5, elementRange = 20;
	srand(static_cast<unsigned int>(time(0)));
	string variants[][100] = { { "Да", "Нет" }, { "Создать", "Задание", "Добавить", "Удалить", "Сортировка адресов", "Сортировка значений" } };
	switch (Select(variants[1], 6))
	{
	case 1:
		DeleteStack(stack);
		cout << "Создать случайный стек?" << "\n";
		if (Select(variants[0], 2) == 1)
		{
			size = 5 + rand() % sizeRange + 1;
			cout << "Размер стека: " << size << "\n\n";
			for (int i = 0; i < size; i++)
			{
				value = rand() % (elementRange * 2 + 1) - elementRange;
				cout << "[" << i << "]: " << value << "\n";
				Add(stack, value);
			}
		}
		else
		{
			InputNumber(size, "Введите размер стека: ", 0);
			cout << "\n";
			for (int i = 0; i < size; i++)
			{
				InputNumber(value, "[" + to_string(i) + "]: ");
				Add(stack, value);
			}
		}
		cout << "\nИтоговый вид:\n\n";
		break;
	case 2:
	{
		Stack** maxElement = &stack;
		for (Stack** tempPointer = &stack; *tempPointer; tempPointer = &(*tempPointer)->next)
			if ((*tempPointer)->value > (*maxElement)->value) maxElement = &(*tempPointer);
		Delete(*maxElement);
		break;
	}
	case 3:
		InputNumber(value, "Значение элемента: ");
		Add(stack, value);
		cout << "\n";
		break;
	case 4:
		Delete(stack);
		break;
	case 5:
		SortAddress(stack);
		break;
	case 6:
		SortValue(stack);
		break;
	}
	Show(stack);
	cout << "\n";
	goto Start;
}

void Add(Stack*& top, int value)
{
	Stack* newElement = new Stack;
	newElement->next = top;
	newElement->value = value;
	top = newElement;
}

void Delete(Stack*& top)
{
	if (!top) return;
	Stack* tempPointer = top->next;
	delete top;
	top = tempPointer;
}

void DeleteStack(Stack*& top)
{
	while (top) Delete(top);
}

void Show(Stack* top)
{
	Stack* tempPointer = top;
	for (int i = 0; tempPointer; i++, tempPointer = tempPointer->next) cout << "[" << i << "]" << ": " << tempPointer->value << "\n";
}

void SortAddress(Stack*& top)
{
	Add(top, 0);
	for (Stack* tempPointer = top; tempPointer; tempPointer = tempPointer->next)
	{
		for (Stack* nextTempPointer = tempPointer->next; nextTempPointer; nextTempPointer = nextTempPointer->next)
		{
			if (nextTempPointer->next && tempPointer->next->value > nextTempPointer->next->value)
			{
				Stack* tempElement = nextTempPointer->next;
				nextTempPointer->next = tempElement->next;
				tempElement->next = tempPointer->next;
				tempPointer->next = tempElement;
				nextTempPointer = tempPointer;
			}
		}
	}
	Delete(top);
}

void SortValue(Stack* top)
{
	for (Stack* tempPointer = top; tempPointer; tempPointer = tempPointer->next)
	{
		for (Stack* nextTempPointer = tempPointer->next; nextTempPointer; nextTempPointer = nextTempPointer->next)
		{
			if (tempPointer->value > nextTempPointer->value)
			{
				int tempValue = tempPointer->value;
				tempPointer->value = nextTempPointer->value;
				nextTempPointer->value = tempValue;
			}
		}
	}
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