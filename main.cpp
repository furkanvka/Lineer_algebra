#include <iostream>
#include <vector>



template<class T, int sutun, int satir>
class matrix
{
private:
    T m_data[sutun][satir];
public:
    //constructors
    matrix()
    {
        for (int i = 0; i < sutun; i++){
            for (int j = 0; j < satir; j++){
                m_data[i][j] = T();
            }      
        }
            
    }
    //this is test
    matrix(const std::vector<T>& vec) {       
        if (vec.size() != sutun * satir)
            throw std::invalid_argument("Vektor buyuklugu uygun degil");
        for(int i = 0;i < sutun;i++){
            for(int j = 0;j < satir;j++){
                m_data[i][j] = vec[i * satir + j];
            }
        }
    }
    

    // T& actual degeri döndürmek için
    T& operator()(size_t y, size_t x)
    {
        return m_data[y-1][x-1];
    }

    const T& operator()(size_t y, size_t x) const
    {
        return m_data[y-1][x-1];
    }

    matrix& operator=(const matrix<T, sutun, satir>& other) {
        for (int i = 0; i < sutun; ++i) {
            for (int j = 0; j < satir; ++j) {
                m_data[i][j] = other.m_data[i][j];
            }
        }
        return *this;
    }

    matrix operator*(const T& scalar) 
    {
        matrix<T,sutun,satir> result;
        for (int i = 0; i < sutun; ++i){
            for (int j = 0; j < satir; ++j){
                result.m_data[i][j] = m_data[i][j] * scalar;
            }
        }
                
        return result;
    }

    template<int p>
    matrix<T,sutun,p> operator*(const matrix<T, satir, p>& other) 
    {
        if (sutun != p)
            throw std::invalid_argument("Vektorlerin buyuklukleri uygun degil");
        matrix<T,sutun,p> result;
        for (int i = 0; i < sutun; ++i){
            for (int j = 0; j < p; ++j){
                result(i+1,j+1) = 0;
                for(int k = 0;k < satir;k++){
                    result(i+1,j+1) += m_data[i][k] * other(k+1,j+1);
                }
            }
        }
                
        return result;
    }

    matrix operator/(const T& scalar) 
    {
        matrix<T,sutun,satir> result;
        for (int i = 0; i < sutun; ++i){
            for (int j = 0; j < satir; ++j){
                result.m_data[i][j] = m_data[i][j] / scalar;
            }
        }
                
        return result;
    }

    

    matrix operator+(const matrix<T, sutun, satir>& other) 
    {
        matrix<T,sutun,satir> result;
        for (int i = 0; i < sutun; ++i){
            for (int j = 0; j < satir; ++j){
                result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
            }
        }
                
        return result;
    }

    matrix<T, satir, sutun> transpoz()
    {
        matrix<T, satir, sutun> result;
        for (int i = 0; i < sutun; ++i) {
            for (int j = 0; j < satir; ++j) {
                result(j+1,i+1) = m_data[i][j];
            }
        }
        return result;
    }

    T determinant_recersive(const T mat[sutun][satir], int n) {
        if (n == 1){
            return mat[0][0];
        }
        if (n == 2){
            return (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]);
        }
        
        T det = 0;
        T submatrix[sutun][satir];

        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
            det += (x % 2 == 0 ? 1 : -1) * mat[0][x] * determinant_recersive(submatrix, n - 1);
        }

        return det;
    }

    T determinant() {
        static_assert(sutun == satir, "kare matris lazim.");
        return determinant_recersive(m_data, sutun);
    }

    matrix<T, satir, sutun> adj() {
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
                T cofactor = ((i + j) % 2 == 0 ? 1 : -1) * determinant_recursive(submatrix, satir - 1);
                result.m_data[j][i] = cofactor;
            }
        }
        return result;
    }
    
    void fill(T data)
    {
        for (int i = 0; i < sutun; i++)
        {
            for (int j = 0; j < satir; j++){
                m_data[i][j] = data;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < sutun; i++)
        {
            for (int j = 0; j < satir; j++){
                std::cout << m_data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

};





int main()
{
    matrix<int,4,2> mat;
    matrix<int,2,4> mat1;
    matrix<int,4,4> mat2;
    matrix<int,3,3> mat3;

    for(int i = 0;i < 9;i++){
        mat3(i/3+1,i%3+1) = i;
    }

    mat3(1,3) = 7;
    mat3(3,3) = 7;
    mat3(3,2) = 31;

    mat.fill(1);
    mat(1,3) = 4;
    mat1 = mat.transpoz();
    mat2 = mat * mat1;

    mat.print();

    std::cout << "\n";
    mat1.print();

    std::cout << "\n";
    mat2.print();

    std::cout << "\n";
    mat3.print();

    std::cout << "\n" << mat3.determinant();


    return 0;
}
