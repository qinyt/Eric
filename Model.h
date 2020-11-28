#pragma once

#define MAX_TOKEN_NAME_SIZE 50

enum TokenType
{
	NON, ID, LEFT_PAR, RIGHT_PAR, INT, FLOAT, OP, FRACT_NUM, NUM,
};


typedef struct Token
{
	char name[MAX_TOKEN_NAME_SIZE];
	TokenType type;
}Token_t;


typedef struct Node
{
	struct Node* parent = 0;
	struct Node* ln = 0;
	struct Node* rn = 0;
	const char*  op = "\0";
	Token* lt = 0;
	Token* rt = 0;
}Node_t;