// task 55
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

#define int int64_t

int32_t main()
{
    setlocale(LC_ALL, "rus");
    ios_base::sync_with_stdio(0);
    const int rows = 5;
    const int cols = 9;
    int **matrix = new int *[rows];

    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
    }

    cout << "Enter el of matrix " << rows << " x " << cols << ":\n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    int sum = 0;
    for (int j = 1; j < cols; j += 2)
    {
        for (int i = 0; i < rows; ++i)
        {
            sum += matrix[i][j];
        }
    }

    cout << "Sum of elem in even colomn: " << sum << endl;

    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
