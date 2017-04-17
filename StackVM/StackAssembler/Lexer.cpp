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

			else if (isGroup(stream[streamIndex])) {

				if(stream[streamIndex] == '"') {
					lexeme[lexemeIndex] = stream[streamIndex];
					streamIndex++;
					lexemeIndex++;
					}
				state = READBLOCK;
				}

			else if(stream[streamIndex] == '/' && stream[streamIndex -1] == '/') {

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

			if (stream[streamIndex] == startChar && stream[streamIndex] != '"') {

				balance++;
				lexeme[lexemeIndex] = stream[streamIndex];
				streamIndex++;
				lexemeIndex++;
			}

			else if (stream[streamIndex] == endChar) {
				balance--;
				lexeme[lexemeIndex] = stream[streamIndex];
				lexemeIndex++;
				streamIndex++;
				if(balance <= 0) state = DUMP;
			}

			else if (endChar == '"' && stream[streamIndex] == '\\')	streamIndex+=2; // TODO: Fix to actually record characters

			else {
				lexeme[lexemeIndex] = stream[streamIndex];
				lexemeIndex++;
				streamIndex++;
			}

			break;

		case SKIP:
			if(isSpace(stream[streamIndex])) streamIndex++;
			else state = READCHAR;

			break;

		case DUMP:
			if(lexemeIndex > 0) {
				lexeme[lexemeIndex] = 0;
				strlist.push_back(lexeme);
				lexemeIndex = 0;

			}
			state = BEGIN;
			break;

		case COMMENT:
			if(stream[streamIndex] != '\n') streamIndex++;
			else state = READCHAR;

			break;

		case END:
			streamIndex = len;
			break;
		}

		if (lexemeIndex > 0) {
			lexeme[lexemeIndex] = 0;
			strlist.push_back(lexeme);
		}
	}

	return strlist;
}

// function defining what a space is
bool Lexer::isSpace(char c) {

	switch(c) {

	case '\n':
	case '\t':
	case '\r':
	case '\f':
	case ' ':
	case '\v':
		return true;
	default:
		return false;
	}
}

bool Lexer::isGroup(char c) {

	startChar = c;
	switch(c) {

	case '"':
		endChar = '"';
		return true;
	case '(':
		endChar = ')';
		return true;
	case ')':
		return true;
	default:
		return false;
	}
}

bool Lexer::isSpecialChar(char c) {

	switch(c) {

	case '[':
	case ']':
		return true;
	default:
		return false;
	}
}
