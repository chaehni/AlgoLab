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

void run(int p)
{
    int a, b;
    cin >> a >> b;

    if (p == 1)
    {
        // create an LP with Ax <= b, lower bound 0 and no upper bounds
        Program lp(CGAL::SMALLER, true, 0, false, 0);

        // set the coefficients of a and b
        const int X = 0;
        const int Y = 1;

        lp.set_a(X, 0, 1);
        lp.set_a(Y, 0, 1);
        lp.set_b(0, 4);

        lp.set_a(X, 1, 4);
        lp.set_a(Y, 1, 2);
        lp.set_b(1, a * b);

        lp.set_a(X, 2, -1);
        lp.set_a(Y, 2, 1);
        lp.set_b(2, 1);

        // objective: we want to maxizmize -> minimize negative
        lp.set_c(Y, -b);
        lp.set_c(X, a);

        // solve the program, using ET as the exact type
        Solution s = CGAL::solve_linear_program(lp, ET());
        assert(s.solves_linear_program(lp));

        if (s.is_infeasible())
            cout << "no\n";
        else if (s.is_unbounded())
            cout << "unbounded\n";
        else
            cout << floor(CGAL::to_double(-s.objective_value())) << "\n";
    }
    else
    {
        // create an LP with Ax >= b, lower bound 0 and no upper bounds
        Program lp(CGAL::LARGER, false, 0, true, 0);

        // set the coefficients of A and b
        const int X = 0;
        const int Y = 1;
        const int Z = 2;

        lp.set_a(X, 0, 1);
        lp.set_a(Y, 0, 1);
        lp.set_a(Z, 0, 0);
        lp.set_b(0, -4);

        lp.set_a(X, 1, 4);
        lp.set_a(Y, 1, 2);
        lp.set_a(Z, 1, 1);
        lp.set_b(1, -a * b);

        lp.set_a(X, 2, -1);
        lp.set_a(Y, 2, 1);
        lp.set_a(Z, 2, 0);
        lp.set_b(2, -1);

        // objective
        lp.set_c(X, a);
        lp.set_c(Y, b);
        lp.set_c(Z, 1);

        // solve the program, using ET as the exact type
        Solution s = CGAL::solve_linear_program(lp, ET());
        assert(s.solves_linear_program(lp));

        if (s.is_infeasible())
            cout << "no\n";
        else if (s.is_unbounded())
            cout << "unbounded\n";
        else
            cout << ceil(CGAL::to_double(s.objective_value())) << "\n";
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int p;
        cin >> p;
        if (p == 0)
            break;
        run(p);
    }
}
