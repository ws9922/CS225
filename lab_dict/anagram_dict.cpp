/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            vector<std::pair<char, int>> key = word_to_key(word);
            (key_map_anagram[key]).push_back(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(string word : words){
        vector<std::pair<char, int>> key = word_to_key(word);
        (key_map_anagram[key]).push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    std::vector<std::pair<char, int>> key = word_to_key(word);
    auto lookUp = key_map_anagram.find(key);
    if(lookUp == key_map_anagram.end() || (lookUp->second).size() == 1)
        return vector<string>();
    return lookUp->second;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> result;
    for(std::pair<std::vector<std::pair<char, int>>, std::vector<std::string>> key_anagram : key_map_anagram){
        if(key_anagram.second.size() > 1){
            result.push_back(key_anagram.second);
        }
    }
    return result;
}

vector<std::pair<char, int>> AnagramDict::word_to_key(std::string word) const{
    std::map<char, int> char_map_int;
    vector<std::pair<char, int>> result;
    for(char c : word){
        if(char_map_int.find(c) == char_map_int.end()){
            char_map_int[c] = 1;
        }else{
            char_map_int[c]++;
        } 
    }
    for(std::pair<const char, int>& char_frequency : char_map_int){
        result.push_back(char_frequency);
    }
    return result;
}