#include <iostream>

#include "lphashtable.h"
#include "schashtable.h"
#include "dhhashtable.h"
#include "textfile.h"
#include <vector>
#include <string>
using namespace std;
int main()
{
    std::cout << "This main file is for you to write and run your own test cases." << std::endl;
    std::cout << "To run the provided test cases, run `./test`" << std::endl;
    // feel free to insert manual test cases here
    vector<string> strings;
	for(int i = 'a'; i <= 'z'; i++) {
		string word = "";
		word += ((char)i);
		strings.push_back(word);
	}
    //cout << strings.size() << endl;
	SCHashTable<string, int> hashTable(3);
	int val = 0;
	for(unsigned int i = 0; i < strings.size(); i++) {
		val++;
		hashTable.insert(strings[i], val);
	}

    return 0;
}
