
var myDictionary = ["she", "ella", "is", "es", "smart", "inteligente", "the", "el", "boy", "muchacho", "ran", "corrió", "down", "por", "street", "calle", "he", "él", "saw", "vío", "a", "un", "man", "hombre", "selling", "viendendo", "ice-cream", "helado", "likes", "le gusta", "so", "así", "bought", "compró", "cone", "cono de", "an", "un", "his", "su", "madre", "was", "estaba", "not", "no", "happy", "contenta", "about", "con", "decision", "decisión"];

var spanish_corpus = "El muchacho corrió por la calle. Vio a un hombre que vendía helado. El chico le gusta el helado y compró un helado. Su madre no estaba contenta con su decisión.";

var english_corpus = "The boy ran down the street. He saw a man selling ice-cream. The boy likes ice cream so he bought an ice-cream cone. His mother was not happy about his decision.";

function translateSentence() {
  //Load Sentence into Variable
  var sentence = document.getElementById("input").value;

  sentence = sentence.split(" ");

  for(var index = 0; index < sentence.length; index++){
  	sentence[index] = searchDictionary(sentence[index]);
  	if (sentence[index]==null) {
  		console.log("DEBUG: Null value returned");
  		break;
  	}
  }
  //sentence = sentence.map((val)=>myDictionary[myDictionary.indexOf(val)+1]);
  sentence = sentence.join(" ");
  document.getElementById("output").value = sentence;
}

function searchDictionary(word){
	for(var index = 0; index < myDictionary.length; index++){
		if (word == myDictionary[index]) {
			return myDictionary[index + 1];
		}
	}
	console.log("ERROR: Could not find word: " + word);
	return null;   //could not find word in dictionary
}

function formatString(){
	//remove punctuations and lowercase all characters within a given string
}

function switchWordPosition(){
	//move a word in a sentence to its most likely position
}

function computeLikelyPosition(){
	//find the most likely position for a word from an english sentence in a spanish sentence
}  
	
  
