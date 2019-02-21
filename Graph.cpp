//============================================================================
// Name        : Graph.cpp
// Author      : Khadeja Khalid
// Version     : Course Project
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>

#include "Graph.h"
#include "HashInterest.h"
#include "List.h"
#include "User.h"
#include "BST.h"

//*************** Constructors and Destructors *******************************

//initializes an empty graph to have u vertices/users
Graph::Graph(int u)
{
	vertices = u;
	edges = 0;

	for (int i = 0; i <= 100; i++)
	{
		rankedFriends[i] = 0;
	}

	for(int i = 0; i <= u; i++)
	{
		color.push_back('W');
		distance.push_back(-1);
		parent.push_back(0);
		adj.push_back(List<int>());
	}

}

//*************** Access Functions *******************************************

//returns the number of edges in the graph
int Graph::getNumEdges() const
{
	return edges;
}

//returns the number of vertices in the graph
int Graph::totalVertices() const
{
	return vertices;
	//return 16;
}

//returns whether the graph is empty (no vertices)
bool Graph::isEmpty() const
{
	return (vertices == 0);
}

//Pre: v <= numVertices
//Returns the value of the distance[v]
int Graph::getDistance(User u) const
{
	//assert(v <= vertices);
	return distance.at(u.getID());
}

//Pre: v <= numVertices
//Returns the value of the parent[v]
int Graph::getParent(User u) const
{
	//assert(v <= vertices);
	return parent.at(u.getID());
}

//Pre: v <= numVertices
//Returns the value of color[v]
char Graph::getColor(User u) const
{
	//assert(v <= vertices);
	return color.at(u.getID());
}

//*************** Manipulation Procedures **************************************

//inserts vertex v into the adjacency list of vertex u (i.e. inserts v into the list at index u)
//and inserts u into v.
void Graph::addEdge(int u1, int u2)
{
	if(adj[u1].isEmpty() || adj[u1].linearSearch(u2) == -1)
		adj[u1].insertLast(u2);

	if(adj[u2].isEmpty() || adj[u2].linearSearch(u2) == -1)
		adj[u2].insertLast(u1);
}

//*************** Additional Operations ****************************************

//Prints the adjacency list of each vertex in the graph,
//vertex: <space separated list of adjacent vertices>
//Prints to the console or to an output file given the ostream parameter
void Graph::printGraph(ostream& out)
{
	for (int i = 1; i <= totalVertices(); i++) //0 is dummy location
	{
		out << i << ": ";
		adj[i].printList(out);
	}
}

//Prints the current values in the parallel vectors after executing BFS
//Prints to the console or to an output file given the ostream parameter
//First prints the heading:
//v <tab> c <tab> p <tab> d <tab>
//Then, prints out this information for each vertex in the graph
//Note that this function is intended purely to help you debug your code
void Graph::printBFS(ostream& out)
{
	out << left << setw(5) << "v"
			<< setw(5) << "c"
			<< setw(5) << "p"
			<< setw(5) << "d" << endl;

	for (int i = 1; i <= totalVertices(); i++) //0 is dummy location
	{
		out << left << setw(5) << i
				<< setw(5) << color[i]
				<< setw(5) << parent[i]
				<< setw(5) << distance[i] << endl;
	}
}

//Performs breath first search on this Graph give a source vertex
//pre: at least one vertex must exist
//pre: source is a vertex in the graph
void Graph::BFS(int source, vector<User>& allUsers)
//                                                 ostream& out IS TEMPORARY,
//                                                   FOR TESTING PURPOSES
{
	//assert (!isEmpty());
	//assert (0 < source && source <= totalVertices());

	List<int> queue;

	while (!friendR.isEmpty())
	{
		friendR.removeFirst();
	}

	for (int i = 1; i <= totalVertices(); i++)
	{
		color[i] = 'W';
		distance[i] = -1;
		parent[i] = 0;
	}

	color[source] = 'G';
	distance[source] = 0;

	queue.insertLast(source);

	while (!queue.isEmpty())
	{
		int x = queue.getFirst();
		queue.removeFirst();

		adj[x].startIterator();
		while(!adj[x].offEnd())
		{
			int y = adj[x].getIterator();
			if (color[y] == 'W')
			{
				color[y] = 'G';
				distance[y] = distance[x] + 1;
				if (distance[y] > 1)
				{
					if (friendR.isEmpty() || friendR.linearSearch(y) == -1)
					{
						//If the distance is 2 or greater, the ID gets added to the list
						friendR.insertLast(y);
					}
				}
				parent[y] = x;
				queue.insertLast(y);
			}
			adj[x].advanceIterator();
		}
		color[x] = 'B';
	}

//	cout << "List of possible friends: ";
//	friendR.printList(cout);
//	cout << endl;
}

void Graph::rankingAlgorithm(int source, vector<User> & allUsers)
{
	int matchInterests[totalVertices()];

	int specificUser[totalVertices()]; //Storing individual users for easy access

//	//Insert source into a hash table for interests
//	HashInterest userHash;
//	userHash.insert(allUsers[source]);  //not working
//
//	//Not printing, might be issue with User again
//	//May have to pull out User's interests here through vector into separate linked list and run linear/binary search
//	cout << "Source's HashInterest: "; //testing
//	userHash.printBucket(cout, source); //not working

	for (int i = 0; i <= 100; i++)
	{
		rankedFriends[i] = 0;
 	}

	User sourceUser = allUsers[source];
	List<string> sourceInterest = sourceUser.getInterest();

//	cout << "Source's Interests: "; //testing
//	sourceInterest.printList(cout);

	friendR.startIterator();
	User temp = allUsers[friendR.getIterator()];
	List<string> listIntMutualF = temp.getInterest();


//	listIntMutualF.startIterator();
//	cout << "User ID 3's Interests: "; //testing
//	while (!listIntMutualF.offEnd())
//	{
//		cout << listIntMutualF.getIterator() << " ";
//		listIntMutualF.advanceIterator();
//	}
//	cout << endl << endl;
//
//	friendR.printList(cout); //testing
//	cout << endl;

	for (int i = 0; i <= totalVertices(); i++)
	{
		specificUser[i] = 100;
	}

	friendR.startIterator();
	while (!friendR.offEnd())
	{
		for (int i = 0; i <= totalVertices(); i++)
		{
			if (i == friendR.getIterator())
			{
				specificUser[i] = friendR.getIterator();
			}
		}
		friendR.advanceIterator();
	}

//	//testing
//	cout << "Specific Users: " << endl; //testing
//	for (int i = 1; i <= totalVertices(); i++)
//	{
//		cout << i << ": " << specificUser[i] << endl;
//	}
//	cout << endl; //testing

	for (int i = 0; i <= totalVertices(); i++)
	{
		matchInterests[specificUser[i]] = 0; //an array to store the # of matching interests
		//cout << "User ID " << i << ": " << matchInterests[specificUser[i]] << endl;
	}

	for (int i = 1; i <= totalVertices(); i++)
	{
		if (specificUser[i] != 100)
		{
			User temp = allUsers[specificUser[i]]; //Set current recc friend as a temp user

			List<string> listIntMutualF = temp.getInterest();

			listIntMutualF.startIterator(); //Here we go
			while (!listIntMutualF.offEnd())
			{
				if (sourceInterest.linearSearch(listIntMutualF.getIterator()) != -1)
				{
					matchInterests[specificUser[i]] = matchInterests[specificUser[i]] + 1;
				}
				listIntMutualF.advanceIterator();
			}
		}
	}

//	for (int i = 1; i <= totalVertices(); i++)
//	{
//		cout << "User ID " << i << ": " << matchInterests[specificUser[i]] << " matching!" << endl;
//	}
//	cout << endl;


	for (int i = 1; i <= totalVertices(); i++)
	{
		if (specificUser[i] != 100)
		{
			specificUser[i] = (50 + (distance[specificUser[i]] - matchInterests[i]));
		}
	}

//	cout << "specific user calculation: ";
//	for (int i = 1; i <= totalVertices(); i++)
//	{
//		cout << specificUser[i] << " ";
// 	}
//	cout << endl;
//	//testing


	for (int i = 1; i <= totalVertices(); i++)
	{
		if (specificUser[i] != 100)
		{
			if (rankedFriends[specificUser[i]])
				rankedFriends[specificUser[i] + 1] = i;
				//if # already exists, move it down
			else
				rankedFriends[specificUser[i]] = i;
		}
	}

//	cout << "rankedFriends: ";
//	for (int i = 0; i <= 100; i++)
//	{
//		if(rankedFriends[i] != 0)
//			cout << rankedFriends[i] << " ";
// 	}
//	cout << endl << endl;
//	cout << "====================================" << endl;
//	//testing


	printFriendRecommendations(rankedFriends, matchInterests, allUsers, cout);
}

void Graph::printFriendRecommendations(int rankedFriends[], int matchInterests[], vector<User> & allUsers, ostream& out)
{
	for (int i = 0; i <= 100; i++)
	{
		if(rankedFriends[i] != 0)
		{
			cout << allUsers[rankedFriends[i]].getFirstname() << " "
				<< allUsers[rankedFriends[i]].getLastname() << endl;
			cout << allUsers[rankedFriends[i]].getCity() << ", "
				<< allUsers[rankedFriends[i]].getState() << endl;
			cout << matchInterests[rankedFriends[i]] << " interest(s) in common!" << endl;
			cout << endl;
		}
	}
}


////Prints the path from the source to the destination vertex
////Prints to the console or to an output file given the ostream parameter
//void Graph::printPath(User source, User destination, ostream& out)
//{
//	if (destination == source)
//		out << source;
//	else if (parent[destination] == 0)
//		out << "No path from " << source << " to " << destination << " exists" << endl;
//	else
//	{
//		printPath(source, parent[destination], out);
//		out << " - " << destination;
//	}
//
//}
