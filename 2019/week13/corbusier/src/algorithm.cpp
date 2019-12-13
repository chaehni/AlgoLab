#include <iostream>
#include <vector>

using namespace std;

void testcase()
{
	int n, rest, k;
	cin >> n >> rest >> k;
	vector<int> disks(n);
	for (int i = 0; i < n; i++)
		cin >> disks[i];

	vector<vector<bool>> memo(n, vector<bool>(k));

	// initialize first column (exactly one value is True)
	memo[0][disks[0] % k] = true;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			// two options: take the disk or don't

			// don't take disk:
			if (memo[i - 1][j])
			{
				memo[i][j] = true;
				continue;
			}

			// take disk:
			int remainder = disks[i] % k;
			if (remainder == j)
			{
				memo[i][j] == true;
				continue;
			}

			if (memo[i - 1][(j + k - remainder) % k])
			{
				memo[i][j] = true;
				continue;
			}
		}
	}

	if (memo[n - 1][rest])
		cout << "yes\n";
	else
		cout << "no\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
