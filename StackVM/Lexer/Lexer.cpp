/*
 * Lexer.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: tdawson
 */

#include "Lexer.h"

Lexer::Lexer() {

}

strings Lexer::lex(std::string stream) {

	strings strlist;
	char lexeme[256];
	int streamIndex = 0;
	int lexemeIndex = 0;
	State state = BEGIN;
	int len = stream.length();
	int balance = 0;

	while (streamIndex < len) {

		switch(state) {

		case BEGIN:
			if (isSpace(stream[streamIndex])) state = SKIP;

			else if (isGroup(steam[streamIndex])) {

				if(stream[streamIndex] == '"') {
					lexeme[lexemeIndex] = stream[streamIndex];
					streamIndex++;
					lexemeIndex++;
					}
				state = READBLOCK;
				}

			else if(stream[streamIndex] == '/' && steam[streamIndex -1] == '/') {

				streamIndex+=2;
				state = COMMENT;
				}

			else state = READCHAR;

			break;

		case READCHAR:
			if(isSpace(stream[streamIndex])) state = DUMP;

			else if (stream[streamIndex] == '\\')  streamIndex+=2;

			else if (isGroup(stream[streamIndex])) {
				if(stream[streamIndex] == '"') {
					lexeme[lexemeIndex] = stream[streamIndex];
					lexemeIndex++;
					streamIndex++;
				}
				state = READBLOCK;
			}

			else if (isSpecialChar(stream[streamIndex])) {

				if(lexemeIndex == 0) {
					lexeme[lexemeIndex] = stream[streamIndex];
					lexemeIndex++;
					streamIndex++;
				}
				state = DUMP;
			}

			else if (stream[streamIndex] == '/' && stream[streamIndex-1] == '/') {
					streamIndex += 2;
					state = COMMENT;
			}

			else {
				lexeme[lexemeIndex] = stream[streamIndex];
				streamIndex++;
				lexemeIndex++;
			}
			break;

		case READBLOCK:
			break;

		case SKIP:
			break;

		case DUMP:
			break;

		case COMMENT:
			break;

		case END:
			break;
		}

	}

	return strlist;
}
