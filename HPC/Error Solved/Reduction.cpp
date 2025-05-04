#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

void min_reduction(int arr[], int n) {
    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    cout << "\nMinimum value: " << min_value;
}

void max_reduction(int arr[], int n) {
    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    cout << "\nMaximum value: " << max_value;
}

void sum_reduction(int arr[], int n) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    cout << "\nSum: " << sum;
}

void average_reduction(int arr[], int n) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double average = (double)sum / n;
    cout << "\nAverage: " << average << endl;
}

int main() {
    int *arr, n;

    cout << "\nEnter total number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid input size.\n";
        return 1;
    }

    arr = new int[n];
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Print number of threads used
    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "\nNumber of threads used: " << omp_get_num_threads() << endl;
        }
    }

    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);

    delete[] arr;
    return 0;
}
