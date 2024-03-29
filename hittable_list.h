#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "utils.h"
#include<memory>
#include<vector>


class hittable_list : public hittable {
public:
	std::vector<shared_ptr<hittable>> objects;
public:
	hittable_list(){}
	hittable_list(shared_ptr<hittable> object) {
		add(object);
	}

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	void clear() {
		objects.clear();
	}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (const auto& object : objects) {
		if (object->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t; //Once the variable closest_so_far is modified, it means that current intersection's t must less than closest_so_far,so it should be update;
			rec = temp_rec;
		}
	}
	return hit_anything;
}


#endif // !HITTABLE_LIST_H

