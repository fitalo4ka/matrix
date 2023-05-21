#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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
        // std::vector<std::vector<name>> main_matrix(line, std::vector<int>(column, 0));
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
        std::string str;
        if (file.is_open()) {
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

    matrix<name> operator!() const {
        if (line != column) {
            throw std::runtime_error("Matrix is not square");
        }
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
}

int main() {
    matrix<int> M;
    matrix<int> M1;
    std::cout << "matrix addition: \n" << M + M1;
    std::cout << "matrix multiplication: \n" << M * M1;
    std::cout << "multiplying a matrix by a number: \n" << M * 2;

    return 0;
}
