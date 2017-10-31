//Matt Strand
// 9-26-2017
//Create and modify Dynamic Arrays, Linked Lists

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <vector>

using namespace std;

//Structs
struct DynamicArray {
	int* array; //the array itself
	int size; //current number of elements
	int maxSize; //maximum number of elements
};
struct node {
	int info;
	node* next;
};
struct LinkedList {
	node* head;
};

//Dynamic Array Declarations
void create(DynamicArray &myArray);
void printArray(DynamicArray theArray);
int length(DynamicArray newArray);
void insertEnd(DynamicArray &endAddArray, int value);
void insertFront(DynamicArray &beginAddArray, int addVal);
void insertAfter(DynamicArray &insertArray, int position, int value);
void reverse(DynamicArray &backward);
void destroy(DynamicArray &destroyArray);
bool search(DynamicArray searchArray, int value);
void remove(DynamicArray &removeArray, int value);
void bubbleSort(DynamicArray &sort);
DynamicArray deepCopy(DynamicArray copy);

//Linked List Declarations
void createLL(LinkedList &theList);
void printList(LinkedList theList);
int lengthLL(LinkedList theList);
void insertEndLL(LinkedList &theList, int value);
void insertFrontLL(LinkedList &theList, int value);
void insertAfterLL(LinkedList &theList, int value, int addVal);
void reverseLL(LinkedList &theList);
void deleteListLL(LinkedList &theList);
bool searchLL(LinkedList theList, int value);
void removeLL(LinkedList &theList, int value);
void bubbleSortLL(LinkedList &theList);
LinkedList deepCopyLL(LinkedList theList);

/************************
*				|		*
*		MAIN   \|/		*
*				V		*
*************************/
int main(){
	DynamicArray hipHipArray;
	LinkedList example;

	create(hipHipArray);
	createLL(example);

	int* testNums = new int[10];
	int loopCount = 0;
	int numCount = 0;
	ofstream myfile;
	myfile.open("testNums.txt");

	while (numCount <= 10) {
		int random = rand();
		testNums[numCount] = random;
		numCount++;
	}

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 10; i++) {
		insertEnd(hipHipArray, testNums[i]);
	}

	deepCopy(hipHipArray);


	auto finish = std::chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() << " s\n";

	myfile.close();

	cin.get();
	return 0;
}

/*
DYNAMIC ARRAY STUFF
*/
void create(DynamicArray &myArray) {
	myArray.array = NULL;
	myArray.maxSize = 0;
	myArray.size = 0;
}

void printArray(DynamicArray theArray) {
	for (int i = 0; i < theArray.size; i++) {
		cout << theArray.array[i] << endl;
	}
}

int length(DynamicArray newArray) {
	return newArray.size;
}

void insertEnd(DynamicArray &endAddArray, int value) {
	if (endAddArray.size == 0) {
		endAddArray.size = 1;
		endAddArray.maxSize = 1;
		endAddArray.array = new int[1];
		endAddArray.array[0] = value;
	}
	else {
		if (endAddArray.size < endAddArray.maxSize) {
			endAddArray.array[endAddArray.size] = value;
			endAddArray.size++;

		}
		else {
			int* temp = new int[endAddArray.maxSize * 2];
			for (int i = 0; i < endAddArray.size; i++) {
				temp[i] = endAddArray.array[i];
			}
			endAddArray.array = temp;
			temp[endAddArray.size] = value;
			endAddArray.maxSize = endAddArray.maxSize * 2;
			endAddArray.size++; //increment the size
		}
	}
}

void insertFront(DynamicArray &beginAddArray, int addVal) {
	if (beginAddArray.size == 0) {
		beginAddArray.size = 1;
		beginAddArray.maxSize = 1;
		beginAddArray.array = new int[1];
		beginAddArray.array[0] = addVal;
	}
	else if (beginAddArray.size < beginAddArray.maxSize) {
		reverse(beginAddArray);
		insertEnd(beginAddArray, addVal);
		reverse(beginAddArray);
	}
	else {
		int* temp3 = new int[beginAddArray.maxSize * 2];
		for (int i = 0; i < beginAddArray.size; i++) {
			temp3[i] = beginAddArray.array[i];
		}
		beginAddArray.array = temp3;
		temp3[beginAddArray.size] = addVal;
		beginAddArray.maxSize = beginAddArray.maxSize * 2;
		beginAddArray.size++; //increment the size

	}

}

void insertAfter(DynamicArray &insertArray, int position, int value) {
	int* temp = new int[insertArray.maxSize * 2];
	if (insertArray.size >= position) {
		if (insertArray.size < insertArray.maxSize) {
			insertArray.size = insertArray.size + 1;
			for (int i = 0; i < position; i++) {
				temp[i] = insertArray.array[i];
			}
			temp[position] = value;
			for (int j = insertArray.size; j > position; j--) {
				temp[j] = insertArray.array[j];
			}
		insertArray.array = temp;
		}
		else {
			insertArray.size++;
			insertArray.maxSize++;
		}
	}
	else {
		cout << "The position is not in the array." << endl;
	}
}

void reverse(DynamicArray &backward) {
		int* temp2 = new int[backward.size];
		int countSize = 0;

		for (int i = backward.size - 1; i >= 0; i--) {
			temp2[countSize] = backward.array[i];
			countSize++;
		}
		backward.array = temp2;
}

void destroy(DynamicArray &destroyArray) {
	delete[] destroyArray.array;
	destroyArray.size = 0;
	destroyArray.maxSize = 0;
}

bool search(DynamicArray searchArray, int value) {
	for (int i = 0; i < searchArray.size; i++) {
		if (searchArray.array[i] == value) {
			cout << "The value is in position ";
			cout << i << endl;
			return true;
		}
	}
	return false;
}

void remove(DynamicArray &removeArray, int value) {
	int decrease = 0;
	for (int j = 0; j < removeArray.size;j++) {
		if (removeArray.array[j] == value) {
			decrease++;
		}
	}
	if (search(removeArray, value) == true) {
		for (int i = 0; i < removeArray.size; i++) {
			if (removeArray.array[i] == value) {
				removeArray.array[i] = removeArray.array[i+1];
				removeArray.array[i + 1] = value;
			}
		}
		cout << removeArray.size;
	removeArray.size = removeArray.size - decrease;
	}
	else {
		cout << "The value is not in the array";
	}
}

void bubbleSort(DynamicArray &sort){
	int temp;

	for (int i = 0; i < sort.size - 1; i++) {
		for (int j = 0; j < sort.size - i - 1; j++) {
			if (sort.array[j] > sort.array[j+1]) {
				temp = sort.array[j];
				sort.array[j] = sort.array[j + 1];
				sort.array[j + 1] = temp;
			}
		}
	}
}

DynamicArray deepCopy(DynamicArray copy) {
	DynamicArray newArr;
	create(newArr);
	newArr.size = copy.size;
	newArr.maxSize = copy.maxSize;

	for (int i = 0; i < copy.size; i++) {
		newArr.array[i] = copy.array[i];
	}
	return newArr;
}

/*
LINKED LIST STUFF
*/
void createLL(LinkedList &theList) {
	theList.head = 0;
}

void printList(LinkedList theList) {
	node* temp = theList.head;
	while (temp != 0) {
		cout << temp->info << endl;
		temp = temp->next;
	}
}

int lengthLL(LinkedList theList) {
	int counter = 0;
	node* temp = theList.head;
	while (temp != 0) {
		temp = temp->next;
		counter++;
	}
	return counter;
}

void insertEndLL(LinkedList &theList, int value) {
	if (theList.head == 0) {
		theList.head = new node;
		theList.head->info = value;
		theList.head->next = 0;
	}
	else {
		node* temp = theList.head;
		while (temp->next != 0) {
			temp = temp->next;
		}
		//create a new node
		node* nodeInsert = new node;
		nodeInsert->info = value;
		nodeInsert->next = 0;
		temp->next = nodeInsert;

	}
}

void insertFrontLL(LinkedList &theList, int value) {
	if (theList.head == 0) {
		theList.head = new node;
		theList.head->info = value;
		theList.head->next = 0;
	}
	else {
		node* temp = new node;
		temp->info = value;
		temp->next = theList.head;
		theList.head = temp;
	}
}

void insertAfterLL(LinkedList &theList, int value, int addVal) {
	if (searchLL(theList, value) == true) {
		if (theList.head != 0) {

			node* temp = new node;
			node* current = theList.head;
			temp->info = addVal;

			while (current->next != 0 && current->next->info == value) {
				current = current->next;
			}
			temp->next = current->next;
			current->next = temp;
		}
		else {
			cout << "The Linked List is empty" << endl;
		}
	}
	else {
		cout << "The value to insert after does not exist." << endl;
	}
}

void reverseLL(LinkedList &theList) {
	node* temp = NULL;
	node* prev = NULL;
	node* current = theList.head;

	while (current != 0) {
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	theList.head = prev;
}

void deleteListLL(LinkedList &theList) {
	node* temp = NULL;
	while (theList.head != 0) {
		temp = theList.head;
		theList.head = theList.head->next;
		delete[] temp;
	}
}

bool searchLL(LinkedList theList, int value) {
	while (theList.head->next != 0) {
		if (theList.head->info == value) {
			cout << "The value is in the Linked List!" << endl;
			return true;
		}
		else {
			theList.head = theList.head->next;
		}
	}
	cout << "The value is not in the Linked List" << endl;
	return false;
}

void removeLL(LinkedList &theList, int value) {
	node* temp = theList.head;
	node* deleter = NULL;
	node* connector = NULL;
	if (searchLL(theList, value) == true) {
		while(temp->next != 0) {
			if (temp->next->info == value) {
				deleter = temp->next;
				temp->next = deleter->next;
				delete deleter;
			}
			else {
				temp = temp->next;
			}

		}
	}
	else {
		cout << "The element to remove was not in the list to begin with." << endl;
	}
}

void bubbleSortLL(LinkedList &theList) {
	node* temp = theList.head;
	int swap;
	while (temp->next != 0) {
		if (temp->info > temp->next->info) {
			swap = temp->info;
			temp->info = temp->next->info;
			temp->next->info = swap;
		}
		temp = temp->next;
	}
}

LinkedList deepCopyLL(LinkedList theList) {
	LinkedList newLL;
	createLL(newLL);

	while (theList.head->next != NULL) {
		newLL.head = theList.head;
		theList.head = theList.head->next;
	}
	return newLL;
}
