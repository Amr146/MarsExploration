//This file is for testing the DS only(will be deleted once we start working in the program)
#include<iostream>
#include"DS/LinkedPriorityQueue.h"
#include"DS/LinkedQueue.h"
using namespace std;

template<typename T>
void print(LinkedQueue<T>& q);

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