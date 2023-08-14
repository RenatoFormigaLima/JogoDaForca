#include "GameData.h"
#include <iostream>
/*
Nome da Fun��o: LoadGameFile
Par�metros:
			nome do jogador (string)
			score do jogador (int)
			numero de vidas (int)
Descri��o: Fun��o respons�vel por criar o jogador

*/
GameData::Player GameData::SetPlayerData(char* name, int score, int lifes) {

	Player newPlayer;
	newPlayer.lifes = lifes;
	newPlayer.score = score;

	if (name == nullptr) {
		std::cout << "ERRO: CAN'T CREATE PLAYER, name is null!\n";
		exit(1);
	}
	int lenName = getWordLen(name);
	newPlayer.name = new char[lenName];
	if (newPlayer.name == nullptr) {
		std::cout << "ERRO: CAN'T CREATE PLAYER NAME!\n";
		exit(1);
	}

	for (int i = 0; i < lenName + 1; i++) {
		newPlayer.name[i] = name[i];
	}

	return newPlayer;

}