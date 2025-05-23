#include<iostream>
#include<omp.h>
using namespace std;

void bubble(int*, int);
void swap(int&, int&);

void bubble(int* a, int n)
{
    for (int i = 0; i < n; i++) {
        int first = i % 2;

        #pragma omp parallel
        {
            #pragma omp single
            {
                cout << "\nNumber of threads used: " << omp_get_num_threads() << endl;
            }

            #pragma omp for
            for (int j = first; j < n - 1; j += 2) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                }
            }
        }
    }
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int* a, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;

    a = new int[n];
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bubble(a, n);

    cout << "\nSorted array is: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << "\t";
    }
    cout << endl;

    delete[] a;
    return 0;
}
