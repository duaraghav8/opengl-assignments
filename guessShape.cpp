#include <cmath>
#include <iostream>

#define SHAPE_RECT 1
#define SHAPE_SQUARE 2

using namespace std;

struct Coords {
	int x, y;
};

double getDistance (Coords a, Coords b) {
	return sqrt (pow ((b.y - a.y), 2) + pow ((b.x - a.x), 2));
}

bool isInCloseProximity (double d1, double d2) {
	return abs (d1 - d2) <= 10.0;
}

void getShape (Coords a, Coords b, Coords c, Coords d) {
	double ab = getDistance (a, b), ac = getDistance (a, c), ad = getDistance (a, d);
	double bc = getDistance (b, c), bd = getDistance (b, d);
	double cd = getDistance (c, d);

	if (isInCloseProximity (ab, cd) && isInCloseProximity (bc, ad)) {
		if (isInCloseProximity (ab, bc)) {
			cout << "SHAPE IS A POTENTIAL SQUARE" << endl;
		} else {
			cout << "SHAPE IS A POTENTIAL RECTANGLE" << endl;
		}
	} else {
		cout << "DOESN'T SEEM LIKE A VALID SHAPE" << endl;
	}
}

int main () {
	return 0;
}
