// task 32
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
    int N; // start size
    int count = 0;

    cout << "Enter size of the matrix: ";
    cin >> N;
    int *A = new int[N];
    cout << "Enter massive elements:" << endl;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    /*
    while (cin >> A[count])
    {
        ++count;
        // if overloading
        if (count >= N)
        {
            int newSize = N * 2;
            int *newNumbers = new int[newSize];
            // copying from old numbers
            for (int i = 0; i < N; ++i)
            {
                newNumbers[i] = A[i];
            }
            delete[] A;
            A = newNumbers;
            N = newSize;
        }
    }
    */

    // find minimum number
    double minPositive = INT_MAX;
    int minPositiveIndex = -1;
    for (int i = 0; i < N; ++i)
    {
        if (A[i] > 0 && A[i] < minPositive)
        {
            minPositive = A[i];
            minPositiveIndex = i;
        }
    }
    // cout << "minPositive: " << minPositive << endl;

    // max
    double maxElement = A[0];
    int maxElementIndex = 0;
    for (int i = 1; i < N; ++i)
    {
        if (A[i] > maxElement)
        {
            maxElement = A[i];
            maxElementIndex = i;
        }
    }
    // cout << "maxElement: " << maxElement << endl;

    // swap min and max elements
    if (minPositiveIndex != -1)
    {
        swap(A[minPositiveIndex], A[maxElementIndex]);
    }
    else
    {
        cout << "There is no positive." << endl;
    }

    // check fifth nonzero element
    int cnt = 0;
    bool fl = true;
    for (int i = 0; i < N; i++)
    {

        if (A[i] != 0)
        {
            cnt++;
            if (cnt == 5)
            {
                if (abs(A[i]) < 2)
                {
                    cout << "Fifth nonzero element by abs < 2." << endl;
                    fl = false;
                }
                else
                {
                    cout << "Fifth nonzero element by abs > 2." << endl;
                    fl = false;
                }
                break;
            }
        }
    }
    if (fl)
    {
        cout << "There is no fifth nonzero element." << endl;
    }

    // all negative in start
    int left = 0;
    int right = N - 1;
    while (left <= right)
    {
        if (A[left] < 0)
        {
            ++left;
        }
        else if (A[right] >= 0)
        {
            --right;
        }
        else
        {
            swap(A[left], A[right]);
            ++left;
            --right;
        }
    }

    cout << "Result massive: ";
    for (int i = 0; i < N; ++i)
    {
        cout << A[i] << " ";
    }
    cout << endl;

    delete[] A;
    return 0;
}
