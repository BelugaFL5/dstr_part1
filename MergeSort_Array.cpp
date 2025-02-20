#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>

using namespace std;

// Define the Article struct
struct Article {
    string title, content, subject, date;
};

// Function to trim spaces and special characters from strings
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to parse a CSV line (handles quoted fields with commas)
void parseCSVLine(const string& line, string& title, string& content, string& subject, string& date) {
    stringstream ss(line);
    string field;
    int fieldCount = 0;

    while (getline(ss, field, ',')) {
        if (fieldCount == 0) title = trim(field);       // Title
        else if (fieldCount == 1) content = trim(field); // Content
        else if (fieldCount == 2) subject = trim(field); // Subject
        else if (fieldCount == 3) date = trim(field);    // Date
        fieldCount++;
    }
}

// Function to read CSV file and store articles in a vector
vector<Article> readCSV(const string& inputFile) {
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << inputFile << endl;
        exit(1);
    }

    string line;
    vector<Article> articles;
    
    // Skip the header line
    getline(file, line);

    // Read each line and parse it
    while (getline(file, line)) {
        string title, content, subject, date;
        parseCSVLine(line, title, content, subject, date);
        
        // Add the parsed article to the vector
        articles.push_back({title, content, subject, date});
    }

    file.close();
    return articles;
}

// Function to split the array into two halves
void mergeSort(vector<Article>& arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        
        // Merge the sorted halves
        vector<Article> left(arr.begin() + low, arr.begin() + mid + 1);
        vector<Article> right(arr.begin() + mid + 1, arr.begin() + high + 1);
        
        int i = 0, j = 0, k = low;
        
        // Merge the two halves
        while (i < left.size() && j < right.size()) {
            if (left[i].subject < right[j].subject) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements from left
        while (i < left.size()) {
            arr[k] = left[i];
            i++;
            k++;
        }
        
        // Copy remaining elements from right
        while (j < right.size()) {
            arr[k] = right[j];
            j++;
            k++;
        }
    }
}

// Function to count articles per subject
void countArticlesPerSubject(const vector<Article>& arr) {
    struct SubjectCountNode {
        string subject;
        int count;
    };

    vector<SubjectCountNode> subjectCount;

    for (const auto& article : arr) {
        bool found = false;
        for (auto& node : subjectCount) {
            if (node.subject == article.subject) {
                node.count++;
                found = true;
                break;
            }
        }
        if (!found) {
            subjectCount.push_back({article.subject, 1});
        }
    }

    // Print results
    cout << "\nArticles per subject:" << endl;
    for (const auto& node : subjectCount) {
        cout << "Subject: " << node.subject << " - " << node.count << " Articles" << endl;
    }
}

// Function to store sorted articles by subject in a file
void storeSortedArticlesBySubject(const vector<Article>& arr, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    if (arr.empty()) {
        cerr << "No articles to write!" << endl;
        return;
    }

    string lastSubject = "";

    for (const auto& article : arr) {
        if (article.subject != lastSubject) {
            if (!lastSubject.empty()) outFile << endl;
            outFile << "Subject: " << article.subject << endl;
            lastSubject = article.subject;
        }

        outFile << "  Title: " << article.title << endl;
        outFile << "  Date: " << article.date << endl;
        outFile << "--------------------------------------" << endl;
    }

    outFile.close();
    cout << "Sorted articles by subject stored in " << filename << " (Ascending Order)." << endl;
}

// Main function to demonstrate usage
int main() {
    auto start = chrono::high_resolution_clock::now();

    // Read articles from both CSV files
    vector<Article> articles;
    vector<Article> fakeArticles = readCSV("data-fake.csv");
    vector<Article> trueArticles = readCSV("data-true.csv");

    // Combine both datasets
    articles.insert(articles.end(), fakeArticles.begin(), fakeArticles.end());
    articles.insert(articles.end(), trueArticles.begin(), trueArticles.end());

    // Measure memory usage (estimate based on the size of the vector and its elements)
    size_t memoryUsage = articles.size() * sizeof(Article) / 1024 / 1024;  // in MB

    // Perform merge sort by subject
    mergeSort(articles, 0, articles.size() - 1);
    
    // Count articles per subject
    countArticlesPerSubject(articles);
    
    // Store sorted articles by subject in a file
    storeSortedArticlesBySubject(articles, "sorted_articles.txt");

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "\nSorting took: " << elapsed.count() << " seconds" << endl;
    cout << "Total Articles: " << articles.size() << endl;
    cout << "Memory usage: " << memoryUsage << " MB" << endl;

    return 0;
}
