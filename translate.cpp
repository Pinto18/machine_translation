// Nicholas DiPinto and Robert Velarde
// CS 332 Final Project Proof of Concept
// Language Translator Program

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

#define A 65			// ASCII code for 'A'
#define Z 90			// ASCII code for 'Z'
#define a 97			// ASCII code for 'a'
#define z 122			// ASCII code for 'z'
#define LOWERCASE 32		// ASCII conversion for uppercase to lowercase

clock_t mathStart;
float mathTime = 0;
clock_t stringStart;
double stringTime = 0;
clock_t fileStart;
double fileTime = 0;

void translateWord(string &word);
void formatString(string &input);
float translationLikelihood(string english, string spanish);

int main() {
	ofstream output("output.txt");	// File to hold translated sentence
	string input, line, translated;
	float likelihood;

	cout << "Enter a sentence in English: ";
	getline(cin, input);
	output << endl << "English: " << input << endl;
	stringStart = clock();
	formatString(input);
	stringTime += (clock() - stringStart) / (double) CLOCKS_PER_SEC;
	output << "Formatted: " << input << endl << "Spanish: ";
	istringstream iss(input);	// Splits sentence into seperate words
	string word;				// Used to hold an individual word
	fileStart = clock();
	while(iss >> word) {			//Loop through each word in the sentence
		translateWord(word);
		output << word << " ";
		translated += word;
		translated += " ";
	}
	fileTime += (clock() - fileStart) / (double) CLOCKS_PER_SEC;
	istringstream spanishSent(translated);
	mathStart = clock();
	likelihood = translationLikelihood(input, translated);
	mathTime = (clock() - mathStart) / (float) CLOCKS_PER_SEC;
	output << endl << "Likelihood: " << likelihood*100 << "%";
	output << endl << "Math Time: " << mathTime << " seconds";
	output << endl << "String Time: " << stringTime << " seconds";
	output << endl << "File Time: " << fileTime << " seconds";
	output.close();
	cout << "Saved to 'output.txt'";
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
	for(string::size_type i = 0; i < input.size(); i++) {	// Iterate each char
		if ((input[i] >= A) && (input[i] <= Z)) {		// Uppercase check
			input[i] += LOWERCASE;						// Convert to lowercase
		} else if (!((input[i] >= a) && (input[i] <= z))) { // Lowercase check
			input[i] = ' ';					// Replace character with a space
		}
	}
}

float translationLikelihood(string english, string spanish) {
	ifstream englishCorpusFile("english_corpus.txt");
	string englishCorpus;
	formatString(englishCorpus);
	istringstream englishCorpusSentence;
	istringstream englishSentence(english);
	string englishSentenceWord;
	string prevEnglishSentenceWord = "";
	string englishCorpusWord;
	string prevEnglishenglishCorpusWord = "";

	int wordPairOccurence;
	int wordOccurence;
	float englishBigramProbability = 1;

	//english bigram
	while (getline(englishCorpusFile, englishCorpus)) {
		formatString(englishCorpus);
		englishCorpusSentence.str(englishCorpus);

		while (englishSentence >> englishSentenceWord) {
			wordPairOccurence = 0; //resetting value for new word
			wordOccurence = 0; //resetting value for new word
			while (englishCorpusSentence >> englishCorpusWord){
				//examining the number of times a word in the inputted sentence appears in the english corpus
				if(englishCorpusWord == englishSentenceWord) {
					wordOccurence++;
					if(prevEnglishenglishCorpusWord == prevEnglishSentenceWord) {
						wordPairOccurence++;
					}
				}

				prevEnglishenglishCorpusWord = englishCorpusWord;
			}

			prevEnglishSentenceWord = englishSentenceWord;
			prevEnglishenglishCorpusWord = "";
			englishCorpusSentence.clear();
			if (wordOccurence != 0) {
				englishBigramProbability *= ((float)wordPairOccurence/(float)wordOccurence);
			}
		}

		prevEnglishSentenceWord = "";
		englishSentence.str(english);
		englishSentence.clear();
	}


	ifstream spanishCorpusFile("spanish_corpus.txt");
	string spanishCorpus;
	getline(spanishCorpusFile, spanishCorpus);
	formatString(spanishCorpus);
	istringstream spanishCorpusSentence(spanishCorpus);
	istringstream spanishSentence(spanish);
	string spanishSentenceWord;
	string spanishCorpusWord;

	int samePositionOccurence;
	int sameWordOccurence;
	float distortionProbability = 1.0;


  	while(getline(spanishCorpusFile, spanishCorpus)){
  		formatString(spanishCorpus);
		spanishCorpusSentence.str(spanishCorpus);

 		samePositionOccurence = 0;
  		sameWordOccurence = 0;

		while ((spanishCorpusSentence >> spanishCorpusWord) && (spanishSentence >> spanishSentenceWord)) {
			if(spanishCorpusWord == spanishSentenceWord) {
				samePositionOccurence++;
			}
		}

		spanishCorpus.clear();
		spanishSentence.clear();

		while(spanishSentence >> spanishSentenceWord) {
			while(spanishCorpusSentence >> spanishCorpusWord) {
				if(spanishSentenceWord == spanishCorpusWord) {
					sameWordOccurence++;
				}
			}
		}

		spanishSentence.clear();
		spanishCorpusSentence.clear();

		if(sameWordOccurence != 0) {
			distortionProbability *= (samePositionOccurence / sameWordOccurence);
		}
	}


	return distortionProbability * englishBigramProbability;  //return
}
