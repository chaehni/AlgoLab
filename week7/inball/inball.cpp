#include <iostream>
#include <cassert>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

// choose exact rational type
#include <CGAL/Gmpq.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quotient<ET> SolT;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run(int n, int d)
{
    // set up quadratic program, do not restrict center of ball -> no boundaries
    Program lp(CGAL::SMALLER, false, 0, false, 0);

    // read inequalities
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < d; j++)
        {
            int a;
            cin >> a;
            sum += a * a;
            lp.set_a(j, i, a); // aj * cJ
        }

        int norm = sqrt(sum); // guaranteed to be an int
        lp.set_a(d, i, norm); // r * norm
        int b;
        cin >> b;
        lp.set_b(i, b); // <= b
    }

    // set objective
    lp.set_c(d, -1);      // dth varibale is radius, we want to maximize -> minimize negative of radius
    lp.set_l(d, true, 0); // enforce non-negative radius

    // solve the program
    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible())
        cout << "none";
    else if (s.is_unbounded())
        cout << "inf";
    else
        cout << floor(CGAL::to_double(-s.objective_value()));
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n, d;
    while (true)
    {
        cin >> n >> d;
        if (n == 0)
            break;
        run(n, d);
    }
}