#pragma once
#include <iostream>
#include "Node.hpp"
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

//This template <typename T> means 
//that any class can be created that our BST can store. 
template <typename T>
class BSTree 
{
	//Listed below are the methods needed in our class to perform 
	//what's expected of the assignment specifications. 
	public: 
		Node* head; 
		
		BSTree(); 
		~BSTree(); 
		void deleteTree(Node* aNode); 
		Node* add(T data); 
		Node* Insert(T data); 
		void Remove(T data); 
		bool ElementExists(T data); 
		Node* Find(T data); 
		int ToArray(T*& arr);
		void Empty(); 
		int Count(Node* root);
		int CountTotalWords(Node* root);
		void swap(T *x, T *y); 
		void SortedArrayByFrequency(T*& retrieveArray);
		void SortedArrayByAlphabet(T*& retrieveArray); 
		void topFiveHighest(T*& arr);
		void topFiveLowest(T*& arr);
}; 
//Initially, the constructor will set the
//head to null as BST is not yet initialized. 
template <typename T>
BSTree<T>::BSTree()
{
	head = nullptr; 
}
//Destructor will delete all the memory in the pointer objects 
//meaning that every one of these objects that we created, 
//will point to a nullptr. 
template <typename T> 
BSTree<T>::~BSTree()
{
	//deleteTree(head); 
}



//function to add a node to binary tree
//This is a helper function to populate our tree with data
//based on the insertion input we receive when we run our program. 
//This is an important function as our tree will store the frequency and word inside the Node. 
template <typename T> 
Node* BSTree<T>::add(T data)
{
	
	//Create a new node here 
	//Populate it with data 
	Node* start = new Node; 
	start->dataToAdd = data; 
	start->left = start->right = NULL; 
	
	return start; 
	
}
//Here is the function that inserts the data we asked from int main(). 
//I followed a very similar implementation to the one shown in this link. 
//I took some inspiration from it because it was intutitive for me to understand 
//when I started to write this by myself. 
//Here is the link shown to it. https://www.geeksforgeeks.org/print-characters-and-their-frequencies-in-order-of-occurrence-using-binary-tree/
template <typename T>
Node* BSTree<T>::Insert(T data) 
{
	//We use the head parameter based on the one defined above in our BSTree class. 
	//If head is null, then this means we don't have any root to start out with. 
	//Therefore, we will populate it with data and return the head. 
	 if (head == NULL) 
    {
        head = add(data);
        return head;
    }
    
	//The queue is very helpful to store each of the Node pointers. 
	//The head node will pushed into our queue. 
	std::queue<Node*> q;
    q.push(head);
	
	//We construct a while loop to perform either of the following operations
	//These include: adding data if a node is null(root, root->left, root->right)
	//incrementing the frequency if the node we are trying to add is duplicate, or traversing through left/right nodes to perform either of those two operations.
	//Our condition in the while is checking if the queue is not empty. 
	//If it's not empty, then we will create a pointer object to the object inside the queue. 
	//We then will use the pop method to take out the node* from the queue 
	//because we will not need it after we perform either of the following operations. 

    while (!q.empty()) {

        Node* temp = q.front();
        q.pop();

        //This is the first operation where if the data we are trying to insert 
		//is already present, then we basically want to increment the frequency and break out of the loop. 
        if (temp->dataToAdd.word == data.word) {
            temp->dataToAdd.frequency++;
            break;
        }
       
		//We also have another if statement to check if temp-> left is null
		//If it is, and we are trying to insert data inside here, then we will call add function. 
        if (temp->left == nullptr) {
            temp->left = add(data);
            break;
        }
        else {
            
			//If the word we are trying to insert, which is already present in BST
			// is inside this location(temp->left->dataToAdd.word)
			//then we will want to increment the frequency and break.
            if (temp->left->dataToAdd.word == data.word) {
                temp->left->dataToAdd.frequency++;
                break;
            }
            
			
            q.push(temp->left);
        }
		
        //If temp-> right is null, 
		//then we will insert data using add function and break. 
        if (temp->right == nullptr) {
            temp->right = add(data);
            break;
        }
        else {
            
			//If the word is present in this location of tree, 
			//then we will increment the frequency only and break. 
            if (temp->right->dataToAdd.word == data.word) {
                temp->right->dataToAdd.frequency++;
                break;
            }
           
			
            q.push(temp->right);
        }
    }
	//This will return the node pointer which be useful for our later functions. 
    return head;
}
//For the remove function shown here, this is called inside our destructor. 
//Basically, we locate our WordEntry object inside the tree 
//and in order to remove it, we set the frequency to 0
//and the word will be set to -1. 
//This indicates that the node's position will be null. 
template <typename T>
void BSTree<T>::Remove(T data)
{
	Node* nodeToRemove = Find(data); 
	nodeToRemove->dataToAdd.frequency = 0; 
	nodeToRemove->dataToAdd.word = "-1";
}
//Here to check whether the element exists and return true or false. 
//If the element exists, we use a Queue structure 
//to check the location of where the word exists in temp->left, temp->right, or the root itself. 
template <typename T>
bool BSTree<T>::ElementExists(T data) 
{
	Node* retrieveRoot = head; 
	bool check = false; 
	queue<Node*> q; 
	q.push(retrieveRoot); 
	
	while(!q.empty())
	{
		Node* temp = q.front(); 
		q.pop(); 
		
		if(temp == nullptr)
		{
			break; 
		}
		
		if(temp->dataToAdd.word == data.word && temp->dataToAdd.frequency >= 1)
		{
			check = true; 
			return check; 
		}
		
		q.push(temp->left); 
		q.push(temp->right); 
	}
}
//This is a helper function 
//that can be used to return a pointer to the exact location of the node we are looking for. 
template <typename T>
Node* BSTree<T>::Find(T data) 
{
	Node* retrieveRoot = head; 
	
	queue<Node*> q; 
	
	q.push(retrieveRoot); 
	
	Node* result = nullptr; 
	
	while(!q.empty())
	{
		Node* temp = q.front(); 
		q.pop(); 
		
		if(temp == nullptr)
		{
			break; //we are done
		}
		
		if(temp->dataToAdd.word == data.word && temp->dataToAdd.frequency >= 1)
		{
			result = temp; 
			return result; 
		}
		
		q.push(temp->left); 
		q.push(temp->right); 
	}
	
	return result; 
	
}
//This function returns the size of the array 
//after taking every element from the BST and placing it inside the array. 
template <typename T>
int BSTree<T>::ToArray(T*& arr) // returns size of array
{
	 //get count of nodes from tree and that would be array size.
	 int countNodes = Count(head); 
	 arr = new T[countNodes]; 
	 
	 int startIndex = 0; 
	 Node* retrieveRoot = head; 
	 queue<Node*> q; 
	 
	 q.push(retrieveRoot); 
	 
	 while(!q.empty())
	 {
		 Node* temp = q.front(); 
		 q.pop(); 
		 
		 if(temp == nullptr)
		 {
			 continue;
		 }
		 
		 q.push(temp->left); 
		 q.push(temp->right); 
		 
		 arr[startIndex] = temp->dataToAdd; 
		 startIndex = startIndex + 1; 
	 }
	 
	 return startIndex;
	 
	 
}
//This will empty out the list 
//once we are done with using it 
//by deleting everything inside our list of Node pointers in the Queue. 
template <typename T>
void BSTree<T>::Empty() 
{
	Node* retrieveRoot = head; 
	queue<Node*> q; 
	
	q.push(retrieveRoot); 
	
	while(!q.empty())
	{
		Node* temp = q.front(); 
		q.pop(); 
		
		if(temp == nullptr)
		{
			break;
		}
		
		q.push(temp->left); 
		q.push(temp->right); 
		
		delete temp; 
	}
	
}
//As the assignment specifications stated, 
//this will count the unique number of nodes 
//inside of the tree. 
//I did take some inspiration from the following link shown
//Since I was able to understand this method, I followed the format similarly. https://math.hws.edu/eck/cs225/s03/binary_trees/
//I don't think I mentioned this, but so far, 
//nodes are being added inside the BST by a level-order format. 
//In this case, however, nodes will traverse the right and left subtrees and take the count of the nodes. 
//It doesn't matter however, since I'm just looking for the count of the nodes in the tree. 
template <typename T>
int BSTree<T>::Count(Node* root)
{
	Node* head = root; 
	
	if(head == NULL)
	{
		return 0; 
	}
	else
	{
		
		int count = 1; 
		count += Count(root->left); 
		
		count += Count(root->right); 
		return count; 
	}
	
}

//Similar to the explanation above, this will find the total number of words inside the tree, by using the frequency counts of each word. 
template <typename T>
int BSTree<T>::CountTotalWords(Node* root)
{
	
	Node* head = root; 
	
	if(head == NULL)
	{
		return 0; 
	}
	else
	{
		int count = head->dataToAdd.frequency;
		
		count +=  CountTotalWords(root->left);
		
		count +=  CountTotalWords(root->right);
		
		return count; 
		
	}
}

//The swap is a helper function for the sorted array by frequency and by alphabet. 
template <typename T>
void swap(T *x, T *y)
{
	int temp = *x; 
	*x = *y; 
	*y = temp; 
}
//Sorting algorithm in the array we made
//Implementing selection sort algorithm
//This is a very similar implementation to the one found in this link for selection sort.
//https://www.geeksforgeeks.org/selection-sort/
//I found this algorithm helpful to sort the array. 
template <typename T>
void BSTree<T>::SortedArrayByFrequency(T*& retrieveArray)
{
	int min; 
	//T* retrieveArray = nullptr;
	ToArray(retrieveArray);
	int sizeOfArray = Count(head); 
	
	for(int i = 0; i < sizeOfArray-1; i++)
	{
		//Find the minimum element
		//in an unsorted array 
		min = i; 
		for(int j = i+1; j < sizeOfArray; j++)
		{
			if(retrieveArray[j].frequency < retrieveArray[min].frequency)
			{
				min = j; 
			}
		}
		//Swap the minimum element 
				//with the first element
		if(min != i)
		{
			std::swap(retrieveArray[min], retrieveArray[i]);
		}
	}

}
//This sorts the array by alphabet with the selection sort algorithm. 
template <typename T> 
void BSTree<T>::SortedArrayByAlphabet(T*& retrieveArray)
{
	int min; 
	ToArray(retrieveArray); 
	
	int sizeOfArray = Count(head); 
	
	
	
	for(int i = 0; i < sizeOfArray-1; i++)
	{
		min = i; 
		for(int j = i+1; j < sizeOfArray; j++)
		{
			if(retrieveArray[j].word < retrieveArray[min].word)
			{
				min = j; 
			}
		}
		
		if(min != i)
		{
			std::swap(retrieveArray[min], retrieveArray[i]); 
		}
	}
}

//This finds the top five lowest used words in the entire txt file. 
//Basically, we are just calling the array we made from toArray(), 
//and looping through that only 5 times to retrieve the first 5 least used words. 
template <typename T> 
void BSTree<T>::topFiveLowest(T*& arr)
{
	const int LENGTH = 5;
	T* sortedarr = nullptr;
	
	SortedArrayByFrequency(sortedarr); 
	
	arr = new T[LENGTH];
	
	int index = 0; 
	for(int i = 0; i < LENGTH; i++)
	{
		arr[index] = sortedarr[i];
		index++; 
	}

}

//This finds the top five highest used words in the entire txt file. 
//We make a backwards for loop after calling toArray() function 
//and loop 5 times from the end of the array to find the 5 most frequently used words. 
template <typename T>
void BSTree<T>::topFiveHighest(T*& arr)
{
	const int LENGTH = 5;
	T* sortedarr = nullptr;
	
	SortedArrayByFrequency(sortedarr); 
	
	arr = new T[LENGTH];
	
	int startMax = Count(head); 
	int stoppingPoint = startMax - 5; 
	int index = 0;
	for(int i = startMax-1; i >= stoppingPoint; i--)
	{
		arr[index] = sortedarr[i];
		index++;
	}
	
}