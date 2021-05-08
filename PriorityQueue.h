#pragma once
#include "TreeNode.h"


//Any class that implements this Data Structure must define the comparison operators 

template<typename T>
class PriorityQueue
{
private:
	TreeNode<T>* arr;
	int queueSize;
	const int maxElements;

	void swap(int i1, int i2); //done
	int leftIndex(int i); //done
	int rightIndex(int i); //done
	int parentIndex(int i); //done
	
	void heapifyUp(int i); //done
	void heapifyDown(int i); //done

	
	
public:
	PriorityQueue();  //safe
	PriorityQueue(int n); //safe
	PriorityQueue(TreeNode<T>* A, int size); //safe
	

	bool isEmpty() const; //safe
	bool insert(T& p, int priority); //safe

	bool peekMax(T& max); //safe
	bool dequeueMax(T& max);
	void buildMaxHeap();

	int size() const;
	
	void printArr(); //used for testing purposes only;

	//only heap sort left

	
};

template <typename T>
PriorityQueue<T>::PriorityQueue() : PriorityQueue(100)
{
	//initializes the queue with a default size 100
}



template<typename T>
PriorityQueue<T>::PriorityQueue(int n) : maxElements(n)
{
	arr = new TreeNode<T>[n + 1];
	queueSize = 0;
	 
}

template<typename T>
PriorityQueue<T>::PriorityQueue(TreeNode<T>* A, int size) : PriorityQueue(size - 1) //location at 0 is ignored
{
	queueSize = maxElements;
	arr = A;
	printArr();
	buildMaxHeap();
	printArr();
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (queueSize == 0)
		return true;
	else return false;
}

template<typename T>
bool PriorityQueue<T>::insert(T& t, int priority)
{
	TreeNode<T>* newNode = new TreeNode<T>(&t, priority);
	if (queueSize >= maxElements)
		return 0;

	arr[++queueSize] = *newNode;
	heapifyUp(queueSize);
	return true;
}

template<typename T>
bool PriorityQueue<T>::peekMax(T& max)
{
	if (isEmpty())
		return false;
	max = arr[1].getVal();
	return true;
}

template<typename T>
bool PriorityQueue<T>::dequeueMax(T& max)
{
	if (isEmpty())
		return false;
	max = *(arr[1].getVal());
	arr[1] = arr[queueSize--];
	heapifyDown(1);
	return true;
}

template<typename T>
void PriorityQueue<T>::buildMaxHeap()
{
	for (int i = queueSize/2; i > 0; i--)
	{
		heapifyDown(i);
	}

	printArr();
}

template<typename T>
int PriorityQueue<T>::size() const
{
	return queueSize;
}

template<typename T>
void PriorityQueue<T>::printArr()
{
	for (int i = 1; i <= queueSize; i++)
	{
		cout << arr[i].getKey() << " ";
	}
	cout << endl;
}


 template<typename T>
 int PriorityQueue<T>::leftIndex(int i)
 {
	 if (2 * i > queueSize)
		 return 0;
	 else
		 return 2 * i;
 }

 template<typename T>
 int PriorityQueue<T>::rightIndex(int i)
 {
	 if (2 * i + 1 > queueSize)
		 return 0;
	 else
		 return 2 * i + 1;
 }

 template<typename T>
 int PriorityQueue<T>::parentIndex(int i)
 {
	 return i/2;
 }

 template<typename T>
 void PriorityQueue<T>::heapifyUp(int i)
 {
	 while (parentIndex(i) > 0 && arr[i] > arr[parentIndex(i)])
	 {
		 swap(i, parentIndex(i));
		 i = parentIndex(i);
	 }
	 printArr();
 }

 template<typename T>
 void PriorityQueue<T>::heapifyDown(int i)
 {
	 int largestIndex = i;
	 if (leftIndex(i) != 0 && arr[leftIndex(i)] > arr[largestIndex])
	 {
		 largestIndex = leftIndex(i);
	 }
	 if (rightIndex(i) != 0 && arr[rightIndex(i)] > arr[largestIndex])
	 {
		 largestIndex = rightIndex(i);
	 }

	 if (i == largestIndex)
		 return;

	 swap(i, largestIndex);
	 heapifyDown(largestIndex);

 }

 template<typename T>
 void PriorityQueue<T>::swap(int i1, int i2)
 {
	 if (i1 == i2)
		 return;
	 TreeNode<T> temp = arr[i1];
	 arr[i1] = arr[i2];
	 arr[i2] = temp;
 }
