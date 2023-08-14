#pragma once

#define MAX_CHAR_LEN 256
#define MAX_CHAR_FOR_EXTRACT 52

#define DEFAULT_LOAD_WORDS 5
#define DONT_CARE_ABOUT_THIS_ARGUMMENT -1

#define DEFAULT_PLAYER_NAME (char*)"Teste"

#define LOAD_MODE_ALL 0
#define LOAD_MODE_N_NUMBER 1
#define LOAD_MODE_FIRST 2
#define LOAD_MODE_LAST 3
#define LOAD_MODE_DEFAULT 4


namespace GameData{

	typedef struct SecretWord {
		char* word;
		int len;
	};

	typedef struct SearchLetter {
		bool isInSecretWord;
		int* IndexesInSecretWord;
		int len;
		char letter;
		SecretWord* sw;
	};


	typedef struct GameFile {
		char* path;
		char** content;
		int len;
	};

	typedef struct Player {
		char* name;
		int score;
		int lifes;
	};
	
	GameFile* LoadGameFile(char[],int,int);

	void SetSecretWord(char*, SecretWord*);
	SearchLetter searchInSecretWord(char, SecretWord*);
	void SetToDefautSearchLetter(SearchLetter*);
	void SetToDefautSearchLetterArray(SearchLetter*,int);
	bool isAlredySearched(SearchLetter*, char, int);

	int getWordLen(char*);
	void initStr(char*, int);
	void fillStr(char*, const char, int);
	void fillStrWithStr(char*, const char*);
	void fillStrWithStep(char*, const char, int, int);
	void ShowSearchLetterinWord(char*, SearchLetter*);


	Player SetPlayerData(char*, int, int);
	//int SetPlayerScore(Player*, int);

}