#include <cstdio>
#include<cstdlib>
#include<memory>
#include "Model.h"

extern void tokenize(const char* line);
extern void tokens_print();
extern bool match_mul(Node** ppnode);
extern void print_node(Node* node);
extern unsigned int count_left_node(Node* node);
extern bool isop(char c);

const char* file = "c:/qin_game/words.txt";

int main(int argc, char** argv) 
{
	tokenize("3/1.55/5*6/3*5*6*7*9.9\0");
	tokens_print();
#if 1
	Node* node = (Node*)malloc(sizeof(Node));
	memset(node, 0, sizeof(Node));
	match_mul(&node);
	int c = count_left_node(node);
	print_node(node);
#endif
	return 0;
}