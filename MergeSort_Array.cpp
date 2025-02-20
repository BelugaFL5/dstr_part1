// SIOW HAN BIN FOR Q1

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

// Custom dynamic array class to simulate vector functionality
template <typename T>
class DynamicArray {
public:
    T* data;
    int size;
    int capacity;

    // Constructor
    DynamicArray(int initialCapacity = 10) {
        capacity = initialCapacity;
        size = 0;
        data = new T[capacity];
    }

    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Add an element to the array
    void push_back(const T& element) {
        if (size == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = element;
    }

    // Get element at index
    T& operator[](int index) {
        return data[index];
    }

    // Get size of the array
    int getSize() const {
        return size;
    }

    // Sort the array (using merge sort)
    void sort() {
        mergeSort(data, 0, size - 1);
    }

private:
    // Merge function for merging two halves of the array
    void merge(T arr[], int low, int mid, int high) {
        int leftSize = mid - low + 1;
        int rightSize = high - mid;

        T* left = new T[leftSize];
        T* right = new T[rightSize];

        for (int i = 0; i < leftSize; i++) {
            left[i] = arr[low + i];
        }
        for (int i = 0; i < rightSize; i++) {
            right[i] = arr[mid + 1 + i];
        }

        int i = 0, j = 0, k = low;
        while (i < leftSize && j < rightSize) {
            if (left[i] < right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < leftSize) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < rightSize) {
            arr[k] = right[j];
            j++;
            k++;
        }

        delete[] left;
        delete[] right;
    }

    // Merge sort algorithm
    void mergeSort(T arr[], int low, int high) {
        if (low < high) {
            int mid = (low + high) / 2;
            mergeSort(arr, low, mid);
            mergeSort(arr, mid + 1, high);
            merge(arr, low, mid, high);
        }
    }
};

// Function to count the number of articles per year
void countArticles_Merge(Article* articles, int articleCount) {
    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Use a dynamic array to hold the year counts (similar to a map)
    DynamicArray<int> years;
    DynamicArray<int> counts;

    for (int i = 0; i < articleCount; i++) {
        int year = extractYear(articles[i].date);
        if (year > 0) {
            bool found = false;
            for (int j = 0; j < years.getSize(); j++) {
                if (years[j] == year) {
                    counts[j]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                years.push_back(year);
                counts.push_back(1);
            }
        }
    }

    // Sort the years
    years.sort();

    // Display the results sorted by year
    cout << "\n";
    for (int i = 0; i < years.getSize(); i++) {
        cout << years[i] << ": " << counts[i] << " articles" << endl;
    }

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "Time taken for merge sort: " << fixed << setprecision(2) << elapsedTime << "ms" << endl;
}

