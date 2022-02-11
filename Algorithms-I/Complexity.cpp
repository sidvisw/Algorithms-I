#include <bits/stdc++.h>
using namespace std;
double power(double x, int n)
{
    if (n == 0)
        return 1;
    double e = power(x, n / 2), o = power(x, (n - 1) / 2);
    if (n % 2 == 0)
        return e * e;
    else
        return o * o * x;
}
//this function runs in constant time as it has fixed size 2 ---> O(1)
double **mat_mult(double **mat1, double **mat2)
{
    double **mult_mat = new double *[2];
    for (int i = 0; i < 2; i++)
    {
        mult_mat[i] = new double[2];
        for (int j = 0; j < 2; j++)
        {
            mult_mat[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                mult_mat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return mult_mat;
}
double **mat_pow(double **mat, int n)
{
    if (n == 1)
        return mat;
    double **e = mat_pow(mat, n / 2);
    if (n % 2 == 0)
        return mat_mult(e, e);
    else
        return mat_mult(mat_mult(e, e), mat);
}
double compute_iterative(int n)
{
    double f1 = 0, f2 = 1;
    if (!n)
        return 0;
    for (int i = 0; i < n - 1; i++)
    {
        int temp;
        temp = 2 * f2 + f1;
        f1 = f2;
        f2 = temp;
    }
    return f2;
}
double compute_recursive(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return 2 * compute_recursive(n - 1) + compute_recursive(n - 2);
}
double compute_formula(int n)
{
    return (power(1 + sqrt(2), n) - power(1 - sqrt(2), n)) / (2 * sqrt(2));
}
double compute_matrix(int n)
{
    double **mat = new double *[2];
    for (int i = 0; i < 2; i++)
    {
        mat[i] = new double[2];
    }
    mat[0][0] = 2;
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[1][1] = 0;
    if (n == 0)
        return 0;
    else
        return mat_pow(mat, n)[0][1];
}
main()
{
    int n;
    cin >> n;
    double time_spent = 0.0;
    clock_t begin = clock();
    cout << compute_iterative(n) << endl;
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased in iterative is %f seconds\n", time_spent);
    time_spent = 0.0;
    begin = clock();
    cout << compute_recursive(n) << endl;
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased in recursive is %f seconds\n", time_spent);
    time_spent = 0.0;
    begin = clock();
    cout << compute_formula(n) << endl;
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased in formula is %f seconds\n", time_spent);
    time_spent = 0.0;
    begin = clock();
    cout << compute_matrix(n) << endl;
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elpased in matrix is %f seconds\n", time_spent);
}