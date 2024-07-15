# Assignment-2-Code
Rachel Briskman

For this assignment, I started by modifying quadratic_probing.h
I added several private variables, and getters for those variables.
elementsCount, probes and collisionsCounter are the private variables.

I also got rid of the namespace, making the isPrime() and nextPrime() functions jut public member functions of quadratic_probing.h, linear_probing.h and double_hashing.h
The namespace worked fine at first, but then as I worked on linear and double hashing it started giving me errors. 

After finishing quadratic, I copy and pasted that code into linear and double_hashing.h. I then modified findPos().
Linear's findPos() is exactly the same as quadratic, except offset is always 1. (In quadratic it's 1,3,5,7,9... odd numbers)

Double Hashing code is more different.
I created a private int variable called rvalue (default value 89).
A function called setR(int input), that only sets R to input if input is a prime number less than array size (101), and setR has not been called before (hence the bool rAlreadySet). If input is valid then it also calls the rehash function.
int getR() which returns rvalue;
A bool rAlreadySet (default value is false)

I also overloaded the paramatized constructor to take in an Rvalue.

In all of the probing files, findPos() increments both the probes and collisionsCounter variables. Since I did it that way, findPos() could no longer be a const function. Not ideal, but it works. Also, since FindPos() is not const anymore, functions that call findPos() can't be const either. So Contains() isn't const anymore either, even though it's code is unchanged.

I don't know why, but when I tested my code for all the different probes the number of elements for double_hashing is different than linear and quadratic's? I tested all my code in both Ubuntu WSL (Win 10) and with docker.

For spell_check.cc, I encountered more issues than I thought I would.
First I implemented MakeDictionary() which filled the param dictionary with the words from the param file.

I made several helper functions:

lowercase(const string& s) which returns the param string in all lowercase form (not modifying the param, but returning a copy).
removePunctuation(const string& s), also returns a copy of param, just without punctuation.

removeLetter(string s, int pos) returns a copy of string s after removing letter at index pos
insertLetter(string s,char c, int pos) returns a copy of string s, after inserting char c at index pos

minusOneLetter() and plusOneLetter() remove and add 1 letter at each position (using the 2 helper functions above), respectively. If any of those resulting words are contained in the table, they get put into a vector. (Both functions return a vector of strings).

In the spellcheck() function, if the word from the file is not contained in the table, I then move to check each of the vectors created by the helper functions and print the appropriate spellcheck case. 
printChecks() takes in the string vector and prints "word is incorrect\n" and then what the proper spelling should be for each word in the vector.

There's also swapAdj(string s, int pos) which swaps the letters at pos and (pos+1).
needSwapAdj() returns a vector of properly spelled words (similar to minus/plusOneLetter())

Unfortunately, when I tried to run the code using make or the g++ command below, the output would be really wonky.
A few times I kept getting either floating point exception or segmentation fault. I think I fixed that a little somehow? Right now I think spellcheck works slightly but it's really slow. (Weird, since hashmaps are O(1))
g++ -std=c++20 spell_check.cc -o spell_check
./spell_check words.txt query_words.txt
10th is CORRECT
1st is INCORRECT
2nd is INCORRECT
3rd is INCORRECT

is the immediate output I'd get. However, if I kept it running, it would keep printing more stuff.

eventually it would also print this in the terminal:
4th is INCORRECT
5th is INCORRECT
6th is INCORRECT
7th is INCORRECT
8th is INCORRECT
9th is INCORRECT
a is INCORRECT
Segmentation fault

(this is Docker)

I tried my best with this project, but at first I had a hard time understanding the provided code for quadratic_probing, (even though I understood our in class lectures.)
My spell_check is probably not the most efficient, but I did it in a way that made sense to me. Hopefully you can see what I was going for. I decided to split it up into multiple helper() to make the code look less confusing.
I don't think I ever went out of bound when accessing string indices, so I have no idea what went wrong with this code.