//============================================================================
// Name        : Graph.h
// Author      : Khadeja Khalid
// Version     : Course Project
//============================================================================

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <cstdlib>
#include <vector>

#include "List.h"
#include "User.h"

using namespace std;

class Graph
{
public:

/**Constructors and Destructors*/

	//Graph(){}

	//~Graph(){}
    Graph(int u);
    //initializes an empty graph to have u users

/*** Access Functions ***/

int getNumEdges() const;
//returns the number of edges in the graph

int totalVertices() const;
//returns the number of users in the graph

bool isEmpty() const;
//returns whether the graph is empty (no users)

int getDistance(User u ) const;
//Pre: u <= getNumUsers
//Returns the value of the distance[v]

int getParent(User u) const;
//Pre: u <= getNumUsers
//Returns the value of the parent[u]

char getColor(User u) const;
//Pre: v <= numVertices
//Returns the value of color[v]

//int getUserID(User u);
//Returns the user ID from the hash table

/*** Manipulation Procedures ***/

void addEdge(int u1, int u2);
//u1.getid
//inserts user 1 into the adjacency list of user 2 (i.e. inserts u2 into the list at index u1)
//and inserts u1 into u2.

/*** Additional Operations ***/

void printGraph(ostream& out);
//Prints the adjacency list of each vertex in the graph,
//vertex: <space separated list of adjacent vertices>
//Prints to the console or to an output file given the ostream parameter

void printBFS(ostream& out);
//Prints the current values in the parallel vectors after executing BFS
//Prints to the console or to an output file given the ostream parameter
//First prints the heading:
//v <tab> c <tab> p <tab> d <tab>
//Then, prints out this information for each vertex in the graph
//Note that this function is intended purely to help you debug your code

void BFS(int source, vector<User>& allUsers);
//Performs breath first search on this Graph give a source user
//pre: at least one user must exist
//pre: source is a user in the graph

void rankingAlgorithm(int source, vector<User> & allUsers);
//Calls BFS on source?
//

void printFriendRecommendations(int rankedFriends[], int matchInterests[], vector<User> & allUsers, ostream& out);
//Can add a friend

void printPath(User source, User destination, ostream& out);
//Prints the path from the source to the destination vertex
//Prints to the console or to an output file given the ostream parameter

private:
	int vertices;
	int edges; //number of edges and vertices
    vector<List<int>> adj; //A list of strings to store users bc a list of users doesn't work
    vector<char> color;
    vector<int> distance;
    vector<int> parent; //Stores the user ID of the parent

    List<int> friendR; //a linked list of friend reccomendations
    int rankedFriends[100];

};

#endif
