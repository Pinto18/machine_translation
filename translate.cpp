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
#define LOWERCASE 32		// ASCII conversion for uppercase to lowercase

void translateWord(string &word);
void formatString(string &input);
float translationLikelihood(string english, string spanish);

int main() {
    ofstream output("output.txt");	// File to hold translated sentence
    string input, line, test;
    //float likelihood;
    
    cout << "Enter an English sentence: ";
    input = "The boy";
    cout << "English: " << input << endl;
    formatString(input);
    cout << "Formatted: " << input << endl << "Spanish: ";
    istringstream iss(input);	// Splits sentence into seperate words
    string word;				// Used to hold an individual word
    while(iss >> word) {			//Loop through each word in the sentence
        //translateWord(word);
        output << word << " ";
        test += word;
        test += " ";
        cout << word << " ";
    }
    istringstream spanishSent(test);
    cout << translationLikelihood(input, test);
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
    for(string::size_type i = 0; i < input.size(); i++) {	// Iterate each char
        if ((input[i] >= A) && (input[i] <= Z)) {		// Uppercase check
            input[i] += LOWERCASE;						// Convert to lowercase
        } else if (!((input[i] >= a) && (input[i] <= z))) { // Lowercase check
            input[i] = ' ';					// Replace character with a space
        }
    }
}

float translationLikelihood(string english, string spanish) {
    cout << "2";
    
    ifstream englishCorpusFile("english_corpus.txt");
    string englishCorpus;
    getline(englishCorpusFile, englishCorpus);
    formatString(englishCorpus);
    istringstream englishCorpusSentence(englishCorpus);
    istringstream englishSentence(english);
    string englishSentenceWord;
    string prevEnglishSentenceWord = "";
    string englishCorpusWord;
    string prevEnglishenglishCorpusWord = "";
    
    float wordPairOccurence;
    float wordOccurence;
    float englishBigramProbability = 1;
    
    cout << "1";
    
    //english bigram
    while (englishCorpusSentence) {
        while (englishSentence >> englishSentenceWord) {
            wordPairOccurence = 0.0; //resetting value for new word
            wordOccurence = 0.0; //resetting value for new word
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
            englishBigramProbability *= (wordPairOccurence/wordOccurence);
        }
        
        prevEnglishSentenceWord = "";
        getline(englishCorpusFile, englishCorpus);
        englishCorpusSentence.str(englishCorpus);
        englishCorpusSentence.clear();
    }
    
    ifstream spanishCorpusFile("spanish_corpus.txt");
    string spanishCorpus;
    getline(spanishCorpusFile, spanishCorpus);
    formatString(spanishCorpus);
    istringstream spanishCorpusSentence(spanishCorpus);
    istringstream spanishSentence(spanish);
    string spanishSentenceWord;
    string spanishCorpusWord;
    
    float samePositionOccurence;
    float sameWordOccurence;
    float distortionProbability = 1.0;
    
    
    while(spanishCorpusSentence){
        samePositionOccurence = 0.0;
        sameWordOccurence = 0.0;
        
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
        getline(spanishCorpusFile, spanishCorpus);
        spanishCorpusSentence.str(spanishCorpus);
        spanishCorpusSentence.clear();
        
        distortionProbability *= (samePositionOccurence / sameWordOccurence);
    }
    
    
    return distortionProbability * englishBigramProbability;  //return
}
