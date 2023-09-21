#include <windows.h>
#include <iostream>


int size_numbers = 0;
int* numbers = nullptr;
int min_num = 0;
int max_num = 0;
int* index_min= nullptr;
int* index_max = nullptr;
int counter_min = 0;
int counter_max = 0;
int average_number = 0;


DWORD WINAPI min_max(LPVOID)
{
	min_num = numbers[0];
	max_num = numbers[0];

	for (int i = 0; i < size_numbers; i++)
	{
		if (min_num > numbers[i])
			min_num = numbers[i];
		Sleep(7);

		if (max_num < numbers[i])
			max_num = numbers[i];
		Sleep(7);
	}

	for (int i = 0; i < size_numbers; i++)
	{
		if (min_num == numbers[i])
		{
			index_min[counter_min] = i;
			counter_min++;
		}
		else if (max_num == numbers[i])
		{
			index_max[counter_max] = i;
			counter_max++;
		}
	}

	std::cout << "\nMinimal element " << min_num;
	std::cout << "\nMaximal element " << max_num;

	return 0;
}


DWORD WINAPI average(LPVOID)
{
	for (int i = 0; i < size_numbers; i++)
	{
		average_number += numbers[i];
		Sleep(12);
	}

	average_number /= size_numbers;

	return 0;
}


int main()
{
	HANDLE hThread_min_max;
	DWORD IDThread_min_max;
	HANDLE hThread_average;
	DWORD IDThread_average;

	std::cout << " Enter the number of elements \n";
	std::cin >> size_numbers;
	std::cout << "Enter elements \n";

	numbers = new int[size_numbers];
	index_min = new int[size_numbers];
	index_max = new int[size_numbers];

	for (int i = 0; i < size_numbers; i++)
		std::cin >> numbers[i];

	hThread_min_max = CreateThread(NULL, 0, min_max, NULL, 0, &IDThread_min_max);
	hThread_average = CreateThread(NULL, 0, average, NULL, 0, &IDThread_average);
	if (hThread_min_max == NULL || hThread_average == NULL)
		return GetLastError();

	WaitForSingleObject(hThread_min_max, INFINITE);
	WaitForSingleObject(hThread_average, INFINITE);

	for (int i = 0; i < counter_min;i++)
		numbers[index_min[i]] = average_number;
	for (int i = 0; i < counter_max;i++)
		numbers[index_max[i]] = average_number;

	std::cout << "\n";

	for (int i = 0; i < size_numbers;i++)
		std::cout << numbers[i] << " ";

	CloseHandle(hThread_min_max);
	CloseHandle(hThread_average);

	delete[] numbers;
	delete[] index_max;
	delete[] index_min;

	return 0;
}