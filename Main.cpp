#include <iostream>
#include <cstring>
#include <string>

using namespace std;

void testCollision();

class student {
    private:
        int id;
        float gpa;
        string first;
        string last;
        
    public:
        student(int studentgpa, string studentfirst, string ssecond, int newid) : gpa(studentgpa), first(studentfirst), last(ssecond), id(newid) {}
        void printStudent(void) {
            cout << "gpa: " << gpa << endl;
            cout << "id: " << id << endl;
            cout << "First: " << first << endl;
            cout << "Last: " << last << endl;
        }
        float getgpa() {
            return gpa;
        }
        int getid() {
            return id;
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
            hashid = (int) (gpa * (size/4)) % size;
        }
        int gethashid() {
            return hashid;
        }
        void sesize(int newsize) {
            size = newsize;
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
        bool rehash = false;
        const int COLLISION = 3;
        hashItm** table;
        hashItm** hashretbl;
    public:
        hashTbl(int newsize) : size(newsize) {
            table = new hashItm*[size];
            for (int i = 0; i < newsize; i++) {
                table[i] = NULL;
            }       
        }
        void deleteTerm(int id, float gpa) {
            int currentid = (int) (gpa * (size/4)) % size;
            hashItm* current = table[currentid];
            hashItm* previous = current;
            while(current != NULL) {
                if (current->getstudent().getid() == id && table[currentid] == current) {
                    table[currentid] = current->getnext();
                    delete current;
                    break;
                }
                else if (current->getstudent().getid() == id) {
                    previous->setnext(current->getnext());
                    delete current;
                    break;
                }
                else {
                    previous = current;
                    current = current->getnext();
                }
            }
        }
        int getsize() {
            return size;
        }
        void addhashentry (hashItm* newitm) {
            int length = 1;
            int hashid = newitm->gethashid();
            hashItm* current = table[hashid];
            for (int i = 0; i < COLLISION; i++) {
                if (table[hashid] == NULL) {
                    table[hashid] = newitm;
                    break;
                }
                else if (current->getnext() != NULL) {
                    current = current->getnext();
                    length++;
                }
                else {
                    if (length < COLLISION) {
                        current->setnext(newitm);
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
        void addrehashentry (hashItm* newitm) {
            int length = 1;
            int hashid = newitm->gethashid();
            hashItm* current = hashretbl[hashid];
            for (int i = 0; i < COLLISION; i++) {
                if (hashretbl[hashid] == NULL) {
                    hashretbl[hashid] = newitm;
                    break;
                }
                else if (current->getnext() != NULL) {
                    current = current->getnext();
                    length++;
                }
                else {
                    if (length < COLLISION) {
                        current->setnext(newitm);
                        break;
                    }
                }
            }
        }
        bool getrebool() {
            return rehash;
        }
        void printAll() {
            cout << "in print all" << endl;
            if (table == NULL) {
                return;
            }
            for (int i = 0; i < size; i++) {
                hashItm* current = NULL;
                current = table[i];

                if (current == NULL) {
                    continue;
                }

                for (int i = 0; i < 3; i++) {
                    if (current->getnext() == NULL) {
                        current->getstudent().printStudent();
                        cout << endl;
                        break;
                    }
                    else {
                        current->getstudent().printStudent();
                        cout << endl;
                        current = current->getnext();
                    }
                }
            }
        }
        hashItm* getItem(int index) {
            return table[index];
        }
        void setItemNull(int index) {
            table[index] == NULL;
        }
        void rehashtbl() {
            if (rehash != true) {
                return;
            }
            
            cout << "in rehash" << endl;
            int newsize = size * 10;
            hashretbl = new hashItm*[newsize];
            for (int i = 0; i < newsize; i++) {
                hashretbl[i] = NULL;
            }   
            hashItm* current = NULL;
            hashItm* carrier = NULL;
            for (int i = 0; i < size; i++) {
                current = table[i];
                while (current != NULL) {
                    carrier = new hashItm(current->getstudent(), newsize);
                    addrehashentry(carrier);
                    hashItm* tmp = current;
                    current = current->getnext();
                    delete tmp;
                }
            }
            delete[] table;
            table = hashretbl;
            size = newsize;
            rehash = false;
        }
};

int main(void) {
    int arrsize = 8;
    hashTbl mainTbl = hashTbl(arrsize);

    //testCollision();

    while(true) {
        char* input = new char(10);
        cout << "add, delete, print or quit?" << endl; 
        cin >> input;
        cout << endl;

        if (strcmp(input, "add") == 0) {
            char* firstName = new char(20);
            char* lastName = new char(20);
            float gpa;
            int studentId;
            cout << "Please enter first name of the student: " << endl;
            cin >> firstName;
            cout << "Please enter last name of the student: " << endl;
            cin >> lastName;
            cout << "Please enter the student ID of the student: " << endl;
            cin >> studentId;
            cout << "Please enter the GPA of the student: " << endl;
            cin >> gpa;
            cout << endl;

            hashItm* newItem = new hashItm(student(gpa, firstName, lastName, gpa), arrsize);

            mainTbl.addhashentry(newItem);

            if (mainTbl.getrebool() == true) {
                mainTbl.rehashtbl();
                mainTbl.addhashentry(newItem);
            }

        }
        else if (strcmp(input, "delete") == 0) {
            int id;
            float gpa;
            cout << "Please enter the id of the student: " << endl;
            cin >> id;
            cout << "Please enter the gpa of the student: " << endl;
            cin >> gpa;
            cout << endl;
            mainTbl.deleteTerm(id, gpa);
        }
        else if (strcmp(input, "quit") == 0) {
            hashItm* deleter = NULL;
            hashItm* dcurrent = NULL;
            for (int i = 0; i < arrsize; i++) {
                deleter = mainTbl.getItem(i);
                while (deleter != NULL) {
                    dcurrent = deleter->getnext();
                    deleter->setnext(NULL);
                    delete deleter;
                    deleter = dcurrent;
                }
                mainTbl.setItemNull(i);
            }
            break;
        }
        else if (strcmp(input, "print") == 0) {
            mainTbl.printAll();
        }
    }
}

void testCollision() {
    hashTbl cTest = hashTbl(2);

    int size = cTest.getsize();

    student s1 = student(1, "s1", "1", 1);
    student s2 = student(3, "s2", "2", 2);
    student s3 = student(5, "s3", "3", 3);
    student s4 = student(7, "s4", "4", 4);

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
    cTest.addhashentry(p2);
    cTest.addhashentry(p3);
    cTest.addhashentry(p4);

    cTest.printAll();

    cTest.deleteTerm(s1.getid(), s1.getgpa());
    cTest.deleteTerm(s2.getid(), s2.getgpa());

    cout << "Delete 1 and 2" << endl;
    cTest.printAll();

    cTest.deleteTerm(s3.getid(), s3.getgpa());
    cTest.deleteTerm(s4.getid(), s4.getgpa());

    cout << "Delete 3 and 4" << endl;
    cTest.printAll();
    cout << "Delete all" << endl;
}