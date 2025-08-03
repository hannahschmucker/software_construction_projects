# Software Construction Projects
A series of projects completed for my software construction class.

> [!Note]
> Distribution of class material is prohibited, per the professor's request. Therefore, I won't include any project outlines. Additionally, I'll omit the course code, institution, and name of the professor to prevent any material from being recycled by future students.

### All projects compiled and run as...
```bash
  g++ *filename.cpp*
```
```bash
-  ./a.out
```

## Project 1
* A loan repayment calculator written in C++.

Overview:
This program allows the user to input a loan amount, annual interest rate, and a monthly payment. Additionally, the user will be prompted for a down-payment. The program outputs an amortization table, as well as the total months and interest accumulated before the loan is paid off.

Goal: 
Learn the basics of C++ and practice coding on a remote server. 

## Project 2
* Simulate a three person 'truel' in C++

Overview: 
This program simulates a three person dual. Each person -- Aaron, Charlie, and Bob -- has a predefined shooting accuracy, which is compared to a randomly generated number. Charlie has a 100% accuracy, therefore will never miss. Additionally, each person uses the strategy of shooting whomever is the 'most lethal', i.e. whichever person has the highest accuracy (and is still alive, obviously). The three alternate turns in the order *Aaron, Bob, and Charlie* until there is only one person left alive. Two strategies are tested *(these only impact the first round)*:
    * Strategy1: Aaron shoots normally on the first round, shooting at the most lethal player.
    * Strategy2: Aaron intentionally misses on the first round. This ensures that if Bob misses Charlie on his turn, Charlie will eliminate Bob.
The program outputs the unit testing cases. Additionally, it simulates the results of strategies 1 and 2, with the percentages of how often each player one. Finally, it outputs the strategy which was more advantagous for Aaron.

Goal:
Use test drivers, randomized numbers, the assert() function, and function prototypes.

## Project 3
* Read in file data and output statistics in C++.

Overview:
This program first takes as input the number of files to be read. Then it prompts the user for the file name (a .txt file) and outputs the data, for each file. Files must contain doubles, negative or positive, written with each number on a newline (no commas or punctuation). If the file contains malformed data, the program will prompt the user again. If the file does not exist or cannot be found, the user will be prompted again. At the end, it produces a sorted list of the numbers, as well as the mean, median, and mode.
>[!Note]
> For further information on how to enter the file names, see the head of the *project3.cpp* file

Goal:
Use input/output streams, read from a file, detect illegal inputs (from files), and organize data.

## Project 4
* Manage multiple project versions with git branching and write to a file.

Overview: 
This program reuses the code from project 3. It has the added feature of writing to a .csv file, which it confirms with a statement output at the end of the file.

Goal:
Use git to initialize a repo, make commits, branch and merge from/to the master branch. 
