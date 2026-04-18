#include <iostream>
using namespace std;
int main()
{
    float R[10];
    // Формування арифметичної прогресії:
    // R2 = 2 Ом, крок = 2 Ом
    for (int i = 0; i < 10; i++)
    {
        R[i] = 2 + i * 2;
    }
    // Послідовне з’єднання
    float Rposl = 0;
    for (int i = 0; i < 10; i++)
    {
        Rposl += R[i];
    }
    // Паралельне з’єднання
    float Rpar = 0;
    for (int i = 0; i < 10; i++)
    {
        Rpar += 1 / R[i];
    }
    Rpar = 1 / Rpar;

    cout << "Poslidovne: " << Rposl << endl;
    cout << "Paralelne: " << Rpar << endl;
    return 0;
}
