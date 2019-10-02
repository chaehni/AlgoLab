#include <iostream>
#include <vector>
#include <stack>

// Triangulation includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

// LP includes
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// Triangulation typedefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int, int>, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex;
typedef K::Point_2 Point;

// LP typedefs
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run()
{
    int a, s, b;
    cin >> a >> s >> b;
    int e;
    cin >> e;
    K::FT total_energy = e;

    vector<pair<Point, K::FT>> asteroids(a);
    for (int i = 0; i < a; i++)
    {
        int x, y, d;
        cin >> x >> y >> d;
        asteroids[i] = {Point(x, y), d};
    }

    vector<Point> shots(s);
    for (int i = 0; i < s; i++)
    {
        int x, y;
        cin >> x >> y;
        shots[i] = Point(x, y);
    }

    vector<Point> hunter(b);
    for (int i = 0; i < b; i++)
    {
        int x, y;
        cin >> x >> y;
        hunter[i] = Point(x, y);
    }

    // create triangulation from bounty hunters, this lets us find the closest hunter for every position
    // this way we can make sure to not get discovered
    Triangulation t;
    t.insert(hunter.begin(), hunter.end());

    Program lp(CGAL::LARGER, true, 0, false, 0); // cannot use negative energy

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < s; j++)
        {
            K::FT dist_asteroid = CGAL::squared_distance(asteroids[i].first, shots[j]);
            ET fraction = dist_asteroid < 1 ? 1 : ET(1) / dist_asteroid;
            if (b == 0) // no bounty hunters
            {
                lp.set_a(j, i, fraction);
            }
            else
            {
                // if there are bounty hunters our radius is limited by hunter nearest to the shot center
                Point nearest = t.nearest_vertex(shots[j])->point();
                K::FT dist_hunter = CGAL::squared_distance(nearest, shots[j]);
                lp.set_a(j, i, dist_asteroid < dist_hunter ? fraction : 0);
            }
        }
        lp.set_b(i, asteroids[i].second);
    }

    for (int i = 0; i < s; i++)
        lp.set_c(i, 1);

    Solution sol = CGAL::solve_linear_program(lp, ET());

    if (sol.is_infeasible() || sol.objective_value() > total_energy)
        cout << "n";
    else
        cout << "y";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}