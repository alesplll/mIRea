#include <bits/stdc++.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#define int int64_t

void findmin(const string &filename)
{
    vector<int> numbers;
    int number;

    // Чтение из файла сохранение в вектор
    int n = 0;
    ifstream inputFile(filename);
    while (inputFile >> number)
    {
        numbers.push_back(number);
        n++;
    }
    inputFile.close();

    int a, b;
    int minn = pow(2, 16);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            a = min(numbers[i], numbers[j]);
            b = max(numbers[i], numbers[j]);
            for (int k = 2; k <= a; k++)
            {
                if (a % k == 0 && b % k == 0)
                {
                    minn = min(minn, k);
                }
            }
        }
    }
    cout << "Min common div: " << minn << endl;
}

void findmax(const string &filename)
{
    vector<int> numbers;
    int number;

    // Чтение из файла сохранение в вектор
    int n = 0;
    ifstream inputFile(filename);
    while (inputFile >> number)
    {
        numbers.push_back(number);
        n++;
    }
    inputFile.close();

    int a, b;
    int maxx = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            a = abs(numbers[i]);
            b = abs(numbers[j]);
            while (a != 0 and b != 0)
            {
                if (a > b)
                {
                    a = a % b;
                }
                else
                {
                    b = b % a;
                }
            }
            if (a + b > maxx)
            {
                maxx = a + b;
            }
        }
    }
    cout << "Max common div: " << maxx << endl;
}

void easynum(const string &filename)
{
    vector<int> numbers;
    int number;

    // Чтение из файла сохранение в вектор
    int s = 0;
    ifstream inputFile(filename);
    while (inputFile >> number)
    {
        numbers.push_back(number);
        s++;
    }
    inputFile.close();

    int n = 100;

    vector<int> sieve(n + 1, 1);

    for (int p = 2; p * p <= n; p++)
    {
        if (sieve[p] == 1)
        {
            for (int j = p * p; j <= n; j += p)
            {
                sieve[j] = 0; // Обнуляем элементы, кратные p
            }
        }
    }

    int cnt = 0;
    vector<int> primes;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= s; j++)
            if (i == numbers[j] && sieve[i] == 1 && i > 1)
            {
                cnt++;
                primes.push_back(numbers[j]);
            }
    }

    ofstream outputFile("primenumbers.txt");
    for (const auto &w : primes)
    {
        outputFile << w << endl;
    }
    outputFile.close();
    cout << "finished primes\n in all: " << cnt << endl;
}

void sortAndAddWordToFile(const string &newWord, const string &filename)
{
    vector<string> words;
    string word;

    // Чтение из файла сохранение в вектор
    ifstream inputFile(filename);
    while (inputFile >> word)
    {
        words.push_back(word);
    }
    inputFile.close();

    // Добавление в вектор
    words.push_back(newWord);

    // Сортировка
    sort(words.begin(), words.end());

    // Запись
    ofstream outputFile(filename);
    for (const auto &w : words)
    {
        outputFile << w << endl;
    }
    outputFile.close();
}

int32_t factt(int t)
{
    long factorial = 1.0;
    if (t < 0)
        return 0;
    else
    {
        for (int i = 1; i <= t; ++i)
        {
            factorial *= i;
        }
        return factorial;
    }
}

void all_answ()
{
    int cnt;
    cout << "Введите № задания" << endl;
    cin >> cnt;
    if (cnt == 1)
    {
        int a, b;
        cout << "Write A and B:\n";
        cin >> a >> b;
        a = abs(a);
        b = abs(b);
        while (a != 0 and b != 0)
        {
            if (a > b)
            {
                a = a % b;
            }
            else
            {
                b = b % a;
            }
        }
        cout << "answ: " << a + b << endl;
    }
    else if (cnt == 2)
    {
        int n;
        cout << "n= ";
        cin >> n;
        cout << "answ: \n";

        vector<int> sieve(n + 1, 1);

        for (int p = 2; p * p <= n; p++)
        {
            if (sieve[p] == 1)
            {
                for (int j = p * p; j <= n; j += p)
                {
                    sieve[j] = 0; // Обнуляем элементы, кратные p
                }
            }
        }

        for (int i = 0; i <= n; i++)
        {
            if (sieve[i] == 1)
            {
                cout << i << ' ';
            }
        }

        cout << "\n";
    }
    else if (cnt == 3)
    {
        int maxx = 0;
        int minn = 2 << 25;
        fstream newfile;
        newfile.open("4-6.txt", ios::in);
        if (newfile.is_open())
        {
            string tp;
            while (getline(newfile, tp))
            {
                int c = 0;
                for (auto it : tp)
                {
                    // cout << it;
                    if (it == ' ' && c > 0)
                    {
                        maxx = max(c - 1, maxx);
                        minn = min(c - 1, minn);
                        c = 0;
                        // cout << " fl  " << it << "  ";
                    }
                    c = c + 1;
                    // cout << maxx << ' ' << minn << ' ' << c << endl;
                }
            }
            newfile.close();
        }
        cout << "Max len: " << maxx << endl;
        cout << "Min len: " << minn << endl;
    }
    else if (cnt == 4)
    {
        cout << "Choose exmpl 1 or 2: ";
        string sh;
        cin >> sh;
        try
        {
            int c = stoi(sh);
            if (c == 1)
            {
                int n;
                cout << "Write N: ";
                cin >> n;
                double res = 0;
                for (int k = 1; k < n + 1; k++)
                {
                    double tempp = 0;
                    for (int i = 1; i <= k; i++)
                    {
                        double t = i;
                        if (i % 2 == 0)
                        {
                            tempp = tempp - 1 / t;
                        }
                        else
                        {
                            tempp = tempp + 1 / t;
                        }
                    }

                    res += factt(k) / tempp;
                }
                cout << "Sum is: " << res << endl;
            }
            else if (c == 2)
            {
                cout << "Input x and e: ";
                double x, e;
                cin >> x >> e;
                double a1 = 0, a2 = 1, a3 = x;
                double a4;
                int n = 4;
                while (1)
                {
                    a4 = 3 + 1 / (pow(2, n)) * pow(cos(a3 * a3 - x * a2 * a2 - a1 / x), 2);
                    a1 = a2;
                    a2 = a3;
                    a3 = a4;
                    a4 = 1;
                    // cout << a1 << " " << a2 << " " << a3 << "\n";
                    n++;
                    if (abs(a3 - a2) < e)
                    {
                        cout << "Answ: " << a3 << " " << n << endl;
                        break;
                    }
                }
            }
            else
            {
                cout << '\n'
                     << "Doesnt exist \n";
            }
        }
        catch (const invalid_argument &e)
        {
            cerr << "Ошибка: Некорректные данные в файле." << endl;
        }
    }
    else if (cnt == 5)
    {
        cout << "Choose exmpl 1 or 2: ";
        string sh;
        cin >> sh;
        try
        {
            int c = stoi(sh);
            if (c == 1)
            {
                string filename = "words.txt";
                string newWord;

                cout << "Enter word: ";
                cin >> newWord;

                sortAndAddWordToFile(newWord, filename);

                cout << "Word added and sorted" << endl;
            }
            else if (c == 2)
            {
                string filename = "numb5_5_2.txt";
                findmin(filename);
                findmax(filename);
                easynum(filename);
                cout << "\n";
                cout << "Do you want to see a file with all numbers?\nEnter [Y/n]\n";
                char chek;
                cin >> chek;
                if (chek == 'Y')
                {
                    string filename = "numb5_5_2.txt";
                    int number;
                    ifstream inputFile(filename);
                    while (inputFile >> number)
                    {
                        cout << number << " ";
                    }
                    inputFile.close();
                }

                cout << "\n";
                cout << "Do you want to see a file with prime numbers?\nEnter [Y/n]\n";
                cin >> chek;
                if (chek == 'Y')
                {
                    string filename = "primenumbers.txt";
                    int number;
                    ifstream inputFile(filename);
                    while (inputFile >> number)
                    {
                        cout << number << " ";
                    }
                    inputFile.close();
                }
                cout << "Finished \n";
            }
            else
            {
                cout << "Doesnt exist\n";
            }
        }
        catch (const invalid_argument &e)
        {
            cerr << "Ошибка: Некорректные данные в файле." << endl;
        }
    }
    else
    {
        cout << "Wrong number";
    }
}

int32_t main()
{
    setlocale(LC_ALL, "rus");
    ios_base::sync_with_stdio(0);
    while (1)
    {
        all_answ();
        cin.get();
        cin.get();

        system("clear");
    }
}