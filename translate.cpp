// Nicholas DiPinto and Robert Velarde
// CS 332 Final Project Proof of Concept
// Language Translator Program

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

#define A 65			// ASCII code for 'A'
#define Z 90			// ASCII code for 'Z'
#define a 97			// ASCII code for 'a'
#define z 122			// ASCII code for 'z'
#define LOWERCASE 32	// ASCII conversion for uppercase to lowercase

void translateWord(string &word);
void onlyAlphabetical(string &input);
void toLowercase(string &input);
void formatString(string &input);

int main()
{
	ofstream output("output.txt");	// File to hold translated sentence
	string input, line;

	cout << "Enter an English sentence: ";
	getline(cin, input);
	output << "English: " << input << endl;
	formatString(input);
	output << "Formatted: " << input << endl << "Spanish: ";
	istringstream iss(input);	// Splits sentence into seperate words
	string word;				// Used to hold an individual word
	while(iss >> word)			//Loop through each word in the sentence
	{
		translateWord(word);
		output << word << " ";
		cout << word << " ";
	}
	output.close();
}

void translateWord(string &word) {
	ifstream dictionary("translation.txt");		// English to Spanish text file
	char delimeter = ':';
	string line, english_token, spanish_token;

	while(getline(dictionary, line)) {
		english_token = line.substr(0, line.find(delimeter));
		spanish_token = line.substr(line.find(delimeter) + 1, line.find("\n"));
		if(word.compare(english_token) == 0) {	// Word is found in dictionary
			dictionary.close();
			word = spanish_token;	// Replace with the Spanish translation
			break;
		}
	}

}

void formatString(string &input) {
	onlyAlphabetical(input);
	toLowercase(input);
}

void onlyAlphabetical(string &input) {
	for(string::size_type i = 0; i < input.size(); i++) {	// Iterate each char
		if ( !(((input[i] >= A) && (input[i] <= Z)) ||		// Uppercase check
			   ((input[i] >= a) && (input[i] <= z)))) {		// Lowercase check
			input[i] = ' ';					// Replace character with a space
		}
	}
}

void toLowercase(string &input) {
	for(string::size_type i = 0; i < input.size(); i++) {	// Iterate each char
		if ((input[i] >= A) && (input[i] <= Z)) {		// Uppercase check
			input[i] += LOWERCASE;						// Convert to lowercase
		}
	}}
