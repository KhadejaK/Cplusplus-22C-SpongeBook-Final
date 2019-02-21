#ifndef USER_H_
#define USER_H_

//#include <string>
#include "List.h"
#include "BST.h"
#include "User.h"

class User
{
private:
	string firstName;
	string lastName;
	string userName;
	string passWord;
	string city;
	string state;
	unsigned ID;
	List<string> friends; // remove linked list of friends if nec.
	BST<string> friendBST;
	BST<User> friendUser;
	List<string> interests;

public:
	/**Constructors*/
	User();
	User(string f, string l, string u, string p, string c, string s, unsigned id);

    /**Access Functions*/

	string getFirstname() const;
	string getLastname() const;
	string getUsername() const;
	string getPassword() const;
	string getCity() const;
	string getState() const;
	bool searchFriend(string name) const;
	unsigned getID() const;
	List<string> getInterest() const;
	List<string> getFriend() const;
	BST<string> getBST();


	/**Manipulation Procedures*/
	void setFirstname(string f);
	void setLastname(string l);
	void setUsername(string u);
	void setPassword(string p);
	void setCity(string c);
	void setState(string s);
	void setFriends(string fr);
	void removeFriend(string fr);
	void setBST(User u);
	void printBST();
	void printFriends() const;
	void setInterests(string i);


	/**Additional Functions*/
	void printText(ostream& out) const;
	friend ostream& operator<<(ostream & out, const User& user);
	bool operator==(const User& user);
	bool operator<(const User& user);
	bool operator>(const User& user);

};



#endif /* USER_H_ */
