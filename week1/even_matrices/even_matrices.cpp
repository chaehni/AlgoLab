#include <iostream>
#include <vector>

using namespace std;

void test()
{
   /*  int n;
    cin >> n;

    // build matrix
    vector<vector<int>> matrix;

    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        int in;
        for (int j = 0; j < n; j++)
        {
            cin >> in;
            temp.push_back(in);
        }

        matrix.push_back(temp);
    }

    // build partial sum matrix
    vector<vector<int>> sum_matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        int in;
        for (int j = 0; j < n; j++)
        {
            int val = matrix[i][j];
            if (i == 0 && j == 0)
            {
                sum_matrix[i][j] = val;
            }
            else if (i == 0)
            {
                sum_matrix[i][j] = sum_matrix[i][j - 1] + val;
            }
            else if (j == 0)
            {
                sum_matrix[i][j] = sum_matrix[i - 1][j] + val;
            }
            else
            {
                sum_matrix[i][j] = sum_matrix[i - 1][j] + sum_matrix[i][j - 1] - sum_matrix[i - 1][j - 1] + val;
            }
        }
    }

    int even = 0;
    for (int i1 = 0; i1 < n; i1++)
    {
        for (int i2 = i1; i2 < n; i2++)
        {
            for (int j1 = 0; j1 < n; j1++)
            {
                for (int j2 = j1; j2 < n; j2++)
                {

                    int sum = 0;

                    if (i1 == 0 && j1 == 0)
                    {
                        sum = sum_matrix[i2][j2];
                    }
                    else if (i1 == 0)
                    {
                        sum = sum_matrix[i2][j2] - sum_matrix[i2][j1 - 1];
                    }
                    else if (j1 == 0)
                    {
                        sum = sum_matrix[i2][j2] - sum_matrix[i1 - 1][j2];
                    }
                    else
                    {
                        sum = sum_matrix[i2][j2] + sum_matrix[i1 - 1][j1 - 1] - sum_matrix[i1 - 1][j2] - sum_matrix[i2][j1 - 1];
                    }

                    if (sum % 2 == 0)
                    {

                        even++;
                    }
                }
            }
        }
    }

    cout << even << "\n"; */

    unsigned n;
	cin >> n;

	vector <vector<int>> X(n, vector<int>(n));
	vector <vector<int>> sums(n, vector<int>(n));

	int n_pairs = 0;

	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < n; j++) {
			cin >> X[i][j];
		}
	}

	for (unsigned j = 0; j < n; j++) {
		int sum = 0;
		for (unsigned i = 0; i < n; ++i) {
			sum += X[i][j];
			sums[j][i] = sum;
		}
	}

    for (unsigned i = 0; i < n; i++) {
        cout << "\n";
		for (unsigned j = 0; j < n; j++) {
			cout << sums[i][j] << " ";
		}
	}

	// Just sum up all possibilities
	for (unsigned i_start = 0; i_start < n; ++i_start) {
		for (unsigned i_end = i_start; i_end < n; ++i_end) {
			int even = 0;
			int odd = 0;
			for (unsigned j = 0; j < n; j++) {
				int sum = sums[j][i_end] - (i_start == 0 ? 0 : sums[j][i_start - 1]);
				if (j == 0) {
					if (sum % 2 == 0) { even = 1; }
					else { odd = 1; }
				} else {
					if (sum % 2 == 0) {
						even += 1;
					} else {
						int tmp = even;
						even = odd;
						odd = tmp + 1;
					}
				}
				n_pairs += even;
			}
		}
	}

	cout << n_pairs << endl;

}

int main()
{
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        test();
    }
    return 0;
}
