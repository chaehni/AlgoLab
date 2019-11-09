#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

//typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void powers(vector<ET> &c, int n)
{
    c[0] = 1;
    for (int i = 1; i <= 30; i++)
        c[i] = c[i - 1] * n;
}

bool solve(int d, vector<vector<vector<ET>>> &cells, int h)
{
    // create an LP with Ax <= b, no bounds
    Program lp(CGAL::SMALLER, false, 0, false, 0);

    // loop over all healthy cells
    for (int c = 0; c < cells.size(); c++)
    {
        int term_cnt = 0;
        // generate the terms of the polynomial of degree d
        for (int x = 0; x <= d; x++)
            for (int y = 0; y <= d - x; y++)
                for (int z = 0; z <= d - x - y; z++)
                    lp.set_a(term_cnt++, c, cells[c][0][x] * cells[c][1][y] * cells[c][2][z]);

        if (c < h)
        {
            lp.set_r(c, CGAL::SMALLER);
            lp.set_b(c, -1);
        }
        else
        {
            lp.set_r(c, CGAL::LARGER);
            lp.set_b(c, 1);
        }
    }

    // no cost function
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);
    Solution s = CGAL::solve_linear_program(lp, ET(), options);

    assert(s.solves_linear_program(lp));
    return s.is_optimal();
}

void run()
{
    int h, t;
    cin >> h >> t;
    vector<vector<vector<ET>>> cells(h + t, vector<vector<ET>>(3, vector<ET>(31)));

    for (int i = 0; i < h + t; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        powers(cells[i][0], x);
        powers(cells[i][1], y);
        powers(cells[i][2], z);
    }

    // replace ths loop with binary search
    bool feasable = false;
    for (int d = 0; d <= 30; d++)
    {
        feasable = solve(d, cells, h);
        if (feasable)
        {
            cout << d << "\n";
            return;
        }
    }

    cout << "Impossible!\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}