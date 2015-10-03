#include <stdio.h>

long long int fatorial(int n) {
	long long int res = 1;
	while(n > 0) res *= n--;
	return res;
}

int main() {
	long long int y = fatorial(9);
	for (int x = 0; x < y;)	{
		x++;
	}

	return 0;
}