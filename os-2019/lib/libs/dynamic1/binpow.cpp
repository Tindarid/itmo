#include "binpow.h"

long long binpow::count(int number, int st) {
	long long res = 1;
	while (st) {
		if (st & 1) {
			res *= number;
        }
		number *= number;
		st >>= 1;
	}
	return res;
}

