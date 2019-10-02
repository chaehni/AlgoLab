#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run(int n, int m)
{
    // read nutrients
    vector<pair<int, int>> nut(n);
    for (int i = 0; i < n; i++)
    {
        int min, max;
        cin >> min >> max;
        nut[i] = make_pair(min, max);
    }

    // read foods
    vector<pair<int, vector<int>>> foods(m);
    for (int i = 0; i < m; i++)
    {
        int price;
        cin >> price;
        vector<int> amount(n);
        for (int j = 0; j < n; j++)
        {
            cin >> amount[j];
        }
        foods[i] = make_pair(price, amount);
    }

    // build linear program
    Program lp(CGAL::LARGER, true, 0, false, 0);

    // fill A matrix
    for (int j = 0; j < m; j++) // variables
    {
        for (int i = 0; i < n; i++) // constraints
        {
            lp.set_a(j, i, foods[j].second[i]);     // for min constraint
            lp.set_a(j, i + n, foods[j].second[i]); // for max constraint
        }
    }

    // fill b vector
    for (int i = 0; i < n; i++)
    {
        lp.set_b(i, nut[i].first);      // min of nutrient i
        lp.set_b(i + n, nut[i].second); // max of nutrient i
        lp.set_r(i + n, CGAL::SMALLER); // override comparison operator for maximum constraints
    }

    // crate target function
    for (int i = 0; i < m; i++)
    {
        lp.set_c(i, foods[i].first);
    }

    // minimize target by solving LP
    Solution s = CGAL::solve_quadratic_program(lp, ET());
    if (s.is_infeasible())
        cout << "No such diet."
             << "\n";
    else
        cout << floor(CGAL::to_double(s.objective_value())) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    while (true)
    {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        else
            run(n, m);
    }
}
