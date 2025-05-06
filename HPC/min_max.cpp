#include <iostream>
#include <omp.h>
using namespace std;

int minval(int arr[], int n) {
    cout << "\n--- Parallel Execution for Minimum ---\n";
    double start_time = omp_get_wtime();  // Start time

    int min_value = arr[0];
    #pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; i++) {
        printf("Thread %d processing index %d (value: %d)\n", omp_get_thread_num(), i, arr[i]);
        if (arr[i] < min_value) min_value = arr[i];
    }

    double end_time = omp_get_wtime();    // End time
    cout << "Minimum value: " << min_value << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";
    return min_value;
}

int maxval(int arr[], int n) {
    cout << "\n--- Parallel Execution for Maximum ---\n";
    double start_time = omp_get_wtime();

    int max_value = arr[0];
    #pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; i++) {
        printf("Thread %d processing index %d (value: %d)\n", omp_get_thread_num(), i, arr[i]);
        if (arr[i] > max_value) max_value = arr[i];
    }

    double end_time = omp_get_wtime();
    cout << "Maximum value: " << max_value << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";
    return max_value;
}

int sum(int arr[], int n) {
    cout << "\n--- Parallel Execution for Sum ---\n";
    double start_time = omp_get_wtime();

    int total = 0;
    #pragma omp parallel for reduction(+ : total)
    for (int i = 0; i < n; i++) {
        printf("Thread %d adding index %d (value: %d)\n", omp_get_thread_num(), i, arr[i]);
        total += arr[i];
    }

    double end_time = omp_get_wtime();
    cout << "Sum: " << total << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";
    return total;
}

double average(int arr[], int n) {
    cout << "\n--- Parallel Execution for Average ---\n";
    double start_time = omp_get_wtime();

    int total = 0;
    #pragma omp parallel for reduction(+ : total)
    for (int i = 0; i < n; i++) {
        printf("Thread %d processing index %d (value: %d)\n", omp_get_thread_num(), i, arr[i]);
        total += arr[i];
    }

    double avg = (double)total / n;
    double end_time = omp_get_wtime();
    cout << "Average: " << avg << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";
    return avg;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    minval(arr, n);
    maxval(arr, n);
    sum(arr, n);
    average(arr, n);

    return 0;
}
