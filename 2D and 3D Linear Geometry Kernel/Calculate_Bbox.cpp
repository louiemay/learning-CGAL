#define CGAL_EIGEN3_ENABLED
#include <CGAL/Simple_cartesian.h>
#include <CGAL\Bbox_3.h>
#include <CGAL\bounding_box.h>
#include <iostream>
#include <vector>
using namespace std;
typedef CGAL::Simple_cartesian<double>     Kernel;
typedef Kernel::Point_3                    Point;
typedef Kernel::Vector_3                   Vector;
int main()
{
	vector<Point> points = { Point(1.0, 0.0, 0.0),
	Point(0.0, 1.0, 0.0),
	Point(0.0, 0.0, 1.0),
	Point(0.5, 0.0, 0.0),
	Point(0.0, 0.5, 2.0),
	Point(0.0, 0.0, -2.0) };
	auto bbox = CGAL::bounding_box(points.begin(), points.end());
	cout << "bbox:\n" << "xmax: " << bbox.xmax() << endl
		<< "xmin: " << bbox.xmin() << endl
		<< "ymax: " << bbox.ymax() << endl
		<< "ymin: " << bbox.ymin() << endl
		<< "zmax: " << bbox.zmax() << endl
		<< "zmin: " << bbox.zmin() << endl;

	cout << Vector(1.0, 2.0, 3.0)*Vector(4.0, 5.0, 6.0) << endl;
	
	return 0;
}

