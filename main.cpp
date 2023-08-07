#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <variant>

#include "functions.h"

using namespace std;

void draw(string hiddenWord, uchar userTrys);
void gameStarted(string wordsList[], uchar wordsCounter);

int main(int argc, char const *argv[]) {

	// disable buffer
	srand(time(0)); // init random generator. For random numbers

  const uchar MAX_WORDS = 30;
  string wordsList[MAX_WORDS];
  uchar wordsCounter = 0; // counter of words in the list (wordsList)

  loadWords(wordsList, MAX_WORDS, &wordsCounter);

  /* main loop */
  bool gameState = true;

  do {
  	clearScreen();
    uchar option;
    cout << "1.Jugar" << endl;
    cout << "2.Salir" << endl;
    cout << ">>> ";
    cin >> option;

    switch (option) {
	    case '1': {
	      gameStarted(wordsList, wordsCounter);
	      break;
	    }

	    case '2': {
	      gameState = false;
	      break;
	    }

	    default: {
	      cout << "Opcion invalida" << endl;
	      waitForInput();
	      break;
	    }
    }

  } while (gameState);

  return 0;
}

void draw(string hiddenWord, uchar userTrys, uchar* letterHistory, uchar lettersCounter) {
  clearScreen();

  cout << statics(userTrys, letterHistory, lettersCounter) << endl;
  cout << drawHangman(userTrys) << endl;

  for (unsigned char i = 0; i < hiddenWord.length(); i++) {
    if (hiddenWord[i] == '*') {
      cout << " __ "; // replace
    } else {
      printf(" %c ", hiddenWord[i]);
    }
  }
}

void gameStarted(string wordsList[], uchar wordsCounter) {

  const uchar MAX_TRYS = 8;
  uchar userTrys = 0; // trys already done by the user
  bool winned = false;

  uchar lettersHistory[27]; // Spanish Alphabet A-Z
  uchar letterCounter = 0;

  string actualWord = wordsList[randomNumber(wordsCounter)]; // random word
  string hiddenWord(actualWord.length(), '*'); // random word template
  string letter;
  
    while (userTrys < MAX_TRYS) { // loop game
      draw(hiddenWord, userTrys, lettersHistory, letterCounter);

      if (checkIfWinned(hiddenWord)) {
        winned = true;
        break;
      }

      // Ask for a letter
      cout << "\n\nInserta una letra\n"
           << ">>> ";
      cin >> letter;
      uchar c_letter = toupper(letter[0]); // fisrt character

      // Verify letters historial (If it was typed before)
      if (!checkLetterHistory(c_letter, lettersHistory, letterCounter)) {
    	bool letterExists = false;
        lettersHistory[letterCounter] = c_letter;
        letterCounter++;

        // Assign letter to original index
        for (uchar i = 0; i < actualWord.length(); i++) {
          if (c_letter == actualWord[i]) { // exists inside
            hiddenWord[i] = c_letter;
            letterExists = true;
          }
        }

        if (!letterExists) {
	      	userTrys++;
        }

      } else {
        cout << "\nYa elegiste esa letra" << endl;
        waitForInput();
      }
    }

    if (winned) {
      cout << "\nGanaste!!!" << endl;
    } else {
      cout << "\nPerdiste. La palabra era: " << actualWord << endl;
    }

    waitForInput();
}