#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Abiturient
{
    string surname;
    string name;
    string phone;
    float zno;
    bool privilege;
};
// додавання нового запису в список
void addAbiturient(vector<Abiturient>& list)
{
    Abiturient a;
    cout << "Прізвище: ";
    cin >> a.surname;
    cout << "Ім'я: ";
    cin >> a.name;
    cout << "Телефон: ";
    cin >> a.phone;
    cout << "ЗНО: ";
    cin >> a.zno;
    cout << "Пільга (1 - так, 0 - ні): ";
    cin >> a.privilege;
    list.push_back(a);
}
// збереження всіх записів у файл
void saveToFile(const vector<Abiturient>& list)
{
    ofstream file("abiturients.txt");
    for (const auto& a : list)
    {
        file << a.surname << " "
            << a.name << " "
            << a.phone << " "
            << a.zno << " "
            << a.privilege << endl;
    }
}
// завантаження даних з файлу у пам’ять
vector<Abiturient> loadFromFile()
{
    vector<Abiturient> list;
    ifstream file("abiturients.txt");
    Abiturient a;
    while (file >> a.surname >> a.name >> a.phone >> a.zno >> a.privilege)
    {
        list.push_back(a);
    }
    return list;
}
// вивід всіх записів
void printAll(const vector<Abiturient>& list)
{
    for (const auto& a : list)
    {
        cout << a.surname << " "
            << a.name << " "
            << a.phone << " "
            << a.zno << " "
            << (a.privilege ? "Пільга" : "Немає") << endl;
    }
}
// фільтр: тільки абітурієнти з пільгою
void printPrivilege(const vector<Abiturient>& list)
{
    cout << "\nАбітурієнти з пільгою:\n";
    for (const auto& a : list)
    {
        if (a.privilege)
        {
            cout << a.surname << " "
                << a.name << " "
                << a.phone << " "
                << a.zno << endl;
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Ukrainian");
    vector<Abiturient> list = loadFromFile();
    int choice;
    do
    {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Додати абітурієнта\n";
        cout << "2. Показати всіх\n";
        cout << "3. Показати з пільгою\n";
        cout << "4. Зберегти і вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addAbiturient(list);
            break;

        case 2:
            printAll(list);
            break;

        case 3:
            printPrivilege(list);
            break;

        case 4:
            saveToFile(list);
            cout << "Збережено у файл" << endl;
            break;
        }
    } while (choice != 4);
    return 0;
}
