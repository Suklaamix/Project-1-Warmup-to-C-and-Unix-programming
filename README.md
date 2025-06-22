# Project-1-Warmup-to-C-and-Unix-programming
Project 1: reverse  
Implemented a reverse code that can reverse the users input, a files text, reverse a files text into an output file.  
The program can be invoked in three ways:  
./reverse: Reads the users inputs and returns them after canceling it with ctrl + d  
./reverse input.txt: Reads from a file and outputs the text.  
./reverse input.txt output.txt: Reads from a file and outputs the text into an output file  
For the implementation a linked list was used to store the information, and the program handles the required edge cases such as:  
Too many arguments  
Input/output file being the same  
Failing to open files  
Malloc failures  
