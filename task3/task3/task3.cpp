#include <iostream>
#include <random>
using namespace std;
/* V = 29 [-39 ; 39]*/
int** Create(int n)
{
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
    return a;
}
void FillRand(int** a, int n)
{
    int left = -39;//-10 -29
    int right = 39;//10 +29

    random_device rd;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = rd() % (right - left + 1) + left;
}
void Print(int** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}
// Сектор 9 (під головною діагоналлю)
int Sector9(int** a, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i > j && a[i][j] % 2 != 0)
                count++;
    return count;
}
// Максимум на головній діагоналі
int MaxDiag(int** a, int n)
{
    int max = a[0][0];
    for (int i = 0; i < n; i++)
        if (a[i][i] > max)
            max = a[i][i];
    return max;
}
// Сектор 4 (нижній між діагоналями)
int Sector4(int** a, int n, int max)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i > j && i + j > n - 1)
            {
                a[i][j] = max;
                count++;
            }
    return count;
}
int main()
{
    int n;
    cout << "n = ";
    cin >> n;
    int** a = Create(n);
    FillRand(a, n);
    cout << "\nMatrix:\n";
    Print(a, n);
    int mx = MaxDiag(a, n);
    int c9 = Sector9(a, n);
    cout << "\nSector 9 (odd numbers): " << c9 << endl;
    int c4 = Sector4(a, n, mx);
    cout << "Sector 4 (replaced elements): " << c4 << endl;
    cout << "\nResult matrix:\n";
    Print(a, n);
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
