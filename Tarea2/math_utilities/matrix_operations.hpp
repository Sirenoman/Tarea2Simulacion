/* matrix_operations in 3D
#include <cmath>
#include "vector.hpp"
#include "matrix.hpp"

void product_scalar_by_matrix(float scalar, Matrix *M, int n, int m, Matrix *R)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            R->set(scalar * M->get(r, c), r, c);
}

void product_matrix_by_vector(Matrix *M, Vector *V, int n, int m, Vector *R)
{
    for (int r = 0; r < n; r++){
        float acc_n = 0;
        for (int c = 0; c < n; c++)
            acc_n += M->get(r, c) * V->get(c);
        R->set(acc_n, r);
    }
}

// Funcion que se usara en MEF_Process
void product_matrix_by_matrix(Matrix *A, Matrix *B, Matrix *R)
{
    int n = A->getNrows(), m = A->getNcols(), p = B->getNrows(), q = B->getNcols();
    if (m == p)
    {
        R->setSize(n, q);
        R->init();

        for (int r = 0; r < n; r++)
            for (int c = 0; c < q; c++)
                for (int i = 0; i < m; i++)
                    R->add(A->get(r, i) * B->get(i, c), r, c);
    }else{
        cout << "*****Dimension incompatibility when multiplying matrices.\n\n";
        exit(EXIT_FAILURE);
    }
}

float determinant(Matrix *M);

float determinant_auxiliar(Matrix *M)
{
    int n = M->getNcols();
    float acc_n = 0;

    for (int c = 0; c < n; c++)
    {
        Matrix clon(n, n);
        M->clone(&clon);
        clon.removeRow(0);
        clon.removeColumn(c);
        acc_n += pow(-1, c) * M->get(0, c) * determinant(&clon);
    }
    return acc_n;
}

float determinant(Matrix *M)
{
    float ans;
    switch (M->getNcols())
    {
    case 1:
        ans = M->get(0, 0);
        break;
    case 2:
        ans = M->get(0, 0) * M->get(1, 1) - M->get(0, 1) * M->get(1, 0);
        break;
    case 3:
        ans = M->get(0, 0) * M->get(1, 1) * M->get(2, 2) - M->get(0, 0) * M->get(1, 2) * M->get(2, 1) - M->get(0, 1) * M->get(1, 0) * M->get(2, 2) + M->get(0, 1) * M->get(1, 2) * M->get(2, 0) + M->get(0, 2) * M->get(1, 0) * M->get(2, 1) - M->get(0, 2) * M->get(1, 1) * M->get(2, 0);
        break;
    default:
        ans = determinant_auxiliar(M);
    }
    return ans;
}

float getMinor(Matrix *M, int n, int r, int c)
{
    Matrix clon(n, n);
    M->clone(&clon);

    // M.show();
    // clon.show();
    clon.removeRow(r);
    clon.removeColumn(c);

    // clon.show();
    return determinant(&clon);
}

void conjugate_matrix(Matrix *M, int n, Matrix *C)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            C->set(pow(-1, r + c) * getMinor(M, n, r, c), r, c);
}

// Funcion transpose
void transpose_matrix(Matrix *M, int n, int m, Matrix *T)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            T->set(M->get(r, c), c, r);
}

void calculate_inverse(Matrix *M, int n, Matrix *R)
{
    cout << "\t\t***Calculating determinant***\n";
    float detM = determinant(M);

    cout << "\t\t***Calculating conjugate Matrix***\n";
    Matrix Conjugate(n, n);
    conjugate_matrix(M, n, &Conjugate);

    cout << "\t\t***Calculating Adjunct Matrix***\n";
    Matrix Adjunct(n, n);
    transpose_matrix(&Conjugate, n, n, &Adjunct);
    // Adjunct.show();

    cout << "\t\t***Multiplying the Adjunct by the determinant.***\n";
    product_scalar_by_matrix(1 / detM, &Adjunct, n, n, R);
}
*/
// matrix_operations in 3D
#include <cmath>
#include "vector.hpp"
#include "matrix.hpp"

void product_scalar_by_matrix(float scalar, Matrix *M, int n, int m, Matrix *R)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            R->set(scalar * M->get(r, c), r, c);
}

void product_matrix_by_vector(Matrix *M, Vector *V, int n, int m, Vector *R)
{
    for (int r = 0; r < n; r++)
    {
        float acc_n = 0;
        for (int c = 0; c < n; c++)
            acc_n += M->get(r, c) * V->get(c);
        R->set(acc_n, r);
    }
}

// Funcion que se usara en MEF_Process
void product_matrix_by_matrix(Matrix *A, Matrix *B, Matrix *R)
{
    int n = A->getNrows(), m = A->getNcols(), p = B->getNrows(), q = B->getNcols();
    if (m == p)
    {
        R->setSize(n, q);
        R->init();

        for (int r = 0; r < n; r++)
            for (int c = 0; c < q; c++)
                for (int i = 0; i < m; i++)
                    R->add(A->get(r, i) * B->get(i, c), r, c);
    }
    else
    {
        cout << "*****Dimension incompatibility when multiplying matrices.\n\n";
        exit(EXIT_FAILURE);
    }
}

float determinant(Matrix *M);

float determinant_auxiliar(Matrix *M)
{
    int n = M->getNcols();
    float acc_n = 0;

    for (int c = 0; c < n; c++)
    {
        Matrix clon(n, n);
        M->clone(&clon);
        clon.removeRow(0);
        clon.removeColumn(c);
        acc_n += pow(-1, c) * M->get(0, c) * determinant(&clon);
    }
    return acc_n;
}

float determinant(Matrix *M)
{
    float ans;
    switch (M->getNcols())
    {
    case 1:
        ans = M->get(0, 0);
        break;
    case 2:
        ans = M->get(0, 0) * M->get(1, 1) - M->get(0, 1) * M->get(1, 0);
        break;
    case 3:
        ans = M->get(0, 0) * M->get(1, 1) * M->get(2, 2) - M->get(0, 0) * M->get(1, 2) * M->get(2, 1) - M->get(0, 1) * M->get(1, 0) * M->get(2, 2) + M->get(0, 1) * M->get(1, 2) * M->get(2, 0) + M->get(0, 2) * M->get(1, 0) * M->get(2, 1) - M->get(0, 2) * M->get(1, 1) * M->get(2, 0);
        break;

    default:
        ans = determinant_auxiliar(M);
    }
    return ans;
}

/*float getMinor(Matrix *M, int n, int r, int c)
{
    Matrix clon(n, n);
    M->clone(&clon);

    // M.show();
    // clon.show();
    clon.removeRow(r);
    clon.removeColumn(c);

    // clon.show();
    return determinant(&clon);
}*/

/*void conjugate_matrix(Matrix *M, int n, Matrix *C)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            C->set(pow(-1, r + c) * getMinor(M, n, r, c), r, c);
}*/

// Funcion transpose
void transpose_matrix(Matrix *M, int n, int m, Matrix *T)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            T->set(M->get(r, c), c, r);
}

void calculateZ_matrix(Matrix *A, int n, Matrix *Z)
{
    // utilizando archivo de Cholesky del repositorio de github
    float acum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                acum = 0;
                for (int k = 0; k < j; k++)
                {
                    // cout << L->get(j,k) << " ";
                    acum += pow(Z->get(k, j), 2);
                }
                cout << A->get(j, j) << " " << acum << "\n";
                if (A->get(j, j) - acum >= 0)
                {
                    Z->set(sqrt(A->get(j, j) - acum), j, j);
                }
                else
                {
                    Z->set(0.000001, j, j);
                }
            }
            else
            {
                if (i > j)
                {
                    if (Z->get(j, j) != 0)
                    {
                        acum = 0;
                        for (int k = 0; k < j; k++)
                        {
                            acum += Z->get(i, k) * Z->get(j, k);
                        }
                        // cout << L->get(j,j) << "\n";
                        Z->set((1 / Z->get(j, j)) * (A->get(i, j) - acum), i, j);
                    }
                    else
                    {
                        Z->set(0.000001, i, j);
                    }
                }
                else
                {
                    Z->set(0, i, j);
                }
            }
        }
    }
}

//mirar sino hay error en sintaxis
void calculateY_matrix(Matrix *Z, int n, Matrix *Y)
{
    // utilizando archivo de Cholesky del repositorio de github
    float acum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i)
            {
                if (Z->get(i, j) != 0)
                {
                    Y->set(1 /Z->get(i, i), i, i);
                }
                else
                {
                    Z->set(0.000001, i, j);
                }
            }
            else if(i > j)
            {
            //if (i > j)
            //{
                if (Z->get(i, i) != 0)
                {
                    acum = 0;
                    for (int k = j; k < i; k++)
                    {
                        acum += Z->get(i, k) * Y->get(k, j);
                    }
                    Y->set(-1*(1 / Z->get(i, i)) * acum, i, j);
                }
                else{
                    Z->set(0.000001, i, j);
                }
            //}
            }
            else{
                Y->set(0, i, j);
            }
        }
    }
}
void calculateX_matrix(Matrix* Y, Matrix* Z, int n, Matrix*X){
    float acum;
    for(int i = n-1 ; i>=0; i--)
        for(int j = 0; j<n; j++){
            if(Z->get(i,i)!=0){
                acum = 0;
                for(int k = i+1; k<n; k++){
                    acum += Z->get(k,i)*X->get(k,j);
                }
                X->set((1/Z->get(i,i))*(Y->get(i,j)-acum),i,j);
            }
            else{
                X->set(0.000001,i,j);
            }
        }

}

void calculate_inverse(Matrix *A, int n, Matrix *X)
{
    //Aplicando las formulas de las matriz de X,Y y Z
    Matrix Z(n, n), Y(n,n);
    Z.init();
    Y.init();

    calculateZ_matrix(A,n,&Z);
    calculateY_matrix(&Z,n,&Y);
    calculateX_matrix(&Y,&Z,n,X);
    
}