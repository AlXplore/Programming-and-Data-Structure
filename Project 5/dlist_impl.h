#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

#include <cstdlib>

template <class T>
Dlist<T>::Dlist()
{
	this -> first = NULL;
	this -> last = NULL;
}

template <class T>
Dlist<T>::Dlist(const Dlist &l)
{
	this -> first = NULL;
	this -> last = NULL;
	this -> copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l)
{
	this -> removeAll();
	this -> copyAll(l);
	return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
	this -> removeAll();
}

template <class T>
bool Dlist<T>::isEmpty() const
{
	return (first == NULL);
}

template <class T>
void  Dlist<T>::insertFront(T *op)
{
	node* t = new node;
	t -> op = op;
	t -> next = this -> first;
	t -> prev = NULL;
	if (isEmpty())
		this -> last = t;
	else
		this -> first -> prev = t;
	this -> first = t;
}

template <class T>
void Dlist<T>::insertBack(T *op)
{
	node* t = new node;
	t -> op = op;
	t -> next = NULL;
	t -> prev = this -> last;
	if (isEmpty())
		this -> first = t;
	else 
		this -> last -> next = t;
	this -> last = t;
}

template <class T>
T* Dlist<T>::removeFront()
{
	if (isEmpty())
	{
		emptyList eL;
		throw eL;
	}
	else
	{
		T* result = first -> op;
		if (first == last)
		{
			delete this -> first;
			this -> first = this -> last = NULL;
		}
		else
		{
			this -> first = this -> first -> next;
			delete this -> first -> prev;
			this -> first -> prev = NULL;
		}
		return result;
	}
}

template <class T>
T* Dlist<T>::removeBack()
{
	if (isEmpty())
	{
		emptyList eL;
		throw eL;
	}
	else
	{
		T* result = last -> op;
		if (first == last)
		{
			delete this -> first;
			this -> first = this -> last = NULL;
		}
		else
		{
			this -> last = this -> last -> prev;
			delete this -> last -> next;
			this -> last -> next = NULL;
		}
		return result;
	}
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l)
{
	node *node_add = l.first;
	while (node_add != NULL)
	{
		insertBack(new T(*node_add -> op));
		node_add = node_add -> next;
	}
}

template <class T>
void Dlist<T>::removeAll()
{
		while (!isEmpty())
		{
			T *node_remove = removeFront();
			delete node_remove;
		}
}

#endif