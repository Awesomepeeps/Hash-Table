#include <iostream>
#include <cstring>
#include <string>

using namespace std;

void testCollision();

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
        int size;
        int hashid;
        hashItm* next = NULL;
        student mystudent;
    public:
        hashItm(student newStudent, int newsize) : mystudent(newStudent),  size(newsize) {
            float gpa = mystudent.getgpa();
            hashid = (int) (gpa * 5) % size;
            cout << "HashID: " << hashid << endl;
        }
        int gethashid() {
            return hashid;
        }
        void sethashid(int newid) {
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
        bool rehash = false;
        const int COLLISION = 3;
        hashItm** table;
    public:
        hashTbl(int newsize) : size(newsize) {
            table = new hashItm*[size];
            count = 0;
            for (int i = 0; i < newsize; i++) {
                table[i] = NULL;
                cout << "hashTbl Constructure table id i set to null: " << i << endl; 
            }
        }
        int getsize() {
            return size;
        }
        void addhashentry (hashItm* newitm) {
            int length = 1;
            int hashid = newitm->gethashid();
            cout << "Hashid in hashTbl add entry: " << hashid << endl;
            hashItm* current = table[hashid];
            for (int i = 0; i < COLLISION; i++) {
                cout << "in for loop, head: " << table[hashid] << endl;
                if (table[hashid] == NULL) {
                    table[hashid] = newitm;
                    cout << "head is null" << endl;
                    break;
                }
                else if (current->getnext() != NULL) {
                    current = current->getnext();
                    length++;
                    cout << "increment length: " << length << endl;
                }
                else {
                    cout << "in else" << endl;
                    if (length < COLLISION) {
                        current->setnext(newitm);
                        cout << "Added Item" << endl;
                        break;
                    }
                    else {
                        rehash = true;
                        cout << "Collision/May have dropped item, i: " << i << endl;
                        break;
                    }
                }
            }
        }
        void printAll() {
            for (int i = 0; i < size; i++) {
                cout << "i is: " << i << ", item is: " << table[i] << endl;

                hashItm* current = NULL;

                current = table[i];

                if (current == NULL) {
                    continue;
                }

                for (int i = 0; i < 3; i++) {
                    if (current->getnext() == NULL) {
                        current->getstudent().printStudent();
                        break;
                    }
                    else {
                        current->getstudent().printStudent();
                        current = current->getnext();
                    }
                }

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
    testCollision();

}

void testCollision() {
    cout << "TestColl" << endl;
    hashTbl cTest = hashTbl(2);

    int size = cTest.getsize();
    cout << "size: " << size << endl;

    student s1 = student(1, "s1");
    student s2 = student(3, "s2");
    student s3 = student(5, "s3");
    student s4 = student(7, "s4");

    //cout << s1.getname() << endl;
    //cout << s2.getname() << endl;
    //cout << s3.getname() << endl;
    //cout << s4.getname() << endl;

    hashItm* p1 = new hashItm(s1, size);
    hashItm* p2 = new hashItm(s2, size);
    hashItm* p3 = new hashItm(s3, size);
    hashItm* p4 = new hashItm(s4, size);

    //cout << p1->gethashid() << endl;
    //cout << p2->gethashid() << endl;
    //cout << p3->gethashid() << endl;
    //cout << p4->gethashid() << endl;

    //cout << "got here" << endl;

    cTest.addhashentry(p1);
    cout << "got here1" << endl;
    cTest.addhashentry(p2);
    cout << "got here2" << endl;
    cTest.addhashentry(p3);
    cout << "got here3" << endl;
    cTest.addhashentry(p4);
    cout << "got here4" << endl;

    cout << "Test Coll End" << endl;

    cout << endl;

    cTest.printAll();
}