#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

#define int int64_t

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

int safeInputInt()
{
    int number;
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

void first(int N) // task 32

{

    int count = 0;
    int *A = new int[N];
    cout << "Enter massive elements:" << endl;

    for (int i = 0; i < N; i++)
    {
        A[i] = safeInputDouble();
    }
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
}

void secound(int N) // task 45

{
    int *array = new int[N];
    cout << "Enter massive elements:" << endl;
    for (int i = 0; i < N; ++i)
    {
        array[i] = safeInputDouble();
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
}

void third() // task 55

{
    const int rows = 5;
    const int cols = 9;
    int **matrix = new int *[rows];

    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
    }

    srand(static_cast<unsigned int>(time(0)));
    cout << "Enter el of matrix " << rows << " x " << cols << ":\n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = rand() % 10;
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
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
}

void fourth() // task 67

{
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
}

void fifth(int N)
{
    int m;
    int n = N;
    int *x = new int[N];
    cout << "Enter el of X: " << endl;
    for (int i = 0; i < n; ++i)
    {
        x[i] = safeInputDouble();
    }

    cout << "Enter size of massive Y: ";
    cin >> m;
    int *y = new int[m];
    cout << "Enter el of Y: " << endl;
    for (int i = 0; i < m; ++i)
    {
        y[i] = safeInputDouble();
    }

    int length = findLCS(x, y, n, m);
    cout << "Length of greatest common subsequence: " << length << endl;

    delete[] x;
    delete[] y;
}

void check_1()
{
    int N = 0;

    while (N <= 0)
    {
        cout << "Enter size of the matrix: ";
        N = safeInputInt();
    }
    first(N);
    cin.get();
}

void check_2()
{
    int N = 0;
    while (N <= 0)
    {
        cout << "Enter size of the matrix: ";
        N = safeInputInt();
    }
    secound(N);
    cin.get();
}

void check_5()
{
    int N = 0;
    while (N <= 0)
    {
        cout << "Enter size of the matrix: ";
        N = safeInputInt();
    }
    fifth(N);
    cin.get();
}

int32_t main()
{
    setlocale(LC_ALL, "rus");
    ios_base::sync_with_stdio(0);
    while (true)
    {
        cout << "Enter number of a task (1-5): ";
        int t = safeInputInt();

        switch (t)
        {
        case 1:
            check_1();
            break;
        case 2:
            check_2();
            break;
        case 3:
            third();
            cin.get();
            break;
        case 4:
            fourth();
            cin.get();
            break;
        case 5:
            check_5();
            break;
        default:
            cout << "This task doesnt exist. Try again." << endl;
            break;
        }
        cin.get();
        system("clear");
    }
}
