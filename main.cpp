#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

template <typename name>
class matrix {
    std::vector<std::vector<name>> mat;
    int n = 0;
    int m = 0;
public:
    matrix() {
        name el;
        std::vector<name> val;
        std::cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            mat.push_back(val);
            for (int j = 0; j < m; ++j) {
                mat[i].push_back(std::cin >> el);
            }
        }
    }
    matrix(int line, int column) : n(line), m(column) {
        std::vector<name> val;
        for (int i = 0; i < n; ++i) {
            mat.push_back(val);
            for (int j = 0; j < m; ++j) {
                mat[i].push_back(0);
            }
        }
    }

    matrix(std::string s) {
        std::ifstream file(s);
        std::string a;
        if (file.is_open()) {
            file >> n >> m;
            for(int i = 0; i < n; ++i) {
                std::getline(file, a);
                std::stringstream(a);
                std::vector<name> val;
                name el;
                for (int j = 0; j < m; ++j) {
                    a >> el;
                    val.push_back(el);
                }
                mat.push_back(val);
            }
        }
    }

    ~matrix() {
        mat = {};
        n = 0;
        m = 0;
    }

    template<typename type>
    friend matrix<type> operator*(matrix<type> &a, type scalar);

    template<typename type>
    friend matrix<type> operator*(matrix<type> &a, matrix<type> &b);

    template<typename type>
    friend matrix<type> operator+(matrix<type> &a, matrix<type> &b);

    template<typename type>
    friend matrix<type> operator-(matrix<type> &a, matrix<type> &b);

    matrix<name> &operator=(const matrix<name> &a) {
        n = a.n;
        m = a.m;
        mat = a.mat;
        return *this;
    }

    bool operator==(const matrix<name> &a) const {
        if (n != a.n || m != a.m ) return false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] != mat[i][j]) return false;
            }
        }
        return true;
    }

    bool operator!=(const matrix<name> &a) const {
        if (n != a.n || m != a.m ) return true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] != mat[i][j]) return true;
            }
        }
        return false;
    }

    bool operator==(int item) {
        if (item == 0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (mat[i][j] != 0) return false;
                }
            }
        } else if (item == 1) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++ j) {
                    if ((i == j && mat[i][j] != 1) || (i != j && mat[i][j] != 0)) return false;
                }
            }
        }
        return true;
    }

    matrix<name> operator!() const {
        if (n != m) {
            std::cerr << "Not square matrix";
        }
    }
};

template<typename type>
matrix<type> operator*(matrix<type> &a, type scalar) {
    matrix<type> m(a.n, a.m);
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            m.mat[i][j] = a.mat[i][j] * scalar;
        }
    }
    return m;
}

template<typename type>
matrix<type> operator*(matrix<type> &a, matrix<type> &b) {
    if(a.m != b.n) {
        std::cerr << "Not same values for multiplication";
    }
    matrix<type> m(a.n, b.m);
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < b.m; ++j) {
            m.mat[i][j] = 0;
            for (int k = 0; k < a.m; ++k) {
                m.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return m;
}

template<typename type>
matrix<type> operator+(matrix<type> &a, matrix<type> &b) {
    if(a.n != b.n || a.m != b.m) {
        std::cerr << "Not same values for addition";
    }
    matrix<type> m(a.n, a.m);
    for(int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            m.mat[i][j] = a.mat[i][j] + b.mat[i][j];
        }
    }
    return m;
}

template<typename type>
matrix<type> operator-(matrix<type> &a, matrix<type> &b) {
    if(a.n != b.n || a.m != b.m) {
        std::cerr << "Not same values for subtraction";
    }
    matrix<type> m(a.n, a.m);
    for(int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            m.mat[i][j] = a.mat[i][j] - b.mat[i][j];
        }
    }
    return m;
}

int main() {

    return 0;
}
