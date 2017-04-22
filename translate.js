var spanish_corpus = "El muchacho corrió por la calle. Vio a un hombre que vendía helado. El chico le gusta el helado y compró un helado. Su madre no estaba contenta con su decisión.";

var english_corpus = "The boy ran down the street. He saw a man selling ice-cream. The boy likes ice cream so he bought an ice-cream cone. His mother was not happy about his decision.";

function translateSentence() {
  //Load Sentence into Variable
  var dictionaryFile = document.getElementById("fileInput");
  var file = dictionaryFile.files[0];
  var reader = new FileReader();

  reader.onload = function(e){
  	//File IO///////////////////////////////////////////////////////
  	console.time('File IO'); //start measuring length of time to complete File IO operations
  	var text = reader.result;
  	console.timeEnd('File IO'); //stop measuring length of time to complete File IO operations
  	////////////////////////////////////////////////////////////////
  	var userInput = document.getElementById("input").value;
    var output = formatSentences(userInput);
    var likelihood = 0.0;

    //String Manipulation/////////////////////////////////////////////////////
    console.time('String Manipulation');  //start measuring length of time to complete string manipulation functions
    text = text.split(/:|\n/);  //using regex detection to split dictionary text file at new lines and commas
    for(var index = 0; index < output.length; index++){
  		output[index] = searchDictionary(output[index], text);
  		if (output[index]==null) {
  			console.log("DEBUG: Null value returned");
  			break;
  		}
    }
    console.timeEnd('String Manipulation');  //stop measuring length of time to complete string manipulation functions
	///////////////////////////////////////////////////////////////////////// 

	//Probability (AKA Floating Point Calculations)//////////////////////////
	console.time('Floating Point Calculations');  //start measuring length of time to complete floating point operations
  	likelihood = calculateTranslationLikelihood(userInput, output);
  	console.timeEnd('Floating Point Calculations');  //stop measuring length of time to complete floating point operations
  	/////////////////////////////////////////////////////////////////////////
  	output = output.join(" ");
  	document.getElementById("output").value = output;
  	console.log("Likelihood of translation = " + likelihood);
  }
  reader.readAsText(file);
}

function searchDictionary(word, myDictionary){
	for(var index = 0; index < myDictionary.length; index++){
		if (word == myDictionary[index]) {
			return myDictionary[index + 1];
		}
	}
	console.log("ERROR: Could not find word: " + word);  //send error message to user in console
	return null;   //could not find word in dictionary
}

function formatSentences(sentences){
	//remove punctuations and lowercase all characters within a given string
	sentences = sentences.toLowerCase();
	sentences = sentences.replace(/[.]/g, "");
	var words = sentences.split(" ");
	return words;
}

function calculateTranslationLikelihood(englishSentence, spanishSentence){
	//calculate probability of sentence using bigram model
	var wordPairOccurence = 0.0;
	var wordOccurence = 0.0;
	var englishBigramProbability;
	var totalEnglishBigramProbability = 1.0;
	var spanishBigramProbability;
	var totalSpanishBigramProbability = 1.0;
	var samePositionOccurence = 0.0;
	var sameWordOccurence = 0.0;
	var totalDistortionProbability = 1.0;
	var englishCorpusWords = english_corpus.toLowerCase();
	var spanishCorpusWords = spanish_corpus.toLowerCase();

	englishCorpusWords = englishCorpusWords.split(/\.|\s+/);
	englishSentence = formatSentences(englishSentence);
	//english bigram
	for(var index = 0; index < englishSentence.length; index++){
		wordPairOccurence = 0.0; //resetting value for new word
		wordOccurence = 0.0; //resetting value for new word
		for(var corpusIndex = 0; corpusIndex < englishCorpusWords.length; corpusIndex++){
			//examining the number of times a word in the inputted sentence appears in the english corpus
			if((index != 0) && (corpusIndex != 0) && (englishSentence[index - 1] == englishCorpusWords[corpusIndex - 1])){
				wordOccurence++;
			}
			else if((index == 0) && (englishSentence[index] == englishCorpusWords[corpusIndex])){
				wordOccurence++;  //case where we are examining the first word in the sentence inputted by user
			}
			//examining the number of word pairs that occur between the word being examined and the previous word
			if((index == 0) && (corpusIndex == 0) && (englishSentence[index] == englishCorpusWords[corpusIndex])){
				wordPairOccurence++; //case where the first elements of the user inputted sentence and the english corpus match
			}
			else if((index == 0) && (corpusIndex != 0) && (englishSentence[index] == englishCorpusWords[corpusIndex]) && (englishCorpusWords[corpusIndex - 1] == "")){
				wordPairOccurence++;  //case where we are examinging the word pair associated with the first word in a sentence (the word itself and nothing)
			}
			else if((index != 0) && (corpusIndex != 0) && (englishSentence[index] == englishCorpusWords[corpusIndex]) && (englishSentence[index - 1] == englishCorpusWords[corpusIndex - 1])){
				wordPairOccurence++;
			}
		}
		if (wordOccurence != 0) {
			englishBigramProbability = wordPairOccurence/wordOccurence;
			totalEnglishBigramProbability = totalEnglishBigramProbability * englishBigramProbability;
		}
	}
	//due to sample size, this calculation always returns a zero
	//calculate distortion probability
	var sampleSentences = spanish_corpus.toLowerCase();
	var spanishCorpusWords = spanish_corpus.split(/\.|\s+/);
	sampleSentences = sampleSentences.split(".");
	for(var index = 0; index < sampleSentences.length; index++){
  		sampleSentences[index] = sampleSentences[index].split(" "); //splitting sentences into 2D array of words
  	}
  	for(var index = 0; index < spanishSentence.length; index++){
 		samePositionOccurence = 0.0;
  		sameWordOccurence = 0.0;
  		for(var sentenceIndex = 0; sentenceIndex < sampleSentences.length; sentenceIndex++){
  			  if(sampleSentences[sentenceIndex][index] == spanishSentence[index]){
  				samePositionOccurence++;
  			}
  		}
  		for(var wordIndex = 0; wordIndex < spanishCorpusWords.length; wordIndex++){
  			if(spanishSentence[index] == spanishCorpusWords[wordIndex]){
  				sameWordOccurence++;
			}
  		}
  		if(sameWordOccurence !=0){
  			distortionProbability = samePositionOccurence / sameWordOccurence;
  			totalDistortionProbability = totalDistortionProbability * distortionProbability;
  		}
	}


	return totalDistortionProbability * totalEnglishBigramProbability;  //return
}