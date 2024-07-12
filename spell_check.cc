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
bool oneDiff(const string& s1, const string& s2)
{
  string temp1 = lowercase(removePunctuation(s1));
  string temp2 = lowercase(removePunctuation(s2));

for(int pos1 = 0; pos1 <= temp1.length();pos1++)
{
  for (char c = 'a'; c <= 'z'; c++)
  {
      string word = insertLetter(s1,c,pos1);
      cout << "word is: " << word << "\n";
      if(word == s2)
        return true;
  }
}
cout << "\n\ntime for second function: \n";
for(int pos2 = 0; pos2 <= temp2.length();pos2++)
{
  for (char c = 'a'; c <= 'z'; c++)
  {
      string word = insertLetter(s2,c,pos2);
      cout << "word is: " << word << "\n";
      if(word == s1)
        return true;
  }
}
 return false;
}
//checks case 3, if 2 words are the same and just need to swap adjacent letters to make them match
bool needSwapAdj(const string& s1, const string& s2)
{
  return true;

}
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
int main()
{
  if (oneDiff("cat","cats"))
  {
    cout << "\n\ntrue";
  }
}
// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
// int main(int argc, char** argv) {
//   if (argc != 3) {
//     cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
//          << endl;
//     return 0;
//   }
  
//   testSpellingWrapper(argc, argv);
  
//   return 0;
// }
