#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

template <typename name>
class matrix : public std::error_code {
    std::vector<std::vector<name>> main_matrix;
    size_t line = 0;
    size_t column = 0;
public:
    matrix() {
        name elem;
        std::vector<name> value;
        std::cout << "Enter the size of the matrix and then the values \n";
        std::cin >> line >> column;
        for (size_t i = 0; i < line; ++i) {
            main_matrix.push_back(value);
            for (size_t j = 0; j < column; ++j) {
                std::cin >> elem;
                main_matrix[i].push_back(elem);
            }
        }
    }
    matrix(size_t line, size_t column) : line(line), column(column) {
        std::vector<name> val;
        for (int i = 0; i < line; ++i) {
            main_matrix.push_back(val);
            for (int j = 0; j < column; ++j) {
                main_matrix[i].push_back(0);
            }
        }
    }

    matrix(std::string s) {
        std::ifstream file(s);
        if (file.is_open()) {
            std::string str;
            file >> line >> column;
            for(size_t i = 0; i < line; ++i) {
                std::getline(file, str);
                std::stringstream(str);
                std::vector<name> value;
                name elem;
                for (size_t j = 0; j < column; ++j) {
                    str >> elem;
                    value.push_back(elem);
                }
                main_matrix.push_back(value);
            }
        } else throw std::runtime_error("File is close");
    }

    ~matrix() {
        main_matrix = {};
        line = 0;
        column = 0;
    }

    template<typename type>
    friend matrix<type> operator*(const matrix<type> &matrix_1, type scalar);

    template<typename type>
    friend matrix<type> operator*(const matrix<type> &matrix_1, const matrix<type> &matrix_2);

    template<typename type>
    friend matrix<type> operator+(const matrix<type> &matrix_1, const matrix<type> &matrix_2);

    template<typename type>
    friend matrix<type> operator-(const matrix<type> &matrix_1, const matrix<type> &matrix_2);

    template<typename type>
    friend std::ostream &operator<<(std::ostream &out, matrix<type> matrix_1);

    matrix<name> &operator=(const matrix<name> &matrix_1) {
        this->line = matrix_1.line;
        this->column = matrix_1.column;
        this->main_matrix = matrix_1.main_matrix;
        return *this;
    }

    bool operator==(const matrix<name> &matrix_1) const {
        if (line != matrix_1.line || column != matrix_1.column ) return false;
        for (size_t i = 0; i < line; ++i) {
            for (size_t j = 0; j < column; ++j) {
                if (matrix_1[i][j] != main_matrix[i][j]) return false;
            }
        }
        return true;
    }

    bool operator!=(const matrix<name> &matrix_1) const {
        if (line != matrix_1.line || column != matrix_1.column ) return true;
        for (size_t i = 0; i < line; ++i) {
            for (size_t j = 0; j < column; ++j) {
                if (matrix_1[i][j] != main_matrix[i][j]) return true;
            }
        }
        return false;
    }

    bool operator==(int item) {
        if (item == 0) {
            for (size_t i = 0; i < line; ++i) {
                for (size_t j = 0; j < column; ++j) {
                    if (main_matrix[i][j] != 0) return false;
                }
            }
        } else if (item == 1) {
            for (size_t i = 0; i < line; ++i) {
                for (size_t j = 0; j < column; ++ j) {
                    if ((i == j && main_matrix[i][j] != 1) || (i != j && main_matrix[i][j] != 0)) return false;
                }
            }
        } else throw std::runtime_error("The check should be for a single and zero matrix");
        return true;
    }

    matrix get_minor (size_t size, size_t l, size_t c) const {
        if (line != column) {
            throw std::runtime_error("Matrix is not square");
        }
        matrix matrix_1(size - 1, size - 1);
        int set_row = 0;
        int set_col = 0;
        for (size_t i = 0; i < size - 1; i++) {
            if (i == l) {
                set_row = 1;
            }
            set_col = 0;
            for (size_t j = 0; j < size - 1; j++) {
                if (j == c) {
                    set_col = 1;
                }
                matrix_1.main_matrix[i][j] = main_matrix[i + set_row][j + set_col];
            }
        }
        return matrix_1;
    }

    name determinant(size_t size) const {
        name det = 0;
        name sign = 1;
        if (size == 1) {
            return main_matrix[0][0];
        } else if (size == 2) {
            return (main_matrix[0][0] * main_matrix[1][1] - main_matrix[0][1] * main_matrix[1][0]);
        }
        for (size_t j = 0; j < size; j++) {
            matrix matrix_1 = get_minor(size, 0, j);
            det = det + (sign * main_matrix[0][j]*matrix_1.determinant(size - 1));
            sign = -sign;
        }
        return det;
    }

    matrix<name> Transpose() const{
        matrix<name> transpose_matrix(line, column);
        for (int i = 0; i < line; ++i) {
            for (int j = 0; j < column; ++j) {
                transpose_matrix.main_matrix[i][j] = this->main_matrix[j][i];
            }
        }
        return transpose_matrix;
    }


    matrix<name> operator!() const {
        if (line != column) {
            throw std::runtime_error("Matrix is not square");
        }
        matrix<name> matrix_1(line, column);
        matrix<name> t = Transpose();
        for (size_t i = 0; i < line; i++) {
            for (size_t j = 0; j < column; j++) {
                matrix_1.main_matrix[i][j] = (t.get_minor(line, i, j)).determinant(line - 1) * pow(-1, i+j);
            }
        }
        matrix<name> b(line, column);
        b = (matrix_1 * (1/this->determinant(line)));
        return b;
    }

    static matrix<name>& zero_matrix(size_t size) {
        matrix<name> Matrix = new matrix<name>;
        Matrix.line = size;
        Matrix.column = size;
        for (size_t i = 0; i < size; ++i) {
            std::vector<name> a;
            for (size_t j = 0; j < size; ++j) {
                a.push_back(0);
            }
            Matrix.main_matrix.push_back(a);
        }
        return *Matrix;
    }

    static matrix<name>& unit_matrix(size_t size) {
        matrix<name> Matrix = new matrix<name>;
        Matrix.line = size;
        Matrix.column = size;
        for (size_t i = 0; i < size; ++i) {
            std::vector<name> a;
            for (size_t j = 0; j < size; ++j) {
                if (i == j) {
                    a.push_back(1);
                }
                else a.push_back(0);
            }
            Matrix.main_matrix.push_back(a);
        }
        return *Matrix;
    }
};

template<typename type>
matrix<type> operator*(const matrix<type> &matrix_1, type scalar) {
    matrix<type> m(matrix_1.line, matrix_1.column);
    for (size_t i = 0; i < matrix_1.line; ++i) {
        for (size_t j = 0; j < matrix_1.column; ++j) {
            m.main_matrix[i][j] = matrix_1.main_matrix[i][j] * scalar;
        }
    }
    return m;
}

template<typename type>
matrix<type> operator*(const matrix<type> &matrix_1, const matrix<type> &matrix_2) {
    if(matrix_1.column != matrix_2.line) {
        throw std::runtime_error("Not same values for multiplication");
    }
    matrix<type> m(matrix_1.line, matrix_2.column);
    for (size_t i = 0; i < matrix_1.line; ++i) {
        for (size_t j = 0; j < matrix_2.column; ++j) {
            m.main_matrix[i][j] = 0;
            for (int k = 0; k < matrix_1.column; ++k) {
                m.main_matrix[i][j] += matrix_1.main_matrix[i][k] * matrix_2.main_matrix[k][j];
            }
        }
    }
    return m;
}

template<typename type>
matrix<type> operator+(const matrix<type> &matrix_1, const matrix<type> &matrix_2) {
    if(matrix_1.line != matrix_2.line || matrix_1.column != matrix_2.column) {
        throw std::runtime_error("Not same values for addition");
    }
    matrix<type> m(matrix_1.line, matrix_1.column);
    for(size_t i = 0; i < matrix_1.line; ++i) {
        for (size_t j = 0; j < matrix_1.column; ++j) {
            m.main_matrix[i][j] = matrix_1.main_matrix[i][j] + matrix_2.main_matrix[i][j];
        }
    }
    return m;
}

template<typename type>
matrix<type> operator-(const matrix<type> &matrix_1, const matrix<type> &matrix_2) {
    if(matrix_1.line != matrix_2.line || matrix_1.column != matrix_2.column) {
        throw std::runtime_error("Not same values for subtraction");
    }
    matrix<type> m(matrix_1.line, matrix_1.column);
    for(size_t i = 0; i < matrix_1.line; ++i) {
        for (size_t j = 0; j < matrix_1.column; ++j) {
            m.main_matrix[i][j] = matrix_1.main_matrix[i][j] - matrix_2.main_matrix[i][j];
        }
    }
    return m;
}

template<typename type>
std::ostream &operator<<(std::ostream &out, matrix<type> matrix_1) {
    for (size_t i = 0; i < matrix_1.line; ++i) {
        for (size_t j = 0; j < matrix_1.column; ++j) {
            out << matrix_1.main_matrix[i][j] << " ";
        }
        out << std::endl;
    }
    out << std::endl;
    return out;
}

int main() {
    matrix<int> M;
    matrix<int> M1;
    std::cout << "matrix addition: \n" << M + M1;
    std::cout << "matrix multiplication: \n" << M * M1;
    std::cout << "multiplying a matrix by a number: \n" << M * 2;
    std::cout << !M;

    return 0;
}
