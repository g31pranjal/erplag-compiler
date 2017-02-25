#include <stdio.h>

int main() {

	unsigned long long a, b, c;

	a = 8589934592;
	b = 262144 + 8589934592;

	printf("%lld\n", b);

	c = b & ~a;

	printf("%llu \n", c);

}