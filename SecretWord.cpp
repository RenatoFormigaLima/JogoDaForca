#include "GameData.h"
#include <iostream>
//#include <cstdlib>

GameData::SearchLetter GameData::searchInSecretWord(char letter, GameData::SecretWord* word) {

	int count = 0;

	int* auxPos = new int[word->len];
	if (auxPos == nullptr) {
		std::cout << "Erro ao criar variavel!\n";
		exit(1);
	}

	SearchLetter sl;
	sl.sw = word;
	sl.letter = letter;
	sl.isInSecretWord = false;

	for (int i = 0; i < word->len; i++) {
		if (word->word[i] == letter || word->word[i] == (letter + 32)  || word->word[i] == (letter - 32)) {
			sl.isInSecretWord = true;
			auxPos[count] = i;
			count++;
		}
	}
	sl.len = count;

	if (count == 0) {
		sl.IndexesInSecretWord = new int[1];
		sl.IndexesInSecretWord[0] = -1;
		sl.len++;
	}
	else {
		sl.IndexesInSecretWord = new int[count];
	}
	
	
	if (sl.IndexesInSecretWord == nullptr) {
		std::cout << "Erro ao criar variavel!\n";
		exit(1);
	}

	for (int i = 0; i < count; i++) {
		sl.IndexesInSecretWord[i] = auxPos[i];
	}

	delete[]auxPos;

	return sl;
}

void GameData::SetSecretWord(char* word, SecretWord* sw) {
	
	if (sw == nullptr) {
		SecretWord* new_sw = new SecretWord;
		if(new_sw == nullptr){
			std::cout << "Erro ao criar variavel!\n";
			exit(1);
		}

		new_sw->len = getWordLen(word);
		new_sw->word = new char[new_sw->len];
		initStr(new_sw->word, new_sw->len);

		if (new_sw->word == nullptr) {
			std::cout << "Erro ao criar variavel!\n";
			exit(1);
		}
		//initStr(new_sw->word,new_sw->len);
		for (int i = 0; i < new_sw->len; i++) {
			new_sw->word[i] = word[i];
		}

		sw = new_sw;

	}
	else {
		sw->len = getWordLen(word);
		//delete[]sw->word;
		sw->word = new char[sw->len];
		if (sw->word == nullptr) {
			std::cout << "ERRO TO COPY THE SECRET WORD!";
		}
		for (int i = 0; i <= sw->len; i++) {
			sw->word[i] = word[i];
		}
	}

}

int GameData::getWordLen(char* word) {
	if (word != nullptr) {
		int count = 0;
		for (int i = 0; word[i] != '\0'; i++) { count++; }

		return count;
	}
	else {
		return 0;
	}
	
}

void GameData::initStr(char* str, int len) {
	for (int i = 0; i <= len; i++) {
		str[i] = '\0';
	}
}

void GameData::ShowSearchLetterinWord(char* word, GameData::SearchLetter* sl) {
	if (word == nullptr || sl == nullptr) {
		std::cout << "ERRO VALUE NULL!" << std::endl;
		exit(1);
	}

	for (int i = 0; i < sl->len; i++) {
		//std::cout << std::endl;
		//std::cout << "i = " << i << std::endl;
		//std::cout << "IndexesInSecretWord[i] = " << sl->IndexesInSecretWord[i] << std::endl;
		//std::cout << "Letter = " << sl->letter << std::endl;
		//std::cout << "word[IndexesInSecretWord[i]] = " << word[sl->IndexesInSecretWord[i]] << std::endl;
		//std::cout << std::endl;
		word[sl->IndexesInSecretWord[i]] = sl->letter;
	}
}
bool GameData::isAlredySearched(GameData::SearchLetter* sl, char ch, int len) {

	bool result = false;

	if (sl != nullptr && len == 1 && sl->letter == ch) {
		return true;
	}
	if (sl == nullptr) {
		return false;
	}
	
	for (int i = 0; i < len; i++) {
		if (sl[i].letter == ch) {
			result = true;
			break;
		}
	}
	return result;

}
void GameData::fillStr(char* word, const char ch, int len) {

	for (int i = 0; i < len; i++) {
		word[i] = ch;
	}

}
void GameData::fillStrWithStep(char* word, const char ch, int len, int step) {

	for (int i = 0; i < len; i = i + step) {
		word[i] = ch;
	}

}
void GameData::fillStrWithStr(char* str, const char* str_copy) {

}

void GameData::SetToDefautSearchLetter(SearchLetter* sl) {
	//if (sl->IndexesInSecretWord != nullptr) {
		//delete[]sl->IndexesInSecretWord;
	//}
		sl->IndexesInSecretWord = nullptr;
		sl->sw = nullptr;
		sl->isInSecretWord = false;
		sl->len = 0;
		sl->letter = ' ';

	//if (sl->sw != nullptr) {
	//	delete[]sl->sw->word;
//		sl->sw->len = 0;
	//}

	
}

void GameData::SetToDefautSearchLetterArray(SearchLetter* sl, int len) {
	if (sl == nullptr) {
		std::cout << "ERRO, OPERACAO INVALIDA!" << std::endl;
	}
	else {
		for (int i = 0; i < len; i++) {
			SetToDefautSearchLetter(&sl[i]);
		}
	}
}