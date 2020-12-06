// Andrea Gray
// Code adapted from shifty.cpp (c) Sam Siewert

#include <iomanip>
#include <iostream>
using namespace std;

class base10 {
public:
	float numberTen;
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

int main(void) {

	// These base built-in types can use the left-shift and right-shift operators << and >>
	// unsigned int x=1000, y=100, z=10;
	// unsigned int a, b, c;

	// C++ does not definte use of shift operators for float,
	// so no built-in definition exists, you must define
	// float x=1000.0, y=100.0, z=10.0;

	float a, b, c;

	base10 x, y, z;

	x.numberTen = 1000.0;
	y.numberTen = 100.0;
	z.numberTen = 10.0;
	
	cout << std::oct << "As Initialized: " << "x=" << x.numberTen << ", y=" << y.numberTen << ", z=" << z.numberTen << "\n";
	cout << std::dec << "As Initialized: " << "x=" << x.numberTen << ", y=" << y.numberTen << ", z=" << z.numberTen << "\n";
	cout << std::hex << "As Initialized: " << "x=" << x.numberTen << ", y=" << y.numberTen << ", z=" << z.numberTen << "\n";

	// example of direct access to public data
	a = x.numberTen, b = y.numberTen, c = z.numberTen;

	// These definitions use the new class/object and overloaded operation for right-shift
	a = x >> 1;
	b = y >> 1;
	c = z >> 1;
	
	cout << std::oct << "Right shifted 1 Octal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";
	cout << std::dec << "Right shifted 1 Decimal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";
	cout << std::hex << "Right shifted 1 Hexidecimal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";

	a = x << 1;
	b = y << 1;
	c = z << 1;

	cout << std::oct << "Left shifted 1 Octal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";
	cout << std::dec << "Left shifted 1 Decimal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";
	cout << std::hex << "Left shifted 1 Hexidecimal: " << "a=" << a << ", b=" << b << ", c=" << c << "\n";

	return 0;
}

static float shifty;

float operator >>(const base10& x, const unsigned shamt) {
	unsigned int idx;
	for (idx = 0; idx < shamt; idx++){
		shifty = x.numberTen / 10;
	}
	return shifty;
}

float operator <<(const base10& x, const unsigned shamt) {
	unsigned int idx;
	for (idx = 0; idx < shamt; idx++) {
		shifty = x.numberTen * 10;
	}
	return shifty;
}

