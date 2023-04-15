#ifndef PERSON_H
#define PERSON_H
#define MAX_NAME_LEN 50

typedef struct {
    char firstName[50];
    char lastName[50];
    int age;
    float weight;
} Person;

void addPerson(Person** people, int* size);
void calculate(Person* people, int size);
void deletePerson(Person** people, int* size);
void displayPerson(Person* people, int size);
void printPerson(Person people);
int searchPerson(Person people[], int numPeople, char firstName[], char lastName[]);
void sortPeople(Person* people, int size);

#endif

