// Nicholas DiPinto and Robert Velarde
// CS 332 Final Project Proof of Concept
// Language Translator Program

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
	ifstream spanish_file;
	string input, line, english_token, spanish_token;
	
	spanish_file.open("spanish.txt");
	cout << "Please enter an english sentence: ";
	getline(cin, input);
	istringstream iss(input);	//used to split user input into separate words
	string word;			//string that represents individual words in user input
	while(iss >> word)		//keep looping until you reach the end of a user's sentence
	{
		while(getline(spanish_file, line))
		{
			english_token = line.substr(0, line.find(":"));
			spanish_token = line.substr(line.find(":") + 1, line.find("\n"));
			if(word.compare(english_token) == 0)
				cout << spanish_token << " ";
		}
		spanish_file.clear();
		spanish_file.seekg(0, ios::beg);
	}
	cout << endl;
	spanish_file.close();
}
