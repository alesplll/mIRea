#include <bits/stdc++.h>
#include <iomanip>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <stdexcept>

using namespace std;

int main()
{

    ofstream datafile("data.txt");
    if (!datafile.is_open())
    {
        cerr << "Ошибка открытия файла для записи данных." << endl;
    }
    const int numPoints = 1000;
    const double xMin = -4 * M_PI;
    const double xMax = 4 * M_PI;
    const double dx = (xMax - xMin) / (numPoints - 1);

    for (int i = 0; i < numPoints; ++i)
    {
        double x = xMin + i * dx;
        double y = sin(x);
        datafile << x << " " << y << endl;
    }

    datafile.close();

    FILE *gnuplotPipe = popen("gnuplot", "w");
    if (!gnuplotPipe)
    {
        cerr << "Ошибка запуска gnuplot." << endl;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'graph.png'\n");
    fprintf(gnuplotPipe, "set title 'График функции y = sin(x)'\n");
    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'y'\n");
    fprintf(gnuplotPipe, "plot 'data.txt' with linespoints title 'y = sin(x)'\n");
    fflush(gnuplotPipe);

    pclose(gnuplotPipe);

    system("xdg-open graph.png");

    return 0;
}
