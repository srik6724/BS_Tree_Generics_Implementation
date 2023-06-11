#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "Balasubramanian_bst.hpp"
#include <cstring>

using namespace std;
int main(int argc, char** argv) 
{
	
	//Parse a sample.txt file.
	//Identify every word inside this file.
	//This is the sampleText.txt file that I tested
	//It is very similar to the one used for Assignment 3. 
	//The name of this file was called alice.txt originally. 
	
	std::ifstream inFile; 
	std::string word; 
	inFile.open("sampleText.txt");
	//If the file happens to fail, then it will print this message out. 
	if(inFile.fail()) 
	{
		std::cout << "There is an error opening the listed file." << std::endl; 
	}
	
	//Node* retrieveHead is of type Node and points to null 
	//to show that the bst is basically empty. 
	int iteration = 1; 
	Node* retrieveHead = nullptr; 
	string check_word = ""; 
	//BSTree<WordEntry> object is created of type WordEntry, since
	//each node in the BST will contain frequency and word property. 
	BSTree<WordEntry> myBst; 
	//Checks every word inside sampleText.txt 
	//inFile >> word takes in every word and ignores the white space. 
	while(inFile >> word) 
	{
		//Word was printed below to check if it has been processed. 
		//Line will be commented out for now however. 
		//std::cout << word << std::endl; 
		int lengthOfWord = word.length(); 
		std::string str = word; 
		
		std::string check_word = ""; 
		//Basically, what's been doing here is this. 
		//We collect each word from the file. 
		//Then, we are looping through word's characters. 
		//Each character goes through a check to see whether it is a letter. 
		//If it is a letter, then what we want do here is make that character lowercase. 
		//This will help, so that any word that comes through will basically be lowercase. 
		//There are two cases that were tested, if it didn't happen to be a letter. 
		//These included the apostrophe, because ex. don't would count as word. 
		//Another case included the '-' as a compound word can be formed using this. 
		//So, ideally, we would want to treat these as separate words. 
		//For the apostrophe condition, it will then be added as part of the word. 
		//However, for the '-', we want to ignore the dash so, we will just append empty string. 
		//But, this means that we want to immediately append what's already been added to check_word. 
		//So, then the word is added inside the BST for that condition. 
		//Other than this, usually if the character is not a letter, we just ignore and move on. 
		for(int i = 0; i < lengthOfWord; i++)
		{
			//Check if current character is not a letter
			int result = isalpha(str[i]); 
			if(result != 0)
			{
				check_word += tolower(str[i]);
			}
			else
			{
				//Consider what to do when it's not a letter: 
				//Special characters: #, $, %, etc. 
				//Numbers: 0,1,2,3,4,5,6,7,8,9
				//Following below is the only edge case we have to consider to form a word.
				//This includes the apostrophe.
				if(str[i] == '\'')
				{
					check_word += tolower(str[i]); 
				}
				else if(str[i] == '-')
				{
					check_word += ' '; 
					std::cout << "Placing string inside tree: " << check_word << std::endl; 
					WordEntry obj{ check_word, 1 };
					if(iteration == 1)
					{
						retrieveHead = myBst.Insert(obj);
						iteration = 0; 
					}
					else
					{
						myBst.Insert(obj); 
					}
					check_word = ""; 
				}
				else
				{
					continue; 
				}
				
	
			}
		}
		//If there are no errors with any of the characters for that specific word, 
		//then the word will basically be processed. 
		//The message is printed Placing string into tree with the string shown. 
		//One thing to note, the iteration == 1 condition. 
		//I found this important because this is the first word to be inputted inside BST. 
		//So, that's why it's set equal to the retrieveHead node. 
		if(check_word.size() != 0) 
		{
			std::cout << "Placing string inside tree: " << check_word << std::endl; 
			WordEntry obj{ check_word, 1 };
			if(iteration == 1)
			{
				retrieveHead = myBst.Insert(obj);
				iteration = 0; 
			}
			else
			{
				myBst.Insert(obj); 
			}
			check_word = ""; 
			//check_word is empty as new word is going to be appended and processed once again. 
		}
	}

	
	//Here is the outfile where all the information asked for is stored inside "finalresult.txt"
	ofstream outfile; 
	outfile.open("finalresult.txt"); 
	//The following variables countOfUniqueWords and CountTotalWords store the 
	//count of total and unique words in the file we are reading. 
	int countOfUniqueWords = myBst.Count(retrieveHead); 
	int countTotalWords = myBst.CountTotalWords(retrieveHead); 
	
	//Messages to print on the console and inside outfile for total/unique words. 
	std::cout << "The count of total words is " << countTotalWords << std::endl;
	outfile << "The count of total words is " << countTotalWords << std::endl;
	std::cout << "The count of unique words is " << countOfUniqueWords << std::endl; 
	outfile << "The count of unique words is " << countOfUniqueWords << std::endl; 
	
	//The WordEntry pointer object is null 
	//because it will eventually point to memory that we want. 
	WordEntry* array = nullptr;
	//the myBST object of type WordEntry
	//calculates the topFiveHighest frequently most used words
	//and it will add them inside the array. 
	myBst.topFiveHighest(array);
	
	//The for loop will print the 5 frequently most used words 
	//in the outfile and to the console. 
	for(int i = 0; i < 5; i++)
	{
		std::cout << "Highest # word " << array[i].word << std::endl;
		outfile << "Highest # word freq " << array[i].word << "," << array[i].frequency << std::endl;
	}
	
	//We have another array created to serve the same purpose similar as above. 
	//Instead, it will print the 5 least frequently most used words 
	//in the outfile and to the console. 
	WordEntry* array2 = nullptr;
	myBst.topFiveLowest(array2);
	for(int j = 0; j < 5; j++)
	{
		std::cout << "Lowest # word " << array2[j].word << std::endl;
		outfile << "Lowest # word freq " << array2[j].word <<  "," << array2[j].frequency << std::endl;
	}
	
	//To ask the user to input a word of their choosing
	//The below while loop is for the user to select a word that they want to choose. 
	//Due to time restrictions currently, if the user doesn't input the correct word, a segmentation fault will occur. 
	//Therefore, beware of that, and for now just input the correct word you are looking for. 
	//If segmentation fault occurs, restart program with control C. 
	bool isUserDone = false; 
	
	while(!isUserDone)
	{
		string selectedWord; 
		int startFrequency = 1; 
		std::cout << "Enter a word of your choosing. Frequency count of that word will be displayed after. " << std::endl; 
		std::cin >> selectedWord;

		WordEntry entry{ selectedWord, startFrequency };
		
		
	    //Message to the console and the outfile is printed showing the number of times that the word has occurred in the file. 
		
		if(myBst.Find(entry) != nullptr)
		{
			std::cout << "Your word has been found this many number of times: " << (myBst.Find(entry))->dataToAdd.word << "," << (myBst.Find(entry))->dataToAdd.frequency << std::endl; 
			outfile << "Your word has been found this many number of times: " << (myBst.Find(entry))->dataToAdd.word << "," << (myBst.Find(entry))->dataToAdd.frequency << std::endl; 
		}
		else
		{
			std::cout << "Your word has been found this many number of times: " << selectedWord << "," << "0" << std::endl; 
			outfile << "Your word has been found this many number of times: " << selectedWord << "," << "0" << endl; 
		}
		
		
		bool correctAnswer = false; 
		//This loop serves as a way to just check if the user would like to continue and retry with a new word. 
		//They have to make sure to input YES or NO. Otherwise, the program will ask the same question. 
		while(!correctAnswer)
		{
			string option1 = "YES"; 
			string option2 = "NO"; 
			string response; 
			std::cout << "Would you like to continue to input words? Answer YES or NO" << std::endl; 
			cin >> response; 
			if(response == option1)
			{
				isUserDone = false; 
				correctAnswer = true; 
			}
			else if(response == option2)
			{
				isUserDone = true; 
				correctAnswer = true; 
			}
			else
			{
				correctAnswer = false; 
			}
		}	
	}
	
	bool finalInput = false; 
	
	//Here is the final question that is asked. 
	//This basically asks for the words to be sorted by frequency or by alphabet. 
	//The user must select one option. Otherwise, the same question will be asked once again. 
	
	while(!finalInput)
	{
		string option1 = "frequency"; 
		string option2 = "alphabet"; 
		string response; 
		std::cout << "Would you like for your words to be sorted by frequency or by alphabet. Please write frequency or alphabet?";
		cin >> response; 
		if(response == option1)
		{
			int counter = myBst.Count(retrieveHead); 
	
			WordEntry* sortedArr = nullptr;
			myBst.SortedArrayByFrequency(sortedArr);
			//Message for option 1: 
			//Will print to the outfile that the words have been sorted by frequency from least to greatest. 
			outfile << "Sorting by frequency---------------" << std::endl;
			for(int i = 0; i < counter; i++)
			{
				outfile << sortedArr[i].word << "," << sortedArr[i].frequency << std::endl;
			}
			
			finalInput = true; 
		}
		else if(response == option2)
		{
			int counter = myBst.Count(retrieveHead);  
			WordEntry* sortedArr = nullptr; 
			myBst.SortedArrayByAlphabet(sortedArr); 
			//Message for option 2: 
			//Will print to the outfile that the words have been sorted by alphabet from A-Z lowercase. 
			outfile << "Sorting alphabetically-------------" << std::endl; 
			for(int i = 0; i < counter; i++)
			{
				outfile << sortedArr[i].word << "," << sortedArr[i].frequency << std::endl; 
			}
			
			finalInput = true;  
		}
		else 
		{
			std::cout << "Please select frequency or alphabet and not anything else that does not align with that." << std::endl; 
			finalInput = false; 
		}
	}
	
	delete retrieveHead;
	//the head pointer is deleted, indicating that we want the entire BST to be deleted. 
	
	outfile.close(); 
	//outfile is closed because we are done collecting information we need to store. 
	
	//After main ends, destructor will be called. 
	
	return 0; 
}