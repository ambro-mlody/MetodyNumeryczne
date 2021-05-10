#include <iostream>
#include <cmath>
#include <complex>
#include <vector>

typedef std::complex<double> Complex;

struct Result
{
	Complex pn;
	double err;
	int k;

	Result() { pn = 0; err = 0; k = 0; }
};

struct HRes
{
	Complex y;
	Complex z;

	HRes() { y = 0; z = 0; }
	HRes(Complex a, Complex b) { y = a; z = b; }
};

HRes dhorner(std::vector<Complex> W, Complex x)
{
	int n = W.size();
	Complex y = W[0];
	Complex z = 0;
	for (int i = 1; i < n; i++)
	{
		z = y + z * x;
		y = y * x + W[i];
	}

	return { y, z };
}

Result polnewton(std::vector<Complex> W, Complex p0, double delta, int max)
{
	Result r;
	for (r.k = 1; r.k < max; r.k++)
	{
		auto c = dhorner(W, p0);
		r.pn = p0 - c.y / c.z;
		r.err = std::abs(r.pn - p0);
		p0 = r.pn;
		if (r.err < delta)
			return r;
	}
}

int main(int argc, char **argv)
{
	std::vector<Complex> W;
	for (int i = 1; i < argc - 5; i+=2)
	{
		double real = std::atof(argv[i]);
		double im = std::atof(argv[i + 1]);
		Complex temp{ real, im };
		W.push_back(temp);
	}

	double real = std::atof(argv[argc-4]);
	double im = std::atof(argv[argc-3]);
	Complex p0{ real, im };

	double delta = std::atof(argv[argc-2]);
	int max = std::atoi(argv[argc-1]);

	Result r = polnewton(W, p0, delta, max);
	std::cout << std::endl << "pn = " << r.pn << std::endl << "err = " << r.err << std::endl << "k = " << r.k << std::endl;
	return 0;
}
