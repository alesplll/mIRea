#include <iostream>

using namespace std;

int findLCS(int *x, int *y, int n, int m)
{
    int **dp = new int *[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        dp[i] = new int[m + 1];
    }

    // first row and col as 0
    for (int i = 0; i <= n; ++i)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; ++j)
    {
        dp[0][j] = 0;
    }

    // Main part take max or if equals then +1
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (x[i - 1] == y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int result = dp[n][m];

    // clear the buffer
    for (int i = 0; i <= n; ++i)
    {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

int main()
{
    int n, m;
    cout << "Enter size of massive X: ";
    cin >> n;
    int *x = new int[n];
    cout << "Enter el of X: " << endl;
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }

    cout << "Enter size of massive Y: ";
    cin >> m;
    int *y = new int[m];
    cout << "Enter el of Y: " << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> y[i];
    }

    int length = findLCS(x, y, n, m);
    cout << "Length of greatest common subsequence: " << length << endl;

    delete[] x;
    delete[] y;

    return 0;
}
