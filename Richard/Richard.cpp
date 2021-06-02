#include <iostream>
#include <vector>
#include <cmath>

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

Matrix Richard(double a, double h, int M)
{
    Matrix D(M + 1, M + 1);
    for (int n = 0; n <= M; n++)
    {
        double dh = h / std::pow(2, n);
        D.set(n, 0, (std::pow(a + dh, 2) - std::pow(a - dh, 2)) / (2 * dh));
    }
    for (int k = 1; k <= M; k++)
    {
        for (int n = k; n <= M; n++)
        {
            D.set(n, k, D.get(n, k - 1) + (D.get(n, k - 1) - D.get(n - 1, k - 1)) / (4 * k - 2));
        }
    }
    return D;
}

int main(int argc, char** argv)
{
    auto res = Richard(std::atof(argv[1]), std::atof(argv[2]), std::atof(argv[3]));
    std::cout << "D = " << std::endl << res;
    return 0;
}