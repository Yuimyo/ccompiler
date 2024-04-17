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
bool consume(char *op);
void expect(char *op);
Token *consume_ident();
int expect_number();
bool at_eof();
bool startswith(char *p, char *q);
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
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
Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

extern Token *token;
extern char *user_input;

void gen(Node *node);
