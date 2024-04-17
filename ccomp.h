// トークンの種類
typedef enum
{
    TK_RESERVED, // 記号
    TK_IDENT,    // 識別子
    TK_NUM,      // 整数トークン
    TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;
typedef struct Token Token;
struct Token;
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool at_eof();
Token *tokenize(char *p);

typedef enum
{
    ND_EQUAL,     // ==
    ND_NEQUAL,    // !=
    ND_LESS,      // <
    ND_LESSEQUAL, // <=
    ND_ADD,       // +
    ND_SUB,       // -
    ND_MUL,       // *
    ND_DIV,       // /
    ND_ASSIGN,    // =
    ND_LVAR,      // ローカル変数
    ND_NUM,       // 整数
} NodeKind;
typedef struct Node Node;
struct Node
{
    NodeKind kind; // ノードの型
    Node *next;    // 次に処理する式(NULLで終了)
    Node *lhs;     // 子(左)
    Node *rhs;     // 子(右)
    int val;       // kindがND_NUMの場合のみ使う
    int offset;    // kindがND_LVARの場合のみ使う
};
Node *stmt();

extern Token *token;
extern char *user_input;

void gen(Node *node);