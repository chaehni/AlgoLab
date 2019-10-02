#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

// memo getters and setters
// we know there are at most 5 stacks. If there are less we use index 0 for remaining dimensions
int get_memo(vector<vector<vector<vector<vector<int>>>>> &memo, vector<int> &p)
{
    return memo[p[0]][p[1]][p[2]][p[3]][p[4]];
}
void set_memo(vector<vector<vector<vector<vector<int>>>>> &memo, vector<int> &p, int value)
{
    memo[p[0]][p[1]][p[2]][p[3]][p[4]] = value;
}

double compute(int n, vector<vector<int>> &stacks, vector<int> &pointers, vector<vector<vector<vector<vector<int>>>>> &memo)
{

    // check memo
    int mem_val = get_memo(memo, pointers);
    if (mem_val != -1)
        return mem_val;

    // stop recursion if not at least 2 stacks are non-empty
    int empty_stacks = 0;
    for (int i = 0; i < n; i++)
        if (pointers[i] == 0)
            empty_stacks++;

    if (empty_stacks >= n - 1) // with less than 2 stacks result is always 0
        return 0;

    // otherwise explore all possible combinations of stacks to remove chips from (2^5 = 32 max)
    double max_points = 0;
    for (int i = 1; i < 1 << n; i++) // start from one since first config is all 0 which would cause an infinite loop
    {
        vector<int> selected;
        for (int s = 0; s < n; s++)
        {
            if (i & 1 << s)
                selected.push_back(s);
        }

        // a subset is only valid if all stacks are non-empty and all have the same number atop
        bool invalid = false;
        int top = -1;

        for (int sel : selected)
        {
            if (pointers[sel] == 0)
            {
                invalid = true; // stack is empty
                break;
            }
            else
            {
                if (top == -1)
                    top = stacks[sel][pointers[sel] - 1];
                if (stacks[sel][pointers[sel] - 1] != top) // top of stack does not match other top of stack
                {
                    invalid = true;
                    break;
                }
            }
        }

        if (invalid) // try next config
            continue;

        // this config is valid, remove top chip from every stack, count points and continue recursion
        for (int sel : selected)
            pointers[sel]--;

        double pts = (selected.size() > 1 ? pow(2, selected.size() - 2) : 0);
        max_points = max(max_points, pts + compute(n, stacks, pointers, memo));
        // recursive call returned, add back chips for next loop iteration
        for (int sel : selected)
            pointers[sel]++;
    }

    set_memo(memo, pointers, max_points);
    return max_points;
}

void run()
{
    int n;
    cin >> n;
    vector<int> stack_sizes(5, 1);
    vector<vector<int>> stacks(n);

    // read stack sizes
    for (int i = 0; i < n; i++)
        cin >> stack_sizes[i];

    // read stacks
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < stack_sizes[i]; j++)
        {
            int t;
            cin >> t;
            stacks[i].push_back(t);
        }
    }

    // memo table saves maximal points for a sub game (two configurations are the same if all the stacks are the same height as their corresponding stack in the other config)
    vector<vector<vector<vector<vector<int>>>>> memo; // <--- FUCKING WHAT?!
    memo = vector<vector<vector<vector<vector<int>>>>>(stack_sizes[0] + 1,
                                                       vector<vector<vector<vector<int>>>>(stack_sizes[1] + 1,
                                                                                           vector<vector<vector<int>>>(stack_sizes[2] + 1,
                                                                                                                       vector<vector<int>>(stack_sizes[3] + 1,
                                                                                                                                           vector<int>(stack_sizes[4] + 1, -1)))));

    int points = compute(n, stacks, stack_sizes, memo);

    cout << points << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
    {
        run();
    }
}