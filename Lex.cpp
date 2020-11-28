#include<cstdlib>
#include<cstdio>
#include<memory>
#include<string.h>
#include"Model.h"
#include<vector>

#define VECTOR_INT_LEN 512
const char* RESERVE_WORDS[] = { "(", ")", "[", "]" , "int", "float" };
const char* op_tokens[] = { "+", "-", "*", "/" , "++", "--", "<<", ">>", "!", ";", "\0" };

Token* tokens = (Token*)malloc(VECTOR_INT_LEN * sizeof(Token));
unsigned int index = 0;

unsigned int vec_cur_size = VECTOR_INT_LEN, token_stack_top = 0;

Token cur_token;

std::vector<char> token_name;

void tokens_print() 
{
	for (unsigned int i = 0; i < token_stack_top; ++i)
	{
		const char* name = tokens[i].name;
		int type = tokens[i].type;
		printf("token name:%s, type:%d\n", name, type);
	}
}

unsigned int get_tk_index() 
{
	return index;
}

void reset_idx(unsigned int idx) 
{
	index = idx;
}

Token* peek_token(unsigned int step = 0) 
{
	return &tokens[index+step];
}

Token* get_token()
{
	return &tokens[index++];
}

void unget_token()
{
	index--;
}

void tokens_resize();

void tokens_push_back(Token* token) 
{
	if (!(token_stack_top < vec_cur_size - 1)) tokens_resize();
	tokens[token_stack_top] = *token;
	++token_stack_top;
}

void tokens_resize() 
{
	unsigned int copy_size = vec_cur_size;
	vec_cur_size = vec_cur_size << 1;
	void* temp = malloc(vec_cur_size * sizeof(Token));
	if (!temp) 
	{
		printf("failed allocating memory");
		exit(0);
	}
	memcpy(temp, tokens, copy_size * sizeof(Token));
	free(tokens);
	tokens = (Token*)temp;
}

bool ischar(char a) 
{
	return ((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z'));
}

bool isnum(char a) 
{
	return ((a >= '0') && (a <= '9'));
}

bool isop(char c)
{ 
	const char** id = op_tokens;
	for (auto w : op_tokens) 
	{
		if (!strcmp(&c, w))
		{
			return true;
		};
	}
	return false;
}

TokenType cur_type = NON;

void token_accepted() 
{
	if (cur_type != NON)
	{
		//token_name.push_back(0);
		if (token_name.size() > MAX_TOKEN_NAME_SIZE)
			printf("token size too big, max size is: %d\n", MAX_TOKEN_NAME_SIZE);
		for (unsigned int i = 0; i < token_name.size(); ++i)
		{
			cur_token.name[i] = token_name.at(i);
		}
		token_name.clear();
		//strcpy(cur_token.name, &token_name.data);
		cur_token.type = cur_type;
		tokens_push_back(&cur_token);
		memset(cur_token.name, 0, 50);
		cur_type = NON;
	}
}


void tokenize(const char* line) 
{
	while (*line) 
	{
		if (*line == ' ') 
		{
			++line; 
			continue;
		}

		if (*line == '(')
		{
			cur_type = LEFT_PAR;
			token_name.push_back('(');
			token_accepted();
			++line;
			continue;
		}

		if (*line == ')')
		{
			cur_type = RIGHT_PAR;
			token_name.push_back(')');
			token_accepted();
			++line;
			continue;
		}

		if (isop(*line))
		{
			cur_type = OP;
			token_name.push_back(*line);
			token_accepted();
			++line;
			continue;
		}

		if (ischar(*line)) 
		{
			cur_type = ID;
			token_name.push_back(*line);
			++line;
			while (*line) 
			{				
				if (*line == 'i') 
				{
					if (*(line + 1) == 'n' && *(line + 2) == 't' && *(line + 3) == ' ')
					{
						cur_type = INT;
						char temp[4] = "int";
						for (int i = 1; i < 4; ++i)
							token_name.push_back(temp[i]);
						token_accepted();
						line += 3;
						break;
					}
				}
				//TODO: add floating point
				if (*line == 'f')
				{
					if (*(line + 1) == 'l' && *(line + 2) == 'o' && *(line + 3) == 'a' && *(line + 4) == 't' && !ischar(*(line + 5)) && !isnum(*(line + 5)))
					{
						cur_type = FLOAT;
						char temp[6] = "float";
						for (int i = 1; i < 6; ++i)
							token_name.push_back(temp[i]);
						token_accepted();
						line += 5;
						break;
					}
				}
				while(ischar(*line) || isnum(*line)) 
				{
					token_name.push_back(*line);
					++line;
				}
				token_accepted();
				break;
			}
			continue;
		}
		if (isnum(*line)) 
		{
			cur_type = NUM;
			token_name.push_back(*line);
			++line;
			int dot = 0;
			while (*line) 
			{
				if ((*line == '.')) 
				{
					++dot;
					if (dot > 1) 
					{
						printf("illegal token for float: more than 1 dot\n");
						exit(0);
					}
					cur_type = FRACT_NUM;
					token_name.push_back('.');
					++line;
					continue;
				}
				if (isnum(*line)) 
				{
					token_name.push_back(*line);
					++line;
					continue;
				}
				if ((*line == ' ') || isop(*(line)) || !(*line))
				{
					token_accepted();
					break;
				}
				printf("illegal token for num\n");
				exit(0);
			}
			token_accepted();
			continue;
		}
		printf("illegal token: %s \n", line);
		exit(0);
	}
}
