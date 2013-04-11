/**
 * Exponentiation
 */

#include <stdio.h>
#include <string.h>

typedef struct {
	int value[1024];	// 21.894 will be stored as: 4 9 8 1 2
	int len;			// 5
	int dot;			// 3
} num_t, *pnum_t;

void read_num(char str[], pnum_t n)
{
	const int len = strlen(str);
	n->len = 0;
	n->dot = 0;

	bool dotnotoccurred = true;
	int i = len - 1, j = 0;		// i to traverse original string, j to fill value field of struct num_t
	while (i >= 0) {
		if (str[i] == '.') {
			dotnotoccurred = false;
		} else {
			n->value[j++] = str[i] - '0';
			++n->len;
		}
		n->dot += dotnotoccurred;
		--i;
	}
	while (n->len > 0 && n->value[n->len-1] == 0) {
		--n->len;
	}
	if (dotnotoccurred == true) {
		n->dot = 0;
	} else if (n->len != 0) {
		int tailzeros = 0;
		while (tailzeros < n->dot && n->value[tailzeros] == 0) {
			++tailzeros;
		}
		if (tailzeros != 0) {
			for (i = tailzeros; i < n->len; ++i) {
				n->value[i-tailzeros] = n->value[i];
				n->value[i] = 0;
			}
			n->len -= tailzeros;
			n->dot -= tailzeros;
		}
	}
}

void dup(pnum_t a, pnum_t b)
{
	int i;
	for (i = 0; i < 1024; ++i) {
		b->value[i] = 0;
	}
	for (i = 0; i < a->len; ++i) {
		b->value[i] = a->value[i];
	}
	b->len = a->len;
	b->dot = a->dot;
}

void init(pnum_t n)
{
	int i;
	for (i = 0; i < 1024; ++i) {
		n->value[i] = 0;
	}
	n->len = 0;
	n->dot = 0;
}

void multiply(pnum_t a, pnum_t b, pnum_t c)
{
	int i, j;
	init(c);
	for (i = 0; i < b->len; ++i) {
		for (j = 0; j < a->len; ++j) {
			c->value[i+j] += a->value[j] * b->value[i];
			c->value[i+j+1] += c->value[i+j] / 10;
			c->value[i+j] %= 10;
		}
		c->value[i+j] += c->value[i+j-1] / 10;
		c->value[i+j-1] %= 10;
	}
	c->len = a->len + b->len + 1;
	while (c->len > 0 && c->value[c->len - 1] == 0) {
		c->len -= 1;
	}
	c->dot = a->dot + b->dot;
	int zeros = 0;
	while ((zeros < c->dot) && (c->value[zeros] == 0)) {
		++zeros;
	}
	if (zeros != 0) {
		for (i = zeros; i < c->len; ++i) {
			c->value[i - zeros] = c->value[i];
			c->value[i] = 0;
		}
		c->len -= zeros;
		c->dot -= zeros;
	}
}

int main()
{
	char value[10];
	
	num_t num[3];
	int n;
	bool current = true;
	while (scanf("%s%d", value, &n) != EOF) {
		if (n == 0) {
			printf("1\n");
			continue;
		}
		read_num(value, &num[2]);
		dup(num + 2, num + 1);
		dup(num + 2, num + 0);
		while (n > 1) {
			current = !current;
			multiply(num + 2, num + !current, num + current);
			--n;
		}
		int i = num[current].len - 1;
		while (i >= num[current].dot) {
			printf("%d", num[current].value[i]);
			--i;
		}
		if (num[current].len == 0) {
			printf("0");
		} else if (num[current].dot != 0) {
			printf(".");
			int j = num[current].dot - i - 1;
			while (j != 0) {
				printf("0");
				--j;
			}
			while (i >= 0) {
				printf("%d", num[current].value[i]);
				--i;
			}
		}
		printf("\n");
	}
	/*
	scanf("%s", value);
	read_num(value, &a);
	scanf("%s", value);
	read_num(value, &b);
	multiply(&a, &b, &c);
	*/
	
	return 0;
}
