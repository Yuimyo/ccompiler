#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccomp.h"

void gen_lvar(Node *node)
{
    if (node->kind != ND_LVAR)
    {
        error("代入の左辺値が変数ではありません");
    }

    printf("  mov rax, rbp\n");
    printf("  sub rax, %d\n", node->offset);
    printf("  push rax\n");
}

int incr_if = 0;
int incr_while = 0;
int incr_for = 0;

void gen(Node *node)
{
    switch (node->kind)
    {
    case ND_NUM:
        printf("  push %d\n", node->val);
        return;
    case ND_LVAR:
        gen_lvar(node);
        printf("  pop rax\n");
        printf("  mov rax, [rax]\n");
        printf("  push rax\n");
        return;
    case ND_ASSIGN:
        gen_lvar(node->lhs);
        gen(node->rhs);

        printf("  pop rdi\n");
        printf("  pop rax\n");
        printf("  mov [rax], rdi\n");
        printf("  push rdi\n");
        return;
    case ND_RETURN:
        gen(node->lhs);

        printf("  pop rax\n");
        printf("  mov rsp, rbp\n");
        printf("  pop rbp\n");

        printf("  ret\n");
        return;
    case ND_IF:
        gen(node->lhs);

        printf("  pop rax\n");
        printf("  cmp rax, 0\n");

        Node *iffolk = node->rhs;
        if (!(iffolk->rhs))
        {
            printf("  je  .Lend%d\n", incr_if);
            gen(iffolk->lhs);
            printf(".Lend%d:\n", incr_if);
        }
        else
        {
            printf("  je  .Lelse%d\n", incr_if);
            gen(iffolk->lhs);
            printf("  jmp .Lend%d\n", incr_if);
            printf(".Lelse%d:\n", incr_if);
            gen(iffolk->rhs);
            printf(".Lend%d:\n", incr_if);
        }

        incr_if++;
        return;
    case ND_WHILE:
        printf(".LWbegin%d:\n", incr_while);

        gen(node->lhs);
        printf("  pop rax\n");
        printf("  cmp rax, 0\n");
        printf("  je  .LWend%d\n", incr_while);
        gen(node->rhs);
        printf("  jmp .LWbegin%d\n", incr_while);

        printf(".LWend%d:\n", incr_while);
        incr_while++;
        return;
    case ND_FOR:
        Node *forfolk = node->lhs;

        gen(forfolk->lhs);
        printf(".LFbegin%d:\n", incr_for);

        gen(forfolk->mhs);
        printf("  pop rax\n");
        printf("  cmp rax, 0\n");
        printf("  je  .LFend%d\n", incr_for);
        gen(node->rhs);
        gen(forfolk->rhs);

        printf("  jmp .LFbegin%d\n", incr_for);

        printf(".LFend%d:\n", incr_for);
        incr_for++;
        return;
    }

    gen(node->lhs);
    gen(node->rhs);

    printf("  pop rdi\n");
    printf("  pop rax\n");

    switch (node->kind)
    {
    case ND_ADD:
        printf("  add rax, rdi\n");
        break;
    case ND_SUB:
        printf("  sub rax, rdi\n");
        break;
    case ND_MUL:
        printf("  imul rax, rdi\n");
        break;
    case ND_DIV:
        printf("  cqo\n");
        printf("  idiv rdi\n");
        break;
    case ND_EQUAL:
        printf("  cmp rax, rdi\n");
        printf("  sete al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_NEQUAL:
        printf("  cmp rax, rdi\n");
        printf("  setne al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_LESS:
        printf("  cmp rax, rdi\n");
        printf("  setl al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_LESSEQUAL:
        printf("  cmp rax, rdi\n");
        printf("  setle al\n");
        printf("  movzb rax, al\n");
        break;
    }

    printf("  push rax\n");
}