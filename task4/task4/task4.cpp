#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int сумаСимволів(const string& s)
{
    int сума = 0;
    for (char c : s)
        сума += (int)c;
    return сума;
}
int main()
{
    setlocale(LC_ALL, "Ukrainian");
    // відкриття файлів
    ifstream вхід("input.txt");
    ofstream вихід("output.txt");
    if (!вхід.is_open() || !вихід.is_open())
    {
        cout << "Помилка відкриття файлів!" << endl;
        return 1;
    }
    vector<string> речення;
    string рядок;
    // зчитування рядків з файлу
    while (getline(вхід, рядок))
    {
        if (!рядок.empty())
            речення.push_back(рядок);
    }
    вхід.close();
    int мінРізниця = INT_MAX;
    string r1, r2;
    // пошук двох найбільш схожих речень
    for (int i = 0; i < речення.size(); i++)
    {
        for (int j = i + 1; j < речення.size(); j++)
        {
            int різниця = abs(
                сумаСимволів(речення[i]) -
                сумаСимволів(речення[j])
            );

            if (різниця < мінРізниця)
            {
                мінРізниця = різниця;
                r1 = речення[i];
                r2 = речення[j];
            }
        }
    }
    // запис результату у файл
    вихід << "Найбільш схожі речення:\n";
    вихід << r1 << "\n";
    вихід << r2 << "\n";
    вихід.close();
    cout << "Готово! Перевір файл output.txt" << endl;
    return 0;
}
