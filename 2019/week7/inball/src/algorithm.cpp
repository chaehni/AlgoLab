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

void run(int n)
{
    int d;
    cin >> d;

    // create an LP with Ax <= b, no bounds
    Program lp(CGAL::SMALLER, false, 0, false, 0);

    // set lower bound for r
    lp.set_l(d, true, 0);

    // set constraints
    for (int i = 0; i < n; i++)
    {
        int norm = 0;
        for (int j = 0; j < d; j++)
        {
            int coeff;
            cin >> coeff;
            norm += coeff * coeff;
            lp.set_a(j, i, coeff);
        }
        norm = sqrt(norm);
        lp.set_a(d, i, norm);
        int b;
        cin >> b;
        lp.set_b(i, b);
    }

    // set cost function: minimihze -radius
    lp.set_c(d, -1);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));

    if (s.is_infeasible())
        cout << "none\n";
    else if (s.is_unbounded())
        cout << "inf\n";
    else
        cout << floor(CGAL::to_double(-s.objective_value())) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}
