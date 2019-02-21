//============================================================================
// Name        : BST.h
// Author      : Khadeja Khalid and Tiffany Tran
// Version     : CIS 22C Lab 7
//============================================================================

#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>

using namespace std;

template<typename bstdata>

class BST
{
private:
    struct Node
	{
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata)
        {
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    /**Private helper functions*/
    void insertNode(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a value into the BST

    void textPrint(ostream& out, Node* root) const;

    void inOrderPrint(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void preOrderPrint(ostream& out, Node* root) const;
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrint(ostream& out, Node* root) const;
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void copyNode(Node* copy);
    //recursive helper function to the copy constructor

    void freeNode(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchNode(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the value is found in the tree

    bstdata minimum(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum value in the tree

    bstdata maximum(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum value in the tree

    Node* removeNode(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSize(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeight(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

public:

    /**constructors and destructor*/

    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory

    /**access functions*/

    bstdata minimum() const;
    //returns the minimum value in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum value in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the value stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()

    /**manipulation procedures*/

    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified value from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()

    /**additional functions*/

    void textPrint(ostream& out) const;

    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void preOrderPrint(ostream& out) const;
    //calls the reOrderPrint function to print out the values
    //stored in the BST

    void postOrderPrint(ostream& out) const;
    //calls the postOrderPrint function to print out the values
    //stored in the BST
};

//**************  Constructors and Destructor ***********************

//Instantiates a new BST
template<typename bstdata>
BST<bstdata>::BST()
{
	root = NULL;
}

//copy constructor
template<typename bstdata>
BST<bstdata>::BST(const BST &bst)
{
	if(bst.isEmpty())	// if the orig tree's root == NULL (isEmpty)
		root = NULL;
	else
	{
		root = new Node(bst.root->data); // else, set new root to a copy of the bst root's data
		copyNode(bst.root);				 // call helper function to check left/right subtrees
	}
}

//deallocates the tree memory
template<typename bstdata>
BST<bstdata>::~BST()
{
	freeNode(root);		// frees left/right subtrees of root
	delete root;		// free root
	root = NULL;		// reset root ptr
}

//************** Private helper functions ********************************

//private helper function for insert
//recursively inserts a value into the BST
template<typename bstdata>
void BST<bstdata>::insertNode(Node* root, bstdata data)
{
	if (root->data == data)      //Base Case, no duplicates
		return;

	else if (root->data > data)  //If data is less than data stored
	{
		if (root->left == NULL)  //Check leftchild
			root->left = new Node(data);      //If true, insert new value at leftchild
		else                     //else,
			insertNode(root->left, data);
	}
	else
	{
		if (root->right == NULL)
			root->right = new Node(data);
		else
			insertNode(root->right, data);
	}
}

//private helper function for inOrderPrint
//recursively prints tree values in order from smallest to largest
template<typename bstdata>
void BST<bstdata>::inOrderPrint(ostream& out, Node* root) const
{
	if (root != NULL)
	{
		inOrderPrint(out, root->left);
		out << root->data << endl;
		inOrderPrint(out, root->right);
	}
}

//private helper function for textPrint
//recursively prints tree values in order separated by comma
template<typename bstdata>
void BST<bstdata>::textPrint(ostream& out, Node* root) const
{
	if (root != NULL)
	{
		textPrint(out, root->left);
		out << root->data;
		if(root->right != NULL)
			out << ", ";
		textPrint(out, root->right);
	}
}


//private helper function for preOrderPrint
//recursively prints tree values in pre order
template<typename bstdata>
void BST<bstdata>::preOrderPrint(ostream& out, Node* root) const
{
	if (root != NULL)
	{
		out << root->data << " ";
		preOrderPrint(out, root->left);
		preOrderPrint(out, root->right);
	}
}

//private helper function for postOrderPrint
//recursively prints tree values in post order
template<typename bstdata>
void BST<bstdata>::postOrderPrint(ostream& out, Node* root) const
{
	if (root != NULL)
	{
		postOrderPrint(out, root->left);
		postOrderPrint(out, root->right);
		out << root->data << " ";
	}
}

//recursive helper function to the copy constructor
template<typename bstdata>
void BST<bstdata>::copyNode(Node* copy)
{
	if(copy->left)				// if there's a leftchild (copy->left != NULL)
	{
		insert(copy->left->data);
		copyNode(copy->left);
	}
	if(copy->right)				// if there's a rightchild (copy->right != NULL)
	{
		insert(copy->right->data);
		copyNode(copy->right);
	}
}

//private helper function for the destructor
//recursively frees the memory in the BST
template<typename bstdata>
void BST<bstdata>::freeNode(Node* root)
{
	if(root == NULL)	 // return if empty BST or @ leaf node
		return;
	else
	{
		if(root->left != NULL)		 // if there's a leftchild
		{
			freeNode(root->left);	 // go to the leftest leftchild :)
			delete root->left;
			root->left = NULL;
		}
		else if(root->right != NULL) // if there's a leftchild
		{
			freeNode(root->right);	 // go to the rightest rightchild : )
			delete root->right;
			root->right = NULL;
		}
	}
}

//recursive helper function to search
//returns whether the value is found in the tree
template<typename bstdata>
bool BST<bstdata>::searchNode(Node* root, bstdata data) const
{
	if (root->data == data)
		return true;

	else if (root->data > data)
	{
		if (root->left == NULL)
			return false; //Value not found
		else
			return (searchNode(root->left, data));
	}
	else
	{
		if (root->right == NULL)
			return false; //Value not found
		else
			return (searchNode(root->right, data));
	}
}

//recursive helper function to minimum
//returns the minimum value in the tree
template<typename bstdata>
bstdata BST<bstdata>::minimum(Node* root) const
{
	if (root->left != NULL)
		return minimum(root->left);
	else
		return root->data;
}

//recursive helper function to maximum
//returns the maximum value in the tree
template<typename bstdata>
bstdata BST<bstdata>::maximum(Node* root) const
{
	if (root->right != NULL)
		return maximum(root->right);
	else
		return root->data;
}

//recursive helper function to remove
//removes data from the tree
template<typename bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeNode(Node* root, bstdata data)
{
	if (root == NULL)
		return root;

	else if (data < root->data)
		root->left = removeNode(root->left, data);

	else if (data > root->data)
		root->right = removeNode(root->right, data);

	else
	{
		if (root->left == NULL && root->right == NULL) //If leaf node
		{
			delete root;
			root = NULL;
		}
		else if (root->right == NULL) //Only left child
		{
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		else if (root->left == NULL) //Only right child
		{
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else
		{
			root->data = minimum(root->right);
			root->right = removeNode(root->right, minimum(root->right));
		}
	}
	return root;

}

//recursive helper function to the size function
//calculates the size of the tree
//stores the result in size
template<typename bstdata>
void BST<bstdata>::getSize(Node* root, int& size) const
{
	if (root != NULL)
	{
		size++;
		getSize(root->left, size);
		getSize(root->right, size);
	}
}

//recursive helper function to the height function
//returns the height of the tree
template<typename bstdata>
int BST<bstdata>::getHeight(Node* root) const
{
	if (root == NULL)
		return -1; //Height of NULL is -1
	else
	{
		int leftHeight = getHeight(root->left);
		int rightHeight = getHeight(root->right);

		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}

}


//************** Access Functions ***********************************

//returns the minimum value in the BST
//pre: !empty()
template<typename bstdata>
bstdata BST<bstdata>::minimum() const
{
	assert (!isEmpty());
	return minimum(root);
}

//returns the maximum value in the BST
//pre: !empty()
template<typename bstdata>
bstdata BST<bstdata>::maximum() const
{
	assert (!isEmpty());
	return maximum(root);
}

//determines whether the BST is empty
template<typename bstdata>
bool BST<bstdata>::isEmpty() const
{
	return root == NULL;
}

//returns the size of the tree
template<typename bstdata>
int BST<bstdata>::getSize() const
{
	int size = 0;
	getSize(root, size);
	return size;
}

//returns the value stored at the root of the BST
//pre: !isEmpty()
template<typename bstdata>
bstdata BST<bstdata>::getRoot() const
{
	assert (!isEmpty());
	return root->data;
}

//returns the height of the tree
template<typename bstdata>
int BST<bstdata>::getHeight() const
{
	return getHeight(root);
}

//returns whether the data is found in the tree
//pre: !isEmpty()
template<typename bstdata>
bool BST<bstdata>::search(bstdata data) const
{
	assert (!isEmpty());

	if (data == root->data)
	    return true;
	else
		return searchNode(root, data); //call helper function

}


//************** Manipulation Procedures *****************************

//inserts new data into the BST
template<typename bstdata>
void BST<bstdata>::insert(bstdata data)
{
	if (root == NULL)
	{
		root = new Node(data); //if the tree is empty insert the value at the root
	}
	else
	{
		insertNode(root, data); //otherwise call the helper function, passing it the root
	}
}

//removes the specified value from the tree
//pre: data is located in the tree
//pre: !isEmpty()
template<typename bstdata>
void BST<bstdata>::remove(bstdata data)
{
	assert (search(data));
	assert (!isEmpty());
	root = removeNode(root, data);
}


//************** Additional Functions ********************************

template<typename bstdata>
void BST<bstdata>::textPrint(ostream& out) const
{
	textPrint(out, root);
}
//calls the inOrderPrint function to print out the values
//stored in the BST
template<typename bstdata>
void BST<bstdata>::inOrderPrint(ostream& out) const
{
	inOrderPrint(out, root);
}

//calls the reOrderPrint function to print out the values
//stored in the BST
template<typename bstdata>
void BST<bstdata>::preOrderPrint(ostream& out) const
{
	preOrderPrint(out, root);
}

//calls the postOrderPrint function to print out the values
//stored in the BST
template<typename bstdata>
void BST<bstdata>::postOrderPrint(ostream& out) const
{
	postOrderPrint(out, root);
}

#endif /* BST_H_ */
