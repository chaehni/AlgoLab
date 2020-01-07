#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef K::Point_2 Point;

// choose input type (input coefficients must fit)
typedef CGAL::Gmpq IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

struct Ast
{
	Point p;
	int d;
};

void testcase()
{
	int a, s, b, e;
	cin >> a >> s >> b >> e;

	vector<Ast> asts(a);
	vector<Point> shots(s);
	vector<Point> hunters(b);

	for (int i = 0; i < a; i++)
	{
		int x, y, d;
		cin >> x >> y >> d;
		Ast ast;
		ast.p = Point(x, y);
		ast.d = d;
		asts[i] = ast;
	}

	for (int i = 0; i < s; i++)
	{
		int x, y;
		cin >> x >> y;
		shots[i] = Point(x, y);
	}

	for (int i = 0; i < b; i++)
	{
		int x, y;
		cin >> x >> y;
		hunters[i] = Point(x, y);
	}

	Triangulation tri;
	tri.insert(hunters.begin(), hunters.end());

	// create linear program with amount of energy shot at every possible location as variables
	Program lp(CGAL::LARGER, true, 0, false, 0); // lower bound must at least be 0

	for (int i = 0; i < a; i++)
	{
		Ast ast = asts[i];

		// for every asteroid go trough all shot locations and compute the distance between asteroid and location
		for (int j = 0; j < s; j++)
		{
			Point shot = shots[j];
			K::FT dist = CGAL::squared_distance(ast.p, shot);

			lp.set_a(j, i, IT(1) / max(K::FT(1), dist));
			if (b > 0)
			{
				// if the asteroid is further away (or equal) from the shot location than the nearest hunter, it doesn't get any energy
				Point nearest = tri.nearest_vertex(shot)->point();
				if (dist >= CGAL::squared_distance(shot, nearest))
					lp.set_a(j, i, 0);
			}
		}

		// left side should be at least the density of the asteroid
		lp.set_b(i, ast.d);
	}

	// minimize on used energy
	for (int j = 0; j < s; j++)
		lp.set_c(j, 1);

	// solve the program, using ET as the exact type
	Solution sol = CGAL::solve_linear_program(lp, ET());
	assert(sol.solves_linear_program(lp));

	if (sol.is_infeasible() || sol.objective_value() > e)
		cout << "n\n";
	else
		cout << "y\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
