#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

// Identify OS
#ifdef _WIN32
#define OS "Windows"
#elif __linux__
#define OS "Linux"
#endif

typedef unsigned char uchar;

// clear screen
inline void clearScreen() {
  if ((std::string)OS == "Linux") {
    system("clear");
  } else {
    system("cls");
  }
}

// clear buffer and wait for a key to continue
inline void waitForInput() {
    std::cin.ignore();
    std::cin.get(); 
}

// load words from file
inline void loadWords(std::string list[], uchar max_size, uchar *amountLoaded) {
  std::ifstream file;
  file.open("words.txt");

  if (file.is_open()) {
    std::string line;
    uchar counter = 0; // to ensure not pass the limit

    while (file >> line && max_size > counter) {
      list[counter] = line;
      counter++;
    }
    *amountLoaded = counter;

  } else {
    throw std::runtime_error("File couldn't open");
  }
}

// generate a random number from 0 to x
inline uchar randomNumber(uchar max) { return rand() % max; }

// check if a letter exists inside the list
inline bool checkLetterHistory(uchar letter, uchar list[], uchar counter) {

  for (uchar i = 0; i < counter; i++) {
    if (letter == list[i]) { // exists inside
      return true;
    }
  }
  return false;
}

inline bool checkIfWinned(std::string hiddenWord) {

  for (unsigned char i = 0; i < hiddenWord.length(); i++) {
    if (hiddenWord[i] == '*') {
      return false; // there're still hidden characters
    }
  }
  return true; // finished
}

inline std::string drawHangman(uchar userTrys) {
	char design[150];
	uchar stick1 = userTrys >= 1 ? '-' : ' ';
	uchar stick2 = userTrys >= 2 ? '+' : ' ';
	uchar head =  userTrys >= 3 ? 'O' : ' ';
	uchar body =  userTrys >= 4 ? '|' : ' ';
	uchar l_arm =  userTrys >= 5 ? '/' : ' ';
	uchar r_arm =  userTrys >= 6 ? '\\' : ' ';
	uchar l_leg =  userTrys >= 7 ? '/' : ' ';
	uchar r_leg =  userTrys >= 8 ? '\\' : ' ';

	sprintf(design,		
	R"(
	   +---%c%c 
	   |    %c    
	   |   %c%c%c 
	   |   %c %c     
	   |     
	   |      
	   |           
	  / \
	)",
	stick1, stick2, head, l_arm, body, r_arm, l_leg, r_leg  	
	);

	std::string hangmanString = design;
	return hangmanString;
}

inline std::string statics(uchar userTrys, uchar letterHistory[], uchar lettersCounter) {
	std::string border(20, '=');
	std::string letters;
      for (uchar i=0; i < lettersCounter; i++) {
          letters += letterHistory[i];
      }

      std::string staticS;
      staticS += border + "\n";
      staticS += "Intentos:" + std::to_string(userTrys) + "/8\n"; 
      staticS += "Historial: " + letters + "\n";
      staticS += border + "\n";

      return staticS;

}
