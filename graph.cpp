#include "graph_dfs.hpp"
#include "graph_toposort.hpp"
#include "graph_bfs.hpp"
#include <cstdio>
#include "edge_property_map.hpp"

class Printer
{
	public:
		void operator()(const graph::adj_matrix::vertex_t & v) const
		{
			printf(" %lu ", v);
		}
};

int main(int, char **)
{
	using namespace graph;

	Printer p;
	adj_matrix m(5);

	m.add(0, 1);
	m.add(0, 2);
	m.add(0, 3);
	m.add(1, 2);
	m.add(1, 3);
	m.add(2, 4);
	m.add(3, 4);

	printf("Breadth First Search: ");
	breadth_first_search(m, 0, p);
	printf("\n");

	printf("Depth First Search  : ");
	depth_first_search(m, 0, p);
	printf("\n");

	adj_matrix::vertex_list v;
	printf("Topological sorted  : ");
	if (topological_sort(m, v) == false) {
		printf("FAILED: circle detected");
	} else {
		for_each(v.begin(), v.end(), p);
	}
	printf("\n");

	typedef edge_property_map<float> EP;
	EP ep(m.size());
	ep.prop(0, 1) = 0.5;
	ep.prop(0, 2) = 0.5;
	ep.prop(0, 3) = 0.5;
	ep.prop(1, 2) = 0.5;
	ep.prop(1, 3) = 0.5;
	ep.prop(2, 4) = 0.5;
	ep.prop(3, 4) = 0.5;

	return 0;
}

