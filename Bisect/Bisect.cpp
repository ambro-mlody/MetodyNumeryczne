#include <iostream>
#include <functional>
#include <cmath>

struct ReturnVal
{
    double c;
    double err;
    double yc;
    int k;

    ReturnVal() { c = 0; err = 0; yc = 0; k = 0; }
};

int sign(float x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    else return 0;
}

ReturnVal bisect(double a, double b, double delta, double epsilon, int max)
{
    double ya = sin(a);
    double yb = sin(b);
    ReturnVal r;
    if (sign(ya) == sign(yb))
    {
        std::cout << "error: sign(f(a)) == sign(f(b))" << std::endl;
        return r;
    }

    for (r.k = 1; r.k < max; r.k++)
    {
        r.c = a + (b - a) / 2;
        r.yc = sin(r.c);
        r.err = fabs((b - a) / 2);
        if ((r.err < delta) || (fabs(r.yc) < epsilon))
            return r;
        if (sign(yb) == sign(r.yc))
        {
            b = r.c;
            yb = r.yc;
        }
        else
        {
            a = r.c;
        }
    }

}

int main()
{
    double a;
    double b;
    double delta;
    double epsilon;
    int max;

    std::cin >> a >> b >> delta >> epsilon >> max;
    auto result = bisect(a, b, delta, epsilon, max);
    std::cout << "c = " << result.c << std::endl << "yc = " << result.yc << std::endl << "err = " << result.err << std::endl << "k = " << result.k << std::endl;

    return 0;
}
