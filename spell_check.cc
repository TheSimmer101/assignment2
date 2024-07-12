// YOUR NAME.
// spell_check.cc: A simple spell checker.

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

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
        exit(1); // exit if failed to open the file
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

bool oneDifference(const string& one, const string& two)
{
  string temp1 = lowercase(removePunctuation(one));
  string temp2 = lowercase(removePunctuation(two));

  //sorts in alphabetical order for easier comparison
  sort(temp1.begin(), temp1.end());
  sort(temp2.begin(), temp2.end());

  int lengthDiff = temp1.length() - temp2.length();
  //difference in length should be 1 if we want to recommend possible properly spelled words.
  //taking absolute value of word1 - word2 lengths because we don't know what word is longer (no need to check with this)
  if(abs(lengthDiff) != 1)
    return false;

  //craft
  //brave
  //
    int countDiff = 0;

    //for example, if we compare these 2 words:
    //cat  -> act   (after sorting & remove punctuation)
    //bats -> abst

    int index = 0;

    // while(index < temp1.length() && index < temp2.length())
    // {

    // }
    return true;
}
//checks case 3, if 2 words are the same and just need to swap adjacent letters to make them match
bool needSwapAdj(const string& s1, const string& s2)
{
  //laws -> alsw
  //lwas -> alsw
  string temp1 = lowercase(removePunctuation(s1));
  string temp2 = lowercase(removePunctuation(s2));

  //sorts in alphabetical order for easier comparison
  sort(temp1.begin(), temp1.end());
  sort(temp2.begin(), temp2.end());

  return (temp1 == temp2);
}
//three cases of misspellings:
// a) Adding one character in any possible position
// b) Removing one character from the word
// c) Swapping adjacent characters in the word 


// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) 
{

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
