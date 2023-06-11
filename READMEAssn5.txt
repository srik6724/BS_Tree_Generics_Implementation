
Instructions for Running Program: 

exe: wordEntry -o 
	g++ -g -Wall Balasubramanian_Srikar_assn5.cpp -o wordEntry.exe 

To run wordEntry.exe 
	./wordEntry.exe

clean: exe
	rm exe *.o 

Note: Please modify sampleText.txt to test with any new text inside the file. 

Final Note: When asking to sort by frequency or by alphabet, the result will be stored in "finalresult.txt".