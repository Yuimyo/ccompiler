#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccomp.h"

Node *code[100];

void program()
{
	int i = 0;
	while (!at_eof())
	{
		code[i++] = stmt();
	}
	code[i] = NULL;
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
	program();

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");

	// プロローグ
	printf("  push rbp\n");
	printf("  mov rbp, rsp\n");
	printf("  sub rsp, %d\n", 26 * 8);

	for (int i = 0; code[i]; i++)
	{
		gen(code[i]);
		printf("  pop rax\n");
	}

	// エピローグ
	printf("  mov rsp, rbp\n");
	printf("  pop rbp\n");

	printf("  ret\n");
	return 0;
}
