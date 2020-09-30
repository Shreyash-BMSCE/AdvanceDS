//   Write a program to perform insertion, deletion and searching operations on a skip list.
//  consider the maximum number of levels to be log n where 'n' is the number of nodes in the list. 

//    NOT COMPLETE 

#include <iostream>
using namespace std; 

class Node 
{ 
public: 
	int key; 
	Node **forward; 
	Node(int key, int level) 
	{ 
		this->key = key; 
		forward = new Node*[level+1];  
		memset(forward, 0, sizeof(Node*)*(level+1)); 
	}
};
