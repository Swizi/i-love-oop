void swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}