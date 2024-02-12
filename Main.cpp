//  This is a program that creates a hash table of students
//  Created by: Nikaansh S.
//  Last Edited: 2/8/24

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

string readName(const string& filename);

// Class for the student, stores name, gpa, and id
class student {
    private:
        int id;
        float gpa;
        string first;
        string last;
        
    public:
        student(float studentgpa, string studentfirst, string ssecond, int newid) : gpa(studentgpa), first(studentfirst), last(ssecond), id(newid) {}
        void printStudent(void) { // Prints everything in the class
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

// Class for an item that will go in the hash table
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

// Class That stores the hash and rehash table
class hashTbl {
    private:
        int size;
        bool rehash = false;
        const int COLLISION = 3;
        hashItm** table;
        hashItm** hashretbl;
    public:
        hashTbl(int newsize) : size(newsize) {
            table = new hashItm*[size]; // Creates table
            for (int i = 0; i < newsize; i++) { // Sets it all to null
                table[i] = NULL;
            }       
        }
        void deleteTerm(int id, float gpa) {
            int currentid = (int) (gpa * (size/4)) % size; // Gets hashid from gpa
            hashItm* current = table[currentid]; // Goes the hashid index in table
            hashItm* previous = current;

            while(current != NULL) { // While there are items in index
                if (current->getstudent().getid() == id && table[currentid] == current) {  // If current id matches studentid and is start of list
                    table[currentid] = current->getnext();
                    delete current;
                    break;
                }
                else if (current->getstudent().getid() == id) { // If current id matches studentid to be deleted
                    previous->setnext(current->getnext());
                    delete current;
                    break;
                }
                else { // Go to next item
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
            int hashid = newitm->gethashid(); // Gets index of item
            hashItm* current = table[hashid];

            for (int i = 0; i < COLLISION; i++) { // Loops through current index
                if (table[hashid] == NULL) { // If index is null
                    table[hashid] = newitm;
                    break;
                }
                else if (current->getnext() != NULL) { // If next is not null go to next item
                    current = current->getnext();
                    length++;
                }
                else {
                    if (length < COLLISION) { // Adds to list as long as it is under three
                        current->setnext(newitm);
                        break;
                    }
                    else { // Sets rehash to true
                        rehash = true;
                        break;
                    }
                }
            }
        }
        void addrehashentry (hashItm* newitm) { // Same as hash entry, just puts item in the rehash table
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
            if (table == NULL) { // Checks for null table
                return;
            }
            for (int i = 0; i < size; i++) { // Goes through table
                hashItm* current = NULL;
                current = table[i];

                if (current == NULL) { // Checks current item
                    continue;
                }

                for (int i = 0; i < 3; i++) { // Goes through current index
                    if (current->getnext() == NULL) { // End of index
                        current->getstudent().printStudent();
                        cout << endl;
                        break;
                    }
                    else { // Middle of index
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
        void rehashtbl() { // Rehashes the table
            if (rehash != true) { // Checks if table needs to be rehashed
                return;
            }
            
            cout << "Rehash in function" << endl; 

            // Set new size and set rehash table
            int newsize = size * 10;
            hashretbl = new hashItm*[newsize];
            for (int i = 0; i < newsize; i++) {
                hashretbl[i] = NULL;
            }   

            hashItm* current = NULL;
            hashItm* carrier = NULL;

            for (int i = 0; i < size; i++) { // Goes through current table
                current = table[i];
                while (current != NULL) { // Goes through current index
                    carrier = new hashItm(current->getstudent(), newsize); // Creates new hash item
                    addrehashentry(carrier); // Adds new item to rehash table
                    hashItm* tmp = current;
                    current = current->getnext(); // Goes to next item
                    delete tmp; // Deletes item
                }
            }
            delete[] table; // Deletes table
            table = hashretbl; // Set table to rehash table
            hashretbl = NULL; // Sets rehash pointer to null
            size = newsize; // Updates size
            rehash = false;

            cout << "end of rehash in function" << endl;
        }
};

int main(void) {
    srand(time(0));
    int arrsize = 100;
    hashTbl mainTbl = hashTbl(arrsize);
    int itemcounter = 1;

    while(true) {
        // Gets input
        char* input = new char(10);
        cout << "add, random, delete, print or quit?" << endl; 
        cin >> input;
        cout << endl;

        if (strcmp(input, "add") == 0) { // If input is add
            // Gets input from user
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

            // Create item
            hashItm* newItem = new hashItm(student(gpa, firstName, lastName, studentId), arrsize);

            // Add item to table
            mainTbl.addhashentry(newItem);
            itemcounter++;

            //Check for rehash
            if (mainTbl.getrebool() == true) {
                mainTbl.rehashtbl();
                mainTbl.addhashentry(newItem);
                arrsize = arrsize * 10;
            }

        }
        else if (strcmp(input, "delete") == 0) { // If input is delete
            // Gets input from user
            int id;
            float gpa;
            cout << "Please enter the id of the student: " << endl;
            cin >> id;
            cout << "Please enter the gpa of the student: " << endl;
            cin >> gpa;
            cout << endl;

            // Deletes term
            mainTbl.deleteTerm(id, gpa);
            itemcounter--;
        }
        else if (strcmp(input, "quit") == 0) { // If input is quit
            hashItm* deleter = NULL;
            hashItm* dcurrent = NULL;

            for (int i = 0; i < arrsize; i++) { // Loops through hash table
                deleter = mainTbl.getItem(i);

                while (deleter != NULL) { // Deletes until nothing left in current index
                    dcurrent = deleter->getnext();
                    deleter->setnext(NULL);
                    delete deleter;
                    deleter = dcurrent;
                }
                mainTbl.setItemNull(i);
            }
            break;
        }
        else if (strcmp(input, "print") == 0) { // If input is print
            mainTbl.printAll();
        }
        else if (strcmp(input, "random") == 0) { // If input is random
            cout << "How many do you want to add?" << endl;
            int repetition = 0;
            cin >> repetition;
            cout << endl;
            
            string ffilename = "firstNames.txt";
            string lfilename = "lastNames.txt";

            for (int i = 0; i < repetition; i++) {

                // Gets random first and last name
                string firstName = readName(ffilename);
                string lastName = readName(lfilename);

                //Gets a random gpa from 1-4
                float randomNumber = 1 + rand() % (4 - 1 + 1);
                float randomNumber1 = 0 + rand() % (9 - 0 + 1);
                float randomNumber2 = 0 + rand() % (9 - 0 + 1);
                float randomgpa = randomNumber + (randomNumber1 / 10) + (randomNumber2 / 100);

                //Creates and adds hash itm
                hashItm* newItem = new hashItm(student(randomgpa, firstName, lastName, itemcounter), arrsize);

                mainTbl.addhashentry(newItem);
                itemcounter++;

                // Checking for rehash
                if (mainTbl.getrebool() == true) {
                    cout << "Rehash in random" << endl;
                    mainTbl.rehashtbl();
                    mainTbl.addhashentry(newItem);
                    arrsize = arrsize * 10;
                }
            }
        }
    }
}

// Gets a random name from file
string readName(const string& filename) {
    
    // Creates a file
    ifstream file;
    file.open(filename);
    vector<string> names;
    string name;

    // Get name at random index
    if (file.is_open()) {
        while (getline(file, name)) {
            names.push_back(name);
        }
        file.close();
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }

    // Gets a random index
    int randomIndex = rand() % names.size();
    return names[randomIndex];
}