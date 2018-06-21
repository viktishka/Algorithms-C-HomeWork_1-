#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

enum Cases{Best, Average, Worst};	//Случаи (Лучший, Средний и Худший)

void SelectionSort(int arr[], int length); //Сортировка выбором		
void InsertSort(int arr[], int length); //Сортировка вставками		
void ShellSort(int arr[], int length); //Сортировка Шелла			
void QuickSort(int arr[], int length); //Быстрая сортировка		
void MergeSort(int arr[], int length); //Сортировка слиянием	
void Merge(int arr[], int length, int L[], int lenL, int R[], int lenR); //Слияние 
void RadixSort(int arr[], int length); //Поразрядная сортировка	
void Print(int arr[], int length);	//Вывод всех элементов массива 
void WriteFile(int arr[], int length, Cases cases, double time);	//Запись тестовых данных в файл.txt
void Check(int arr[], int length);	//Проверка массива на отсортированность элементов 

//Генерация массива
int* GenerateArray(int length, Cases cases) {
	int *a = new int[length];
	srand(unsigned(time(NULL)));
	for (int i = 0; i < length; ++i) {
		a[i] = rand() % 3000000000 + 0;
	}
	if (cases == Best) {
		return a;
	}
	if (cases == Average) {
		return a;
	}
	if (cases == Worst) {
		return a;
	}
	return a;
}

int main() {
	int length = 100;
  //int length = 500;
  //int length = 1000;
  //int length = 5000;
  //int length = 10000;
  //int length = 50000;
  //int length = 100000;
	Cases cases = Best;
  //Cases cases = Average;
  //Cases cases = Worse;
	int *A = GenerateArray(length, cases); //Создание массива
	double start = clock(); //Время начала работы алгоритма
	RadixSort(A, length); //Непосредственно сортировка
	Print(A, length); //Вывод массива в консоль
	double finish = clock(); //Время окончания работы алгоритма
	long long time = finish - start; //Время выполнения алгоритма сортировки
	std::cout << time << " ms" << endl; //Формат времени = ms
	WriteFile(A, length, cases, time);	//Запись тестовых данных в файл.txt
	Check(A, length); //Проверка массива на отсортированность
	delete[] A; //Освобождение памяти (вызов деструктора)
}
void Print(int arr[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
}

//Алгоритм сортировки выбором
void SelectionSort(int arr[], int length) {
	long long n = 0;	//Счетчик сравнений
	int k = 0;	//Счетчик перестановок
	// Перебираем каждый элемент массива
	for (int i = 0; i < length - 1; i++)
	{
		int min_i = i;
		// Ищем элемент меньше min_i в остальной части массива
		for (int j = i + 1; j < length; j++)
		{
			// Если есть элемент меньше элемента min_i, то запоминаем его
			if (arr[j] < arr[min_i]) {
				min_i = j;
			}
			n++;
		}
    if (min_i != i) {
		  std::swap(arr[i], arr[min_i]);
		  k++;
	  }
  }
	cout << "Compares number: " << n << "\nReshuffles number: " << k << endl;
}

//Алгоритм сортировки вставками		
void InsertSort(int arr[], int length) {
	long long n = 0;	//сравнение
	int k = 0;
	for (int i = 1; i < length; i++) {
		int tmp = arr[i];
		int j = i-1;
		while (arr[j] > tmp && j >= 0) {
			k++;
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
		n++;
	}
	cout << "Compares number: " << n << "\nReshuffles number: " << k << endl;
}

//Сортировка Шелла
void ShellSort(int arr[], int length) {
	int h = 0;
	for (h = 1; h <= length/9; h = 3*h + 1);
	for (; h > 0; h /= 3) {
		for (int i = h; i < length; ++i) {
			int j = i;
			int tmp = arr[i];
			while (j >= h && tmp < arr[j - h]) {
				arr[j] = arr[j - h];
				j -= h;
			}
			arr[j] = tmp;
		}
	}
}
//Быстрая сортировка (сортировка Хоара)
void QuickSort(int arr[], int length) {
	int i = 0;
	int j = length - 1;
	bool side = false;
	while (i != j) { // процедура разбиения
		if (arr[i] > arr[j]) {
			std::swap(arr[i], arr[j]);
			side = !side;
		}
		if (side) {
			++i;
		}
		else {
			--j;
		}
	}
	// Рекурсивные вызовы для половинок 
	if (i > 1) QuickSort(arr, i);
	if (length > i + 1) QuickSort(arr + (i + 1), length - (i + 1));
} 

//Алгоритм сортировки слиянием
void MergeSort(int arr[], int length)
{
	if (length>1) {
		int middle = length/2;
		int rem = length - middle;
		int* L = new int[middle];
		int* R = new int[rem];
		for (int i = 0; i<length; i++) {
			if (i<middle) {
				L[i] = arr[i];
			}
			else {
				R[i - middle] = arr[i];
			}
		}
		MergeSort(L, middle);
		MergeSort(R, rem);
		Merge(arr, length, L, middle, R, rem);
	}
}
void Merge(int arr[], int length, int L[], int lenL, int R[], int lenR) {
	int i = 0;
	int j = 0;
	while (i<lenL || j<lenR) {
		if (i<lenL & j<lenR) {
			if (L[i] <= R[j]) {
				arr[i + j] = L[i];
				i++;
			}
			else {
				arr[i + j] = R[j];
				j++;
			}
		}
		else if (i<lenL) {
			arr[i + j] = L[i];
			i++;
		}
		else if (j<lenR) {
			arr[i + j] = R[j];
			j++;
		}
	}
}
//Поразрядная сортировка
void RadixSort(int arr[], int length) {
	int **count = new int*[10];
	int *b = new int[length];
	int i, j;

	if (length < 2) {
		return;
	}
	// инициализируем счетчик [cnt]
	for (j = 0; j < 10; j++) {
		count[j] = new int[257];
		for (i = 0; i < 257; i++) count[j][i] = 0;
	}
	// подсчитываем количество элементов для каждого значения j-го разряда
	for (i = 0; i < length; i++) {
		for (j = 0; j < 10; j++) {
			count[j][1 + ((arr[i] >> (8 * j)) & 0xff)]++;
		}
	}
	for (j = 0; j < 10; j++) {
		for (i = 1; i < 256; i++) count[j][i] += count[j][i - 1];
		// расставляем элементы из массива arr в массив b в указанном порядке
		for (i = 0; i < length; i++) {
			b[count[j][(arr[i] >> (8 * j)) & 0xff]++] = arr[i];
		}
		// копируем массив b на место массива arr
		for (i = 0; i < length; i++) arr[i] = b[i];
	}
	delete[] b;
	delete[] count;
}
//Запись тестовых данных в файл
void WriteFile(int arr[], int length, Cases cases, double time) {
	string text;
	if (cases == Best) text = "Best";
	if (cases == Average) text = "Average";
	if (cases == Worst) text = "Worst";

	ofstream fout;
	fout.open("Best100.txt"); //создаем поток в ИмяФайла.txt
	fout << "Array elements number: " << length << ", "
		 << text << " case, "
		 << "Execution time: " << time << " ms" << endl;
	for (int i = 0; i<length; i++) {
		fout << arr[i] << " "; // выводим в файл необходимые элементы в строку через пробел
	}
	fout.close(); //закрываем поток
}

//Проверка массива на отсортированность элементов
void Check(int arr[], int length) {
	int i;
	bool check;
	for (i = 1; i < length; i++) {
		if (arr[i] < arr[i - 1]) {
			check = false;
			break;
		}
		else check = true;
	}
	std::cout << ((check == true) ? "CORRECT":"INCORRECT") << endl;	
};