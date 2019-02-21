//============================================================================
// Name        : List.h
// Author      : Khadeja Khalid & Tiffany Tran
// Version     : Tuesday, February 27, 2018
//============================================================================

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <assert.h>
#include <cstddef> //for NULL
using namespace std;

template <class listdata> 	//list stores generic listdata, not any specific C++ type
class List {
private:
    struct Node {
        listdata data;
        Node* next;
        Node* prev;

        Node(listdata newData){
            data = newData;
            next = NULL;
            prev = NULL;
        }
    };

    Node* first;
    Node* last;
    Node* iterator;		// ptr to a node; used to traverse list
    int length;

    void reversePrint(Node* node) const;
        //Helper function for the public reversePrint() function.
        //Recursively prints the data in a List in reverse.

    bool isSorted(Node* node) const;
        //Helper function for the public isSorted() function.
        //Recursively determines whether a list is sorted in ascending order.

    int binarySearch(int low, int high, listdata data) const;
        //Recursively search the list by dividing the search space in half
        //Returns the index of the element, if it is found in the List
        //Returns -1 if the element is not in the List
        //Post: The iterator location has not been changed


public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: an empty list will be created, variables initialized (first, last, and length = 0)

    List(const List &list);
    //Copy Constructor; creates a deep copy of the original list
    // postcondition: a deep copy of the list in the parameter is created

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: memory is freed, list is empty



    /**Accessors*/

    listdata getFirst() const;
    //Returns the first data in the list
    //Precondition: list must not be empty (length!=0 OR first!=NULL)

    listdata getLast() const;
    //Returns the last data in the list
    //Precondition: list must not be empty (length!=0 OR first!=NULL)

    listdata getIterator() const;
    // returns the element currently pointed at by the iterator
    // precondition: list must not be empty (length!=0 or iterator != NULL)

    bool offEnd() const;
    // returns whether the iterator is off the end of the list
    // (returns if iterator == NULL)

    bool isEmpty() const;
    //Determines whether a list is empty.

    int getLength() const;
    //Returns the size of the list

    bool isSorted() const;
    //Wrapper function that calls the isSorted helper function to determine whether
    //a list is sorted in ascending order.
    //We will consider that a list is trivially sorted if it is empty.
    //Therefore, no precondition is needed for this function

    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: !offEnd()

    int linearSearch(listdata data) const;
    //Searchs the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Does not call the indexing functions in the implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed

    int binarySearch(listdata data) const;
    //Returns the index where data is located in the List
    //Calls the private helper function binarySearch to perform the search
    //Pre: length != 0
    //Pre: List is sorted (must test on a sorted list)
    //Post: The iterator location has not been changed




    /**Manipulation Procedures*/

    void startIterator();
    // moves the iterator to the beginning of the list
    // post: iterator == first
    void removeIterator();
    // removes the element currently pointed to by the iterator
    // pre: iterator is not already pointing at NULL
    // post: iterator points to NULL, length--
    void insertIterator(listdata data);
    // inserts an element after the node currently pointed to by the iterator
    // precondition: iterator is not off the end of the list
    // postcondition: length++, the prev and next links around the new node are updated
    void advanceIterator();
    // moves the iterator up by one node
    // precondition: iterator is not off end
    void reverseIterator();
    // moves the iterator down by one node
    // precondition: iterator is not off end
    void removeFirst();
    //Removes the value stored in first node in the list
    //Precondition: list must not be empty (length!=0 OR first!=NULL)
    //Postcondition: The old first is different from the new first (oldFirst != first)
    //				 length decreases
    void removeLast();
    //Removes the value stored in the last node in the list
    //Precondition: list must not be empty (length!=0 OR first!=NULL)
    //Postcondition: The old last is different from the new last (oldLast != last)
    //				 length decreases
    void insertFirst (listdata data);
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: The old first is different from the new first (oldFirst != first)
    //				 and if the list was empty initially, (first == last)
    //				 length increases
    void insertLast(listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: The old last is different from the new last (oldLast != last)
    //				 and if the list was empty initially, (first == last)
    //				 length increases
    void advanceToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size




    /**Additional List Operations*/

    void printList(ostream& out) const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints nothing if the list is empty
    //Prints a empty newline character if it's empty..

    void printNumberedList() const;
    // prints the contents of the linked list to the screen in the format:
    // #. <element> followed by a newline

    bool operator==(const List &list);
    // compares two lists to see if they are equal
    // postcondition: returns true if lists are equal, false otherwise

    void reversePrint() const;
    //Wrapper function that calls the reverse helper function to print a list in reverse
    //prints nothing if the List is empty

};



///*************************Constructors and Destructors*************************/

template <class listdata>
List<listdata>::List(){
//Default constructor; initializes an empty list
//Postcondition: an empty list will be created, variables initialized (first, last, iterator, and length = 0)
	first = last = iterator = NULL;
	length = 0;
}

template <class listdata>
List<listdata>::List(const List &list){
//Copy Constructor; creates a deep copy of the original list
// postcondition: an identical list is created
	if(list.isEmpty())						// if orig list empty, make empty list
		first = last = iterator = NULL;
	else{
		first = new Node(list.first->data); // construct new node
		Node* temp = list.first;			// set temp node ptr to pt @ first of orig list
		iterator = first;					// set iterator to pt to first node of new list

		while(temp->next != NULL){
			temp = temp->next;
			iterator->next = new Node(temp->data);	// construct new node w/ copy of data
			iterator->next->prev = iterator;		// set the new Node's prev to the previous node
			iterator = iterator->next; 		// advance to this new node
		}
		last = iterator;					// once done copying orig list over, iterator reaches the end
		iterator = NULL;
	}
	length = list.length;
}

//Destructor. Frees memory allocated to the list
//Postcondition: memory is freed, list is empty
template <class listdata>
List<listdata>::~List()
{
	Node* b = first;		// traverses through the list
	Node* a;				// pts at next node

	while(b){				// while b != 0
		a = b->next;		// a = addr of node after b
		delete b;			//remove b (you know it is not NULL from if)
		b = a;				//b "catches up" with a (both point to same place in list)
	}
}



//===============================================================================================
//================================ Access Functions =============================================
//===============================================================================================


//Returns the first data in the list
//Precondition: list must not be empty (length!=0 OR first!=NULL)
template <class listdata>
listdata List<listdata>::getFirst() const
{
	assert(!isEmpty());
	return first->data;
}

//Returns the last data in the list
//Precondition: list must not be empty (length!=0 OR first!=NULL)
template <class listdata>
listdata List<listdata>::getLast() const
{
	assert(!isEmpty());		// precondition
	return last->data;
}

//Determines whether a list is empty.
template <class listdata>
bool List<listdata>::isEmpty() const
{
	return (length == 0);
}

//Returns the size of the list
template <class listdata>
int List<listdata>::getLength() const
{
	return length;
}


// returns the element currently pointed at by the iterator
// precondition: list must not be empty, tested by iterator != NULL
template <class listdata>
listdata List<listdata>::getIterator() const
{
	assert (!offEnd());		// precondition, iterator != NULL
	return iterator->data;
}

// returns whether the iterator is off the end of the list
// (returns if iterator == NULL)
template <class listdata>
bool List<listdata>::offEnd() const
{
	return (iterator == NULL);
}

//Wrapper function that calls the isSorted helper function to determine whether
//a list is sorted in ascending order.
//We will consider that a list is trivially sorted if it is empty.
template <class listdata>
bool List<listdata>::isSorted() const
{
	return isSorted(first);
}

//Indicates the index of the Node where the iterator is currently pointing
//Nodes are numbered starting at 1 through the size of the list
//Pre: !offEnd()
template <class listdata>
int List<listdata>::getIndex() const
{
	assert(!offEnd());

	Node* N = first;      //Start at beginning
	int index = 1;        //Index is beginning

	while(N != iterator)  //Make sure first is not the iterator
	{		              //because you want the position of the iterator
		N = N->next;      //Move node down the list
		index++;
	}
	return index;         //Return the position of the index
}

//Searches the list, element by element, from the start of the List to the end of the List
//Returns the index of the element, if it is found in the List
//Does not call the indexing functions in the implementation
//Returns -1 if the element is not in the List
//Pre: length != 0
//Post: The iterator location has not been changed
template <class listdata>
int List<listdata>::linearSearch(listdata data) const
{
	assert(!isEmpty()); 				// pre: length != 0

	Node* N = first;            		//Temp nodeptr pointing to beginning

	for(int i = 1; i <= length; i++){	// i is index
		if(N->data == data)
			return i;
		N = N->next;
	}

	return -1; 					// if we've gone through the list, return not found
}

//Public
//Returns the index where data is located in the List
//Calls the private helper function binarySearch to perform the search
//Pre: length != 0
//Pre: List is sorted (must test on a sorted list)
//Post: The iterator location has not been changed
template <class listdata>
int List<listdata>::binarySearch(listdata data) const
{
	assert(!isEmpty());					  // pre: length != 0
	assert(isSorted());
	return binarySearch(1, length, data); //Lowest length is 1 and highest is length's value
}


//===============================================================================================
//============================ Manipulation Procedures ==========================================
//===============================================================================================

//Removes the value stored in first node in the list
//Precondition: list must not be empty (length!=0 OR first!=NULL)
//Postcondition: The old first is different from the new first (oldFirst != first)
//				 length decreases, iterator = NULL
template <class listdata>
void List<listdata>::removeFirst()
{
	assert(!isEmpty());			// precondition
	if(length == 1){
		delete first;
		first = last = NULL;
	}
	else{
		Node* temp = first;		// temp = addr of 1st node
		first = first->next;	// first = addr of 2nd node
		first->prev = NULL;		// set prev to null
		delete temp;			// delete old 1st node
	}
	length--;
	iterator = NULL;
}

//Removes the value stored in the last node in the list
//Precondition: list must not be empty (length!=0 OR first!=NULL)
//Postcondition: The old last is different from the new last (oldLast != last)
//				 length decreases, iterator = NULL
template <class listdata>
void List<listdata>::removeLast()
{
	assert(!isEmpty());			// precondition
	if(length == 1){
		delete last;
		first = last = NULL;
	}
	else{
		Node* temp = last;		// temp ptr @ current last
		last = last->prev;		// set last ptr @ prev node
		last->next = NULL;		// set ptr at null rather than deallocated memory
		delete temp;
	}
	length--;
	iterator = NULL;
}

//Inserts a new data at the beginning of the list
//If the list is empty, the new data becomes both first and last
//Postcondition: The old first is different from the new first (oldFirst != first)
//				 and if the list was empty initially, (first == last)
//				 length increases
template <class listdata>
void List<listdata>::insertFirst (listdata data)
{
	Node* N = new Node(data);	// allocate mem for new first node, initialized
	if(isEmpty()){
		first = last = N;
	}
	else{
		N->next = first;		// first becomes the next item
		first->prev = N;		//need to update the prev pointer of first to pt back at new node
		first = N;				// N is the new first item
	}
	length++;
}

//Inserts a new data at the end of the list
//If the list is empty, the new data becomes both first and last
//Postcondition: The old last is different from the new last (oldLast != last)
//				 and if the list was empty initially, (first == last)
//				 length increases
template <class listdata>
void List<listdata>::insertLast(listdata data)
{
	Node* N = new Node(data);	//N->data = data

	if(isEmpty()){				// if length == 0
		first = last = N;
	}
	else{
		N->prev = last;			// update the new node's prev pointer to the previous last node
		last->next = N;			// current last's next ptr @ the new node
		last = N;				// new last ptr @ new node
	}
	length++;
}

// moves the iterator to the beginning of the list
//post: iterator == first, iterator != NULL
template <class listdata>
void List<listdata>::startIterator()
{
	iterator = first;
}

// removes the element currently pointed to by the iterator
// pre: iterator is pointing at a node and not NULL
// post: iterator points to NULL
template <class listdata>
void List<listdata>::removeIterator()
{
	assert(!offEnd());		// precondition

	if(iterator == last)
		removeLast();

	else if(iterator == first)
		removeFirst();

	else{
		iterator->prev->next = iterator->next;
		iterator->next->prev = iterator->prev;
		delete iterator;
		length--;
		iterator = NULL;
	}
}

// inserts an element after the node currently pointed to by the iterator
// precondition: iterator is not off the end of the list
template <class listdata>
void List<listdata>::insertIterator(listdata data)
{
	assert(!offEnd());				// precondition
	if(iterator == last){			// if length == 0
		insertLast(data);
	}
	else{
		Node* N = new Node(data);	//N->data = data

		N->prev = iterator;			//update pointers
		N->next = iterator->next;
		iterator->next->prev = N;
		iterator->next = N;

		length++;
	}
}

// moves the iterator up by one node
//precondition: iterator is not off end
template <class listdata>
void List<listdata>::advanceIterator()
{
    assert(!offEnd());
	iterator = iterator->next;
}

// moves the iterator down by one node
//precondition: iterator is not off end (iterator != NULL)
template <class listdata>
void List<listdata>::reverseIterator()
{
	assert(!offEnd());
	iterator = iterator->prev;
}

//Moves the iterator to the node whose index number is specified in the parameter
//Nodes are numbered starting at 1 through the size of the List
//Pre: size != 0
//Pre: index <= size
template <class listdata>
void List<listdata>::advanceToIndex(int index)
{
	assert(!isEmpty());				//Pre: size != 0
	assert(index <= length);		//Pre: index <= size

	iterator = first;               //Start at front of list

	for (int x = 1; x < index; x++)
	{
		iterator = iterator->next;  //Move down list one by one until index is found
	}
}


//===============================================================================================
//============================= Additional List Operations ======================================
//===============================================================================================

//Prints to the console the value of each data in the list sequentially
//and separated by a blank space
//Prints nothing if the list is empty
//Prints a empty newline character if it's empty..
template <class listdata>
void List<listdata>::printList(ostream& out) const
{
	Node *temp = first;
	while(temp->next != NULL){	// temp != null, temp != 0
		out << temp->data << ", ";
		temp = temp->next;
	}
	out << temp->data;
	out << endl;	//print new line whether or not line is empty
}

// prints the contents of the linked list to the screen in the
// format: #. <element> followed by a newline
template <class listdata>
void List<listdata>::printNumberedList() const
{
	int num = 1;
	Node *temp = first;

		while(temp)  // temp != null, temp != 0
		{
			cout << num << ". " << temp->data << endl;
			temp = temp->next;
			num++;
		}
}

// compares two lists to see if they are equal
//Postcondition: returns true if lists are equal and false otherwise
template <class listdata>
bool List<listdata>::operator==(const List &list)
{
	if(length != list.length)
		return false;
	Node* temp1 = first;
	Node* temp2 = list.first;
	while(temp1 != NULL)
	{
		if(temp1->data != temp2->data)
			return false;
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	return true;
}

//Wrapper function that calls the reverse helper function to print a list in reverse
//prints nothing if the List is empty
template <class listdata>
void List<listdata>::reversePrint() const
{
	if(!isEmpty())
		reversePrint(last);				// reverse print starting from the end
}


//===============================================================================================
//==================================== Private Functions ========================================
//===============================================================================================

//Helper function for the public reversePrint() function.
//Recursively prints the data in a List in reverse.
template <class listdata>
void List<listdata>::reversePrint(Node* node) const
{
	if (node != NULL){					// keep going if the node is not at the end
		cout << node->data << " ";
		reversePrint(node->prev);
	}

}

//Helper function for the public isSorted() function.
//Recursively determines whether a list is sorted in ascending order.
template <class listdata>
bool List<listdata>::isSorted(Node* node) const
{
	if(node == last)                           //If the nodeptr points to last (1 or 0 nodes), return true
		return true;
	else if((node->data) > (node->next->data)) //If data > next's data, return false
	    return false;
	else
	    return isSorted(node->next);          //otherwise, pass next node and check next one's value

}

//Recursively search the list by dividing the search space in half
//Returns the index of the element, if it is found in the List
//Returns -1 if the element is not in the List
//Post: The iterator location has not been changed
// call : return binarySearch(1, length, data);
template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const
{
	if (high < low)                  //Return not found if high passes low
		return -1;

	int mid = (low + (high-low)/2);  //Midpoint formula, should be int bc numeric

	Node* N = first;				// N @ index 1
	for(int i=1; i<mid; i++)		// to get N to index mid
		N = N->next;

	if (N->data == data)             //Check if the mid is the data needed
		return mid;

	else if (N->data > data)          //Check left side of mid
		return binarySearch(low, mid-1, data);

	else                             //Check right side of mid
		return binarySearch(mid+1, high, data);
}

#endif /* LIST_H_ */
