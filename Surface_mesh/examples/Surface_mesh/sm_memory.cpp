#include <vector>

#include <boost/assign.hpp>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>

typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Surface_mesh<typename K::Point_3> Mesh;

int main()
{
  Mesh m;

  Mesh::Vertex_descriptor u;
  for(unsigned int i=0; i < 5; ++i){
    Mesh::Vertex_descriptor v = m.add_vertex(K::Point_3(0,0,i+1));  
    if(i==2) u=v;
  }

  m.remove_vertex(u);

  std::cout << "After insertion of 5 vertices and removal of the 3. vertex\n"
            << "# used vertices / total vertices = " 
            << m.num_vertices() - m.num_removed_vertices()
            << " / " << m.num_vertices() << std::endl;
  
  std::cout << "Iterate over used vertices\n";
  {
    Mesh::Vertex_iterator vbegin, vend;
    for(boost::tie(vbegin, vend) = m.vertices(); vbegin != vend; ++vbegin) {
      std::cout << m.point(*vbegin) << std::endl;
    }
  }
  
  // The status of being used or removed is stored in a property map
  CGAL::Property_map<Mesh::Vertex_descriptor,bool> removed
    = m.get_property_map<Mesh::Vertex_descriptor,bool>("v:removed");
 
  
  std::cout << "\nIterate over used and deleted vertices\n"
            << "# used vertices / total vertices = " 
            << m.num_vertices() - m.num_removed_vertices()
            << " / " << m.num_vertices() << std::endl;
    {
    unsigned int i = 0, end = m.vertices().second->idx();
    for( ; i < end; ++i) {
      Mesh::Vertex_descriptor vh(i);
      assert(m.is_removed(vh) == removed[vh]);
      std::cout << m.point(vh) << ((m.is_removed(vh)) ? "  R\n" : "\n");
    }
  }

  m.collect_garbage();

  std::cout << "\nAfter garbage collection\n"
            << "# used vertices / total vertices = "
            << m.num_vertices() - m.num_removed_vertices()
            << " / " << m.num_vertices() << std::endl;
  
 {
    unsigned int i = 0, end = m.vertices().second->idx();
    for( ; i < end; ++i) {
      Mesh::Vertex_descriptor vh(i);
      std::cout << m.point(vh) << ((m.is_removed(vh)) ? "  R\n" : "\n");
    }
  }

  return 0;
}
