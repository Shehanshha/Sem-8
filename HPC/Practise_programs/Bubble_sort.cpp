#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Parallel Bubble Sort (Odd-Even Transposition Sort)
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for
        for (int j = (i % 2); j < n - 1; j += 2) {
            int thread_id = omp_get_thread_num();  // Get thread ID
           printf("Thread %d processing index %d (value:%d)\n",thread_id,j,arr[j]);
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> original(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> original[i];
    }

    cout << "\nOriginal array: ";
    for (int num : original)
        cout << num << " ";
    cout << "\n\n";

    // Sequential Bubble Sort
    vector<int> bubbleArr = original;
    double start_time = omp_get_wtime();
    bubbleSort(bubbleArr);
    double end_time = omp_get_wtime();
    printArray(bubbleArr, "Sequential Bubble Sorted array");
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n\n";

    // Parallel Bubble Sort
    vector<int> parBubbleArr = original;
    start_time = omp_get_wtime();
    parallelBubbleSort(parBubbleArr);
    end_time = omp_get_wtime();
    printArray(parBubbleArr, "Parallel Bubble Sorted array");
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n\n";
	
	return 0;
}	