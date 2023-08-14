#include "GameData.h"
#include <iostream>
#include <fstream>

/*
Nome da Função: LoadGameFile
Parâmetros: 
			local do arquivo (string)
			número de palavras (int)
			Modo de carregamento (int)
Descrição: Função responsável por carregar os dados do arquivo

*/

GameData::GameFile* GameData::LoadGameFile(char path[], int NumberofWords, int mode) {

	
	GameFile* gf = new GameFile;

	if (gf == nullptr) {
		std::cout << "ERRO UNABLE TO CREATE GAMEFILE!\n";
		exit(1);
	}
	//Armazenando o dado de arquivo 
	gf->path = path;
	//Abrindo o arquivo
	std::ifstream file(path);
	//Criando o dado para a linha, utiliza um número máximo de caracteres
	char* line = new char[MAX_CHAR_LEN];
	//Configurando o carregamento dependendo do modo
	switch (mode)
	{
	case LOAD_MODE_ALL:
		if (file.is_open()) {
			int conut = 0;
			while (file.getline(line, MAX_CHAR_LEN)) {
				conut++;
			}
			gf->len = conut;
			gf->content = new char* [conut];
			NumberofWords = conut;
			file.close();
		}
		else {
			std::cout << "ERRO UNABLE TO LOAD GAMEFILE!\n";
			exit(1);
		}
		file.open(path);
		break;
	case LOAD_MODE_FIRST:
		gf->len = 1;
		NumberofWords = 1;
		break;
	case LOAD_MODE_N_NUMBER:
		gf->len = NumberofWords;
		break;
	case LOAD_MODE_LAST:
		gf->len = 1;
		NumberofWords = 1;
		break;
	case LOAD_MODE_DEFAULT:
		gf->len = NumberofWords;
		break;
	default:
		gf->len = 1;
		NumberofWords = DEFAULT_LOAD_WORDS;
		break;
	}
	//Alocando a quantidade de palavras que foi requisitado 
	gf->content = new char* [NumberofWords];

	//leitura do arquivo
	if (file.is_open()) {

		int i = 0;
		while (file.getline(line,MAX_CHAR_LEN) && i < NumberofWords) {

			int LenOfLine = getWordLen(line); //Tamanho exato da palavra, economia de espaço

			gf->content[i] = new char[LenOfLine];//Alocando os caracteres da palavra

			if (gf->content[i] == nullptr) {
				std::cout << "ERRO TO CREATE DATA!\n";
				exit(1);
			}

			initStr(gf->content[i], LenOfLine); //Inicializa a string

			for (int j = 0; j < LenOfLine && line[j] != ';'; j++) {
				gf->content[i][j] = line[j]; //Copia os dados menos o ;
			}
			i++;
		}

		file.close(); //fecha o arquivo
	}
	else {
		std::cout << "ERRO UNABLE TO LOAD GAMEFILE!\n";
		exit(1);
	}

	delete[]line;//desalocação da linha usada na função
	return gf;
}

