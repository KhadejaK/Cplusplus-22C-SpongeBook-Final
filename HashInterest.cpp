/*
 * HashFriend.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: joewy
 */

#include "HashInterest.h"

    /**Access Functions*/

//return the index of the key
int HashInterest::hash(string key) const
{
	int index, sum = 0;
	for(unsigned i = 0; i < key.length(); i++)
		sum += (int) key[i]; //summing the ASCII values for each character in the string

	index = sum % SIZE; //dividing the summed ASCII values by 35 && storing remainder as my index

	return index;
}

int HashInterest::countBucket(int index) const
{
	assert(index >= 0 && index < SIZE);
	return Table[index].getLength();
}

int HashInterest::search(string interest) const
{
	int index = hash(interest);

	if(Table[index].isEmpty())
		return -1;
	else
		return index;
}

List<int> HashInterest::getBucket(int index) const
{
	return Table[index];
}

/**Manipulation Procedures*/

//insert a new book in the hash table
void HashInterest::insert(User u)
{
	List<string> temp = u.getInterest();

	if(temp.getLength() != 0)
	{
		temp.startIterator();

	for(int i = 0; i < temp.getLength(); i++)
	{
		int index = hash(temp.getIterator());
		if(Table[index].isEmpty())
			Table[index].insertLast(u.getID());
		if(Table[index].linearSearch(u.getID()) == -1)
			Table[index].insertLast(u.getID());
		temp.advanceIterator();
	}
	}
}

/**Additional Functions*/

void HashInterest::printBucket(ostream & out, int index) const
{
	assert(index >= 0 && index <= SIZE);

	Table[index].printList(out);
}

void HashInterest::printTable(ostream& out) const
{
	for(int i = 0; i < SIZE; i++)
	{
		if(!Table[i].isEmpty())
		{
			out << "Group " << i + 1 << endl;
			out << Table[i].getFirst() << endl;
			out << "+" << countBucket(i) - 1 << " more user(s)\n\n\n";
		}
	}
	cout << endl;
}
