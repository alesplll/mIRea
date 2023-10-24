#include <bits/stdc++.h>
#include <math.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    ios_base::sync_with_stdio(0);

    int cnt;
    cout << "Введите № задания" << endl;
    cin >> cnt;

    if (cnt == 1)
    {
        double s, p, n, m;
        cout << "S, p, n:";
        cin >> s >> p >> n;
        if (s > 0 and p > 0 and p < 100 and n > 0)
        {
            double r;
            r = p / 100;
            m = (s * r * pow((1 + r), n)) / (12 * (pow((1 + r), n) - 1));
            cout << m << endl;
        }
        else
        {
            cout << "Error\n";
        }
    }
    else if (cnt == 2)
    {
        double s, m, n;
        cout << "s, m, n:";
        cin >> s >> m >> n;
        bool flag = false;
        int l = 9;
        int r = 100;
        int mid;
        if (s > 0 and m > 0 and n > 0)
        {
            while (r > l + 1)
            {
                mid = (l + r) / 2;
                if (m < (s * mid * pow((1 + mid), n)) / (12 * (pow((1 + mid), n) - 1)))
                {
                    r = mid;
                }
                else
                {
                    l = mid;
                }
            }
            cout << r << endl;
        }
        else
        {
            cout << "wrong input";
        }
    }
    else if (cnt == 3)
    {
        string text;
        cout << "Input: ";
        cin.ignore();
        getline(cin, text);
        fstream newfile;
        newfile.open("for_3_3.txt", ios::out);
        if (newfile.is_open())
        {
            newfile << text;
            newfile.close();
        }
        newfile.open("for_3_3.txt", ios::in);
        if (newfile.is_open())
        {
            string tp;
            while (getline(newfile, tp))
            {
                cout << tp << "\n";
            }
            newfile.close();
        }
        else
        {
            cout << "Error\n";
        }
    }
    else if (cnt == 4)
    {
        string text;
        cout << "Input: ";
        cin.ignore();
        getline(cin, text);

        fstream newfile;
        newfile.open("for_3_3.txt", ios::out);
        if (newfile.is_open())
        {
            newfile << text;
            newfile.close();
        }

        newfile.open("for_3_3.txt", ios::in);
        if (newfile.is_open())
        {
            string tp;
            while (getline(newfile, tp))
            {
                tp.erase(remove_if(tp.begin(), tp.end(), ::isalpha), tp.end());
                cout << tp << endl;
            }
            newfile.close();
            cout << endl;
        }
        else
        {
            cout << "Error\n";
        }
    }
    else if (cnt == 5)
    {
        char alphabet[30];
        cout << "Enter letters:\n";
        cin >> alphabet;

        fstream newfile;
        newfile.open("tpoint.txt", ios::out);
        if (newfile.is_open())
        {
            newfile << alphabet;
            newfile.close();
        }
        else
        {
            cout << "error\n";
        }

        newfile.open("tpoint.txt", ios::in);
        if (newfile.is_open())
        {
            string tp;
            while (getline(newfile, tp))
            {
                const int N = 30;
                int A[N], i, tmp;

                i = 0;
                while (i < N)
                {
                    if (i == 0 || tp[i - 1] <= tp[i])
                        ++i;
                    else
                    {
                        tmp = tp[i];
                        tp[i] = tp[i - 1];
                        tp[i - 1] = tmp;
                        --i;
                    }
                }

                for (i = 4; i < N; i++)
                {
                    cout << tp[i];
                }
                cout << endl;
                return 0;
            }
            newfile.close();
        }
        else
        {
            cout << "Error\n";
        }
    }
    else
    {
        cout << "Wrong number";
    }
}