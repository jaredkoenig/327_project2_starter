/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 23, 2019
 *      Author: Jared Koenig
 */
 
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>

#include "utilities.h"
using namespace std;

struct word_analyzer {
	string word;
	int count;
};


int compareChar(char & c1, char & c2) {
	if (c1 == c2) {
		return 0;
	}
	else if (std::toupper(c1) == std::toupper(c2)) {
		return 0;
	}
	else if (std::toupper(c1) < std::toupper(c2)) {
		return -1;
	}
	else if (std::toupper(c1) > std::toupper(c2)) {
		return 1;
	}
	return false;
}
 

int caseInSensitiveStringCompare(string  str1, string str2) {
	for(int i = 0; i < str1.length() && i < str2.length() ; i++) {
		if(std::toupper(str1.at(i)) == std::toupper(str2.at(i))) {
			continue;
		}
		else if(std::toupper(str1.at(i)) < std::toupper(str2.at(i))) {
			return -1;
		}
		else if(std::toupper(str1.at(i)) > std::toupper(str2.at(i))) {
			return 1;
		}
	}
	if(str1.length() > str2.length()) {
		return 1;
	}
	else if(str1.length() < str2.length()) {
		return -1;
	}
	else {
		return 0;
	}
}

int main () {
	word_analyzer w;
	int wordcount = 0;
	int count = 0;
	string line;
	
	ifstream myfile;
	myfile.open("test.txt");
	if (myfile.is_open())
	{
    	while ( getline (myfile,line) )
    	{
      		int whitespace = 0;
      		while ((whitespace = line.find(" ", whitespace)) != string::npos ) 
    		{
    			wordcount++;
        		line.erase(0, whitespace+1);
        		
				whitespace=0;
			}
    	}
    }
    myfile.close();
    myfile.open("test.txt");
	word_analyzer words[wordcount];
	word_analyzer combined_words[wordcount];
	if (myfile.is_open())
	{
    	while ( getline (myfile,line) )
    	{
      		int whitespace = 0;
      		while ((whitespace = line.find(" ", whitespace)) != string::npos ) 
    		{
    			w.word = line.substr(0, whitespace+1);
    			w.count = 1;
				strip_unwanted_chars(w.word);
				
				bool added = false;
    			for(int i = 0; i < count; i++)
    			{
					if(!w.word.empty() && words[i].word.compare(w.word) == 0)
					{
						words[i].count += 1;
						added = true;
						break;
					}
				}
				
				if(!added) {
					if(!w.word.empty()) {
						words[count].word = w.word;
						words[count].count = 1;
						count++;
					}
				}
        		line.erase(0, whitespace+1);
        		
				whitespace=0;
    		}
    		if(!line.empty())
    		{
    			w.word = line.substr(0);
    			w.count = 1;
    			strip_unwanted_chars(w.word);
    			
				bool added = false;
    			for(int i = 0; i < count; i++)
    			{
					if(!w.word.empty() && words[i].word.compare(w.word) == 0)
					{
						words[i].count += 1;
						added = true;
						break;
					}
				}
				
				if(!added) {
					if(!w.word.empty()) {
						words[count].word = w.word;
						words[count].count = 1;
						count++;
					}
				}
			}
	   	}
   		myfile.close();
	}
	
	bool not_sorted = true;
	for(int i = 0; i < count; i++) {
		for(int j = i+1; j < count; j++) {
			if(caseInSensitiveStringCompare(words[i].word, words[j].word) > 0) {
				word_analyzer store = words[i];
				words[i] = words[j];
				words[j] = store;
			}
		}
	}
	
	ofstream outputFile("out.txt");
	if(outputFile.is_open())
	{
		for(int i = 0; i < count; i++)
		{
			cout << words[i].word << " " << words[i].count << endl;
			outputFile << words[i].word << " " << words[i].count << endl;
		}
		outputFile.close();
	}
	return 0;
}

void toUpper(string &myString) {
	std::transform(myString.begin(), myString.end(), myString.begin(),
			::toupper);
}

string intToString(int Number) {
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

void strip_char(string &s, char badchar){
	const int NUMBER_CHARS_TO_ERASE = 1;
	if (s.empty())
		return;

	std::size_t found = s.find(badchar);
	if (found!=std::string::npos)
		s.erase(found,NUMBER_CHARS_TO_ERASE);
}

bool strip_unwanted_chars(string &mystring) {
	strip_char(mystring,'\r');
	strip_char(mystring,'.');
	strip_char(mystring,' ');
	strip_char(mystring,',');
	return (mystring.length()>0);
}
