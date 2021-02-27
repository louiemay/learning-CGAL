#include <iostream>
#include <fstream>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL\IO\read_off_points.h>
#include <CGAL\Polygon_mesh_processing\compute_normal.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3>                 Mesh;

typedef boost::graph_traits<Mesh>::vertex_descriptor        vertex_descriptor;
typedef boost::graph_traits<Mesh>::face_descriptor          face_descriptor;

typedef std::map<vertex_descriptor, Kernel::Vector_3>       Vertex_normal_map;
typedef std::map<face_descriptor, Kernel::Vector_3>         Face_normal_map;

int main()
{
	Mesh mesh;
	std::ifstream file("771.off");

	file >> mesh;

	std::cout << "Number of vertices: " << mesh.number_of_vertices() << std::endl;
	std::cout << "Number of facets: " << mesh.number_of_faces() << std::endl;

	Vertex_normal_map vnormal;
	Face_normal_map fnormal;

	CGAL::Polygon_mesh_processing::compute_normals(mesh, boost::make_assoc_property_map(vnormal),
		boost::make_assoc_property_map(fnormal));

	std::cout << "size of vnormal: " << vnormal.size() << std::endl;
	std::cout << "size of fnormal: " << fnormal.size() << std::endl;

	return true;
}


