enum {
    ND_NUM = 256,
    ND_IDENT,
};

enum {
    TK_NUM = 256,
    TK_IDENT,
    TK_EOF,
};

typedef struct {
    int ty;
    int val;
    char *input;
} Token;

typedef struct Node {
    int ty;
    struct Node *lhs;
    struct Node *rhs;
    int val;
    char name;
} Node;

typedef struct {
    void **data;
    int capacity;
    int len;
} Vector;

typedef struct {
    Vector *keys;
    Vector *vals;
} Map;

extern Token tokens[100];

extern int pos;

extern Node *code[100];

void error(char *msg, char *input);

Node *new_node(int ty, Node *lhs, Node *rhs);

Node *new_node_num(int val);

int consume(int ty);

Node *add();

Node *mul();

Node *term();

Vector *new_vector();

void vec_push(Vector *vec, void *elem);

int expect(int line, int expected, int actual);

void test_vector();

void test_map();

void runtest();

void gen(Node *node);

void tokenize(char *p);

Node *assign();

Node *stmt();

void program();
