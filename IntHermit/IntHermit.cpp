#include <iostream>
#include <vector>

typedef std::vector<double> Vector;

class Matrix
{
    std::vector<Vector> matrix;
    int rows;
    int columns;

public:

    Matrix() {}
    Matrix(int n, int m)
    {
        rows = n;
        columns = m;
        for (int i = 0; i < n; i++)
        {
            matrix.push_back(std::vector<double>());
            for (int j = 0; j < m; j++)
                matrix[i].push_back(0);
        }
    }

    void set_row(int row, std::vector<double> val)
    {
        for (int i = 0; i < val.size(); i++)
        {
            this->matrix[row][i] = val[i];
        }
    }

    void set_column(int column, Vector val)
    {
        for (int i = 0; i < val.size(); i++)
        {
            this->matrix[i][column] = val[i];
        }
    }

    int get_rows() { return rows; }
    int get_columns() { return columns; }
    std::vector<Vector> get_matrix() { return matrix; }

    double get(int i, int j) { return matrix[i][j]; }
    void set(int i, int j, double val) { matrix[i][j] = val; }



    friend std::ostream& operator<<(std::ostream& o, Matrix A)
    {
        for (int i = 0; i < A.get_rows(); i++)
        {
            for (int j = 0; j < A.get_columns(); j++)
            {
                o << A.get(i, j) << " ";
            }
            o << std::endl;
        }
        o << std::endl;
        return o;
    }

    friend Matrix operator*(Vector a, Matrix b)
    {
        Matrix res(1, b.get_columns());
        for (int j = 0; j < b.get_columns(); ++j)
            for (int k = 0; k < a.size(); ++k)
            {
                res.set(0, j, res.get(0, j) + a[k] * b.get(k, j));
            }
        return res;
    }
};

Vector poly(double x)
{
    Vector y;
    y.push_back(1);
    y.push_back(-x);
    return y;
}

Vector conv(Vector a, Vector b)
{
    Vector res;
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < a.size(); j++)
        {
            if (j + i < res.size())
                res[j + i] += a[j] * b[i];
            else
                res.push_back(a[j] * b[i]);
        }
    }
    return res;
}

unsigned int factorial(int n)
{
    unsigned int r = 1;
    for (int i = 1; i <= n; i++)
    {
        r *= i;
    }
    return r;
}

struct Result
{
    Matrix D;
    Vector C;
};

Result inthermit(Vector X, Vector Y)
{
    int n = X.size();
    Matrix D = Matrix(n, n);
    D.set(0, 0, Y[0]);
    for (int j = 1; j < n; j++)
    {
        if (X[j] == X[j - 1])
        {
            D.set(j, 0, D.get(j - 1, 0));
        }
        else
        {
            D.set(j, 0, Y[j]);
        }
    }

    for (int j = 1; j < n; j++)
    {
        int s = 0;
        for (int k = j; k < n; k++)
        {
            if (X[k] == X[k - j])
            {
                D.set(k, j, Y[k - s] / factorial(j));
                s++;
            }
            else
            {
                D.set(k, j, (D.get(k, j - 1) - D.get(k - 1, j - 1)) / (X[k] - X[k - j]));
                s = 0;
            }
        }
    }

    Vector C;
    C.push_back(D.get(n - 1, n - 1));
    for (int k = n - 2; k > -1; k--)
    {
        C = conv(C, poly(X[k]));
        int m = C.size();
        C[m - 1] = C[m - 1] + D.get(k, k);
    }
    return {D, C};
}

int main(int argc, char** argv)
{
    std::vector<double> x;
    std::vector<double> y;

    for (int i = 0; i < argc / 2; i++)
    {
        x.push_back(std::atof(argv[i + 1]));
        y.push_back(std::atof(argv[argc / 2 + i + 1]));
    }

    Result res = inthermit(x, y);
    std::cout << "D = \n" << res.D << "C = \n";
    for (auto a : res.C)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
    return 0;
}