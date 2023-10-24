#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int cntt = 0;

void printPermutations(int *balls, int step, int n)
{
    if (step == n + 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (balls[i] == i)
            {
                cntt++;
                /*
                                cout << "В комбинации шарик " << i << " стоит на своем месте: ";
                                for (int j = 1; j <= n; ++j)
                                {
                                    cout << balls[j] << " ";
                                }
                                cout << endl;
                */
                break;
            }
        }
        return;
    }

    for (int i = step; i <= n; ++i)
    {
        swap(balls[i], balls[step]);
        printPermutations(balls, step + 1, n);
        swap(balls[i], balls[step]);
    }
}

int main()
{
    int n; // количество шариков
    cout << "Input N: ";
    cin >> n;
    cout << endl;
    int *balls = new int[n + 1];

    for (int i = 1; i <= n; ++i)
    {
        balls[i] = i;
    }

    printPermutations(balls, 1, n);
    cout << endl;
    cout << "Всего для " << n << " шариков " << cntt << " комбинаций..." << endl;
    cout << endl;
    delete[] balls;

    return 0;
}
