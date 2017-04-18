#pragma once
#include <assert.h>
template <class T>
class CircularDoublyLinkedList {
private:
	//Declaration of Node class
	class Node {

	public:
		T value;
		Node * previous;
		Node * next;
		//Node class constructor
		Node(T v, Node * n = NULL, Node * r = NULL) { 
			value = v;
			next = n;
			previous = r;
		}
	};

public:
	//Declaration of Iterator Class
	class Iterator {// iterators are used for efficient traversal of linked lists
	private:
		Node* m_ptr;    // an iterator hides a pointer to node
	public:
		Iterator(Node* ptr) { m_ptr = ptr; }
		void operator++ () { m_ptr = m_ptr->next; } // for forward traversing
		void operator--() { m_ptr = m_ptr->previous; } //for backward traversing
		bool operator != (const Iterator& b) { return m_ptr != b.m_ptr; }
		T operator *() { return m_ptr->value; }
		T getNextValue() { return m_ptr->next->value; }
		T getValue() { return m_ptr->value; }
		void setValue(T val) { m_ptr->value = val; }
	};

private:
	Node * m_head;	//pointer that points to the head of the list
	Node * m_tail;	//pointer that points to the tail of the list
	int m_size;	//stores the size of the list

public: 

	//
	//FUNCTION DECLARATIONS
	//

	CircularDoublyLinkedList(); // construct an empty linked list
	CircularDoublyLinkedList(const CircularDoublyLinkedList &other);	//Copy constructor
	~CircularDoublyLinkedList(); //Destruct the list

	T retrieveHead() const;	//return the head
	T retrieveTail() const;	//return the tail
	T retrieve(int position) const;	//retrieve the value of a node at a specified position

	void addHead(T item);	//adds a node to the front of the list
	void addTail(T item);	//adds a node to the back of the list
	void add(T item, int position); //adds a node to a specified position in the list

	T removeTail(); //Removes the tail and returns its value
	T removeHead(); //Removes the head and returns its value
	T remove(int position); //Removes a node at a specified position and returns its value

	void moveRight(); //Shifts all of the elements 1 spot to the right
	void moveLeft(); //Shifts all of the elements 1 spot to the left

	// Forward Traversal Iterators
	Iterator begin() { return Iterator(m_head); }
	Iterator end() { return Iterator(m_tail); }

	T replace(T value, int position); //Replaces the value in a node at a specified position
	void swap(int, int); //Swaps the value of 2 nodes
	bool isEmpty(); //Checks if list is empty
	int size() const; // return number of items in the list 
};

//
//FUNCTION DEFINITIONS
//

template <class T>
CircularDoublyLinkedList<T> ::CircularDoublyLinkedList(){
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

template<class T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(const CircularDoublyLinkedList & other)
{
	if (other.m_size == 0) {
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
	else {
		m_size = other.m_size;
		m_head = new Node(other.m_head->value, nullptr, nullptr);
		if (m_size == 1)
			m_tail = m_head;
		else {
			//Iterate through the other list and set each node as the tail of the new list as it gets to it
			Node * copy = other.m_head->next;
			for (int i = 1; i < m_size; i++) {
				addTail(copy->value);
				copy = copy->next;
				m_size--;	//Decrement m_size because the size was already set to the correct size and the addTail() function increments it
			}
		}
	}
}

template<class T>
CircularDoublyLinkedList<T>::~CircularDoublyLinkedList()
{
	Node * here = m_head;
	Node * nextNode;

	//Iterate through the list, deleting each node as as it gets to it 
	for (int i = 0; i < m_size; i++) {
		nextNode = here->next;
		delete here;
		here = nextNode;
	}
}

template <class T>
int CircularDoublyLinkedList<T> ::size() const
{
	return m_size;
}

template <class T>
void CircularDoublyLinkedList<T> ::addHead(T item)
{
	if (m_size == 0) {
		m_head = new Node(item, nullptr, nullptr);
		m_tail = m_head;	//Set the tail to equal the head since there is only 1 node

	}
	else {
		m_head = new Node(item, m_head, m_tail);
		m_head->next->previous = m_head;	//set the previous pointer of the next node to point to the head
		m_tail->next = m_head;
	}
	m_size++;
}

template<class T>
void CircularDoublyLinkedList<T>::addTail(T item)
{
	if (m_size == 0) {
		m_tail = new Node(item, nullptr, nullptr);
		m_head = m_tail;	//Set the head to equal the tail since there is only 1 node

	}
	else {
		m_tail = new Node(item, m_head, m_tail);
		m_head->previous = m_tail;
		m_tail->previous->next = m_tail;	//set the next pointer of the previous node to point to the tail
	}
	m_size++;
}

template<class T>
void CircularDoublyLinkedList<T>::add(T item, int pos)
{
	//check that the position is valid
	assert((pos >= 0 && pos < size) && "invalid index(in add)");
	if (pos == 0)
		addHead(item);
	else if (pos == m_size - 1)
		addTail(item);
	else {
		Node * here = m_head;
		for (unsigned int k = 1; k < pos; k++) here = here->next;
		here->next = new Node(item,here->next,here);
		m_size++;
	}
}

template<class T>
T CircularDoublyLinkedList<T>::replace(T newValue, int pos)
{
	//check that the position is valid
	assert((pos >=0 && pos < m_size) && "invalid index(in replace)");

	T returnVal;
	Node *here = m_head;
	//Iterate through the list until you get to the specified position, then replace the value
	for (int i = 0; i < pos; i++)
		here = here->next;
	returnVal = here->value;
	here->value = newValue;
	return returnVal;
}

template<class T>
void CircularDoublyLinkedList<T>::swap(int position1, int position2)
{
	int temp;
	temp = retrieve(position1);	//Store the value of pos1 in a temp variable
	replace(retrieve(position2), position1);	//replace pos1 with the value of pos2
	replace(temp, position2);	//replace pos2 with the temp variable
}

template<class T>
bool CircularDoublyLinkedList<T>::isEmpty()
{
	if(m_size == 0)
		return true;
	return false;
}

template<class T>
T CircularDoublyLinkedList<T>::removeTail()
{
	//check that there is a tail to remove
	assert(m_size > 0 && "List is empty(in removeTail)");

	T returnValue = m_tail->value;
	
	//Let the element before the tail point to the head
	m_tail->previous->next = m_head; 
	//Let the previous pointer of m_head point to the element before tail
	m_head->previous = m_tail->previous; 
	delete m_tail;
	//Assign the m_tail to point to the new tail
	m_tail = m_head->previous;
	m_size--;
	return returnValue;
}

template<class T>
T CircularDoublyLinkedList<T>::removeHead()
{
	//check that there is a head to remove
	assert(m_size > 0 && "List is empty(in removeHead)");

	T returnValue = m_head->value;

	//Let the previous pointer of the new head point to m_tail
	m_head->next->previous = m_tail;
	//Let the next pointer of m_tail point to the new head
	m_tail->next = m_head->next;
	delete m_head;
	//Let m_head point to the new m_head
	m_head = m_tail->next;
	m_size--;
	return returnValue;
}

template<class T>
 T CircularDoublyLinkedList<T>::remove(int position)
{
	if (position == 0)
		return removeHead();
	else if (position == m_size - 1)
		return removeTail();
	else {
		T returnValue;
		Node *here = m_head;
		//Iterate through the list until we get to the node that needs to be removed
		for (unsigned int k = 1; k <= position; k++)
			here = here->next;
		returnValue = here->value;
		//Let the next node point to the previous node and the previous node point to the next one
		here->next->previous = here->previous;
		here->previous->next = here->next;

		m_size--;
		return returnValue;
	}
}

 template<class T>
 void CircularDoublyLinkedList<T>::moveRight()
 {
	 //check that their are atleast 2 elements in the list
	 assert(m_size > 1 && "Less than 2 elements(in moveRight)");

	 //Move the head and tail 1 spot to the right
	 m_head = m_tail;
	 m_tail = m_tail->previous;
 }

 template<class T>
 void CircularDoublyLinkedList<T>::moveLeft()
 {
	 //check that their are atleast 2 elements in the list
	 assert(m_size > 1 && "Less than 2 elements(in moveLeft)");

	 //Move the head and tail 1 spot to the left
	 m_tail = m_head;
	 m_head = m_head->next;
 }

template <class T>
T CircularDoublyLinkedList<T>::retrieveHead() const
{
	//check that there is a head to retrieve
	assert((m_size > 0 && "List is empty(in retrieveHead)"));

	return m_head->value;
}

template<class T>
T CircularDoublyLinkedList<T>::retrieveTail() const
{
	//check that there is a tail to retrieve
	assert(m_size > 0 && "List is empty(in retrieveTail)");

	return m_tail->value;
}

template<class T>
T CircularDoublyLinkedList<T>::retrieve(int position) const
{
	//check that the position is valid
	assert((position >= 0 && position <= m_size) && "Invalid position(in retrieve)");

	if (position == 0) {
		return retrieveHead();
	}
	else if (position == m_size - 1)
		return retrieveTail();
	else {
		Node * here = m_head;
		//Iterate through the list until we get to the required position
		for (int i = 0; i < position; i++)
			here = here->next;
		return here->value;
	}
}