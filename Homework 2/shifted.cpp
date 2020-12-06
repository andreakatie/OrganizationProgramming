// Andrea Gray
// Code adapted from shifty.cpp (c) Sam Siewert

#include <iostream>
using namespace std;

class base10 {
public:
	float numberTen;
};

class base08 {
public:
	float numberEight;
};

class base16 {
public:
	float numberSixteen;
};

// Note that operator overloading is intended to work with a
// class/object definition, but can involve base types
// as formal parameters (e.g. shift amount) and the return value which
// is a simple float rather than an object.
//
// It makes sense mathematically if shift operations applied to floating
// point would shift the base 10 decimal point
// to the left or right - i.e. either divide by 10 or multiply by 10, much
// like binary operators divide by 2 or multiply by
// 2 using bit-shifting operations, so, here we define this for our base10 class.
//

float operator >>(const base10& x, const unsigned shamt);
float operator <<(const base10& x, const unsigned shamt);
float operator >>(const base16& x, const unsigned shamt);
float operator <<(const base16& x, const unsigned shamt);
float operator >>(const base08& x, const unsigned shamt);
float operator <<(const base08& x, const unsigned shamt);

int main(void) {

	// These base built-in types can use the left-shift and right-shift operators << and >>
	// unsigned int x=1000, y=100, z=10;
	// unsigned int a, b, c;

	// C++ does not definte use of shift operators for float,
	// so no built-in definition exists, you must define
	// float x=1000.0, y=100.0, z=10.0;

	float a, b, c;
	float d, e, f;
	float g, h, i;

	base08 r, s, t;
	base10 x, y, z;
	base16 u, v, w;
	
	r.numberEight = 0200;
	s.numberEight = 020;
	t.numberEight = 02;

	x.numberTen = 1000.0;
	y.numberTen = 100.0;
	z.numberTen = 10.0;
	
	u.numberSixteen = 0x200;
	v.numberSixteen = 0x20;
	w.numberSixteen = 0x2;
	
	cout << "As Initialized: " << "r=" << r.numberEight << ", s=" << s.numberEight << ", t=" << t.numberEight << "\n";
	cout << "As Initialized: " << "x=" << x.numberTen << ", y=" << y.numberTen << ", z=" << z.numberTen << "\n";
	cout << "As Initialized: " << "u=" << u.numberSixteen << ", v=" << v.numberSixteen << ", w=" << w.numberSixteen << "\n";

	// example of direct access to public data
	g = r.numberEight, h = s.numberEight, i = t.numberEight;
	a = x.numberTen, b = y.numberTen, c = z.numberTen;
	d = u.numberSixteen, e = v.numberSixteen, f = w.numberSixteen;

	// These definitions use the new class/object and overloaded operation for right-shift
	g = r >> 1;
	h = s >> 1;
	i = t >> 1;
	
	a = x >> 1;
	b = y >> 1;
	c = z >> 1;

	d = u >> 1;
	e = v >> 1;
	f = w >> 1;
	
	cout << "Right shifted 1 octal: " << "g=" << g << ", h=" << h << ", i=" << i << "\n";
	cout << "Right shifted 1 Decimal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";
	cout << "Right shifted 1 Hex: " << "d=" << d << ", e=" << e << ", f=" << f << "\n";

	g = r << 1;
	h = s << 1;
	i = t << 1;
	
	a = x << 1;
	b = y << 1;
	c = z << 1;

	d = u << 1;
	e = v << 1;
	f = w << 1;

	cout << "Left shifted 1 Octal: " << "g=" << g << ", h=" << h << ", i=" << i << "\n";
	cout << "Left shifted 1 Decimal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";
	cout << "Left shifted 1 Hex: " << "d=" << d << ", e=" << e << ", f=" << f << "\n";

	return 0;
}

static float shiftx;
static float shifty;
static float shiftz;

float operator <<(const base08& x, const unsigned shamt) {
	unsigned int idz;
	for (idz = 0; idz < shamt; idz++) {
		shiftz = x.numberEight * 8;
	}
	return shiftz;
}

float operator >>(const base08& x, const unsigned shamt) {
	unsigned int idz;
	for (idz = 0; idz < shamt; idz++) {
		shiftz = x.numberEight / 8;
	}
	return shiftz;
}

float operator >>(const base10& x, const unsigned shamt) {
	unsigned int idx;
	for (idx = 0; idx < shamt; idx++){
		shiftx = x.numberTen / 10;
	}
	return shiftx;
}

float operator <<(const base10& x, const unsigned shamt) {
	unsigned int idx;
	for (idx = 0; idx < shamt; idx++) {
		shiftx = x.numberTen * 10;
	}
	return shiftx;
}

float operator >>(const base16& x, const unsigned shamt) {
	unsigned int idy;
	for (idy = 0; idy < shamt; idy++) {
		shifty = x.numberSixteen / 16;
	}
	return shifty;
}

float operator <<(const base16& x, const unsigned shamt) {
	unsigned int idy;
	for (idy = 0; idy < shamt; idy++) {
		shifty = x.numberSixteen * 16;
	}
	return shifty;
}
