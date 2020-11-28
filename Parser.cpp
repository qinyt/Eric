#include "Model.h"
#include<memory>

extern Token* tokens;
extern Token* peek_token(unsigned int step = 0);
extern Token* get_token();
extern unsigned int get_tk_index();
extern void reset_idx(unsigned int idx);



/*
op:
add|sub|div|mul
add:
expression + expression
expression:
mul|div|(op)
*/
Node_t match_add() 
{
	Node_t node;
	return node;
}
void delete_node_children(Node* node)
{
	if (!node) return;
	if (node->ln != 0) delete_node_children(node->ln);
	else free(node->ln);
	if (node->rn != 0) delete_node_children(node->rn);
	else free(node->rn);
	//free(node); delete self
}
bool match_mul(Node** ppnode)
{
	Node* node = *ppnode;
	auto idx = get_tk_index();
	auto tok = peek_token();
	if (tok->type == NUM || tok->type == FRACT_NUM)
	{
		node->lt = get_token();
		while (peek_token()->type == OP)
		{
			node = *ppnode;
			node->op = get_token()->name;
			auto tok = peek_token();
			if (tok->type == NUM || tok->type == FRACT_NUM)
			{
				node->rt = get_token();
				if (peek_token()->type == OP) 
				{
					Node* lnode = (Node*)malloc(sizeof(Node));
					memset(lnode, 0, sizeof(Node));
					if(!lnode)
					{
						printf("not enough memory\n");
						exit(0);
					}
					lnode->ln = node;
					node->parent = lnode;
					*ppnode = lnode;
				}
			}
			else 
			{
				reset_idx(idx);
				delete_node_children(node);
				return false;
			}
		}
		return true;
	}
	return false;
}

int eval_node(Node* node) 
{
	if (node->ln) eval_node(node->ln);
	if (node->rn) eval_node(node->rn);
	if (!strcmp(node->op, "+")) 
	{
		//sscanf(node->lt->name, "");
	}
	return 0;
}

unsigned int count_left_node(Node* node) 
{
	Node* _node = node;
	int c = 0;
	while(_node->ln != nullptr)
	{
		++c;
		_node = _node->ln;
	}
	return c;
}

void print_node(Node* node) 
{
	printf("\nnode tree:\n\n");
	Node* _node = node;
	while (_node->ln) 
	{
		int c = count_left_node(_node);
		++c; //counting for leaf printing
		int c1 = c - 1;
		printf(" ");
		while (c--)
		{
			printf(" ");
		}
		printf(" ");
		if(!(_node->parent == 0)) printf("%s %s\n", _node->op, _node->parent->rt->name);
		else printf("%s\n", _node->op);
		printf(" ");
		while (c1--)
		{
			printf(" ");
		}
		printf(" ");
		printf("/ \\\n");
		_node = _node->ln;
	} 
	//print leaf
	printf(" %s   %s\n", _node->lt->name, _node->rt->name);

	printf("\n\n");
}


bool match_express() 
{
	auto idx = get_tk_index();
	auto tok = peek_token();
	if (tok->type == NUM || tok->type == FRACT_NUM) 
	{
		while (1) 
		{
				
		}
	}
	reset_idx(idx);
	return false;
}