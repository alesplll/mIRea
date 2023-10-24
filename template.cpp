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
    }
    else if (cnt == 2)
    {
    }
    else if (cnt == 3)
    {
    }
    else if (cnt == 4)
    {
    }
    else if (cnt == 5)
    {
    }
    else
    {
        cout << "Wrong number";
    }

    fstream newfile;
    newfile.open("tpoint.txt", ios::out);
    if (newfile.is_open())
    {

        newfile << "Tutorials point \n";
        newfile.close();
    }
    newfile.open("tpoint.txt", ios::in);
    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            cout << tp << "\n";
        }
        newfile.close();
    }

    string a1, b1;
    cin >> a1 >> b1;
    try
    {
        int a = stoi(a1);
        double b = stod(b1);
        // func
    }
    catch (const invalid_argument &e)
    {
        cerr << "Ошибка: Некорректные данные в файле." << endl;
    }
}