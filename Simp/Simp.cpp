#include <iostream>
#include <vector>
#include <algorithm>

double simp(double a, double b, int M)
{
    double h = (b - a) / (2 * M);
    std::vector<double> x;
    for (double i = a + h; i <= b - h; i += 2 * h)
    {
        x.push_back(i);
    }
    std::vector<double> y;
    for (auto f : x)
    {
        y.push_back(sin(f));
    }
    double s1 = 0;
    for (auto z : y)
        s1 += z;
    x.clear();
    y.clear();
    for (double i = a + 2 * h; i <= b - 2 * h; i += 2 * h)
    {
        x.push_back(i);
    }
    for (auto f : x)
    {
        y.push_back(sin(f));
    }
    double s2 = 0;
    for (auto z : y)
        s2 += z;
    double s = h * (sin(a) + sin(b) + 4 * s1 + 2 * s2) / 3;
    return s;
}

int main(int argc, char** argv)
{
    auto res = simp(std::atof(argv[1]), std::atof(argv[2]), std::atoi(argv[3]));
    std::cout << "s = " << std::endl << res;
    return 0;
}