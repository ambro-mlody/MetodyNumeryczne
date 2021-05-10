#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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

    Matrix(std::vector<double> matrix) : Matrix(std::sqrt(matrix.size()), std::sqrt(matrix.size()))
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                this->matrix[i][j] = matrix[i * rows + j];
            }
        }
    }

    int get_rows() { return rows; }
    int get_columns() { return columns; }
    std::vector<std::vector<double>> get_matrix() { return matrix; }

    double get(int i, int j) { return matrix[i][j]; }
    void set(int i, int j, double val) {matrix[i][j] = val; }

    Matrix transpose()
    {
        Matrix dest(columns, rows);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                dest.set(j, i, matrix[i][j]);
            }
        }

        return dest;
    }

    void identity()
    {
        for (int i = 0; i < std::min(rows, columns); i++)
        {
            matrix[i][i] = 1;
        }
    }

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

    friend Matrix operator/(Matrix A, Matrix B)
    {
        Matrix res(A.get_rows(), A.get_columns());
        for (int i = 0; i < A.get_rows(); i++)
        {
            for (int j = 0; j < A.get_columns(); j++)
            {
                res.set(i, j, A.get(i, j) / B.get(i, j));
            }
        }

        return res;
    }
};

Matrix max(Matrix A)
{
    Matrix res(1, A.get_columns());
    for (int i = 0; i < A.get_columns(); i++)
    {
        int max = 0;
        for (int j = 0; j < A.get_rows(); j++)
        {
            if (A.get(j, i) > max)
                max = A.get(j, i);
        }
        res.set(0, i, max);
    }
    return res;
}

Matrix col(Matrix A, std::vector<int> p, int k, int n)
{
    Matrix res(n-k, 1);
    for (int i = k, j = 0; i < n; i++, j++)
    {
        res.set(j, 0, A.get(p[i], k));
    }
    return res;
}

Matrix row(Matrix A, std::vector<int> p, int k, int n)
{
    Matrix res(1, n - k);
    for (int i = k, j = 0; i < n; i++, j++)
    {
        res.set(0, j, A.get(0, p[i]));
    }
    return res;
}

Matrix abs(Matrix v)
{
    for (int i = 0; i < v.get_rows(); i++)
    {
        for (int j = 0; j < v.get_columns(); j++)
        {
            if (v.get(i, j) < 0)
                v.set(i, j, v.get(i, j) * -1);
        }
    }

    return v;
}

int pos(Matrix A)
{
    int pos = 0;
    double max = 0;
    for (int i = 0; i < A.get_rows(); i++)
    {
        if (A.get(i, 0) > max)
        {
            max = A.get(i, 0);
            pos = i;
        }
    }
    return pos;
}

Matrix matrix(Matrix A, std::vector<int> p)
{
    Matrix res(A.get_rows(), A.get_columns());
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = 0; j < A.get_columns(); j++)
        {
            res.set(i, j, A.get(p[i], j));
        }
    }
    return res;
}

struct PLU {
    Matrix P;
    Matrix L;
    Matrix U;

    PLU(Matrix &p, Matrix &l, Matrix &u)
    {
        P = p;
        L = l;
        U = u;
    }
};

PLU decomPLU(Matrix A)
{
    int n = A.get_rows();
    int m = A.get_columns();
    Matrix P = Matrix(n, m); P.identity();
    Matrix L = Matrix(n, m); L.identity();
    Matrix U{n, m};
    PLU res(P, L, U);

    if (n != m)
    {
        std::cout << "error: n != m \n";
        exit(0);
    }

    std::vector<int> p;
    for (int i = 0; i < n; i++)
    {
        p.push_back(i);
    }

    Matrix s = max(abs(A.transpose()));

    for (int k = 0; k < n - 1; k++)
    {
        int j = pos(abs(col(A, p, k, n)) / row(s, p, k, n).transpose());
        j += k;
        int t = p[j];
        p[j] = p[k];
        p[k] = t;
        for (int i = k + 1; i < n; i++)
        {
            double z = A.get(p[i], k) / A.get(p[k], k);
            A.set(p[i], k, z);

            for (int r = k + 1; r < n; r++)
            {
                A.set(p[i], r, A.get(p[i], r) - z * A.get(p[k], r));
            }
        }
    }

    res.P = matrix(res.P, p);
    A = matrix(A, p);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i <= j)
            {
                res.U.set(i, j, A.get(i, j));
            }
            else
            {
                res.L.set(i, j, A.get(i, j));
            }
        }
    }

    return res;
}

int main(int argc, char** argv)
{
    std::vector<double> input;
    for (int i = 1; i < argc; i++)
    {
        input.push_back(atof(argv[i]));
    }

    Matrix A(input);

    PLU res = decomPLU(A);

    std::cout << "A = \n" << A << "P = \n" << res.P << "L = \n" << res.L << "U = \n" << res.U;

    return 0;
}