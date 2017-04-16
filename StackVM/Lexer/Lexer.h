/*
 * Lexer.h
 *
 *  Created on: Apr 16, 2017
 *      Author: tdawson
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <vector>


typedef uint8_t byte;
typedef std::vector<std::string> strings;

enum State : byte {

	BEGIN,
	READCHAR,
	READBLOCK,
	SKIP,
	DUMP,
	COMMENT,
	END
};


class Lexer {

	bool isSpace(char c);
	bool isSpecialChar(char c);
	bool isGroup(char c);
	char endChar, startChar;

public:
	Lexer();
	strings lex(std::string stream);
	virtual ~Lexer();
};

#endif /* LEXER_H_ */
