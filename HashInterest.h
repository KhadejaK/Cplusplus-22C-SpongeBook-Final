/*
 * HashInterest.h
 *
 *  Created on: Mar 9, 2018
 *      Author: joewy
 */

#ifndef HASHINTEREST_H_
#define HASHINTEREST_H_

#include "User.h"

class HashInterest
{
private:
	static const int SIZE = 5 * 17 *2;
	List<int> Table[SIZE];

public:
    /**Constructors*/

	HashInterest(){}
    //constructor

    ~HashInterest(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;

    int countBucket(int index) const;

    int search(string interest) const;

    List<int> getBucket(int index) const;

    /**Manipulation Procedures*/

    void insert(User u);


    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;

    void printTable(ostream& out) const;

};



#endif /* HASHINTEREST_H_ */
