/*
 * HashFriend.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: joewy
 */

#include "HashFriend.h"

    /**Access Functions*/

//return the index of the key
int HashFriend::hash(string key) const
{
	int index, sum = 0;
	for(unsigned i = 0; i < key.length(); i++)
		sum += (int) key[i]; //summing the ASCII values for each character in the string

	index = sum % SIZE; //dividing the summed ASCII values by 35 && storing remainder as my index

	return index;
}

int HashFriend::countBucket(int index) const
{
	assert(index >= 0 && index < SIZE);
	return Table[index].getLength();
}

int HashFriend::search(string name) const
{
	int index = hash(name);

	if(Table[index].isEmpty())
		return -1;
	else
		return index;
}

List<int> HashFriend::getBucket(int index) const
{
		return Table[index];

}
/**Manipulation Procedures*/

//insert a new book in the hash table
void HashFriend::insert(User u)
{
	int index = hash(u.getFirstname() + u.getLastname());
	Table[index].insertLast(u.getID());
}

void HashFriend::remove(User u)
{
	int index = search(u.getFirstname() + u.getLastname());
	assert(index != -1);

	Table[index].removeFirst();
}

/**Additional Functions*/

void HashFriend::printBucket(ostream & out, int index) const
{
	assert(index >= 0 && index <= SIZE);

	Table[index].printList(out);
}

void HashFriend::printTable(ostream& out) const
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
