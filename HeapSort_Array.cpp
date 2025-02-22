#include "CSVHandling_Array.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream> 

using namespace std;

// Function to calculate additional memory usage for Heap Sort
size_t calcHeapSortMemoryUsage(int n) {
    // Heap Sort uses O(1) additional memory for the heap
    return sizeof(int) * n; // Memory used by the heap
}

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

    // Sort the array (using heap sort)
    void sort() {
        heapSort(data, size);
    }

private:
    // Heapify function for sorting
    void heapify(T arr[], int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left].subject > arr[largest].subject)
            largest = left;

        if (right < n && arr[right].subject > arr[largest].subject)
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    // Heap sort algorithm
    void heapSort(T arr[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

// Function to sort articles by subject and export the results to a text file
void sortArticlesBySubject_Heap(Article* articles, int articleCount, const string& outputFileName) {
    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Use a dynamic array to hold the articles
    DynamicArray<Article> articleArray;
    for (int i = 0; i < articleCount; i++) {
        articleArray.push_back(articles[i]);
    }

    // Sort the articles by subject using heap sort
    articleArray.sort();

    // Open a file for writing the sorted results
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << outputFileName << " for writing." << endl;
        return;
    }

    // Write the sorted results to the file
    outputFile << "Articles sorted by subject:\n";
    for (int i = 0; i < articleArray.getSize(); i++) {
        outputFile << "Subject: " << articleArray[i].subject << ", Title: " << articleArray[i].title << endl;
    }
    outputFile.close();

    // Display a confirmation message
    cout << "\nSorted results have been exported to " << outputFileName << endl;

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "Time taken for heap sort: " << fixed << setprecision(2) << elapsedTime << "ms" << endl;

    // Calculate memory usage for the input array
    size_t inputMemoryUsage = calcMemoryUsage(articles, articleCount);

    // Calculate additional memory usage for Heap Sort
    size_t heapSortMemoryUsage = calcHeapSortMemoryUsage(articleCount);

    // Total memory usage
    size_t totalMemoryUsage = heapSortMemoryUsage + inputMemoryUsage;

    cout << "Memory usage for heap sort: " << totalMemoryUsage / (1024.0 * 1024.0) << " MB" << endl;
}