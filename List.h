/*
	Header file for a custom linked list class
*/
#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
using namespace std;

template <class T>
class List
{
private:
	template <class U>
	struct Node		// Node container struct
	{
		U data;		// Holds data of type U, passed from main class
		Node<U> *next;	// Location of next in list
		Node() {}		// Default constructor
		Node(U value)	// Overloaded constructor
		{
			data = value;
			next = NULL;
		}
	};

	typedef Node<T> node;
	node *first;	// First in the linked list
	int size;		// Size of the linked list
public:
	// Constructor
	List()
	{
		first = new node();
		size = 0;
	}
	// Destructor
	~List()
	{
		Empty();
	}

	// Pushes object of type T onto the back of the list
	void Push_Back(T value)
	{
		if (size == 0)	// If list has no members
		{
			first->data = value;
			first->next = NULL;
			size++;
		}
		else
		{
			node *ptr;
			ptr = first;
			while (1)	// Run until break
			{
				if (ptr->next == NULL)	// End of the list
				{
					ptr->next = new node(value);
					size++;
					break;
				}
				else
					ptr = ptr->next;
			}
		}
	}

	// Pushes object of type T onto the front of the list
	void Push_Front(T value)
	{
		if (size == 0)	// If list has no members
		{
			first->data = value;
			first->next = NULL;
			size++;
		}
		else
		{
			node *oldfirst = new node();	// Need to save old first
			oldfirst->data = first->data;		// data in a new memory
			oldfirst->next = first->next;		// location
			first->data = value;
			first->next = oldfirst;				
			size++;
		}
	}

	// Returns data of type T from the back of the list and removes node
	T Pop_Back()
	{
		if (size == 1)	// Single node list
		{
			T data = first->data;
			size--;
			return data;
		}
		else if (size > 1)	// Multi node list
		{
			Node<T> *ptr, *prev;
			ptr = first;

			while (ptr->next != NULL)
			{
				prev = ptr;
				ptr = ptr->next;
			}

			T data = ptr->data;	// Store data
			delete ptr;			// Delete back node
			prev->next = NULL;	// Dereference deleted node
			size--;				// Decrement size
			return data;		// Return stored data
		}
		else	// Trying to pop an empty list throws an unhandled exception
			;	// And there doesn't seem to be any way to return a safe value
	}			// under the limitations of the template

	// Returns data of type T from the front of the list and removes node
	T Pop_Front()
	{
		if (size == 1)	// Single node list
		{
			T data = first->data;
			size--;
			return data;
		}
		else if (size > 1)	// Multi node list
		{
			node *ptr;
			T data = first->data;	// Store data
			ptr = first->next;		// Store address of next node
			delete first;			// Delete front node
			first = ptr;			// Set next node as front
			size--;					// Decrement size
			return data;			// Return stored data
		}
		else	// Throws unhandled exception like Pop_Back()
			;
	}

	// Returns size of list
	int Size() { return size; }

	// Checks size against number of nodes, returns amount
	int SizeCheck()
	{
		int count = 1;
		node *ptr;
			ptr = first;
		while (1)	// Run until break
		{
			if (ptr->next == NULL)	// End of list
				break;
			else
			{
				count++;
				ptr = ptr->next;
			}
		}
		if (size != count)
			size = count;
		return size;
	}

	// Deletes all contents of list
	void Empty()
	{
		node *ptr, *prevptr;
		ptr = first;
		while (ptr->next != NULL)
		{
			prevptr = ptr;
			ptr = ptr->next;
			prevptr->next = NULL;
			delete prevptr;
		}
		delete ptr;
	}

	// Inserts a new node into list at location index
	void Insert(T data, int index)
	{
		if (index >= size)
			return;	// TODO: throw an error
		node *ptr;
		ptr = first;
		for (int i = 1; i < index; i++) // Traverse list to just before
			ptr = ptr->next;			// index to place new value
		node *forwardnode;
		forwardnode = ptr->next;		
		ptr->next = new node(data);		// Place new value, set next
		ptr->next->next = forwardnode;	// to forward node
	}

	// Deletes a node at location index
	void Delete(int index)
	{
		if (index >= size)
			return;	// TODO: throw an error
		node *ptr;
		ptr = first;
		for (int i = 1; i < index; i++)	// Traverse list to just before
			ptr = ptr->next;			// index
		node *prevptr = ptr, *nextptr = ptr->next->next;
		ptr = ptr->next;
		delete ptr;
		prevptr->next = nextptr;
		size--;
	}

	// Searches for a node containing value 
	// Returns null pointer if not found
	T *Search(T value)
	{
		if (first->data == value) // If data is in first node
			return &first->data;
		node *ptr = first;
		while (ptr->next != NULL) // else search the list 
		{
			ptr = ptr->next;
			if (ptr->data == value)
				return &ptr->data;
		}
		return NULL;	// Value not found
	}
};
#endif