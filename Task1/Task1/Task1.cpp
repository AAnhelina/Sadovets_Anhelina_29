#include <iostream>
#include <chrono>
#include <future>
using namespace std;
using namespace chrono;
// функція виведення масиву
void printArray(int arr[], int n) {
    if (n <= 10) {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
    }
    else {
        for (int i = 0; i < 5; i++)
            cout << arr[i] << " ";

        cout << "..." << n - 10 << " ... ";

        for (int i = n - 5; i < n; i++)
            cout << arr[i] << " ";
    }
    cout << endl;
}
//генератор випадкового масиву
void generateArray(int arr[], int n) {
    // функція заповнює масив випадковими числами
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}
// сортування вставкою(Insertion Sort)
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
// сортування вибором(Selection Sort)
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}
// сортування Шелла(Shell Sort)
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
// бінарний пошук
int binarySearch(int arr[], int n, int x) {
    // працює тільки з відсортованим масивом
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
    // якщо не знайдено
}
int main() {
    srand(time(0));
    int sizes[] = { 12, 125, 1500, 7000, 35000, 170000 };
    for (int k = 0; k < 6; k++) {
        int n = sizes[k];
        int* arr = new int[n];
        generateArray(arr, n);

        cout << "\n" << n << "\n";
        cout << "Original array: ";
        printArray(arr, n);
        //insertion sync
        int* a1 = new int[n];
        copy(arr, arr + n, a1);
        auto start = high_resolution_clock::now();
        insertionSort(a1, n);
        auto end = high_resolution_clock::now();
        cout << "Insertion (SYNC): "<< duration_cast<milliseconds>(end - start).count()<< " ms\n";
        delete[] a1;
        //insertion async
        int* a1a = new int[n];
        copy(arr, arr + n, a1a);
        start = high_resolution_clock::now();
        auto f1 = async(launch::async, insertionSort, a1a, n);
        f1.get();
        end = high_resolution_clock::now();
        cout << "Insertion (ASYNC): "<< duration_cast<milliseconds>(end - start).count()<< " ms\n";
        delete[] a1a;
        //selection sync
        int* a2 = new int[n];
        copy(arr, arr + n, a2);
        start = high_resolution_clock::now();
        selectionSort(a2, n);
        end = high_resolution_clock::now();
        cout << "Selection (SYNC): "<< duration_cast<milliseconds>(end - start).count()<< " ms\n";
        delete[] a2;
        //selection async
        int* a2a = new int[n];
        copy(arr, arr + n, a2a);
        start = high_resolution_clock::now();
        auto f2 = async(launch::async, selectionSort, a2a, n);
        f2.get();
        end = high_resolution_clock::now();
        cout << "Selection (ASYNC): "<< duration_cast<milliseconds>(end - start).count()<< " ms\n";
        delete[] a2a;
        //shell sync
        int* a3 = new int[n];
        copy(arr, arr + n, a3);
        start = high_resolution_clock::now();
        shellSort(a3, n);
        end = high_resolution_clock::now();
        cout << "Shell (SYNC): "<< duration_cast<milliseconds>(end - start).count()<< " ms\n";
        delete[] a3;
        //shell async
        int* a3a = new int[n];
        copy(arr, arr + n, a3a);
        start = high_resolution_clock::now();
        auto f3 = async(launch::async, shellSort, a3a, n);
        f3.get();
        end = high_resolution_clock::now();
        cout << "Shell (ASYNC): " << duration_cast<milliseconds>(end - start).count()<< " ms\n";
        delete[] a3a;
        //binary search
        shellSort(arr, n);
        int x;
        cout << "Enter element: ";
        cin >> x;
        int res = binarySearch(arr, n, x);
        if (res != -1)
            cout << "Found at index " << res << endl;
        else
            cout << "Not found\n";
        delete[] arr;
        cout << "\n";
    }
    return 0;
}
