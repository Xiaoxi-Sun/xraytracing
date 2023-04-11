//Generate a soft ray tracing with opengl and glfw
#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0); //y in [-1,1], so it should add 1 and multiply 0.5 to convert t into [0, 1], so that t can be used as a interpolation parameter;
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	//linearly blends white and blue depending on the height of the y coordinate after scaling the ray direction to unit length
}

int main(){
	//Image
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//Camera
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point3 origin(0, 0, 0);
	vec3 horizontal(viewport_width, 0, 0);
	vec3 vertical(0, viewport_height, 0);
	point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//Render
	std::ofstream file("image.ppm");
	file << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i ++) {
			//Compute ray direction
			//screen coordinate project to viewport
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			
			vec3 ray_direction = lower_left_corner + u * horizontal + v * vertical - origin;
			ray r(origin, ray_direction);
			color pixel_color = ray_color(r);
			write_color(file, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}