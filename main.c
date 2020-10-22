#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    int id;
    char firstName[20];
    char lastName[20];
    char major[20];
    char grade[20];
}Student;

/*
** Function: initStudents
**______________________________
** Applys the same id (-1) to all the students in the student array to have a common id
** to be defined as not declared
**
** students[]: the students array
** length: the length of the array
**
** returns: none
**
*/
void initStudents(Student students[], int length){
    for(int i = 0; i < length-1; i++)
        students[i].id = -1;
}


void mainMenu(){

    printf("  **Main Menu**\n"
           "Choose a Function\n"
           "0. Exit\n"
           "1. List Student Info\n"
           "2. Insert New Student\n"
           "3. Search Student ID\n"
           "4. Delete Student\n"
           "5. Update Student Info\n"
    );
}

/*
** Function: existingID
**______________________________
** Goes to the passed ID in the students array checking
** if the ID is set to a defined ID or the ID set in initStudents
**
** students[]: the students array storying all the students
** id: position in the array as well as the students ID if defined
**
** returns: true: if the current ID is set to a defined ID
**          false: if the student ID has yet to be declared
**
*/
bool existingID(Student students[], int id){
    if(students[id].id > -1){
        return true;
    }
    else{
        return false;
    }
}

/*
** Function: removeStudent
**----------------------------------
** Created to be reusable in the update student function to remove the duplicate
** student after changing the variable.  It resets the students id to -1 (the defined undeclared student id)
** and all other information in the object to empty
**
** stdudents[]: students array
** id: student id 
**
** returns: none
**
*/
void removeStudent(Student students[], int id){
        students[id].id = -1;
        strcpy(students[id].firstName, " ");
        strcpy(students[id].lastName, " ");
        strcpy(students[id].major, " ");
        strcpy(students[id].grade, " ");
}

//Database functions
void displayStudents(Student students[], int length);
void searchID(Student students[]);
void insert(Student students[]);
void delete(Student students[]);
void update(Student students[]);

int main(){

    Student students[20];
    initStudents(students, 20);
    int input = -1;
    while(input != 0){
        // getchar();
        mainMenu();
        scanf("%d", &input);
        getchar();
        switch(input){
            case 0:
                printf("Exiting...\n");
                break;
            case 1:
                displayStudents(students, 20);
                break;
            case 2:
                insert(students);
                break;
            case 3:
                searchID(students);
                break;
            case 4:
                delete(students);
                break;
            case 5:
                update(students);
            default:
                break;
        }

    }
    return 0;
}



void displayStudents(Student students[], int length){
    for(int i = 0; i < length - 1; i++){
        if(existingID(students, i)){
            printf("Student ID: %d\n"
                   "Full Name: %s %s\n"
                   "Major: %s\n"
                   "Grade: %s\n\n",
                   students[i].id,
                   students[i].firstName, students[i].lastName,
                   students[i].major,
                   students[i].grade
            );
        }
    }
    printf("Press enter to return to main menu\n");
    getchar();
}

void insert(Student students[]){
    bool valid = true;
    int id;
    do{
        id = 0;
        printf("Enter the new Students ID:  ");
        scanf("%d", &id);
        if(id > 20 || id < 0){
            printf("That ID is not supported.\n");
            valid = false;
            continue;
        }
        if(existingID(students, id) == true){
            printf("There is already an existing student ID.\n");
            valid = false;
            continue;
        }else{
            students[id].id = id;
            valid = true;
        }
    }while(!valid);
    getchar();
    printf("Enter students first name: ");
    scanf("%s", students[id].firstName);
    getchar();
    printf("Enter students last name: ");
    scanf("%s", students[id].lastName);
    getchar();
    printf("Enter students major: ");
    scanf("%s", students[id].major);
    getchar();
    printf("Enter students grade(Freshman-Senior): ");
    scanf("%s", students[id].grade);
    getchar();

    printf("New student created...\n");
  
}

void searchID(Student students[]){
    int id;
    printf("Enter the student id to search: ");
    scanf("%d", &id);
    if(!existingID(students, id)){
        printf("No existing student ID... Returning to menu\n");
    }else{
        printf("Student ID: %d\n"
               "Student Full Name: %s %s\n"
               "Student Major: %s\n"
               "Student Grade: %s\n",
               students[id].id,
               students[id].firstName, students[id].lastName,
               students[id].major,
               students[id].grade
        );
    }
}

void delete(Student students[]){
    int id;
    printf("Enter the student ID to delete: ");
    scanf("%d", &id);
    getchar();
    // If student ID does not exist, no reason to delete anything
    // Return to menu
    if(!existingID(students, id)){
        printf("No student to delete...Returning to menu\n");
    }else{
        // Call remove student function
        removeStudent(students, id);
    }
}

void update(Student students[]){
    int id;
    int input = -1;
    int newID = 0;

    printf("Enter student Id to update information: ");
    scanf("%d", &id);
    getchar();
    if(!existingID(students, id)){
        printf("No student ID existed, returning to menu...\n");
    }else{
        printf("Stuent ID selected: %d\n"
                   "Student First Name: %s\n"
                   "Student Last Name: %s\n"
                   "Student Major: %s\n"
                   "Student Grade: %s\n",
                   students[id].id,
                   students[id].firstName,
                   students[id].lastName,
                   students[id].major,
                   students[id].grade
        );
        while(input != 0){
            printf("What would you like to update about the user?\n"
                   "0. Return to Main Menu\n"
                   "1. Update Student ID\n"
                   "2. Update Student First Name\n"
                   "3. Update Student Last Name\n"
                   "4. Update Student Major\n"
                   "5. Update Student Grade\n"
            );
            scanf("%d", &input);
            switch(input){
                //Exit Function
                case 0:
                    break;
                //Edit ID
                case 1:
                    printf("Enter Updated Student ID\n");
                    scanf("%d", &newID);
                    if(!existingID(students, newID)){
                        students[newID] = students[id];
                        students[newID].id = newID;
                        removeStudent(students, id);
                    }else{
                        int swap = 0;
                        Student tempStudent;
                        printf("There is already an existing Student with that ID...\n"
                               "Would you like to swap student IDs?\n"
                               "1. Yes\n"
                               "2. No\n"
                        );
                        scanf("%d", &swap);
                        if(swap == 1){
                        //ID Editing Student
                        //Transfering target swap student to temporary variable
                        tempStudent = students[newID];
                        // Transfering searched student to the new spot in the Array
                        students[newID] = students[id];
                        // Assigning the tempStudent to  the new ID
                        students[id] = tempStudent;
                        //Updating both students IDs in the system
                        students[newID].id = newID;
                        students[id].id = id;
                        printf("Student IDs swapped...Returning to main menu\n");
                        }else{
                            printf("Returning to main menu\n");
                            continue;
                        }
                    }
                    break;
                //Edit Student First names
                case 2:
                    printf("Enter students new first name\n");
                    scanf("%s", students[id].firstName);
                    getchar();
                    break;
                //Edit Student Last Name
                case 3:
                    printf("Enter students new last name\n");
                    scanf("%s", students[id].lastName);
                    getchar();
                //Edit Students Major
                case 4:
                    printf("Enter students new major\n");
                    scanf("%s", students[id].major);
                    getchar();
                //Edit Students Grade   
                case 5:
                    printf("Enter students new grade\n");
                    scanf("%s", students[id].grade);
                    getchar();
                //Default
                default:
                    break;
            // End of Switch statement
            }
        // End of While statement
        }
    // End of Else statement
    }
// End of update function
}