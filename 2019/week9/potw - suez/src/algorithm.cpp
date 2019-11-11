#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

using namespace std;

void run()
{
    int n, m, h, w;
    cin >> n >> m >> h >> w;

    vector<Point> newp(n);
    vector<Point> oldp(m);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        newp[i] = Point(x, y);
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        oldp[i] = Point(x, y);
    }

    // create an LP with Ax <= b, lower bound 1 (scaling factor)
    Program lp(CGAL::SMALLER, true, 1, false, 0);

    int cnt = 0;

    // add constraints for new pictures
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // find which of 2dx/w or 2dy/h is allows for a bigger zoom factor (we need to satisfy only one of the constraints)
            K::FT dx = abs(newp[i].x() - newp[j].x());
            K::FT dy = abs(newp[i].y() - newp[j].y());
            K::FT max_metric = max(2 * dx / w, 2 * dy / h);
            lp.set_a(i, cnt, 1);
            lp.set_a(j, cnt, 1);
            lp.set_b(cnt, max_metric);
            cnt++;
        }
    }

    // add constraints for old pictures
    for (int i = 0; i < n; i++)
    {
        K::FT min_max = INT64_MAX;
        for (int j = 0; j < m; j++)
        {
            // find out if 2dx/w or 2dy/h is the limiting factor
            K::FT dx = abs(newp[i].x() - oldp[j].x());
            K::FT dy = abs(newp[i].y() - oldp[j].y());
            K::FT max_metric = max((2 * dx / w) - 1, (2 * dy / h) - 1);
            min_max = min(min_max, max_metric);
        }
        lp.set_a(i, cnt, 1);
        lp.set_b(cnt, min_max);
        cnt++;
    }

    // set target cost
    for (int i = 0; i < n; i++)
        lp.set_c(i, -2 * (w + h));

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));

    cout << ceil(CGAL::to_double(-s.objective_value())) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << setprecision(0) << fixed;
    int t;
    cin >> t;
    while (t--)
        run();
}
