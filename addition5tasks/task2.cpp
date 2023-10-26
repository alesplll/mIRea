// task 45
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
    int N;
    cout << "Enter size of the matrix: ";
    cin >> N;
    int *array = new int[N];
    cout << "Enter massive elements:" << endl;
    for (int i = 0; i < N; ++i)
    {
        cin >> array[i];
    }

    int count = 0;
    bool isIncreasing = false;

    for (int i = 1; i < N; ++i)
    {
        if (array[i] > array[i - 1])
        {
            if (!isIncreasing)
            {
                isIncreasing = true;
                count++;
            }
        }
        else
        {
            isIncreasing = false;
        }
    }

    cout << "Count of fields where nmbs'r growing const-ly: " << count << endl;

    delete[] array;

    return 0;
}
