#pragma once
#include "DS/ListADT.h"
#include"DS/Node.h"

template<typename T>
class LinkedList : public ListADT<T>
{
private:
	Node<T>* head;

public:
	LinkedList()
	{
		head = nullptr;
	}

	bool isEmpty() const
	{
		return(head == nullptr);
	}

	int getLength() const
	{
		int length = 0;
		Node<T>* ptr = head;
		while (ptr)
		{
			length++;
			ptr = ptr->getNext();
		}
		return length;
	}

	bool insert(int newPosition, const T& newEntry)
	{
		int index = 0;
		Node<T>* ptr = head;
		Node<T>* prevptr = head;
		if (newPosition == 0)
		{
			Node<T>* R = new Node<T> (newEntry);
			if (!R)
				return false;
			R->setNext(head);
			head = R;
			return true;
		}
		while (ptr)
		{
			if (index == newPosition)
			{
				Node<T>* R = new Node<T>(newEntry);
				if (!R)
					return false;
				R->setNext(ptr);
				prevptr->setNext(R);
				return true;
			}
			index++;
			prevptr = ptr;
			ptr = ptr->getNext();
		}
		if (newPosition == index)
		{
			Node<T>* R = new Node<T>(newEntry);
			if (!R)
				return false;
			prevptr->setNext(R);
			R->setNext(nullptr);
			return true;
		}
		return false;
	}

	bool remove(int position)
	{
		if (position == 0)
		{
			Node<T>* temp = head;
			head = head->getNext();
			delete temp;
			return true;
		}
		Node<T>* ptr = head->getNext();
		Node<T>* prevptr = head;
		int index = 1;
		while (ptr)
		{
			if (index == position)
			{
				Node<T>* temp = ptr->getNext();
				prevptr->setNext(temp);
				delete ptr;
				return true;
			}
			index++;
			prevptr = ptr;
			ptr = ptr->getNext();
		}
		return false;
	}
	
	void clear()
	{
		while (!isEmpty())
		{
			remove(0);
		}
	}

	T getEntry(int position) const
	{
		Node<T>* ptr = head;
		int index = 0;
		while (ptr)
		{
			if (index == position)
			{
				return ptr->getItem();
			}
			index++;
			ptr = ptr->getNext();
		}
	}

	T replace(int position, const T& newEntry)
	{
		Node<T>* ptr = head;
		int index = 0;
		while (ptr)
		{
			if (index == position)
			{
				T temp = ptr->getItem();
				ptr->setItem(newEntry);
				return temp;
			}
			index++;
			ptr = ptr->getNext();
		}
	}

	~LinkedList()
	{
		clear();
	}
};