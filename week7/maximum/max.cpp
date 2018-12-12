#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void type_1(int a, int b){
    // by default, we have a nonnegative LP with Ax <= b
    Program lp (CGAL::SMALLER, true, 0, false, 0);

    // now set the non-default entries
    const int X = 0; 
    const int Y = 1;
    lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);   //  x + y  <= 4
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);  // 4x + 2y <= a*b
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1) ;  // -x + y  <= 1

    // we want to maximize b*y - a*x^2 => minimize -(b*y - a*x^2)
    lp.set_d(X, X, 2*a);      // a*x^2
    lp.set_c(Y, -b);        // -b*y

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_quadratic_program(lp, ET());
    if (s.is_infeasible())
        cout << "no" << "\n";
    else if (s.is_unbounded())
        cout << "unbounded" << "\n";
    else
        cout << floor(-1 * CGAL::to_double(s.objective_value())) << "\n";
}

void type_2(int a, int b){
    // by default, we have a nonnegative LP with Ax >= b
    Program lp (CGAL::LARGER, false, 0, true, 0);

    // now set the non-default entries
    const int X = 0; 
    const int Y = 1;
    const int Z = 2; // we substitute z^2 with z to solve this problem
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, -4);                       // x + y >= -4
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_a(Z, 1, 1); lp.set_b(1, -a*b);  // 4x + 2y + z^2 >= -ab
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);                      // -x + y >= -1

    // we substituted Z, it's a square so it must always be >=0
    lp.set_l(Z, true, 0);
    lp.set_u(Z, false, 0);

    lp.set_d(X, X, 2*a);  // a*x^2
    lp.set_c(Y, b);     // b*y
    lp.set_d(Z, Z, 2);  // z^4

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_quadratic_program(lp, ET());
    if (s.is_infeasible())
        cout << "no" << "\n";
    else if (s.is_unbounded())
        cout << "unbounded" << "\n";
    else
        cout << ceil(CGAL::to_double(s.objective_value())) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    while(true){
        int p, a, b; cin >> p >> a >> b;
        if (p == 0)
            break;
        else if (p == 1)
            type_1(a, b);
        else
            type_2(a, b);
    }
}
