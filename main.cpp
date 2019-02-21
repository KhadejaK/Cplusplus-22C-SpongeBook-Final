#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "BST.h"
#include <algorithm>
#include "User.h"
#include "HashFriend.h"
#include "HashInterest.h"
#include "Graph.h"

using namespace std;

int logIn();
int mainMenu();
void viewFriends(int id);
void searchNewFriends(HashFriend& hf, HashInterest& hi, int id);
void removeFriends(int id);
void friendRecs(int id);
void searchByFriend(HashFriend& hf, int id);
void searchByInterest(HashInterest& hi, int id);
void viewProfile(int id);
string createAccount();

vector<User> userID;
HashFriend hf;
HashInterest hi;

void readFile()
{
        string firstName, lastName, userName, passWord, city, state, friendName, interest;
        string filename;
        unsigned id = 1;

        User empty;
        userID.push_back(empty); // index 0 is a empty user

        filename = "data.txt";
        ifstream inputfile;
        inputfile.open(filename);

        assert(inputfile);

        while(inputfile)
        {
        inputfile >> firstName;
        inputfile >> lastName;
        inputfile >> userName;
        inputfile >> passWord;
        inputfile.get(); // go to next line
        getline(inputfile, city, ',');
        inputfile.get();
        getline(inputfile, state);

        User user(firstName, lastName, userName, passWord, city, state, id);

        getline(inputfile, friendName);
        istringstream tempF(friendName);
        while(tempF)
        {
            getline(tempF, friendName, ',');
            if(tempF.peek() == ' ')
                tempF.get();
            user.setFriends(friendName);
        }

        getline(inputfile, interest);
        istringstream tempI(interest);
        while(tempI)
        {
            getline(tempI, interest, ',');
            if(tempI.peek() == ' ')
                tempI.get();
            user.setInterests(interest);
        }

        while(inputfile.peek() == '\n')
            inputfile.get(); // go to next line
        while(inputfile.peek() == ' ')
            inputfile.get(); // go to next line

        userID.push_back(user); // insert to the id vector
        hf.insert(user);// insert to hashFriend
        hi.insert(user);// insert to hashInterest
        id++;
        }
    inputfile.close();
}

int main()
{
    string name;
    int choice;
    int id = 0;
    readFile();

    // Log in validation
    while (id <= 0)
        id = logIn();


    name = userID[id].getFirstname();
    cout << "\nWelcome, " << name << "!\n\n";


    do{
        choice = mainMenu();

        switch(choice)
        {
            case 1:     // view friends
                viewFriends(id);
                break;

            case 2:     // search for new friends
                searchNewFriends(hf, hi, id);
                break;

            case 3:     // friends rec
                friendRecs(id);
                break;


            case 4:      //quit
            {
                ofstream outfile;
                outfile.open("data.txt");

                for(int i = 1; i < userID.size() ; i++){
                	outfile << userID[i];
                }
                outfile.close();

                cout << "     You are signed out"
                     << "\n\t- GOODBYE! -" << endl;
            }
        }

    }while(choice != 4);

    return 0;
}


/// Returns bool for whether or not username & password combo are matched
int logIn()
{
    string un, pw, fn, ln, city, state;
    string choice = "0";
    int id;
    bool option = false;

    while (!option)
    {
        while (choice != "1" && choice != "2" && choice != "3")
        {
                cout << "  - WELCOME TO SPONGEBOOK -" << endl;
                cout << "1. Log in " << endl;
                cout << "2. Create an account " << endl;
                cout << "3. Quit " << endl;
                cout << "\nEnter choice: ";
                cin >> choice;
                cout << endl;
        }

        if (choice == "1")
        {
            int count = 0;

            while (true)
            {
                string userInput;

                cout << "\t- LOG IN -" << endl
                         << "Username: ";
                    cin >> un;
                    cout << "Password: ";
                    cin >> pw;

                    for (int i = 1; i <= userID.size(); i++)
                    {
                        if (un == userID[i].getUsername() && pw == userID[i].getPassword())
                        {
                            cout << "\n *** Login successful ***" << endl;
                            id = i;
                            option = true;
                            return id;
                        }
                    }

                    cout << "\n*** Incorrect username or password. Please try again **\n\n";
                    count ++;

                    if (count > 3)
                    {
                        while (userInput != "YES" && userInput != "NO")
                        {
                            cout << "Multiple failed attempts. Would you like to go back to the main menu? ";
                            cin >> userInput;
                            transform(userInput.begin(), userInput.end(), userInput.begin(),::toupper);
                        }

                        if (userInput == "YES")
                        {
                            cout << endl;
                            choice = "0";
                            option = true;
                            return false;
                        }
                        else if (userInput == "NO")
                        {
                            choice = "1";
                            count = 0;
                        }
                    }
                }
        }
        else if (choice == "2")
        {
            choice = createAccount();
        }
        else if (choice == "3")
        {
            ofstream outfile;
            outfile.open("data.txt");

            for(int i = 1; i < userID.size() ; i++) {
            	outfile << userID[i];
            }

            outfile.close();

        	cout << "\t- GOODBYE! -" << endl;
            exit(0);
        }
    }
    return id;
}

string createAccount()
{
	string un, pw, fn, ln, city, state, choice;
	int id;
	cout << "\t- CREATE AN ACCOUNT -" << endl
	     << "First name: ";
	cin >> fn;

	cout << "Last name: ";
	cin >> ln;

	cout << "Username: ";
	cin >> un;

	cout << "Password: ";
	cin >> pw;

	cout << "City: ";
	cin.ignore();
	getline(cin, city);

	cout << "State: ";
	cin >> ws;
	cin >> state;

	id = userID.size() + 1;

	User newUser(fn, ln, un, pw, city, state, id);
	userID.push_back(newUser);

	bool more = true;
	string interests;

	while (more)
	{
	    cout << "Enter interest or 'stop' to finish: ";
	    cin >> interests;

	    transform(interests.begin(), interests.end(), interests.begin(),::toupper);

	    if (interests == "STOP")
	        more = false;
	    else
	    {
	        transform(interests.begin(), interests.end(), interests.begin(),::tolower);
	        newUser.setInterests(interests);
	    }
	}

	cout << "\n\t*** Account successfully created. You may now log in ***\n" << endl;

	return choice = "0";
}
/// Main Menu :)
int mainMenu()
{
    string input = "0";
    do{
        cout << "\t - MENU -" << endl
             << "1. View Friends" << endl
             << "2. Search for New Friends" << endl
             << "3. Friends Recommendations" << endl
             << "4. Quit\n\n"
             << "Enter choice: ";
        cin >> input;

        if(!isdigit(input[0]))
        {
            cout << "Please enter numbers only.\n";
            input = "0";
        }
        else if(!(input == "1" || input == "2" || input == "3" || input == "4"))
        {
            cout << "Invalid input.\n";
            input = "0";
        }

    }while(input == "0");

    cout << endl;
    int choice = atoi(input.c_str());

    return choice;
}


/// Menu option to view friends
void viewFriends(int id)
{

    string input = "0";

    cout << "     - View Friends -" << endl;

        cout << "1. View all friends\n"
             << "2. View a friend's profile\n"
             << "3. Remove a friend\n\n"
             << "Enter choice or 'm' for menu: ";
        cin >> input;

     do{
    	if(input[0] == 'm')
                return;
        else if(!isdigit(input[0]))
        {
            cout << "Please enter numbers or 'm' only.\n\n";
            input = "0";
        }
        else if(!(input == "1" || input == "2" || input == "3"))
        {
            cout << "Invalid input.\n\n";
            input = "0";
        }
        else if (input == "2")
        {
            viewProfile(id);
        }
        else if (input == "3")
        {
            removeFriends(id);
        }
        else        // input == 1
        {
        	cout << "\n--------------------------------\n";
        	cout << "\n   - Friend List -\n";
            userID[id].printFriends();
            cout << "\n--------------------------------\n";
            cout << "\n1. View a friend's profile\n"
                 << "2. Remove a friend\n\n"
                 << "Enter choice or 'm' for menu: ";
            string input2;
            cin >> input2;

            if(input2[0] == 'm')
            {
            	cout << endl;
				return;
            }
            if (input2 == "1")
            {
                viewProfile(id);
            }
            else if (input2 == "2")
            {
                removeFriends(id);
            }
            else
            {
                cout << "Invalid input. Please try again.\n" << endl;
            }
        }

    }while(input == "0");
    cout << endl;
}

void viewProfile(int id)
{
    string name, fn, ln, input;
    bool results;
    bool option = true;

    User u = userID[id];

    while (option)
        {
            bool find = true;
            while (find)
            {
                cout << "\nEnter the name of the friend you'd like to view: " << endl;
                //cin.ignore();
                cout << "   First Name: ";
                cin >> fn;
                cout << "   Last Name: ";
                cin >> ln;

                name = fn + " " + ln;
                results = u.searchFriend(name);

                if (results == 0)
                {
                    cout << "\nFriend not found. Please try again. \n";
                }
                else
                {
                    for(int i = 1; i <= userID.size(); i++)
                    {
                    	if (fn == userID[i].getFirstname() && ln == userID[i].getLastname())
						{
							User u = userID[i];
							List<string> interest = u.getInterest();

							cout << "\n-----------------------------------------\n";
							cout << "\nProfile of ";
							cout << u.getFirstname() << " " << u.getLastname() << endl << endl;
							cout << "Location: ";
							cout << u.getCity() << endl << endl;
							cout << "Friends: " << endl;
							u.printFriends();
							cout << "\nInterests: " ;
							interest.printList(cout);
							cout << "\n-----------------------------------------\n";
						}
                    }
                    find = false;
                }
            }

            bool more = true;

            while (more)
            {
                cout << "\nWould you like to view more friends? ";;
                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::toupper);

                if (input == "NO")
                {
                    cout << "\nBack to the main menu. " << endl;
                    more = false;
                    option = false;
                }
                else if (input == "YES")
                {
                    more = false;
                }
                else
                {
                    cout << "Please enter only yes or no " << endl;
                }
            }
        }
}
/// Menu option to search for new friends
void searchNewFriends(HashFriend& hf, HashInterest& hi, int id)
{
    string input = "0";
    cout << " - Search for New Friends -" << endl;
    do{
        cout << "1. Search by Name\n"
             << "2. Search by Interest\n\n"
             << "Enter choice or 'm' for menu: ";
        cin >> input;

        if(input[0] == 'm')
                return;
        else if(!isdigit(input[0]))
        {
            cout << "Please enter numbers or 'm' only.\n\n";
            input = "0";
        }
        else if(!(input == "1" || input == "2"))
        {
            cout << "Invalid input.\n\n";
            input = "0";
        }
        else if(input == "1")    // input == 1 or 2
        {
            searchByFriend(hf, id);
        }
        else
        {
            searchByInterest(hi, id);
        }

    }while(input == "0");
    cout << endl;
}


/// Menu option to get friend recommendations
void friendRecs(int id)
{
	Graph g(userID.size());

	cout << "--------------------------------\n";
    cout << "\n - Friend Recommendations -\n" << endl;

    for (int i = 1; i <= userID.size(); i++)
    {
    	List<string> friendList = userID[i].getFriend();
    	friendList.startIterator();

    	while (!friendList.offEnd())
    	{
    		string name = friendList.getIterator();  //Returns a variable
    		for (int x = 1; x <= userID.size(); x++)
    		{
    			string friendName = userID[x].getFirstname() + " " + userID[x].getLastname();
    			if (friendName == name)
    			{
    				g.addEdge(i, x);
    			}
    		}
    		friendList.advanceIterator();
    	}
    }

    g.BFS(id, userID);
    g.rankingAlgorithm(id, userID);

    cout << "--------------------------------\n";
    searchByFriend(hf, id);
    cout << endl;
}

void removeFriends(int id)
{
    string name, input, fn, ln;
    bool results;
    bool option = true;

    while (option)
    {
        bool find = true;
        while (find)
        {
            cout << "\nEnter the name of the friend you'd like to remove: " << endl;
            cout << "   First Name: ";
			cin >> fn;
			cout << "   Last Name: ";
			cin >> ln;
			name = fn + " " + ln;

            results = userID[id].searchFriend(name);

            string username = userID[id].getFirstname() + " " + userID[id].getLastname();

            int friendID;

            for (int i = 1; i <= userID.size(); i++)
            {
            	if (userID[i].getFirstname() + " " + userID[i].getLastname() == name)
            	{
            		friendID = i;
            	}
            }

            if (results == 0)
            {
                cout << "\nFriend not found. Please try again." << endl;
            }
            else
            {
                userID[id].removeFriend(name);
                userID[friendID].removeFriend(username);

                cout << "\n--------------------------------\n\n";
                cout << "    - Updated Friends List -\n";
                userID[id].printFriends();
                cout << "\n--------------------------------\n";

                cout << endl;
                find = false;
            }
        }

        bool more = true;

        while (more)
        {
            cout << "Would you like to remove more friends? ";;
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::toupper);

            if (input == "NO")
            {
                cout << "\nBack to the main menu. " << endl;
                more = false;
                option = false;
            }
            else if (input == "YES")
            {
                more = false;
            }
            else
            {
                cout << "Please enter only yes or no " << endl;
            }
        }
    }
}

void searchByFriend(HashFriend& hf, int id)
{
	string firstN, lastN;
	cout << "\nEnter the first name or 'm' for menu: ";
	cin >> firstN;
	if(firstN == "m" || firstN == "M")
		return;

	cout << "Enter the last name or 'm' for menu: ";

	if(lastN == "m" || lastN == "M")
		return;
	cin >> lastN;

	while(userID[id].getFirstname() + userID[id].getLastname() == firstN + lastN) // can't search the same name to self
	{
		cout << "\nSorry, you can not search for yourself!\n";
		return searchByFriend(hf, id);
	}
	for(unsigned i = 0; i < firstN.length(); i++) // first name can't have any integer
	{
		if(isdigit(firstN[i]))
		{
			cout <<"\nUser's name can not contain any integer\n";
			return searchByFriend(hf, id);
		}
	}
	for(unsigned i = 0; i < lastN.length(); i++)// last name can't have any integer
	{
		if(isdigit(lastN[i]))
		{
			cout <<"\nUser's name can not contain any integer\n";
			return searchByFriend(hf, id);
		}
	}

	int index = hf.search(firstN + lastN); //get the index of the bucket

	if(index == -1) // can't find a user
		{
			cout << "\nUser does not exist!\n";
			return searchByFriend(hf, id);
		}
	else                 // found a user
	{
		if(userID[id].getFriend().linearSearch(firstN + " " + lastN) != -1) // verify whether the user is your friend already
		{
			cout << "\n" <<firstN << " "<< lastN << " is your friend already!\n";
			return searchByFriend(hf, id);
		}

		List<int> temp = hf.getBucket(index);// get the list of the bucket

			temp.startIterator();
			for(int i = 0; i < temp.getLength(); i++) // each bucket might have collision
			{
				int searchid = temp.getIterator();
				if(userID[searchid].getFirstname() + userID[searchid].getLastname() == firstN + lastN)
				{

					cout << "\n" << userID[searchid].getFirstname() << " " << userID[searchid].getLastname() << " is found!\n";
					cout << "\nDo you want to add the user to your friend list, Yes or No? \n";
					string choice;
					cin >> choice;
					if(choice == "YES" || choice == "yes" || choice == "Yes")
					{
						cout << "\n" << firstN << " " << lastN << " has been added to your list.\n";
						userID[id].setFriends(firstN + " " + lastN);
						userID[searchid].setFriends(userID[id].getFirstname() + " " + userID[id].getLastname());
						return;
					}
					else if(choice == "NO" || choice == "no" || choice == "No")
						return;
					else
					{
						cout <<"Invalid input!";
						return;
					}
				}
				else
				{
					if(i == temp.getLength() - 1) // make sure go through all the collison
					{
						cout << "\nUser does not exist!\n";
						return searchByFriend(hf, id);
					}
				}
				temp.advanceIterator();
			}
	}
}

//searching user by interest
void searchByInterest(HashInterest& hi, int id)
{

	string interest;
	cout << "\nEnter the name of the interest or 'm' for menu: ";
	if(interest == "m" || interest == "M")
		return;

	cin.ignore();
	getline(cin, interest);

	int index = hi.search(interest);  //get the index of the bucket

	if(index == -1) // can't find a user with that interest
	{
		cout << "\nNo user has this interest!\n";
		return;
	}
	else                 // found a user
	{
		List<int> temp = hi.getBucket(index);// get the list of the bucket
		vector<int> listInterest;
		int listIndex = 1;
		temp.startIterator();

		cout << "\n---------------------------------------\n\n";

		for(int i = 0; i < temp.getLength(); i++)
		{
			int searchid = temp.getIterator();
			if(searchid != id) // not including user himself
			{
				if(userID[searchid].getInterest().linearSearch(interest) != -1) //minimize collisions by making sure only show the user has that interest
				{
					cout << listIndex << ". " <<userID[searchid].getFirstname() << " " << userID[searchid].getLastname() << " has the interest!\n";
					listInterest.push_back(searchid);
					listIndex++;
				}
			}

			temp.advanceIterator();
		}

		cout << "\n---------------------------------------\n";

		cout << "\nDo you want to add a user to your friend list, Yes or No? ";
		string choice;
		cin >> choice;
		if(choice == "YES" || choice == "yes" || choice == "Yes")
		{
			cout << "Enter the number of the user you want to add:";
			unsigned index;
			cin >> index;

			if(index < 1 || index > listInterest.size())
			{
				cout << "\nNumber is out of range!\n";
				return;
			}

			string tempName = userID[listInterest[index - 1]].getFirstname() + " " + userID[listInterest[index - 1]].getLastname();
			if(!userID[id].getBST().search(tempName)) // make sure is not friend already
			{
				userID[id].setFriends(tempName);
				userID[listInterest[index - 1]].setFriends(userID[id].getFirstname() + " " + userID[id].getLastname());
				cout << "\n" << tempName << " has been added in your friend list.\n";
			}
			else
				cout << "\n" << tempName << " is your friend already!\n";

		}
		else if(choice == "NO" || choice == "no" || choice == "No")
			return;
		else
		{
			cout <<"Invalid input!\n";
			return;
		}
	}
}
