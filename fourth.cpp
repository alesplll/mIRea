/// Роман Маркович Огорельцев
#include <bits/stdc++.h>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

const string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
typedef unsigned int UI;

string ConvertBase(const string &num, int sourceBase, int targetBase)
{
    // Переводим исходное число в десятичную систему счисления
    int decimalValue = 0;
    int power = 0;
    for (int i = num.length() - 1; i >= 0; --i)
    {
        char digit = num[i];
        int digitValue;
        if (isdigit(digit))
        {
            digitValue = digit - '0';
        }
        else
        {
            digitValue = digit - 'A' + 10; // Для шестнадцатеричных чисел (A=10, B=11, и так далее)
        }
        decimalValue += digitValue * pow(sourceBase, power);
        ++power;
    }

    // Переводим десятичное число в целевую систему счисления
    string result = "";
    while (decimalValue > 0)
    {
        int remainder = decimalValue % targetBase;
        char digit;
        if (remainder < 10)
        {
            digit = '0' + remainder;
        }
        else
        {
            digit = 'A' + remainder - 10;
        }
        result = digit + result;
        decimalValue /= targetBase;
    }

    return result;
}

void Reverse(string &str)
{
    UI i = -1, j = str.length();
    while (++i < --j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

bool ValidNumber(string &num, int base)
{
    if (base < 2 || base > 36)
        return false;

    UI i = -1;
    while (++i < num.length())
        if (alphabet.find(num[i]) >= base)
            return false;
    return true;
}

void ex2(double s)
{
    if (s < 0)
    {
        cout << "-1\n";
    }
    else if (s == 0)
    {
        cout << "0\n";
    }
    else if (s > 0)
    {
        cout << "+1\n";
    }
    else
    {
        cout << "Wrong input\n";
    }
}

void rect()
{
    string a1, b1;
    cout << "Input size of Rectangular (A B): ";
    cin >> a1 >> b1;
    try
    {
        double a = stod(a1);
        double b = stod(b1);
        if (a > 0 and b > 0)
        {
            cout << a * b << endl;
        }
        else
        {
            cout << "rect doesnt exist" << endl;
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Wrong input." << endl;
    }
}

void triang()
{
    string a1, b1, c1;
    cout << "Input size of Triangular (A B C): ";
    cin >> a1 >> b1 >> c1;
    try
    {
        double a = stod(a1);
        double b = stod(b1);
        double c = stod(c1);
        if (a > 0 and b > 0 and c > 0 and a + b > c and a + c > b and b + c > a)
        {
            int p = (a + b + c) / 2;
            cout << sqrt(p * (p - a) * (p - b) * (p - c)) << endl;
        }
        else
        {
            cout << "triangular doesnt exist" << endl;
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Wrong input." << endl;
    }
}

void circle()
{
    string r1;
    cout << "Input size of Circle - Radius (R): ";
    cin >> r1;

    try
    {
        double r = stod(r1);
        if (r > 0)
        {
            cout << M_PI * r * r << endl;
        }
        else
        {
            cout << "Circule doesnt exist" << endl;
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Wrong input." << endl;
    }
}

bool isCorrectLetter(const char &letter)
{ // проверка символов
    const int size = 7;
    char mySymbols[size] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for (int i = 0; i < size; ++i)
    {
        if (letter == mySymbols[i])
        {
            return true;
        }
    }
    return false;
}

bool isCorrectSequence(const char &previous, const char &next, int &recurrence)
{
    if (next == previous && (previous == 'L' || previous == 'D' || previous == 'V'))
    {
        return false;
    }
    if (recurrence == 3 && (next == 'X' || next == 'C' || next == 'M' || next == 'I'))
    {
        return false;
    }
    if ((next == 'X' && previous == 'V') || (next == 'C' && previous == 'L') || (next == 'M' && previous == 'D') || (next == 'M' && previous == 'I'))
    {
        return false;
    }

    return true;
}

int getArabNumber(const char &rimNumber)
{
    switch (rimNumber)
    {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    }
    return 0;
}

int calculation(const char array[], const int &count)
{
    int res = 0;
    int prev = 0, next;
    for (int i = count; i >= 0; --i)
    {
        next = getArabNumber(array[i]);
        if (prev > next)
        {
            res = (res - prev) + (prev - next);
        }
        else
        {
            res += next;
        }
        prev = next;
    }
    return res;
}

int recursion_rand(int m, int i, int c)
{
    if (i == 0)
    {
        return 0;
    }
    else
    {
        return ((m * recursion_rand(m, i - 1, c) + i) % c);
    }
}

void all_asnw()
{
    string cnt1;
    cout << "Введите № задания" << endl;
    cin >> cnt1;
    try
    {
        int cnt = stoi(cnt1);
        if (cnt == 1)
        {
            vector<double> numbers;

            cout << "Введите 10 чисел:" << endl;

            for (int i = 0; i < 10; ++i)
            {
                string input;
                cout << "Число " << (i + 1) << ": ";
                cin >> input;

                // Проверка на корректность введенных данных
                istringstream iss(input);
                double number;
                if (!(iss >> number) || iss.peek() != EOF)
                {
                    cerr << "Ошибка: Некорректный ввод. Пожалуйста, введите число." << endl;
                }

                numbers.push_back(number);
            }

            // Запись чисел в файл
            ofstream outputFile("numbers.txt");
            if (!outputFile.is_open())
            {
                cerr << "Ошибка: Не удалось открыть файл для записи." << endl;
            }

            for (const double &num : numbers)
            {
                outputFile << num << endl;
            }
            outputFile.close();

            // Чтение чисел из файла и вычисление суммы
            ifstream inputFile("numbers.txt");
            if (!inputFile.is_open())
            {
                cerr << "Ошибка: Не удалось открыть файл для чтения." << endl;
            }

            double sum = 0.0;
            string line;
            while (getline(inputFile, line))
            {
                try
                {
                    double num = stod(line);
                    sum += num;
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Ошибка: Некорректные данные в файле." << endl;
                }
            }
            inputFile.close();

            cout << "Сумма чисел из файла: " << setprecision(12) << sum << endl;
        }
        else if (cnt == 2)
        {
            string s;
            cout << "Enter a number: ";
            cin >> s;

            try
            {
                double num = stod(s);
                ex2(num);
            }
            catch (const invalid_argument &e)
            {
                cerr << "Error: Wrong input." << endl;
            }
        }
        else if (cnt == 3)
        {
            string line;
            cout << "Choose figure:\n1-rectangular\n2-triangular\n3-circle\n";
            cin >> line;
            try
            {
                int x = stoi(line);
                switch (x)
                {
                case 1:
                    rect();
                    break;
                case 2:
                    triang();
                    break;
                case 3:
                    circle();
                    break;
                default:
                    cout << "Wrong input";
                }
            }
            catch (const invalid_argument &e)
            {
                cerr << "Error: Wrong input." << endl;
            }
        }
        else if (cnt == 4)
        {
            /*
            ofstream scriptFile("us_flag.gnu");

            scriptFile << "set terminal png" << endl;
            scriptFile << "set output 'us_flag.png'" << endl;
            scriptFile << "set xrange [0:19]" << endl;
            scriptFile << "set yrange [0:10]" << endl;
            scriptFile << "unset xtics" << endl;
            scriptFile << "unset ytics" << endl;

            // Нарисовать фон флага
            scriptFile << "set object 1 rect from 0,0 to 19,10 fc rgb 'white' behind" << endl;

            // Нарисовать полосы
            const int numStripes = 13;
            const double stripeHeight = 10.0 / numStripes;
            for (int i = 0; i < numStripes; ++i)
            {
                string color = (i % 2 == 0) ? "red" : "white";
                scriptFile << "set object " << i + 2 << " rect from 0," << i * stripeHeight << " to 19,"
                           << (i + 1) * stripeHeight << " fc rgb '" << color << "' behind" << endl;
            }

            // Нарисовать синий прямоугольник (кантон)
            scriptFile << "set object " << numStripes + 2 << " rect from 0,7 to 7,10 fc rgb 'blue' behind" << endl;

            // Нарисовать звёзды
            const int numStarsPerRow = 6;
            const int numRows = 9;
            const double starSpacingX = 7.0 / numStarsPerRow;
            const double starSpacingY = 10.0 / numRows;
            const double starSize = 0.4;

            for (int row = 0; row < numRows; ++row)
            {
                for (int col = 0; col < numStarsPerRow; ++col)
                {
                    double x = col * starSpacingX + 0.5 * starSpacingX;
                    double y = 7.0 - row * starSpacingY - 0.5 * starSpacingY;
                    scriptFile << "set object " << numStripes + 3 + row * numStarsPerRow + col
                               << " circle at " << x << "," << y + 9.9 << " size " << starSize << " fc rgb 'white' behind" << endl;
                }
            }

            scriptFile << "plot NaN" << endl;
            scriptFile.close();

            // Вызов Gnuplot для выполнения скрипта
            system("gnuplot us_flag.gnu");

            cout << "Флаг США был нарисован и сохранен как us_flag.png" << endl;
            */

            int flagWidth = 60;  // flag's width
            int flagHeight = 20; // height
            int blueWidth = flagWidth / 2;
            int blueHeight = flagHeight / 2;

            for (int i = 0; i < flagHeight; ++i)
            {
                for (int j = 0; j < flagWidth; ++j)
                {
                    if (i < 10 and j < 26)
                    {
                        if (i % 2 == 0)
                        {
                            cout << "\033[44m *";
                            // cout << "\033[44m ";
                            cout << "\033[44m ";
                            cout << "\033[0m";
                            j++;
                            j++;
                        }
                        else
                        {
                            cout << "\033[44m ";
                            cout << "\033[44m ";
                            cout << "\033[44m ";
                            cout << "\033[0m";
                            j++;
                            j++;
                        }
                    }

                    else if (i % 2 == 0)
                    {
                        cout << "\033[41m ";
                    }
                    else
                    {
                        cout << "\033[47m ";
                    }
                }
                cout << "\033[0m" << endl;
            }
        }
        else if (cnt == 5)
        {

            const int width = 120; // ширина консоли
            const int height = 15; // высота

            const double xMin = -2 * 3.14; // мин x
            const double xMax = 2 * 3.14;  // макс x
            const double yMin = -1.0;      // мин y
            const double yMax = 1.0;       // макc y

            const double dx = (xMax - xMin) / width;
            const double dy = (yMax - yMin) / height;

            for (double y = yMax; y >= yMin; y -= dy)
            {
                for (double x = xMin; x <= xMax; x += dx)
                {
                    double value = sin(x);
                    if (abs(value - y) < dy / 2)
                    {
                        cout << "*";
                    }
                    else if (abs(x) < dx / 2)
                    {
                        cout << "|";
                    }
                    else if (abs(y) < dy / 2)
                    {
                        cout << "-";
                    }
                    else
                    {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
        else if (cnt == 6)
        {
            int sign_symbol;
            const int size = 256;
            char s[size], next, previous;
            int i, recurrence = 0;
            bool isCorrect = true;

            cout << "Enter the Roman number: \n";

            cin.get();
            for (i = 0; (next = cin.get()) != '\n'; ++i)
            {
                /*if (s[0] == '-')
                {
                    sign_symbol = -1;
                }
                */
                if (i == 0)
                {
                    s[i] = next;
                    previous = next;
                }
                else
                {
                    if (previous == next)
                        recurrence++;
                    else
                        recurrence = 0;
                    if (isCorrectLetter(next) && isCorrectSequence(previous, next, recurrence))
                    {
                        s[i] = next;
                        previous = next;
                    }
                    else
                    {
                        isCorrect = false;
                        break;
                    }
                }
            }
            if (!isCorrect || (s[i - 3] == 'I' && s[i - 2] != 'I'))
            {
                cout << "The number deosnt exist";
            }
            else
            {
                cout << "Arabian number: " << calculation(s, i - 1) << endl; //* sign_symbol << endl;
            }
        }
        else if (cnt == 7)
        {
            int s = 0;
            int m, i, c;
            int s1;
            m = 37;
            i = 3;
            c = 64;
            cout << "First version(start on id=-2): ";
            for (int j = 0; j < 10; j++)
            {
                cout << recursion_rand(m, j, c) << " ";
            }

            cout << endl;
            cout << "Secound version(start on id=-2): ";
            s = 0;
            s1 = s;
            m = 25173;
            i = 13849;
            c = 65537;
            for (int j = 0; j < 10; j++)
            {
                cout << recursion_rand(m, j, c) << " ";
            }
            cout << endl;
        }
        else if (cnt == 8)
        {
            double A[3][4];
            double B[4][2];
            A[0][0] = 5;
            A[0][1] = 2;
            A[0][2] = 0;
            A[0][3] = 10;

            A[1][0] = 3;
            A[1][1] = 5;
            A[1][2] = 2;
            A[1][3] = 5;

            A[2][0] = 20;
            A[2][1] = 0;
            A[2][2] = 0;
            A[2][3] = 0;

            B[0][0] = 1.20;
            B[0][1] = 0.50;

            B[1][0] = 2.80;
            B[1][1] = 0.40;

            B[2][0] = 5.00;
            B[2][1] = 1.00;

            B[3][0] = 2.00;
            B[3][1] = 1.50;

            int row1, row2, col1, col2;
            double **c;

            row1 = 3;
            col1 = 4;
            row2 = 4;
            col2 = 2;

            c = new double *[row1];
            for (int i = 0; i < row1; i++)
            {
                c[i] = new double[col2];
                for (int j = 0; j < col2; j++)
                {
                    c[i][j] = 0;
                    for (int k = 0; k < col1; k++)
                        c[i][j] += A[i][k] * B[k][j];
                }
            }
            /*
                    cout << "Matrix C: " << endl;
                    for (int i = 0; i < row1; i++)
                    {
                        for (int j = 0; j < col2; j++)
                            cout << c[i][j] << " ";
                        cout << endl;
                    }
                    cin.get();
                    cin.get();
            */
            int maxx1 = 0;
            int minn1 = 10000;
            int idd1, idn1;
            for (int k = 0; k < 3; k++)
            {
                if (c[k][0] > maxx1)
                {
                    maxx1 = c[k][0];
                    idd1 = k;
                }
                if (c[k][0] < minn1)
                {
                    minn1 = c[k][0];
                    idn1 = k;
                }
            }
            cout << "1 question: max id: " << idd1 + 1 << "  ";
            cout << "minn id: " << idn1 + 1 << endl;

            int maxx = 0;
            int minn = 10000;
            int idd, idn;
            for (int k = 0; k < 3; k++)
            {
                if (c[k][1] > maxx)
                {
                    maxx = c[k][1];
                    idd = k;
                }
                if (c[k][1] < minn)
                {
                    minn = c[k][1];
                    idn = k;
                }
            }
            cout << "2 question: max id: " << idd + 1 << "  ";
            cout << "minn id: " << idn + 1 << endl;

            cout << "3 question: " << c[0][0] + c[1][0] + c[2][0] << endl;
            cout << "4 question: " << c[0][1] + c[1][1] + c[2][1] << endl;
            cout << "5 question: " << c[0][1] + c[1][1] + c[2][1] + c[0][0] + c[1][0] + c[2][0] << endl;
        }
        else if (cnt == 9)
        {
            string inputNum;
            string s_sourceBase, s_targetBase;

            cout << "Введите число: ";
            cin >> inputNum;
            cout << "Введите исходную систему счисления: ";
            cin >> s_sourceBase;
            cout << "Введите целевую систему счисления: ";
            cin >> s_targetBase;
            try
            {
                bool fl = 1;
                int sourceBase = stoi(s_sourceBase);
                int numb = stoi(inputNum);
                int targetBase = stoi(s_targetBase);
                for (int p = 0; p < inputNum.length(); p++)
                {
                    int sg = numb / (pow(10, inputNum.length() - p - 1));
                    sg = sg % 10;
                    if (sg >= sourceBase)
                    {
                        fl = 0;
                        break;
                    }
                }
                if (fl)
                {
                    string result = ConvertBase(inputNum, sourceBase, targetBase);
                    cout << "Results: " << result << endl;
                }
                else
                {
                    cout << "Wrong input number" << endl;
                }
            }
            catch (const invalid_argument &e)
            {
                cerr << "Error: Wrong input." << endl;
            }
        }
        else
        {
            cout << "Wrong number";
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: This task doesnt exist." << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    ios_base::sync_with_stdio(0);
    while (1)
    {
        try
        {
            all_asnw();
            cin.get();
            cin.get();
        }
        catch (const invalid_argument &e)
        {
            cerr << "Caused an error, try again." << endl;
        }
        catch (const exception &e)
        {
            cerr << "Caught exception: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Caught unknown exception" << endl;
        }
        system("clear");
    }
}