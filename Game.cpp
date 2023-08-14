#include <iostream>
#include <stdlib.h>
#include "Game.h"
 
void Game::ShowHud(Game::game* g, int rl) {

	if (g->word == nullptr) {
		std::cout << "\nTHE WORD IS NOT LOADED!\n";
		exit(1);
	}
	if (g->player->name == nullptr) {
		std::cout << "\nPLAYER NAME IS NULL!\n";
		exit(1);
	}
	

	std::cout << "\n--------------JOGO DA FORCA V1.0--------------" << std::endl;
	std::cout << "->Player Name:" << g->player->name << std::endl;
	std::cout << "->Lifes:" << g->player->lifes << std::endl;
	std::cout << "->Score:" << g->player->score << std::endl;
	std::cout << "->Word:";
	//std::cout << "g->word->len = " << g->word->len << std::endl;
	int cw = g->CurrentWord;
	GameData::SecretWord aux = g->word[cw];
	char* showWords = new char[aux.len];
	if (showWords == nullptr) {
		std::cout << "ERRO, CANT SHOW HUD!" << std::endl;
		exit(1);
	}
	GameData::initStr(showWords, aux.len);
	GameData::fillStr(showWords,'_', aux.len);
	//std::cout << "AUX LEN:" << aux.len << std::endl;
	std::cout << "AUX WORD: " << aux.word << std::endl;
	//loop que verifica se uma letra foi acertada ou não e mostra o resultado na tela;
	for (int i = 0; i < aux.len; i++) {
		//std::cout <<std::endl << i << std::endl;
		if (g->listOfLetters != nullptr) {
			if (g->listOfLetters[i].isInSecretWord && rl > i) {
				GameData::ShowSearchLetterinWord(showWords, &g->listOfLetters[i]);
			}
		}
	}

	std::cout << showWords << std::endl;

	std::cout << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
}

char Game::ShowOptions() {

	char resp = ' ';

	std::cout << "\n---------------Escolha uma acao----------------" << std::endl;
	std::cout << "[q] Sair do programa" << std::endl;
	std::cout << "[g] Adivinhar a palavra" << std::endl;
	std::cout << "[n] Proxima palavra" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "resposta:";
	std::cin >> resp;

	return resp;

}

void Game::GameLoop(game* g) {
	
	char system_resp = ' ';
	char letterToGuess = ' ';
	int RightLetters = 0;
	bool isSearched = false;
	bool isWin = false;
	bool GameOver = false;

	GameData::SecretWord CurrentSecretWord = g->word[g->CurrentWord];
	const int _MAX_GUESS_ = GameData::getWordLen(CurrentSecretWord.word);

	while (system_resp != 'q' && g->player->lifes > 0) {

		ShowHud(g, RightLetters);

		isWin = CheckIsWin(g, RightLetters);
		if (!isWin) {
			std::cout << ">> NAO GANHOU AINDA" << std::endl;
		}
		else {
			std::cout << ">> PARABENS VOCE GANHOU!!!" << std::endl;
			system("pause");
			break;
		}

		
		system_resp = ShowOptions();
		
		if (g->listOfLetters == nullptr) {
			g->listOfLetters = new GameData::SearchLetter[_MAX_GUESS_]; //Assegura que pelo menos o tamanho vai ser suficiente
			GameData::SetToDefautSearchLetterArray(g->listOfLetters, _MAX_GUESS_);
			if (g->listOfLetters == nullptr) {
				std::cout << "ERRO TO CREATE DATA!" << std::endl;
				exit(1);
			}
		}
		
		switch (system_resp)
		{
		case 'g':
			std::cout << "Digite a letra:\n<<";
			std::cin >> letterToGuess;
			isSearched = GameData::isAlredySearched(g->listOfLetters,letterToGuess, RightLetters);
			GameData::SearchLetter guess = GameData::searchInSecretWord(letterToGuess, &CurrentSecretWord);

			if (isSearched) {
				std::cout << ">> Voce ja procurou por essa palavra!" << std::endl;
			}
			else if (guess.isInSecretWord) {
				std::cout << ">> Parabens, voce acertou a letra!" << std::endl;
				g->player->score += g->scoreBasePoints * guess.len;
				if (RightLetters < _MAX_GUESS_) {
					g->listOfLetters[RightLetters] = guess;
					RightLetters++;
				}
				else {
					std::cout << ">> Número maximo de tentativas excedidas!" << std::endl;
				}
			}
			else {
				std::cout << ">> A letra nao pertence a palavra! Tente novamente!" << std::endl;
				g->player->lifes--;
				if (g->player->lifes <= 0) {
					std::cout << ">>>>>GAME OVER<<<<<" << std::endl;
					GameOver = true;
				}
			}
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}	
}
Game::game* Game::InitGame(GameData::GameFile* gf,GameData::Player* pl, int difficult) {
	game* g = new game;

	if (pl == nullptr || gf == nullptr || g == nullptr){
		std::cout << "ERRO TO INITIALIZE THE GAME!" << std::endl;
		exit(1);
	}

	g->player = pl;

	switch (difficult)
	{
		case EASY_MODE:
			g->mode = EASY_MODE;
			g->randBase = EASY_RAND;
			g->scoreBasePoints = EASY_SCORE_BASE;
			pl->lifes = EASY_LIFE_POINTS;
			break;
		case MEDIUM_MODE:
			g->mode = MEDIUM_MODE;
			g->randBase = MEDIUM_RAND;
			g->scoreBasePoints = MEDIUM_SCORE_BASE;
			pl->lifes = MEDIUM_LIFE_POINTS;
			break;
		case HARD_MODE:
			g->mode = HARD_MODE;
			g->randBase = HARD_RAND;
			g->scoreBasePoints = HARD_SCORE_BASE;
			pl->lifes = HARD_LIFE_POINTS;
			break;
		default:
			break;
	}
	g->isWin = false;
	g->listOfLetters = nullptr;
	RandChoseWords(gf, g);
	return g;
}

void Game::RandChoseWords(GameData::GameFile* gf, Game::game* g) {
	if (g == nullptr || gf->content == nullptr) {
		std::cout << "ERRO GAME IS NULL OR THE GAME FILE IS NOT LOADED!" << std::endl;
		exit(1);
	}
	srand(time(NULL));
	
	int* idsRandWord = new int[g->randBase];
	if (idsRandWord == nullptr) {
		std::cout << "ERRO idsRandWord can\'t be created!" << std::endl;
		exit(1);
	}
	g->word = new GameData::SecretWord[g->randBase];
	if (g->word == nullptr) {
		std::cout << "ERRO word in game can\'t be created!" << std::endl;
		exit(1);
	}
	for (int i = 0; i < g->randBase; i++) {
		int Randindex = rand() % g->randBase;
		if (Randindex < 0) {
			std::cout << "ERRO CAN\'T CHOSE THE WORD!" << std::endl;
			exit(1);
		}
		GameData::SetSecretWord(gf->content[Randindex], &g->word[i]);
	}

	g->CurrentWord = rand() % g->randBase;

}

bool Game::CheckIsWin(Game::game* g, int lenOfList) {

	int param = g->word->len;

	if (lenOfList == 0) {
		return false;
	}
	int quantOfLetters = 0;
	for (int i = 0; i < lenOfList; i++) {
		if (g->listOfLetters->IndexesInSecretWord != nullptr && g->listOfLetters[i].isInSecretWord) {
			//std::cout << "i = " << i << std::endl;
			quantOfLetters += g->listOfLetters[i].len;
			//std::cout << " sum = " << quantOfLetters << std::endl;
		}
	}
	std::cout << "len = " << g->word->len << std::endl;
	std::cout << "RETURN VALUE: " << (quantOfLetters == param) << std::endl;
	std::cout << " sum = " << quantOfLetters << std::endl;
	return (quantOfLetters == param);
}