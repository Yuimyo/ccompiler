#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccomp.h"

Node *program()
{
	Node head;
	head.next = NULL;
	Node *cur = &head;
	while (!at_eof())
	{
		cur->next = stmt();
		cur = cur->next;
	}
	return head.next;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		error("引数の個数が正しくありません");
		return 1;
	}

	user_input = argv[1];
	token = tokenize(argv[1]);
	Node *cur = program();

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");

	// プロローグ
	printf("  push rbp\n");
	printf("  mov rbp, rsp\n");
	int lmemsize = allocated_lvar_size();
	if (lmemsize)
	{
		printf("  sub rsp, %d\n", lmemsize);
	}

	for (int i = 0; cur; i++)
	{
		gen(cur);
		printf("  pop rax\n");
		cur = cur->next;
	}

	// エピローグ
	printf("  mov rsp, rbp\n");
	printf("  pop rbp\n");

	printf("  ret\n");
	return 0;
}
