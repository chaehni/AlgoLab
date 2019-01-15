#include <iostream>
#include <cassert>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

using namespace std;

// choose exact integral type
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct Point
{
    int x, y;
};

void run()
{
    int n, m, h, w;
    cin >> n >> m >> h >> w;

    vector<Point> nails(n);
    vector<Point> posters(m);

    // read nails
    for (int i = 0; i < n; i++)
        cin >> nails[i].x >> nails[i].y;

    // read posters
    for (int i = 0; i < m; i++)
        cin >> posters[i].x >> posters[i].y;

    // set up linear program, scaling factor must be at least 1 -> lower bound is 1
    Program lp(CGAL::SMALLER, true, 1, false, 0);
    int id = 0;

    // add constraints between new and old posters
    for (int i = 0; i < n; i++)
    {
        Point newp = nails[i];
        ET most_restrictive = INT32_MAX;
        // for a given new poster check all old and add constraint for most restrictive
        for (int j = 0; j < m; j++)
        {
            Point oldp = posters[j];
            ET dx = abs(newp.x - oldp.x);
            ET dy = abs(newp.y - oldp.y);
            ET limit = 2 * max(dx / w, dy / h) - 1;
            most_restrictive = min(most_restrictive, limit);
        }
        // constraint for closest poster
        lp.set_a(i, id, 1);
        lp.set_b(id, most_restrictive);
        id++;
    }

    // add constraints between new posters
    for (int i = 0; i < n; i++)
    {
        Point p1 = nails[i];
        for (int j = i + 1; j < n; j++)
        {
            Point p2 = nails[j];
            ET dx = abs(p1.x - p2.x);
            ET dy = abs(p1.y - p2.y);
            ET limit = 2 * max(dx / w, dy / h);
            lp.set_a(i, id, 1);
            lp.set_a(j, id, 1);
            lp.set_b(id, limit);
            id++;
        }
    }

    // objective function, minimize negative of objective
    for (int i = 0; i < n; i++)
        lp.set_c(i, -2 * (w + h));

    // Call Solver
    Solution s = CGAL::solve_linear_program(lp, ET());
    cout << ceil(CGAL::to_double(-s.objective_value())) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << setprecision(0) << fixed;
    int n;
    cin >> n;
    while (n--)
        run();
}