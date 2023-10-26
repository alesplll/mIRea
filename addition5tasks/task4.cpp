// task 67
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

#define int int64_t

double safeInputDouble()
{
    double number;
    string input;

    while (true)
    {
        getline(cin, input);

        stringstream ss(input);
        if (ss >> number && ss.eof())
        {
            return number;
        }
        else
        {
            cout << "Inv-d inp. Enter a v-d number. Try again: ";
            ss.clear();
        }
    }
}

double findMinimum(double A, double B)
{
    return (A < B) ? A : B;
}

int32_t main()
{
    setlocale(LC_ALL, "rus");
    ios_base::sync_with_stdio(0);
    double A, B, C, D;

    cout << "Enter number A: ";
    A = safeInputDouble();
    cout << "Enter number B: ";
    B = safeInputDouble();
    cout << "Enter number C: ";
    C = safeInputDouble();
    cout << "Enter number D: ";
    D = safeInputDouble();

    double minAB = findMinimum(A, B);
    double minAC = findMinimum(A, C);
    double minAD = findMinimum(A, D);

    cout << "Minimun of A and B: " << minAB << endl;
    cout << "Minimun of A and C: " << minAC << endl;
    cout << "Minimun of A and D: " << minAD << endl;

    return 0;
}
