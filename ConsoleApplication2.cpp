#include <iostream>

#include "GameData.h"
#include "Game.h"

int main(int argc, char** argv)
{
	/*Criação do GAMEFILE para carregar os dados na RAM*/
	GameData::GameFile* gf;
	Game::game* g;
	/*
		Configuração do programa:
	*/
	switch (argc)
	{
		case 2://Caso queira especificar o caminho
			std::cout << "arguments: " << argc << std::endl;
			gf = GameData::LoadGameFile(argv[1], DEFAULT_LOAD_WORDS, LOAD_MODE_N_NUMBER);
			break;
		case 3://caso queira especificar o caminho + colocar um número exato de palavras para carregar do arquivo
			std::cout << "arguments: " << argc << std::endl;
			gf = GameData::LoadGameFile(argv[1], atoi(argv[2]), LOAD_MODE_N_NUMBER);
			break;
		case 4://caso queira abilitar o debug mode
			std::cout << "arguments: " << argc << std::endl;//concertar a verificação do argumento
			if (argv[3] == "-d") {
				std::cout << "\n\n__DEBUG MODE__\n\n";
				gf = GameData::LoadGameFile(argv[1], DONT_CARE_ABOUT_THIS_ARGUMENT, LOAD_MODE_ALL);
			}
			else if (argv[3] == "-h") {
				std::cout << "COMANDOS:\n" << "caminho - numero de palavras - debug mode[-d]/help[-h]\n";
				exit(1);
			}
		default://caso não for passado nenhum argumento
			char path[] = "C:\\Users\\renat\\Downloads\\teste.txt";
			gf = GameData::LoadGameFile(path, DONT_CARE_ABOUT_THIS_ARGUMENT, LOAD_MODE_ALL); //Carregamento dos dados do arquivo
			break;
	}

	GameData::Player player;
	player = GameData::SetPlayerData(DEFAULT_PLAYER_NAME, 0, 0);
	g = Game::InitGame(gf, &player, EASY_MODE);
	Game::GameLoop(g);
	std::cout << std::endl;
}

