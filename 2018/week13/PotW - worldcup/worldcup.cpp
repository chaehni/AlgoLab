#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct whouse
{
    K::Point_2 p;
    int s, a;
};

struct stad
{
    K::Point_2 p;
    int d, u;
};

struct contl
{
    K::Point_2 p;
    int r;
};

void run()
{
    int n, m, c;
    cin >> n >> m >> c;

    vector<K::Point_2> combined(n + m);

    // read warehouses
    vector<whouse> whouses(n);
    for (int i = 0; i < n; i++)
    {
        cin >> whouses[i].p;
        cin >> whouses[i].s;
        cin >> whouses[i].a;
        combined[i] = whouses[i].p;
    }

    // read stadiums
    vector<stad> stads(m);
    for (int i = 0; i < m; i++)
    {
        cin >> stads[i].p;
        cin >> stads[i].d;
        cin >> stads[i].u;
        combined[n + i] = stads[i].p;
    }

    // read revenues
    vector<vector<ET>> revs(n, vector<ET>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> revs[i][j];

    // reduce the number of contour lines to be checked later, based on the constraint that there are at most 100 contour lines that contain warehouses/stadiums

    /* CGAL PART */

    Triangulation t;
    t.insert(combined.begin(), combined.end());

    vector<contl> contls;
    for (int i = 0; i < c; i++)
    {
        K::Point_2 p;
        int r;
        cin >> p >> r;

        // check if this contour line contains any warehouses/stadiums
        K::Point_2 nearest = t.nearest_vertex(p)->point();
        if (CGAL::square(r) > CGAL::squared_distance(nearest, p))
            contls.push_back({p, r * r});
    }

    for (int k = 0; k < contls.size(); k++)
    {
        for (int i = 0; i < n; i++)
        {
            bool wh_in = CGAL::squared_distance(contls[k].p, whouses[i].p) < contls[k].r;
            for (int j = 0; j < m; j++)
            {
                bool stad_in = CGAL::squared_distance(contls[k].p, stads[j].p) < contls[k].r;
                if (wh_in != stad_in) // they have to be either both in or both out of the circle to not cost anything
                    revs[i][j] -= ET(1) / 100;
            }
        }
    }

    /* LP PART */

    // variables are (w,s)-pairs with index w*m+s

    Program lp(CGAL::SMALLER, true, 0, false, 0); // cannot ship negative amount of beer

    // exact demand constraint
    int cnt = 0;
    for (int s = 0; s < m; s++)
    {
        for (int w = 0; w < n; w++)
            lp.set_a(w * m + s, cnt, 1);

        lp.set_b(cnt, stads[s].d);
        lp.set_r(cnt, CGAL::EQUAL);
        cnt++;
    }

    // max alc constraint
    for (int s = 0; s < m; s++)
    {
        for (int w = 0; w < n; w++)
            lp.set_a(w * m + s, cnt, ET(whouses[w].a) / 100); // alcohol is given as percentage

        lp.set_b(cnt, stads[s].u);
        cnt++;
    }

    // supply constraint
    for (int w = 0; w < n; w++)
    {
        for (int s = 0; s < m; s++)
            lp.set_a(w * m + s, cnt, 1);

        lp.set_b(cnt, whouses[w].s);
        cnt++;
    }

    // objective: maximize profit -> minimize loss
    for (int w = 0; w < n; w++)
        for (int s = 0; s < m; s++)
            lp.set_c(w * m + s, -revs[w][s]);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible())
        cout << "RIOT!";
    else
        cout << floor(CGAL::to_double(-s.objective_value()));
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int n;
    cin >> n;
    while (n--)
        run();
}