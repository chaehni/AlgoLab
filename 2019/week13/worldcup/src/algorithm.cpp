#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef double IT;
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

struct WH
{
    Point p;
    int s, a;
};

struct Stad
{
    Point p;
    int d, u;
};

struct Cont
{
    Point p;
    int r;
};

void run()
{
    int n, m, c;
    cin >> n >> m >> c;

    vector<WH> wh(n);
    vector<Stad> st(m);
    vector<Cont> cont;
    cont.reserve(100);
    vector<Point> locs;
    locs.reserve(n + m);
    vector<vector<IT>> rev(n, vector<IT>(m));

    for (int i = 0; i < n; i++)
    {
        int x, y, s, a;
        cin >> x >> y >> s >> a;
        Point p(x, y);
        locs.push_back(p);
        wh[i] = {p, s, a};
    }

    for (int i = 0; i < m; i++)
    {
        int x, y, d, u;
        cin >> x >> y >> d >> u;
        Point p(x, y);
        locs.push_back(p);
        st[i] = {p, d, u};
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> rev[i][j];

    // only at most 100 contour lines are relevant, find the ones with at least one warehouse/stadium insinde
    Triangulation t;
    t.insert(locs.begin(), locs.end());

    for (int i = 0; i < c; i++)
    {
        int x, y, r;
        cin >> x >> y >> r;
        Point p(x, y);
        Point nearest = t.nearest_vertex(p)->point();
        if (CGAL::squared_distance(nearest, p) < r * r)
            cont.push_back({p, r});
    }

    // account for loss because of contour lines
    for (int k = 0; k < cont.size(); k++)
    {
        for (int i = 0; i < n; i++)
        {
            bool w_in = CGAL::squared_distance(cont[k].p, wh[i].p) < cont[k].r * cont[k].r;
            for (int j = 0; j < m; j++)
            {
                bool s_in = CGAL::squared_distance(cont[k].p, st[j].p) < cont[k].r * cont[k].r;
                if (w_in != s_in)
                    rev[i][j] -= IT(1) / 100;
            }
        }
    }

    // LP
    Program lp(CGAL::SMALLER, true, 0, false, 0); // lower bound: cannot deliver less than 0 from any w to any s

    // not exceed supply of warehouses constraints
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            lp.set_a(i * m + j, cnt, 1);
        lp.set_b(cnt++, wh[i].s);
    }

    // match demand of stadium exactly constraints
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
            lp.set_a(i * m + j, cnt, 1);
        lp.set_b(cnt, st[j].d);
        lp.set_r(cnt++, CGAL::EQUAL);
    }

    // upper bound on absolute alcohol constraints
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
            lp.set_a(i * m + j, cnt, wh[i].a);
        lp.set_b(cnt++, st[j].u * 100);
    }

    // set objective function
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            lp.set_c(i * m + j, -rev[i][j]);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));

    // output
    if (s.is_infeasible())
        cout << "RIOT!\n";
    else
        cout << floor(CGAL::to_double(-s.objective_value())) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int t;
    cin >> t;
    while (t--)
        run();
}
