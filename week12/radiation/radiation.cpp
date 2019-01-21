#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void compute_pws(int n, vector<ET> &pw)
{
    pw[0] = 1;
    pw[1] = ET(n);
    for (int p = 2; p < 31; ++p)
        pw[p] = pw[p - 1] * pw[1];
}

bool try_solve(int d, int H, int T, vector<vector<vector<ET>>> &cells)
{
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);

    for (int i = 0; i < H; ++i)
    {
        lp.set_b(i, -1); // works bescause we don't have fractions (must be smaller than 0)
    }
    for (int i = H; i < H + T; ++i)
    {
        lp.set_r(i, CGAL::LARGER);
        lp.set_b(i, 1); // works bescause we don't have fractions (must be larger than 0)
    }

    // set constraints for all variables
    for (int c = 0; c < H + T; c++)
        for (int i = 0, cnt = 0; i <= d; i++)
            for (int j = 0; j <= d - i; j++)
                for (int k = 0; k <= d - i - j; k++)
                    lp.set_a(cnt++, c, cells[c][0][i] * cells[c][1][j] * cells[c][2][k]);

    // Solve
    Solution s = CGAL::solve_linear_program(lp, ET(), options);
    assert(s.solves_linear_program(lp));

    return s.is_optimal();
}

void run()
{
    int H, T;
    cin >> H >> T;

    vector<vector<vector<ET>>> cells(H + T, vector<vector<ET>>(3, vector<ET>(31)));
    for (int i = 0; i < H + T; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        cells[i] = {vector<vector<ET>>(3, vector<ET>(31))};
        compute_pws(x, cells[i][0]);
        compute_pws(y, cells[i][1]);
        compute_pws(z, cells[i][2]);
    }

    // we can use at most 30 degrees, try to find a solution with degrees 0 to 30
    for (int d = 0; d <= 30; d++) // could be sped up by about 1s using binary search
    {
        bool solvable = try_solve(d, H, T, cells);

        if (solvable)
        {
            cout << d << "\n";
            return;
        }
    }
    cout << "Impossible!\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}