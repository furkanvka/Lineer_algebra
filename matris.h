#ifndef matris  
#define matris  

#include <vector>
#include <stdexcept> //error library
#include <iostream>

template <class T, int sutun, int satir>
class matrix {
private:
    T m_data[sutun][satir];  // Matrix data storage

public:
    // Default constructor
    matrix();

    // Constructor from a vector
    matrix(const std::vector<T>& vec);

    // Access elements
    T& operator()(size_t y, size_t x);
    const T& operator()(size_t y, size_t x) const;

    // Assignment operator
    matrix& operator=(const matrix<T, sutun, satir>& other);

    // Scalar multiplication
    matrix operator*(const T& scalar);

    // Matrix multiplication
    template <int p>
    matrix<T, sutun, p> operator*(const matrix<T, satir, p>& other);

    // Scalar division
    matrix operator/(const T& scalar);

    // Matrix addition
    matrix operator+(const matrix<T, sutun, satir>& other);

    // Transpose matrix
    matrix<T, satir, sutun> transpoz();

    // Determinant of the matrix (recursive)
    T determinant_recersive(const T mat[sutun][satir], int n);

    // Determinant of the matrix
    T determinant();

    // Adjugate matrix
    matrix<T, satir, sutun> adj();

    // Fill the matrix with a value
    void fill(T data);

    // Print the matrix
    void print();
};

// Default constructor
template <class T, int sutun, int satir>
matrix<T, sutun, satir>::matrix() {
    for (int i = 0; i < sutun; i++) {
        for (int j = 0; j < satir; j++) {
            m_data[i][j] = T();  // Initialize with default value of T
        }
    }
}

// Constructor from a vector
template <class T, int sutun, int satir>
matrix<T, sutun, satir>::matrix(const std::vector<T>& vec) {
    if (vec.size() != sutun * satir) {
        throw std::invalid_argument("Vektor buyuklugu uygun degil");
    }
    for (int i = 0; i < sutun; i++) {
        for (int j = 0; j < satir; j++) {
            m_data[i][j] = vec[i * satir + j];
        }
    }
}

// Access elements (non-const)
template <class T, int sutun, int satir>
T& matrix<T, sutun, satir>::operator()(size_t y, size_t x) {
    return m_data[y - 1][x - 1];
}

// Access elements (const)
template <class T, int sutun, int satir>
const T& matrix<T, sutun, satir>::operator()(size_t y, size_t x) const {
    return m_data[y - 1][x - 1];
}

// Assignment operator
template <class T, int sutun, int satir>
matrix<T, sutun, satir>& matrix<T, sutun, satir>::operator=(const matrix<T, sutun, satir>& other) {
    for (int i = 0; i < sutun; ++i) {
        for (int j = 0; j < satir; ++j) {
            m_data[i][j] = other.m_data[i][j];
        }
    }
    return *this;
}

// Scalar multiplication
template <class T, int sutun, int satir>
matrix<T, sutun, satir> matrix<T, sutun, satir>::operator*(const T& scalar) {
    matrix<T, sutun, satir> result;
    for (int i = 0; i < sutun; ++i) {
        for (int j = 0; j < satir; ++j) {
            result.m_data[i][j] = m_data[i][j] * scalar;
        }
    }
    return result;
}

// Matrix multiplication
template <class T, int sutun, int satir>
template <int p>
matrix<T, sutun, p> matrix<T, sutun, satir>::operator*(const matrix<T, satir, p>& other) {
    if (sutun != p) {
        throw std::invalid_argument("Vektorlerin buyuklukleri uygun degil");
    }
    matrix<T, sutun, p> result;
    for (int i = 0; i < sutun; ++i) {
        for (int j = 0; j < p; ++j) {
            result(i + 1, j + 1) = 0;
            for (int k = 0; k < satir; ++k) {
                result(i + 1, j + 1) += m_data[i][k] * other(k + 1, j + 1);
            }
        }
    }
    return result;
}

// Scalar division
template <class T, int sutun, int satir>
matrix<T, sutun, satir> matrix<T, sutun, satir>::operator/(const T& scalar) {
    matrix<T, sutun, satir> result;
    for (int i = 0; i < sutun; ++i) {
        for (int j = 0; j < satir; ++j) {
            result.m_data[i][j] = m_data[i][j] / scalar;
        }
    }
    return result;
}

// Matrix addition
template <class T, int sutun, int satir>
matrix<T, sutun, satir> matrix<T, sutun, satir>::operator+(const matrix<T, sutun, satir>& other) {
    matrix<T, sutun, satir> result;
    for (int i = 0; i < sutun; ++i) {
        for (int j = 0; j < satir; ++j) {
            result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
        }
    }
    return result;
}

// Transpose matrix
template <class T, int sutun, int satir>
matrix<T, satir, sutun> matrix<T, sutun, satir>::transpoz() {
    matrix<T, satir, sutun> result;
    for (int i = 0; i < sutun; ++i) {
        for (int j = 0; j < satir; ++j) {
            result(j + 1, i + 1) = m_data[i][j];
        }
    }
    return result;
}

// Determinant (recursive)
template <class T, int sutun, int satir>
T matrix<T, sutun, satir>::determinant_recersive(const T mat[sutun][satir], int n) {
    if (n == 1) {
        return mat[0][0];
    }
    if (n == 2) {
        return (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]);
    }

    T det = 0;
    T submatrix[sutun][satir];

    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                submatrix[subi][subj] = mat[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * mat[0][x] * determinant_recersive(submatrix, n - 1);
    }

    return det;
}

// Determinant
template <class T, int sutun, int satir>
T matrix<T, sutun, satir>::determinant() {
    static_assert(sutun == satir, "kare matris lazim.");
    return determinant_recersive(m_data, sutun);
}

// Adjugate matrix
template <class T, int sutun, int satir>
matrix<T, satir, sutun> matrix<T, sutun, satir>::adj() {
    static_assert(sutun == satir, "kare matris lazim.");
    matrix<T, satir, sutun> result;

    if (satir == 1) {
        result.m_data[0][0] = 1;
        return result;
    }

    T submatrix[sutun - 1][satir - 1];

    for (int i = 0; i < satir; ++i) {
        for (int j = 0; j < sutun; ++j) {
            int subi = 0;
            for (int k = 0; k < satir; ++k) {
                if (k == i) continue;
                int subj = 0;
                for (int m = 0; m < sutun; ++m) {
                    if (m == j) continue;
                    submatrix[subi][subj] = m_data[k][m];
                    subj++;
                }
                subi++;
            }
            T cofactor = ((i + j) % 2 == 0 ? 1 : -1) * determinant_recersive(submatrix, satir - 1);
            result.m_data[j][i] = cofactor;
        }
    }
    return result;
}

// Fill matrix with a value
template <class T, int sutun, int satir>
void matrix<T, sutun, satir>::fill(T data) {
    for (int i = 0; i < sutun; i++) {
        for (int j = 0; j < satir; j++) {
            m_data[i][j] = data;
        }
    }
}

// Print matrix
template <class T, int sutun, int satir>
void matrix<T, sutun, satir>::print() {
    for (int i = 0; i < sutun; i++) {
        for (int j = 0; j < satir; j++) {
            std::cout << m_data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

#endif  
