#include <iostream>
#include "debug2.cpp"

int main() {
	int x = 5;
	int* t = new int[x];
	t[1] = 5;
	t[0] = function(t[1]);
	return 0;
}
