#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run(int n, int m)
{
    vector<pair<int, int>> nut(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nut[i].first;
        cin >> nut[i].second;
    }

    vector<int> price(m);
    vector<vector<int>> foods(m, vector<int>(n));
    for (int i = 0; i < m; i++)
    {
        cin >> price[i];
        for (int j = 0; j < n; j++)
            cin >> foods[i][j];
    }

    // create an LP with Ax <= b, lower bound 0 since one cannot eat less than nothing
    Program lp(CGAL::LARGER, true, 0, false, 0);

    // add constraints
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // min constraint
            lp.set_a(j, i, foods[j][i]);
            lp.set_b(i, nut[i].first);

            // max constraint
            lp.set_a(j, n + i, foods[j][i]);
            lp.set_r(n + i, CGAL::SMALLER);
            lp.set_b(n + i, nut[i].second);
        }
    }

    // set objective
    for (int j = 0; j < m; j++)
        lp.set_c(j, price[j]);

    Solution s = CGAL::solve_linear_program(lp, ET());

    if (s.is_infeasible())
        cout << "No such diet.\n";
    else
        cout << floor(CGAL::to_double(s.objective_value())) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        run(n, m);
    }
}
