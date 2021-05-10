#include <iostream>
#include <vector>

class Matrix
{
    std::vector<std::vector<double>> matrix;
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

    int get_rows() { return rows; }
    int get_columns() { return columns; }
    std::vector<std::vector<double>> get_matrix() { return matrix; }

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

    friend Matrix operator*(std::vector<double> a, Matrix b)
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

std::vector<double> poly(double x)
{
    std::vector<double> y;
    y.push_back(1);
    y.push_back(-x);
    return y;
}

std::vector<double> conv(std::vector<double> a, std::vector<double> b)
{
    std::vector<double> res;
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

std::vector<double> div(std::vector<double> a, double x)
{
    std::vector<double> res;
    for (auto v : a)
    {
        res.push_back(v / x);
    }
    return res;
}

struct Res 
{
    Matrix C;
    Matrix L;
};

Res intlagran(std::vector<double> X, std::vector<double> Y)
{
    Res res;
    int w = X.size();
    res.L = Matrix(w, w);
    for (int k = 0; k < w; k++)
    {
        std::vector<double> V;
        V.push_back(1);
        for (int j = 0; j < w; j++)
        {
            if (k != j)
            {
                V = div(conv(V, poly(X[j])), (X[k] - X[j]));
            }
        }
        res.L.set_row(k, V);
    }
    res.C = Y * res.L;
    return res;
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

    Res res = intlagran(x, y);
    std::cout << "C = \n" << res.C << "L = \n" << res.L;
    return 0;
}
