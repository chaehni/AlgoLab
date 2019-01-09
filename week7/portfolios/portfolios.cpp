
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

struct Asset
{
    int cost, ret;
};

void run(int n, int m)
{
    vector<Asset> assets(n);
    vector<vector<int>> covars(n, vector<int>(n));

    // set up quadratic program, cannot buy negative amount of assets -> lower bound = 0
    Program qp(CGAL::SMALLER, true, 0, false, 0);

    const int COST = 0;
    const int RET = 1;

    // set A-matrix
    for (int i = 0; i < n; i++)
    {
        int c, r;
        cin >> c >> r;
        qp.set_a(i, COST, c);
        qp.set_a(i, RET, r);
    }

    // read covariances and add to D-matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int cov;
            std::cin >> cov;
            // TODO: only lower half
            qp.set_d(i, j, 2 * cov);
        }
    }

    // answer questions
    for (int i = 0; i < m; i++)
    {
        int c, r, v;
        cin >> c >> r >> v;

        // add max cost constraint to b-vector
        qp.set_b(COST, c);

        // add min return constraint to b-vector
        qp.set_b(RET, r);
        qp.set_r(RET, CGAL::LARGER); // override "SMALLER" operator for return. Return mast be LARGER than specified value

        // run solver
        Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());

        if (s.is_infeasible() || s.objective_value() > v)
            cout << "No.";
        else
            cout << "Yes.";
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n, m;
    while (true)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        run(n, m);
    }
}