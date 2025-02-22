#include "CSVHandling_Array.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream> // Include for file handling

using namespace std;

// Function to calculate additional memory usage for Merge Sort
size_t calcMergeSortMemoryUsage(int n) {
    // Merge Sort uses O(n) additional memory for temporary arrays
    return n * sizeof(Article); // Memory used by temporary arrays
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

    // Sort the array (using merge sort)
    void sort() {
        mergeSort(data, 0, size - 1);
    }

private:
    // Merge function to merge two halves
    void merge(T arr[], int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        T* leftArray = new T[n1];
        T* rightArray = new T[n2];

        for (int i = 0; i < n1; i++)
            leftArray[i] = arr[left + i];

        for (int i = 0; i < n2; i++)
            rightArray[i] = arr[middle + 1 + i];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            // Compare articles based on their subject
            if (leftArray[i].subject <= rightArray[j].subject) {
                arr[k++] = leftArray[i++];
            } else {
                arr[k++] = rightArray[j++];
            }
        }

        while (i < n1) {
            arr[k++] = leftArray[i++];
        }

        while (j < n2) {
            arr[k++] = rightArray[j++];
        }

        delete[] leftArray;
        delete[] rightArray;
    }

    // Merge sort algorithm
    void mergeSort(T arr[], int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);

            merge(arr, left, middle, right);
        }
    }
};

// Function to sort articles by subject and export the results to a text file
void sortArticlesBySubject_Merge(Article* articles, int articleCount, const string& outputFileName) {
    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Sort the articles by subject using merge sort
    DynamicArray<Article> articleArray;
    for (int i = 0; i < articleCount; i++) {
        articleArray.push_back(articles[i]);
    }
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
    cout << "Time taken for merge sort: " << fixed << setprecision(2) << elapsedTime << "ms" << endl;

    // Calculate memory usage for the input array
    size_t inputMemoryUsage = calcMemoryUsage(articles, articleCount);

    // Calculate additional memory usage for Merge Sort
    size_t mergeSortMemoryUsage = calcMergeSortMemoryUsage(articleCount);

    // Total memory usage
    size_t totalMemoryUsage = inputMemoryUsage + mergeSortMemoryUsage;

    cout << "Memory usage for merge sort: " << totalMemoryUsage / (1024.0 * 1024.0) << " MB" << endl;
}