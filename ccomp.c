#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccomp.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		error("引数の個数が正しくありません");
		return 1;
	}

	user_input = argv[1];
	token = tokenize(argv[1]);
	Node *node = expr();

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");

	gen(node);

	// スタックトップに式全体の値が残っているはずなので
	// それをRAXにロードして関数からの返り値とする
	printf("  pop rax\n"); // 電卓の計算結果を格納
	printf("  ret\n");

	return 0;
}
