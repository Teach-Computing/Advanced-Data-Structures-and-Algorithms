#include <iostream>
#include <cmath>
#include <list>

using namespace std;

class HashTable {
private:
    static const int tableSize = 11;
    list<long> table[tableSize]; // array of linked lists

public:
    HashTable() {
        
    }

    int hash(long key) {
        return key % tableSize;
    }

    void insert(long key){
        int index = hash(key);
        table[index].push_back(key);
    }

    bool search(long key){
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); it++){
            if (*it == key){
                return true;
            }
        }
        return false;
    }

    void display(){
        for (int i = 0; i < tableSize; i++){
            cout << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); it++){
                cout << *it << " ";
            }
            cout << endl;
        }
    }

};


int main() {
    HashTable hashTable;
    hashTable.insert(10);
    hashTable.insert(20);
    hashTable.insert(30);
    hashTable.insert(40);
    hashTable.insert(50);
    hashTable.insert(60);
    hashTable.insert(70);
    hashTable.insert(80);
    hashTable.insert(90);
    hashTable.insert(100);
    hashTable.insert(110);
    hashTable.insert(120);
    hashTable.insert(130);  
    hashTable.insert(140);
    hashTable.insert(150);

    hashTable.display();
}