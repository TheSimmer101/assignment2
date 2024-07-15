// YOUR NAME.
// spell_check.cc: A simple spell checker.

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  // Fill dictionary_hash.
  ifstream words(dictionary_file);
    if (words.fail()) {
        cerr << "ERROR" << endl;
        return dictionary_hash; // exit if failed to open the file
    }
    //words is each line.
    //singleword extracts each word from each line.
    string singleWord;
    while(words >> singleWord)
    {
        dictionary_hash.Insert(singleWord);
    }
  return dictionary_hash;
}

//returns a string that is the param but all lowercase
string lowercase(const string& word)
{
  string result = word;
  for(int i = 0; i < result.length(); i++)
    result[i] = tolower(result[i]);

  return result;
}

string removePunctuation(const string& s) 
{
  string result = "";

  for(auto letter: s)
  {
    if(isalpha(letter))
      result+=letter;
  }
  return result;
}
//returns param string with every letter except the letter at param position
string removeLetter(const string str, int position)
{
  string result = "";
    for(int i = 0; i <= str.length(); i++)
      {
        if(i != position)
          result += str[position];
      }

      return result;
}
//insert param letter in str at param position
string insertLetter(const string& str, char letter, int position)
{
  string result = "";
  for(int i = 0; i <= str.length(); i++)
  {
    if(i == position)
      result += letter;
    result+= str[i];
    
    // if(position == str.length())
    //     result+=letter;

  }
  return result;
}

//adds 1 letter at every possible position and adds it to result vector if string+letter exists in table.
//example: ant becomes-> cant,pant,want,aint,ants,anti, etc.
//if those are actual words that exist in table, we add it to the vector (which is returned later)
vector<string> plusOneLetter(const string& s1, HashTableDouble<string> table)
{
  string temp1 = lowercase(removePunctuation(s1));
  vector<string> matchingWords = {};
  for(int pos1 = 0; pos1 <= temp1.length();pos1++)
  {
    for (char c = 'a'; c <= 'z'; c++)
    {
        string word = insertLetter(s1,c,pos1);
        //cout << "word is: " << word << "\n";
        if(table.Contains(word))
          matchingWords.push_back(word);
    }
  }
  return matchingWords;
}

//same idea as plusOneLetter() except it removes one letter at each possible position at a time.
//if word minus letter exists in table, add to result vector.
vector<string> minusOneLetter(const string& s1, HashTableDouble<string> table)
{
  string temp1 = lowercase(removePunctuation(s1));
  vector<string> matchingWords = {};
  for(int pos1 = 0; pos1 < temp1.length();pos1++)
  {
       
        string word = removeLetter(s1,pos1);
        //cout << "word is: " << word << "\n";
        if(table.Contains(word))
          matchingWords.push_back(word);
  }
  
  return matchingWords;
}
//swaps letters at pos and (pos+1)
//max value of pos must be str.length()-2
string swapAdj(const string& str,int pos)
{
  string temp = lowercase(removePunctuation(str));
  if(pos < 0 || pos > str.length()-2)
    return "";

  string result;

  for(int i = 0; i<temp.length()-2;i++)
  {
    if(i == pos)
    {
      result+=temp[pos+1];
    }
    else if(i == (pos+1))
      result+=temp[pos];
    else
      result+=temp[i];
  }
  return result;
}
//checks case 3, if 2 words are the same and just need to swap adjacent letters to make them match
vector<string> needSwapAdj(const string& s1, HashTableDouble<string> table)
{
  string temp1 = lowercase(removePunctuation(s1));

vector<string> matches = {};
 
  for(int i = 0; i <=temp1.length()-2;i++)
  {
    string swapped = swapAdj(temp1,i);
    if(table.Contains(swapped))
      matches.push_back(swapped);
  }
  return matches;

}

//takes in vector of strings 
void printChecks(string str, vector<string> matches, char caseType)
{
  cout << str << " is INCORRECT\n";

  for(string m: matches)
  {
    cout << m;
    //cout << "**" << str << "-> " << m << "** case " << toupper(caseType) << "\n";
  }

}
// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections

//removed const from dictionary parameter (Contains() is not a const function because I had to make findPos() a non-const function)
//I needed Contains() to check for spelling.
void SpellChecker(HashTableDouble<string>& dictionary, const string &document_file) 
{
  //cout << "hello world\n";
//Cases:
// a) Adding one character in any possible position
// b) Removing one character from the word
// c) Swapping adjacent characters in the word 
//ifstream code copied from 135 Lab 3 Instructions (Fall 2023)
  ifstream doc(document_file);
  if (doc.fail()) {
          cerr << "ERROR" << endl;
          exit(1); // exit if failed to open the file
      }
    string wordInput = "";
    while(doc >> wordInput)
    {
        if(dictionary.Contains(wordInput))
        {
          cout << wordInput << " is CORRECT\n";
        }
        else
        {
          cout << wordInput << " is INCORRECT\n";

          if(!plusOneLetter(wordInput,dictionary).empty())
          {
            printChecks(wordInput,plusOneLetter(wordInput,dictionary),'A');
          }
          else if (!minusOneLetter(wordInput,dictionary).empty())
            printChecks(wordInput,minusOneLetter(wordInput,dictionary),'B');
          else if(!needSwapAdj(wordInput,dictionary).empty())
            printChecks(wordInput,needSwapAdj(wordInput,dictionary),'C');
        }
    }

}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
