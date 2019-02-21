/*
 * HashFriend.h
 *
 *  Created on: Mar 9, 2018
 *      Author: joewy
 */

#ifndef HASHFRIEND_H_
#define HASHFRIEND_H_

#include "User.h"

class HashFriend
{
private:
	static const int SIZE = 30;
	List<int> Table[SIZE];

public:
    /**Constructors*/

	HashFriend(){}
    //constructor

    ~HashFriend(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;

    int countBucket(int index) const;

    int search(string name) const;

    List<int> getBucket(int index) const;

    /**Manipulation Procedures*/

    void insert(User u);

    void remove(User u);

    void printBucket(ostream& out, int index) const;

    void printTable(ostream& out) const;
};



#endif /* HASHFRIEND_H_ */
