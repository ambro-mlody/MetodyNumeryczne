#include <iostream>
#include <cmath>

struct ReturnVal {
    double pn;
    double err;
    double ypn;
    int k;

    ReturnVal() { pn = 0; err = 0; ypn = 0; k = 0; }
};

ReturnVal secant(double p0, double p1, double delta, double epsilon, int max)
{
    ReturnVal r;
    for (r.k = 1; r.k < max; r.k++)
    {
        r.pn = p1 - sin(p1) * (p1 - p0) / (sin(p1) - sin(p0));
        r.err = fabs(r.pn - p1);
        p0 = p1;
        p1 = r.pn;
        r.ypn = sin(r.pn);
        if ((r.err < delta) || (fabs(r.ypn) < epsilon))
            return r;
    }
}

int main()
{
    double p0, p1, delta, epsilon;
    int max;
    std::cin >> p0 >> p1 >> delta >> epsilon >> max;

    auto r = secant(p0, p1, delta, epsilon, max);

    std::cout << "pn = " << r.pn << std::endl << "err = " << r.err << std::endl << "ypn = " << r.ypn << std::endl << "k = " << r.k << std::endl;

    return 0;
}
