#pragma once

//Any class that implements this Data Structure must define the comparison operators 

template<typename T>
class PriorityQueue
{
private:
	T* arr;
	int queueSize;
	const int maxElements;

public:
	PriorityQueue(int n);
	bool insert(T* p);
	void maxHeapify(int index);
	int leftIndex(int i);
	int rightIndex(int i);
	int parentIndex(int i);
	void shiftUp(int i);
	void shiftDown(int i);
	void swap(int i1, int i2);
	//add build maxHeap and HeapSort
};

template<typename T>
PriorityQueue<T>::PriorityQueue(int n)
{
	arr = new T[n];
	queueSize = 0;
	maxElements = n - 1; //Because we ignore the location at index = 0
}

template<typename T>
bool PriorityQueue<T>::insert(T* t)
{
	if (queueSize >= maxElements)
		return 0;
	arr[++queueSize] = t;
}

template<typename T>
 void PriorityQueue<T>::maxHeapify(int index)
{
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
 void PriorityQueue<T>::shiftUp(int i)
 {
	 while (parentIndex(i) > 0 && arr[i] > arr[parentIndex(i)])
	 {
		 swap(i, parentIndex(i));
		 i = parentIndex(i);
	 }
 }

 template<typename T>
 void PriorityQueue<T>::shiftDown(int i)
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
	 shiftDown(largestIndex);

 }

 template<typename T>
 void PriorityQueue<T>::swap(int i1, int i2)
 {
	 if (i1 == i2)
		 return;
	 T* temp = arr[i1];
	 arr[i1] = arr[i2];
	 arr[i2] = arr[i1];
 }
