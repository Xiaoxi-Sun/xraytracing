#ifndef UTILS_H
#define UTILS_H

#include<cmath>
#include<limits>
#include<memory>
#include<cstdlib>


//Usings
using std::shared_ptr;
using std::make_shared;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility Function
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	//Return a random real in [0,1)
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	return min + random_double() * (max - min);
}

inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

//Common Headers
#include "ray.h"
#include "vec3.h"
#endif // !UTILS_H

