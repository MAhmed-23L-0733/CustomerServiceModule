#include <iostream>
#include <vector>
#include <list>
#include <random>

class DoubleHashingIndex {
private:
    std::vector<std::list<int>> table;
    int size;
    int p; // Prime number for universal hash function
    int a; // Random integer for universal hash function
    int b; // Random integer for universal hash function

    // Find the next prime number after the given number
    int findNextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    // Check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    // Universal hash function
    int hash(int key) {
        return ((a * key + b) % p) % size;
    }

    // Double hashing for collision resolution
    int doubleHash(int key, int i) {
        return (hash(key) + i * (1 + (key % (size - 1)))) % size;
    }

public:
    DoubleHashingIndex(int size) {
        this->size = size;
        table.resize(size);
        // Choose a random prime number for p
        p = findNextPrime(size);
        // Choose random integers for a and b
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, p - 1);
        a = distrib(gen);
        b = distrib(gen);
    }

    // Insert a new key into the index
    void insert(int key) {
        int i = 0;
        int index = doubleHash(key, i);
        while (std::find(table[index].begin(), table[index].end(), key) != table[index].end()) {
            i++;
            index = doubleHash(key, i);
        }
        table[index].push_back(key);
    }

    // Search for a key in the index
    bool search(int key) {
        int i = 0;
        int index = doubleHash(key, i);
        while (std::find(table[index].begin(), table[index].end(), key) != table[index].end()) {
            return true;
        }
        return false;
    }

    // Delete a key from the index
    void deleteKey(int key) {
        int i = 0;
        int index = doubleHash(key, i);
        while (std::find(table[index].begin(), table[index].end(), key) != table[index].end()) {
            table[index].remove(std::find(table[index].begin(), table[index].end(), key));
            return;
        }
    }

    // Print the index
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << "Index " << i << ": ";
            for (int key : table[i]) {
                std::cout << key << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    DoubleHashingIndex index(10);
    index.insert(10);
    index.insert(20);
    index.insert(30);
    index.insert(40);
    index.insert(50);
    std::cout << "Index after insertion:" << std::endl;
    index.print();
    std::cout << "Search for key 30: " << index.search(30) << std::endl;
    std::cout << "Search for key 60: " << index.search(60) << std::endl;
    index.deleteKey(30);
    std::cout << "Index after deletion:" << std::endl;
    index.print();
    return 0;
}
