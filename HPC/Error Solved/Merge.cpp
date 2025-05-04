#include <iostream>
#include <omp.h>
using namespace std;

void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort(int a[], int i, int j) {
    if (i < j) {
        int mid = (i + j) / 2;

        #pragma omp parallel
        {
            #pragma omp single
            {
                cout << "\nNumber of threads in mergesort: " << omp_get_num_threads() << endl;

                #pragma omp task
                mergesort(a, i, mid);

                #pragma omp task
                mergesort(a, mid + 1, j);

                #pragma omp taskwait
            }
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2) {
    int size = j2 - i1 + 1;
    int* temp = new int[size];
    int i = i1, j = i2, k = 0;

    while (i <= j1 && j <= j2) {
        if (a[i] < a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }

    while (i <= j1) temp[k++] = a[i++];
    while (j <= j2) temp[k++] = a[j++];

    for (i = i1, k = 0; i <= j2; i++, k++) {
        a[i] = temp[k];
    }

    delete[] temp;
}

int main() {
    int n;
    cout << "\nEnter total number of elements: ";
    cin >> n;

    int* a = new int[n];
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    double start_time = omp_get_wtime();
    mergesort(a, 0, n - 1);
    double end_time = omp_get_wtime();

    cout << "\nSorted array is:";
    for (int i = 0; i < n; i++) cout << " " << a[i];

    cout << "\n\nTime taken: " << end_time - start_time << " seconds.\n";

    delete[] a;
    return 0;
}
