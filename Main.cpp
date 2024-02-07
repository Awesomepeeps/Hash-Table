#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class student {
    private:
        float gpa;
        string name;
    public:
        student(int studentgpa, string studentname) : gpa(studentgpa), name(studentname) {

        }
        void printStudent(void) {
            cout << "gpa: " << gpa << endl;
            cout << "Name: " << name << endl;
        }
        float getgpa() {
            return gpa;
        }
        string getname() {
            return name;
        }
};

class hashItm {
    private:
        int hashid;
        hashItm* next;
        student mystudent;
    public:
        hashItm(int newid, hashItm* newNext, student newStudent) : hashid(newid), next(NULL), mystudent(newStudent) {
            float gpa = mystudent.getgpa();
            hashid = gpa * 5;
        }
        int getid() {
            return hashid;
        }
        void setid(int newid) {
            hashid = newid;
        }
        void setnext(hashItm* newnext) {
            next = newnext;
        }
        hashItm* getnext() {
            return next;
        }
        student getstudent() {
            return mystudent;
        }
};

class hashTbl {
    private:
        int size;
        int count;
        hashItm* table[];
    public:
        hashTbl(int newsize) : size(newsize) {
            table[size];
            for (int i = 0; i < newsize; i++) {
                table[i] = NULL;
            }
        }
        void printAll() {
            for (int i = 0; i < size; i++) {
                cout << "i is: " << i << ", item is: " << table[i] << endl;

                /*if (table[i] != NULL) {
                    cout << "i is: " << i << ", item is not null" << endl;
                }
                else {
                    cout << "i is: " << i << ", item is null" << endl;
                }*/
            }
        }
};

//hashftn // this is the hash function
//createhash // creates hash table
//student* createitem(string key, student* student); // creates a pointer to a hash table item
//addhash // adds item to hash table
//deleteitem // deletes item from hash table
//deletehash // deletes hash table
//rehash // re-hashes the table
//printhash // prints the hash table

int main(void) {
    int arrsize = 100;

    cout << "Hello, World" << endl;
    student test = student(1, "John");
    test.printStudent();
    hashTbl table = hashTbl(5);
    table.printAll();
}