#include <iostream>
#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh_approximation/approximate_triangle_mesh.h>

#include <CGAL/boost/graph/iterator.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel   Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3>                   Mesh;
typedef boost::graph_traits<Mesh>::face_descriptor            face_descriptor;
typedef boost::graph_traits<Mesh>::vertex_descriptor          vertex_descriptor;
typedef Mesh::Property_map<face_descriptor, std::size_t>      Face_proxy_pmap;

typedef Mesh::Face_index    face_d;
typedef Mesh::Vertex_index  vertex_d;

namespace VSA = CGAL::Surface_mesh_approximation;
using namespace std;

int main()
{
	// read input surface triangle mesh
	Mesh mesh;
	std::ifstream file("data/bear.off");
	file >> mesh;

	/* output facet indices */
	/*BOOST_FOREACH(face_descriptor f, faces(mesh))
		std::cout << f.idx() << " ";*/

	/* calculate vertices around facets */
	/*BOOST_FOREACH(face_descriptor f, CGAL::faces(mesh)) {
		for (vertex_descriptor vd : CGAL::vertices_around_face(mesh.halfedge(f), mesh))
			std::cout << vd.idx() << " ";
		std::cout << std::endl;
	}*/

	/* calculate facets around facets */
	/*BOOST_FOREACH(face_descriptor f, CGAL::faces(mesh)) {
		for (face_descriptor fcirc : CGAL::faces_around_face(mesh.halfedge(f), mesh))
			std::cout << fcirc.idx() << " ";
		std::cout << std::endl;
	}*/

	//Mesh::Face_range::iterator fb, fe;
	//Mesh::Face_range r = mesh.faces();
	//fb = r.begin();
	//std::cout << fb->idx() << std::endl;    // 0
	//std::cout << (fb + 100)->idx() << std::endl;    // 100
	//std::cout << (fb + 200)->idx() << std::endl;    // 200

	/*BOOST_FOREACH(face_descriptor f, CGAL::faces(mesh)) {
		CGAL::Face_around_face_iterator<Mesh> vbegin, vend;
		boost::tie(vbegin, vend) = CGAL::faces_around_face(mesh.halfedge(f), mesh);
		std::cout << vbegin->idx();
		vbegin++;
		std::cout << vbegin->idx();
		vbegin++;
		std::cout << vbegin->idx() << std::endl;
	}*/

	/*BOOST_FOREACH(face_descriptor f, faces(mesh)) {
		for (vertex_descriptor vd : CGAL::vertices_around_face(mesh.halfedge(f), mesh))
			cout << mesh.point(vd).x() << " " << mesh.point(vd).y() << " " << mesh.point(vd).z() << " "
			<< vd.idx() << " ";
		cout << endl;
	}*/

	BOOST_FOREACH(face_descriptor f, CGAL::faces(mesh)) {
		CGAL::Vertex_around_face_iterator<Mesh> vbegin, vend;
		boost::tie(vbegin, vend) = CGAL::vertices_around_face(mesh.halfedge(f), mesh);
		cout << (vbegin++)->idx() << " " << (vbegin++)->idx() << " " << vbegin->idx() << endl;
	}


	return 0;

	// output indexed triangle mesh
	std::vector<Kernel::Point_3> anchors;
	std::vector<CGAL::cpp11::array<std::size_t, 3> > triangles; // triplets of indices

	// output face proxy index property map
	Face_proxy_pmap fpxmap =
		mesh.add_property_map<face_descriptor, std::size_t>("f:proxy_id", 0).first;

	// output planar proxies
	std::vector<Kernel::Vector_3> proxies;

	// free function interface with named parameters
	VSA::approximate_triangle_mesh(mesh,
		CGAL::parameters::min_error_drop(0.05). // seeding with minimum error drop
		number_of_iterations(40). // set number of clustering iterations after seeding
		subdivision_ratio(0.3). // set chord subdivision ratio threshold when meshing
		face_proxy_map(fpxmap). // get face partition map
		proxies(std::back_inserter(proxies)). // output proxies
		anchors(std::back_inserter(anchors)). // output anchor points
		triangles(std::back_inserter(triangles)).pca_plane(true)); // output indexed triangles

	for (auto item : proxies)
		std::cout << item << std::endl;


	return EXIT_SUCCESS;
}
