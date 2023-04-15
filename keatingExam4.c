/*
* Author: Kevin Keating
* Written: 04/11/23
* Purpose: Create a DJDMA of type person. User will be able to add a person,
* delete a person, display the array, search the array, and sort the array in
* ascending order.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeatingExam4H.h"

int main() {
    char searchFirstName[MAX_NAME_LEN]; //Used to search array
    char searchLastName[MAX_NAME_LEN];
    Person* people = NULL;
    int size = 0;
    int choice;

    while (1) {
        printf("\nMenu\n");
        printf("1. Add a person\n");
        printf("2. Delete a person\n");
        printf("3. Display list\n");
        printf("4. Search for a person\n");
        printf("5. Sort the list\n");
        printf("6. Quit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { //Will keep looping until choice is an integer
        //If I attempt to add || getchar() != '\n' here, it won't enter the first letter of name
            printf("Invalid input. Please enter an integer.\n");
            // clear the input buffer
            while (getchar() != '\n');
            continue;
        }

        system("cls"); //Here so the console isn't bloated

        switch (choice) {
        case 1:
            addPerson(&people, &size); //Adds a person
            break;
        case 2:
            deletePerson(&people, &size); //Deletes a person
            break;
        case 3:
            displayPerson(people, size); //Displays the list allong with some stats
            break;
        case 4: //Best way I found to do the sort
            if (size == 0) { //Will boot back to menu if array is empty
                printf("The array is empty. There is nothing to search.\n");
                break;
            }
            printf("Enter the first and last name to search: ");
            scanf("%s %s", searchFirstName, searchLastName); //Gets name for searching

            int index = searchPerson(people, size, searchFirstName, searchLastName); //Finds the index of the person
            if (index == -1) {
                printf("Person not found.\n");
            }
            else {
                printf("Found person at index %d:\n", index);
                printPerson(people[index]); //Displays record
            }

            break;
        case 5:
            sortPeople(people, size); //Sorts list alphabetically by last name
            break;
        case 6:
            printf("Goodbye!\n");
            free(people); //Frees the memory
            return 0;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }

}

void addPerson(Person** people, int* size) {
    Person newPerson;
    char fullName[100];

    printf("Enter the person's name: ");
    getchar();
    fgets(fullName, sizeof(fullName), stdin);
    sscanf(fullName, "%s %s", newPerson.firstName, newPerson.lastName); //Looks for the space and parses off into first and last name
    while (1) {
        printf("Enter age: ");
        if (scanf("%d", &newPerson.age) != 1 || getchar() != '\n') { //Keeps looping until age is an integer
            printf("Invalid input. Please enter a whole number.\n");
            // clear the input buffer
            while (getchar() != '\n');
            continue;
        }
        else {
            break;
        }
    }
    while (1) {
        printf("Enter the person's weight: ");
        if (scanf("%f", &newPerson.weight) != 1) { //Keeps looping until weight is an integer of decimal
            printf("Invalid input. Please enter a number.\n");
            // clear the input buffer
            while (getchar() != '\n');
            continue;
        }
        else {
            break;
        }
    }

    (*size)++;
    *people = realloc(*people, (*size) * sizeof(Person));
    (*people)[*size - 1] = newPerson;
}

void calculate(Person* people, int size) {
    int allAges = 0, letterCount = 0, nameLength = 0;
    float allWeight = 0, averageAge = 0, averageWeight = 0, averageNameLength = 0;

    for (int i = 0; i < size; i++) {
        allAges += people[i].age; //Gets total age
        allWeight += people[i].weight; //Gets total weight
        letterCount = (strlen(people[i].firstName) + strlen(people[i].lastName)); //Gets the letter count of each name
        nameLength += letterCount; //Gets the total count of letters
    }
    averageAge = allAges / size; //Average age
    averageWeight = allWeight / size; //Average weight
    averageNameLength = nameLength / size; //Average length of names
    printf("Average age: %.2f\n", averageAge);
    printf("Average weight: %.2f\n", averageWeight);
    printf("Average name length: %.2f\n", averageNameLength);
}

void deletePerson(Person** people, int* size) {
    if (*size == 0) { //Will boot back to menu if array is empty
        printf("The array is empty. There is no person to delete.\n");
        return;
    }
    int index;
    printf("Enter the index of the person to delete (0-%d): ", *size - 1);
    scanf("%d", &index);

    if (index < 0 || index >= *size) {
        printf("Invalid index.\n");
        return;
    }
    printf("%s %s's record has been deleted.\n", people[index]->firstName, people[index]->lastName);

    for (int i = index; i < *size - 1; i++) {
        (*people)[i] = (*people)[i + 1];
    }

    (*size)--;
    *people = realloc(*people, (*size) * sizeof(Person));
}

void displayPerson(Person* people, int size) {
    if (size == 0) { //Will boot back to menu if array is empty
        printf("The array is empty. There is nothing to display.\n");
        return;
    }
    printf("List of people:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. Name: %s %s, Age: %d, Weight: %.2f\n", i + 1, people[i].firstName, people[i].lastName, people[i].age, people[i].weight);
    }
    calculate(people, size); //Wil calculate the average age, weight and length of name
}

void printPerson(Person people){ //Used in searching for an entry
    printf("Name: %s %s\n", people.firstName, people.lastName);
    printf("Age: %d\n", people.age);
    printf("Weight: %.2f\n", people.weight);
}

int searchPerson(Person people[], int size, char firstName[], char lastName[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(people[i].firstName, firstName) == 0 && strcmp(people[i].lastName, lastName) == 0) {
            return i;
        }
    }
    return -1;
}


void sortPeople(Person* people, int size) {
    if (size == 0) { //Will boot back to menu if array is empty
        printf("The array is empty. There is no people to sort.\n");
        return;
    }
    // bubble sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(people[j].firstName, people[j + 1].firstName) > 0) {
                // swap the two people
                Person temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }
    printf("List sorted.\n");
}
