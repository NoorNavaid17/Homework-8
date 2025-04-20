#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<int>(c)) {}

    void set(int r, int c, int val) {
        data[r][c] = val;
    }

    int get(int r, int c) const {
        return data[r][c];
    }

    Matrix transpose() const {
        Matrix t(cols, rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                t.set(j, i, data[i][j]);
        return t;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.cols; j++)
                for (int k = 0; k < cols; k++)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.set(i, j, data[i][j] + other.get(i, j));
        return result;
    }

    Matrix scalarMultiply(int scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.set(i, j, data[i][j] * scalar);
        return result;
    }

    void display() const {
        for (const auto& row : data) {
            for (int val : row)
                std::cout << val << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    Matrix A(2, 2), B(2, 3), C(2, 3);

    A.set(0, 0, 6); A.set(0, 1, 4);
    A.set(1, 0, 8); A.set(1, 1, 3);

    B.set(0, 0, 1); B.set(0, 1, 2); B.set(0, 2, 3);
    B.set(1, 0, 4); B.set(1, 1, 5); B.set(1, 2, 6);

    C.set(0, 0, 2); C.set(0, 1, 4); C.set(0, 2, 6);
    C.set(1, 0, 1); C.set(1, 1, 3); C.set(1, 2, 5);

    Matrix result = A + (B.scalarMultiply(3) * C.transpose());

    std::cout << "D = A + (3 * B) * C^T:" << std::endl;
    result.display();

    return 0;
}
