#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> naiveMatrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();

    vector<vector<int>> result(n, vector<int>(p, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}