#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray {
public:
	point3 orig;
	vec3 dir;
public:
	ray() : orig(0, 0, 0), dir(0, 0, 0) {}
	ray(const point3& o, const vec3& d) : orig(o), dir(d) {}
	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }
	point3 at(double t) const {
		return orig + t * dir;
	}
};
#endif
