/*
Filname: Chunklist.h
Author : Shafi Gilanizadeh
Due    : 02/26/2020
Purpose: The purpose of this program is to implement a chunklist using STD templates, this program is implemented for the puspose of creating a chunklist of
		 max 8 element a time, for all elements more then 8 there will be dynamically alocating memory in the heap to store the new elements.
		 This file contains the header and the implemention files of the class, since the STD templates are used in this program, the implementation fill is implemented
		 in the same file as the header file.
*/
#pragma once
#include <iostream>
#include <fstream>
using namespace std;


const int ARRAY_SIZE = 8;			// constant chunkSize
static int totalChunk;				// static variable to store total number of chunk in the list

class EmptyListError {};			// expection handler class definations
class BadIndex {};
class wrongelement {};


//pre:   we will be structing an array of specific sized nodes, with a next pointer for the next node in the list. the array ItemT is a template type, whcih means this struct
//	     is able to create user defined type chunklist. user can decide whichever data type to use.
//post:  If the list is empty, the Node will automatically create a chunk with max 8 elements, the chunk will can store max elements and it will has a next pointer to the 
//		 next chunk.
template <typename ItemT>
struct Node
{
	ItemT value[ARRAY_SIZE];			// array can be user defined type, Maxsize will be 8
	Node* next = nullptr;				// Next pointer to point to the next chunk in the list
	int totalChunkElem;					// variable to count the total number of element in each chunk

};

//pre : Class chunklist will have all the functions to perform the chunklist operations
//post: chunklist class instances will call the Node to allocate memory in the heap as needed, also chunklist class contains private and pulib variables to keep
//		track of the total list elements and the total available chunks in the list.

template <typename ItemT>
class ChunkList
{
private:
								// declaring head and tail pointer to the chunklist		
	Node<ItemT> *head;
	Node<ItemT> *tail;	
	int totalListElments;		// this variable will count the total elements exist in the list

public:
	ChunkList();				// default contructor
	void Append(ItemT elem);	// append will continously add elements at the end of the list without removing the existence ones
	int GetLength();			// (refers to the total number of elements, not the number of chunk nodes)
	ItemT  GetIndex(int i);		// GetIndex will return the element at a specific index in the list
	bool  IsEmpty();			// isEmpty will check if the lsit is empty or its full
	void Print(ostream& outfile);// print will output the result in the textfile
	void operator+(ItemT elem);	 // operator will ivoke the append function and add the elemets in the list
	bool Contains(ItemT elem);	 // Contain function checks if the element exist in the list, before any other operation
	void  Remove(ItemT elem);	 //(removes first instance of elem) it will remove the element at the first time its found
};

//pre:  Default constructor will set the pointers to null initially
//post: default constructor makes sure the pointers are intially holding NULL value
template<typename ItemT>
ChunkList<ItemT>::ChunkList()
{
	head = nullptr;
	tail = nullptr;
}

//pre:  operator will call the append function to add the elements in the chunklist
//post: using operator allows the user to add the object and later it will pass it to the append function
template<typename ItemT>
void ChunkList<ItemT>::operator +(ItemT elem)
{
	Append(elem);
}

//pre:	Append function will add all the element passed by user in the order in which it recived. it wont errase or remove the existing items
//post:	Depending on the chunklist, append function can create a new chunk and add the element in it or add the element in the same chunk if the size allows.
template<typename ItemT>
void ChunkList<ItemT>::Append(ItemT elem)
{
	{
		if (tail == nullptr)  // if tail is NULL, So its empty, create a new chunk or if the chunk has space in it before creating a new one 
		{
			Node<ItemT>* newNode = new Node<ItemT>();				// allocate a new chunk of size 8
			newNode->value[newNode->totalChunkElem] = elem;			// add the element in the chunk
			newNode->totalChunkElem++;								// count the total elements in the chunk
			head = newNode;											// since its the onlu chunk, head and tail should point to the same chunk
			tail = newNode;
			totalChunk++;											// Increment number of chunk
			newNode->next = nullptr;								// the new chunks next will point to nullptr
		}
		else if (tail->totalChunkElem < ARRAY_SIZE)					// If the current chunk has space, add the elements in it untill it reaches the max size
		{
			tail->value[tail->totalChunkElem] = elem;				// add th element at the tails position
			tail->totalChunkElem++;									// increase the number of total elements
		}
		else
		{
			Node<ItemT>* newNode = nullptr;							// Here we will create a new chunk
			newNode = new Node<ItemT>();
			newNode->totalChunkElem = 0;							// total elements of the new chunk is 0 at the beganing
			totalChunk++;											// increase the number of chunks
			newNode->value[newNode->totalChunkElem] = elem;			// add the element in the list
			newNode->totalChunkElem++;								// total Elements of the chunk ++
			tail->next = newNode;									// connect the two chunk
			tail = newNode;											// tail will point to the new chunnk now 
			newNode->next = nullptr;
		}
	}
			totalListElments++;										// total elemetnis in th list

}

//pre:  the total number of element in the list will be counted and returend as the user requests
//post:	total list element is counting the total elements in the entire list, including the total chunk elements
template<typename ItemT>
int ChunkList<ItemT>::GetLength()
{
	return totalListElments;
}

//pre:  this function will return the element at a particular position, this function will skip the chunks whos index are less then the location of the index being searched.  
//post:	all element in the list has an index location, the getindex function will return the element at the exact location of the list
template<typename ItemT>
ItemT ChunkList<ItemT>::GetIndex(int i)
{
	if (IsEmpty())		
	{
		throw EmptyListError();
	}

	if (i < 0)
	{
		throw BadIndex();
	}

	Node<ItemT>* temp = head;								// temp variable will travers through the list to find the element
	while (temp!=nullptr)
	{
		if ((i - temp->totalChunkElem) < 0)					// if the element is not at the first,second .. ect chunk, then skip traversing in it
		{
			return temp->value[i];							// return the element at the position found
		}
			i = i - temp->totalChunkElem;					// update i
			temp = temp->next;								// go to the next element
	}
	return 0;

}

//pre:  this function will determine if the list contains elements or not
//post: isempty chekcs the total number of elements in the list, if there is nothing in the list then return true
template<typename ItemT>
bool ChunkList<ItemT>::IsEmpty()
{
	return (totalListElments == 0);
}

//pre:	contain function determines if an element exist in the list before calling the remove function
//post:	if the element in the list does not exist, the contain function will return before the remove function starts searching for the element again.
template <class ItemT>
bool ChunkList<ItemT>::Contains(ItemT elem)
{
	Node<ItemT>* temp = head;
	while (temp != nullptr)										// while temp is not empty, continue to traverse the list
	{
		for (int i = 0; i < temp->totalChunkElem; i++)
		{
			if (temp->value[i] == elem)							// if the value is found at the position then return 
			{
				return true;
			}
		}
		temp = temp->next;
	}
	return false;
}

//pre:
//post:

template<class ItemT>
void ChunkList<ItemT>::Remove(ItemT elem)
{
	if (!Contains(elem))
	{
		throw wrongelement();
	}
	Node<ItemT> *temp = head;										// two pointers to travers throu the list
	Node<ItemT> *prev = head;
	
	while(temp!=nullptr)
	{
		for (int i = 0; i < temp->totalChunkElem; i++)				// loop throu each chunk
		{
			if (temp->value[i] == elem)								// if the element is found and its at the middle of the chunk list 
			{
				for (int k = i; k < head->totalChunkElem - 1; k++)
				{
					temp->value[k] = temp->value[k + 1];			// shift everything up a location
				}
				temp->totalChunkElem--;								// decrease total chunk elements and the total list elements
				totalListElments--;
				if (temp->totalChunkElem == 0)
				{
					prev = temp->next;
					delete temp;
					totalChunk--;
				}
				return;
			}
		}
		prev = temp;
		temp = temp->next;
	}
}

//pre:	print function will output the information to the screen
//post:	since the output file is open at the driver, the print function will also gets the object to output the information to the textfile
template<typename ItemT>
void ChunkList<ItemT>::Print(ostream& outfile)
{
	if (IsEmpty())
		throw EmptyListError();
	
	Node<ItemT>* tempPtr = head;
	for (int k = 0; k < totalChunk; k++)
	{
		outfile << "\nChunk: " << k + 1 << " - Total Element: " << tempPtr->totalChunkElem << endl;
		outfile << "[ ";
		for (int i = 0; i < tempPtr->totalChunkElem; i++)
		{
			//cout << tempPtr->value[i] << " ";
			outfile << tempPtr->value[i] << " ";
		}
		outfile << "]" << endl;
		tempPtr = tempPtr->next;
	}
	outfile << endl;
	//	outfile.close();
}

// End of the implementation file






	


