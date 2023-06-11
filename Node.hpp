#include <iostream> 
#include "WordEntry.hpp"
//This is a struct Node 
//The data inside struct Node
//contains the WordEntry object
//and pointer objects of left and right of type Node
struct Node 
{
		WordEntry dataToAdd; 
		Node* left; 
		Node* right; 
};