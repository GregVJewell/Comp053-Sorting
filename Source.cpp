#include<iostream>
#include<vector>
#include<utility>
#include<ctime>
#include<conio.h>

#include "Class File.h"

using namespace std;

vector<Products*> list;
Products* listPtr = NULL;

int Partition(Products* numbers, int i, int k) {
	int l = 0;
	int h = 0;
	int midpoint = 0;
	int pivot = 0;
	Products* temp = NULL;
	bool done = false;

	midpoint = i + (k - i) / 2;
	pivot = list.at(midpoint)->getItemPrice();

	l = i;
	h = k;

	while (!done) {
		while (list.at(l)->getItemPrice() < pivot) {
			++l;
		}
		while (pivot < list.at(h)->getItemPrice()) {
			--h;
		}
		if (l >= h) {
			done = true;
		}
		else {
			temp = list.at(l);
			list.at(l) = list.at(h);
			list.at(h) = temp;

			++l;
			--h;
		}
	}
	return h;
}

void Quicksort(Products* numbers, int i, int k) {
	int j = 0;

	if (i >= k) {
		return;
	}

	j = Partition(numbers, i, k);

	Quicksort(numbers, i, j);
	Quicksort(numbers, j + 1, k);
}

void merge(Products* arr, int i, int j, int k) {
	int mergedSize = k - i + 1;
		int mergePos = 0;
		int leftPos = i;
		int rightPos = j + 1;
		Products *mergedNumbers = new Products[mergedSize];

		while (leftPos <= j && rightPos <= k) {
			if (list.at(leftPos)->getItemPrice() <= list.at(rightPos)->getItemPrice()) {
				mergedNumbers[mergePos] = *list.at(leftPos);
					++leftPos;
			}
			else {
				mergedNumbers[mergePos] = *list.at(rightPos);
					++rightPos;
			}
			++mergePos;
		}

	while (leftPos <= j) {
		mergedNumbers[mergePos] = *list.at(leftPos);
			++leftPos;
			++mergePos;
	}

	while (rightPos <= k) {
		mergedNumbers[mergePos] = *list.at(rightPos);
		++rightPos;
		++mergePos;
	}

	for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
		list.at(i + mergePos) = &mergedNumbers[mergePos];
	}
}

void mergeSort(Products* arr, int i, int k) {
	int j = 0;

		if (i < k) {
			j = (i + k) / 2;

			mergeSort(arr, i, j);
			mergeSort(arr, j + 1, k);

			merge(arr, i, j, k);
		}
}

void shellSort(Products* arr, int arrSize) {
	for (int gap = arrSize / 2; gap > 0; gap /= 2) {

		for (int i = gap; i < arrSize; i += 1) {
			Products *temp = list.at(i);

			int j;
			for (j = i; j >= gap && list.at(j - gap)->getItemPrice() > temp->getItemPrice(); j -= gap)
				list.at(j) = list.at(j - gap);

			list.at(j) = temp;
		}
	}
}

int getMax(Products* arr, int arrSize) {
	int mx = list.at(0)->getItemPrice();

	for (int i = 1; i < arrSize; ++i)
		if (list.at(i)->getItemPrice() > mx)
			mx = list.at(i)->getItemPrice();
	return mx;
}

void countSort(Products* arr, int arrSize, int exp) {

	Products *output[200];
	int i, count[10] = { 0 };

	for (i = 0; i < arrSize; ++i)
		count[(list.at(i)->getItemPrice() / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = arrSize - 1; i >= 0; i--)
	{
		output[count[(list.at(i)->getItemPrice() / exp) % 10] - 1] = list.at(i);
		count[(list.at(i)->getItemPrice() / exp) % 10]--;
	}

	for (i = 0; i < arrSize; i++)
		list.at(i) = output[i];
}

void radixSort(Products* arr, int arrSize) {

	int m = getMax(arr, arrSize);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, arrSize, exp);
}

double diffClock(clock_t clock1, clock_t clock2) {
	double diffticks = clock2 - clock1;
	double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
	return diffms;
}

int main() {

	int choice;
	int h;

	for (unsigned int i = 0; i < 200; ++i) {
		listPtr = new Products(i, rand() % 600);
		list.push_back(listPtr);
		list.at(i)->printInfo();
	}

	cout << "\nPlease select the NUMBER of the sorting method you would like to run on the above" << endl;
	cout << "1) Insertion Sort" << endl;
	cout << "2) Merge Sort" << endl;
	cout << "3) Quick Sort" << endl;
	cout << "4) Radix Sort" << endl;
	cout << "5) Selection Sort" << endl;
	cout << "6) Shell Sort" << endl;
	cin >> choice;

	clock_t start = clock(); //Time Start!

	if (choice == 1) {
		cout << "Running Insertion Sort!" << endl;

		int i = 0;
		int j = 0;
		Products* temp = NULL;

		for (i = 1; i < 200; ++i) {
			j = i;
			while (j > 0 && list.at(j)->getItemPrice() < list.at(j - 1)->getItemPrice()) {
				temp = list.at(j);
				list.at(j) = list.at(j - 1);
				list.at(j - 1) = temp;
				--j;
			}
		}

	}
	else if (choice == 2) {
		cout << "Running Merge Sort!" << endl;
		mergeSort(listPtr, list.at(0)->getItemNumber(), list.size() - 1);
	}
	else if (choice == 3) {
		cout << "Running Quick Sort!" << endl;
		Quicksort(listPtr, list.at(0)->getItemNumber(), list.size() - 1);

	}
	else if (choice == 4) {
		cout << "Running Radix Sort!" << endl;
		radixSort(listPtr, list.size());
	}
	else if (choice == 5) {
		cout << "Running Selection Sort!" << endl;
		int i = 0;
		int j = 0;
		int indexSmallest = 0;
		Products* temp = NULL;

		for (i = 0; i < 200 - 1; ++i) {
			indexSmallest = i;
			for (j = i + 1; j < 200; ++j) {
				if (list.at(j)->getItemPrice() < list.at(indexSmallest)->getItemPrice())
					indexSmallest = j;
			}
			temp = list.at(i);
			list.at(i) = list.at(indexSmallest);
			list.at(indexSmallest) = temp;
		}
	}
	else if (choice == 6) {
		cout << "Running Shell Sort!" << endl;
		shellSort(listPtr, list.size());
	}
	else
		cout << "Please check your input and try again" << endl;

	clock_t end = clock(); //Time End!

	for (unsigned int i = 0; i < 200; ++i) {
		list.at(i)->printInfo();
	}

	cout << "The sorting took: " << diffClock(start, end) << " milliseconds!" << endl;

	char exit;
	cin >> exit;

	return 1;
}