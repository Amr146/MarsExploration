//This file is for testing the DS only(will be deleted once we start working in the program)
#include<iostream>
#include"../DS/LinkedPriorityQueue.h"
#include"../DS/LinkedQueue.h"
#include"../DS/LinkedList.h"
using namespace std;

template<typename T>
void print(LinkedQueue<T>& q);

template<typename T>
void print(LinkedList<T>& L);

int main()
{
	LinkedQueue<int> Q;
	int temp;
	Q.enqueue(6);
	Q.enqueue(7);
	Q.enqueue(6);
	Q.enqueue(8);
	print(Q);
	cout << endl;
	Q.dequeue(temp);
	print(Q);
	cout << endl;
	while (!Q.isEmpty())
	{
		Q.dequeue(temp);
	}
	print(Q);

	cout << endl;


	LinkedPriorityQueue<int> PQ;
	PQ.add(6, 10);
	PQ.add(7, 20);
	PQ.add(5, 76.7);
	PQ.add(8, .7);
	PQ.remove(temp);
	cout << temp;
	cout << endl;
	PQ.remove(temp);
	cout << temp;
	cout << endl;
	while (!PQ.isEmpty())
	{
		PQ.remove(temp);
		cout << temp << " ";
	}
	cout << endl << PQ.isEmpty();

	LinkedList<int> L;

	cout << L.isEmpty() << endl;

	L.insert(0, 2);
	L.insert(5, 3);
	L.insert(1, 7);
	print(L);
	L.clear();
	cout << L.isEmpty() << endl;
	L.insert(0, 3);
	L.insert(1, 9);
	L.insert(1, 6);
	cout << L.getLength() << endl;
	print(L);
	L.remove(1);
	print(L);
	L.replace(0, 7);
	print(L);
	L.remove(0);
	print(L);

	return 0;
}

template<typename T>
void print(LinkedQueue<T>& q)
{
	LinkedQueue<T> temp;
	T R;
	while (!q.isEmpty())
	{
		q.dequeue(R);
		cout << R << " ";
		temp.enqueue(R);
	}
	while (!temp.isEmpty())
	{
		temp.dequeue(R);
		q.enqueue(R);
	}
}

template<typename T>
void print(LinkedList<T>& L)
{
	int N = L.getLength();
	for (int i = 0; i < N; i++)
	{
		cout << L.getEntry(i) << endl;
	}
}