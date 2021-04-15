//	Global functions implemenation
size_t nearest_power(const size_t y)
{
	size_t x = y;
	if (x <= 1) return 1;
	size_t power = 2;
	x--;
	while (x >>= 1) power <<= 1;
	return power;
}