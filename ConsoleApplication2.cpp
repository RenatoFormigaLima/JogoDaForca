#include <iostream>
#include "GameData.h"
#include "Game.h"



int main(int argc, char** argv)
{
	/*Criação do GAMEFILE para carregar os dados na RAM*/
	GameData::GameFile* gf;
	Game::game* g;
	/*Mostra os valores dos argumentos*/
	for (int i = 0; i < argc; i++) {
		std::cout << "Argv[" << i << "] = "<< argv[i] << std::endl;
	}
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
				gf = GameData::LoadGameFile(argv[1], DONT_CARE_ABOUT_THIS_ARGUMMENT, LOAD_MODE_ALL);
			}
			else if (argv[3] == "-h") {
				std::cout << "COMANDOS:\n" << "caminho - numero de palavras - debug mode[-d]/help[-h]\n";
				exit(1);
			}
		default://caso não for passado nenhum argumento

			/*TESTE DE FUNCIONAMENTO*/
			//Carregamento dos dados do arquivo
			char path[] = "C:\\Users\\renat\\Downloads\\teste.txt";
			gf = GameData::LoadGameFile(path, DONT_CARE_ABOUT_THIS_ARGUMMENT, LOAD_MODE_ALL);
			GameData::Player player;
			player = GameData::SetPlayerData(DEFAULT_PLAYER_NAME, 0, 0);
			g = Game::InitGame(gf, &player, EASY_MODE);
			Game::GameLoop(g);
			
			

			//Escolhendo a palavra secreta
			GameData::SecretWord* sw = new GameData::SecretWord;
			GameData::SetSecretWord(gf->content[0],sw);
			//Mostrando os dados da palavra secreta
			if (sw != nullptr) {
				std::cout << "Secret Word Len: " << sw->len << std::endl;
				std::cout << "Secret Word: " << sw->word << std::endl;
				//Pesquisando a palavra e gerando o número de ocorrências, as posições em que aparece e se aparece ou não a palavra
				GameData::SearchLetter guess = GameData::searchInSecretWord((char)'r', sw);
				//Mostrando os dados da pesquisa
				std::cout << "guess.letter: " << guess.letter << std::endl;
				std::cout << "guess.isInSecretWord: " << guess.isInSecretWord << std::endl;
				for (int i = 0; i < guess.len; i++) {
					std::cout << "guess.IndexesInSecretWord[" << i << "] " << ":" << guess.IndexesInSecretWord[i] << std::endl;
				}

				std::cout << "guess.len:" << guess.len << std::endl;
			}
			
			break;
	}

	std::cout << std::endl;
	//Mostrando todos os dados carregados do arquivo de jogo
	for (int i = 0; i < gf->len ; i++) {
		std::cout << gf->content[i] << std::endl;
	}
}

