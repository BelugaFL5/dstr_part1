// SIOW HAN BIN FOR Q3(sort year and subject)
#include "CSVHandling_Array.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream> 
#include "MergeSort_Array.hpp"

using namespace std;

// Assuming Article class/structure is defined somewhere in the project
struct Article {
    string title;
    string date;
    string subject;
    Article* next;
};

struct YearCount {
    int year;
    int count;
    
    // This is for sorting YearCount by year (ascending)
    bool operator<(const YearCount& other) const {
        return year < other.year;
    }
};



// Stores sorted articles in a file grouped by subject
void storeSortedArticlesBySubject(Article* head, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    if (!head) {
        cerr << "No articles to write!" << endl;
        return;
    }

    string lastSubject = "";

    // Write articles to file, grouping by subject
    while (head) {
        if (head->subject != lastSubject) {
            if (!lastSubject.empty()) outFile << endl;
            outFile << "Subject: " << head->subject << endl;
            lastSubject = head->subject;
        }

        // Write article details
        outFile << "  Title: " << head->title << endl;
        outFile << "  Date: " << head->date << endl;
        outFile << "--------------------------------------" << endl;

        head = head->next;
    }

    outFile.close();
    cout << "Sorted articles by subject stored in " << filename << " (Ascending Order)." << endl;
}

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

// Function to count articles per year using a dynamic array of YearCount structs
void countArticles_Merge(Article* articles, int articleCount) {
    auto start = chrono::high_resolution_clock::now();

    DynamicArray<YearCount> yearCounts;

    // Count articles per year
    for (int i = 0; i < articleCount; i++) {
        int year = extractYear(articles[i].date);
        if (year > 0) {
            bool found = false;
            for (int j = 0; j < yearCounts.getSize(); j++) {
                if (yearCounts[j].year == year) {
                    yearCounts[j].count++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                YearCount newYearCount = {year, 1};
                yearCounts.push_back(newYearCount);
            }
        }
    }

    // Sort YearCount array by year
    yearCounts.sort();

    // Display results sorted by year
    cout << "\n";
    for (int i = 0; i < yearCounts.getSize(); i++) {
        cout << yearCounts[i].year << ": " << yearCounts[i].count << " articles" << endl;
    }

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "Time taken for merge sort: " << fixed << setprecision(2) << elapsedTime << "ms" << endl;
}
