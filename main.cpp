#include <iostream>
#include <vector>
#include "matris.h"


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
