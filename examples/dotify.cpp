#include <iostream>
#include <graph/dot.hpp>
#include <graph/adjmatrix.hpp>

int main(int, char **)
{
	graph::adjmatrix m{5, {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {1, 4}, {3, 4}}};

	std::cout << graph::dot(m);
	return 0;
}
