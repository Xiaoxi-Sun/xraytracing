#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	point3 center;
	double radius;
public:
	sphere() : center(0, 0, 0), radius(0) {};
	sphere(point3 _center, double _radius) : center(_center), radius(_radius) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 v = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double half_b = dot(v, r.direction());
	double c = dot(v, v) - radius * radius;
	double discriminat = half_b * half_b - a * c;
	if (discriminat < 0.0) return false;
	double root = (-half_b - sqrt(discriminat)) / a;
	if (root < t_min || root > t_max) {
		root = (-half_b + sqrt(discriminat)) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_nomal(r, outward_normal);
	return true;
}

#endif // !SPHERE_H

