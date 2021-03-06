// Task1_CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//задача 19. В данном массиве найдите наибольшую серию подряд идущих элементов, расположенных по возрастанию.
//Сынкова Анастасия

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//ввод числа с заданными границами
int InputNum(const char *txt, int min, int max)
{
	int num;
	cout << txt << endl; //вывод вопроса на экран
	cin >> num;
	while ((num < min) || (num > max)) //пока число num не попадает в диапозон [min..max] 
	{
		cout << "Недопустимое значение, введите еще раз:" << endl;
		cin >> num;
	}
	return num;
}

int* CreateMas(int n)
{
	int *A; //создаём массив введённой размерности
	A = new int[n]; 
	return A;
}

//ввод размерности из файла
void InputMasSizeFile(ifstream &in, int* n)
{
	if (in.is_open())
		in >> *n;
}

//ввод массива из файла
void InputMasFile(int* mas, ifstream &FileIn, int n)
{
	if (FileIn.is_open())
	{
		cout << "Введенный массив:\n";
		for (int i = 0; i < n; ++i)
		{
			FileIn >> mas[i];
			cout << mas[i] << " ";
		}
		cout << endl;
	}
}

//ввод массива с клавиатуры
int* InputMasKey(int *n)
{
	*n = InputNum("Введите размер массива", 0, 50);
	int *A; //создаём массив введённой размерности
	A = new int[*n];
	for (int i = 0; i < *n; i++) //вводим элементы массива
	{
		cout << "A[" << i + 1 << "] = ";
		cin >> A[i];
	}

	cout << "Введенный массив:\n";
	for (int i = 0; i < *n; ++i)
		cout << A[i] << " ";
	cout << endl;
	return A;
}

//проверка массива на максимальное количество подряд идущих возрастающих элементов
int CheckMas(int *mas, int n, int &first, int &last)
{
	int max = 1;
	int l = 1;
	for (int i = 1; i < n; i++) //идем по массиву
	{
		if (mas[i] > mas[i - 1]) //если очередной элемент больше предыдущего
			l++;
		else
			l = 1; //сбрасываем количество в 1

		if (l > max) //если очередное количество возрастающих элементов больше максимального
		{
			max = l; //меняем максимум
			first = i - l + 1; //начальная позиция возрастающей последовательности
			last = i + 1; //конечная позиция возрастающей последовательности
		}
	}
	return max;
}

//вывод результата в файл
void OutputResFile(int *mas, int n)
{
	int f = 0, lt = n;
	int max = CheckMas(mas, n,  f, lt);
	ofstream FileOut("output.txt");
	if (FileOut.is_open())
	{
		FileOut << "Самая длинная последовательность идущих подряд возрастающих элементов состоит из: " << max << " элементов \n";
		for (int j = f; j < lt; ++j)
			FileOut << mas[j] << " ";
		cout << endl;
		FileOut << endl;
	}
	FileOut.close();
}

//вывод результата в консоль
void OutputResKey(int *mas, int n)
{
	int f = 0, lt = n;
	int max = CheckMas(mas, n, f, lt);
	cout << "Самая длинная последовательность идущих подряд возрастающих элементов состоит из: " << max << " элементов \n";
	for (int j = f; j < lt; j++)
		cout << mas[j] << " ";
	cout << endl;
}

//выбор пункта меню ввода
int SelectInputMenuItem(void)
{
	cout << "1 - Ввод массива из консоли" << endl;
	cout << "2 - Ввод массива из файла" << endl;
	return InputNum("0 - выход", 0, 2);
}

//выбор пункта меню вывода результата
int SelectResultMenuItem(void)
{
	cout << "1 - Вывести результат в консоль" << endl;
	cout << "2 - Вывести результат в файл" << endl;
	return InputNum("0 - выход", 0, 2);
}

int main()
{

	setlocale(LC_ALL, "Russian");//русский язык	
	ifstream FileIn("input.txt");
	int n;

	int *A = new int[0]; 
	int *ptr = A;

	int MenuItem = -1;
	int SubMenuItem = -1;
	MenuItem = SelectInputMenuItem();
	switch (MenuItem)
	{
	case 1:
		A = InputMasKey(&n);
		break;
	case 2:
		InputMasSizeFile(FileIn, &n);
		A = CreateMas(n);
		InputMasFile(A, FileIn, n);
		break;
	default:
		return 0;
	}

	SubMenuItem = SelectResultMenuItem();
	switch (SubMenuItem)
	{
	case 1:
		OutputResKey(A, n);
		system("pause");
		break;
	case 2:
		OutputResFile(A, n);
		system("pause");
		break;
	default:
		return 0;
	}
	FileIn.close();
	return 0;
}