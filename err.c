#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccomp.h"

// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// 入力プログラム
char *user_input;

// エラー箇所を報告するための関数
// 第2引数より、printfと同じ引数を取る
void error_at(char *loc, char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, " "); // pos個の空白を出力
    fprintf(stderr, "^ ");

    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");

    exit(1);
}