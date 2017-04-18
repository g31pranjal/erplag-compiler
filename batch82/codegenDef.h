




typedef struct c_ln codeLine;

struct c_ln {
	char line[100];
	codeLine * next;
};

typedef struct c_bl codeBlock;

struct c_bl {
	codeLine * top;
	codeLine * bot;
};
