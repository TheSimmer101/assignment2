// YOUR NAME.
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
// Uncomment when you implemented linear probing & double hashing
// #include "linear_probing.h"
//#include "double_hashing.h"

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
using namespace std;


vector<string> createVector(string file)
{
   
    //ifstream code copied from 135 Lab 3 Instructions (Fall 2023)
    vector<string> result = {};
    ifstream words(file);
    if (words.fail()) {
        cerr << "ERROR" << endl;
        exit(1); // exit if failed to open the file
    }
    string wordInput = "";
    while(words >> wordInput)
    {
        result.push_back(wordInput);
    }
    return result;
}
// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table

/*
Expected Output:
number_of_elements: <int>
size_of_table: <int>
load_factor: <float>
collisions: <int>
avg_collisions: <float>
<word1> Found <probes1>
<word2> Not_Found <probes2>
<word3> Found <probes3>
*/
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename,const string &query_filename) 
{
   // hash_table.MakeEmpty();
    
    vector<string> words = createVector(words_filename);
    //cout << words[0];
    vector<string> queries = createVector(query_filename);
    int countElements = 0;
    for(string s: words)
      hash_table.Insert(s);
    
        // number_of_elements: <int>
        // size_of_table: <int>
        // load_factor: <float>
        // collisions: <int>
        // avg_collisions: <float>
        cout << "number_of_elements: " << hash_table.totalElements();
        cout << "\nsize_of_table: " << hash_table.currentSize();
        cout << "\nload_factor: " << (float)(hash_table.totalElements())/hash_table.currentSize();
        cout << "\ncollisions: " << hash_table.totalCollisions();
        cout << "\navg_collisions: " << (float)hash_table.totalCollisions()/hash_table.totalElements();
        cout << "\n\n";
    
    for(string q: queries)
    {
        string found = " Found ";
        if(hash_table.Contains(q) == false)
            found = " Not_Found ";
        cout << q << found << hash_table.totalProbes(q) << "\n";
    }

}


// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename,
      			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
       // Uncomment below when you have implemented double hashing.
	HashTableDouble<string> double_probing_table;
    double_probing_table.setR(R);
	TestFunctionForHashTable(double_probing_table, words_filename,
				 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
