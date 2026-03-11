int main(int argc, char const* argv[]) {
	/*
	  +--+--+--+--+
	x |c0|c1|c2|c3|
	  +--+--+--+--+
	*/

	/*
	258
	8b + 2

	00000000 00000000 000000001 00000010
	0x00     0x00     0x01      0x02
	c3       c2       c1        c0

	Architecture is Big Endian		-> MSB (Most Significant Byte) goes first
	Architecture is Little Endian	-> LSB (Least Significant Byte) goes first

	x86 (and consequentially x64) are Little Endian

	   02 01 00 00
	  +--+--+--+--+
	x |c0|c1|c2|c3|
	  +--+--+--+--+
	*/

	// Casting
	/*
	int x = 258;
	int* p = &x;
	unsigned char c0, c1, c2, c3;

	unsigned char* q = (unsigned char*)p;

	c0 = *(q);
	c1 = *(q + 1);
	c2 = *(q + 2);
	c3 = *(q + 3);
	*/

	int x = 258;
	int* p = &x;
	unsigned char c0, c1, c2, c3;

	unsigned char* q = reinterpret_cast<unsigned char*>(p);

	c0 = *(q);		// q[0] = 0x02
	c1 = *(q + 1);	// q[1] = 0x01
	c2 = *(q + 2);	// q[2] = 0x00
	c3 = *(q + 3);	// q[3] = 0x00

	// Can't be done as y is const:
	/*
	const int y = 6;
	int* r = &y;
	*/
	// What can be done is this:
	const int y = 6;
	int* r = (int*)&y;
	*r = 7;
	x = 7;

	return 0;
}
