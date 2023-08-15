#pragma once

#include "GameData.h"

#define EASY_MODE 0
#define MEDIUM_MODE 1
#define HARD_MODE 2

#define MEDIUM_SCORE_BASE 10
#define EASY_SCORE_BASE 20
#define HARD_SCORE_BASE 30

#define EASY_LIFE_POINTS 5
#define MEDIUM_LIFE_POINTS 4
#define HARD_LIFE_POINTS 3

#define EASY_RAND 3
#define MEDIUM_RAND 5
#define HARD_RAND 8
#define CAOTIC_RAND

namespace Game {

	typedef struct game{
		bool isWin;
		int mode;
		int scoreBasePoints;
		int randBase;
		int CurrentWord;
		GameData::Player* player;
		GameData::SearchLetter* listOfLetters;
		GameData::SecretWord* word;
	};
	


	game* InitGame(GameData::GameFile*, GameData::Player*,int);
	void GameLoop(game*);
	void RandChoseWords(GameData::GameFile*, game* );



	void ShowHud(game* , int);
	char ShowOptions();

	bool CheckIsWin(game*, int);
	

}
