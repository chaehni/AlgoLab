#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// choose input type (input coefficients must fit)
typedef CGAL::Gmpq IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run()
{
    int xs, xy, n;
    cin >> xs >> xy >> n;

    Program lp(CGAL::SMALLER, false, 0, false, 0);

    // read legions and add to LP
    for (int i = 0; i < n; i++)
    {
        long a, b, c;
        int v;
        cin >> a >> b >> c >> v;
        int s = sqrt(a * a + b * b) * v;

        // find out on what side of line they start
        int sign_pos = (a * xs + b * xy + c) >= 0;
        lp.set_a(0, i, IT(a) / s);
        lp.set_a(1, i, IT(b) / s);
        lp.set_a(2, i, sign_pos ? -1 : 1);
        lp.set_b(i, IT(-c) / s);
        if (sign_pos)
            lp.set_r(i, CGAL::LARGER);
    }

    // maximize radius
    lp.set_c(2, -1);

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));

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
