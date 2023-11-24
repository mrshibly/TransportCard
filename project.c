#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct Student {
    int studentID;
    char studentName[50];
    char department[50]; // Add department field
    bool isCleared; 
};


struct Teacher {
    int teacherID;
    char teacherName[50];
};

struct Alumni {
    int alumniID;
    char alumniName[50];
};

struct User {
    int userID;
    char category[20]; // Student, Teacher, Alumni
    char route[50];    // Route they choose
    float balance;      // Add balance field
    union {
        struct Student student;
        struct Teacher teacher;
        struct Alumni alumni;
    } user_info;
};


struct Node {
    struct User data;
    struct Node* next;
};

void freeList(struct Node* head)
{
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}


// Function to add a new user
void addUser(struct Node** head)
{
    // Create a new node for the user
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Unable to add the user.\n");
        return;
    }

    // Autogenerate a unique ID (you can implement your own logic for generating unique IDs)
    static int uniqueID = 1; // Initialize with a starting value
    newNode->data.userID = uniqueID++;

    printf("Select Category:\n");
    printf("\t1. Student\n");
    printf("\t2. Teacher\n");
    printf("\t3. Alumni\n");
    int categoryChoice;
    scanf("%d", &categoryChoice);

    switch (categoryChoice) {
    // Inside the case for student category in the switch statement
    case 1:
        printf("Enter Student Name: ");
        scanf("%s", newNode->data.user_info.student.studentName);

        printf("Enter Department: ");
        scanf("%s", newNode->data.user_info.student.department);

        printf("Enter Student ID: ");
        scanf("%d", &newNode->data.user_info.student.studentID);

        printf("Select Student Category:\n");
        printf("\t1. Regular Student\n");
        printf("\t2. Student Assistant\n");
        printf("\t3. Student from Hall\n");
        int studentCategoryChoice;
        scanf("%d", &studentCategoryChoice);

        switch (studentCategoryChoice) {
        case 1:
            strcpy(newNode->data.category, "Student");
            newNode->data.user_info.student.isCleared = 0; // Initialize as not cleared
            break;
        case 2:
            strcpy(newNode->data.category, "Student Assistant");
            newNode->data.user_info.student.isCleared = 0; // Initialize as not cleared
            break;
        case 3:
            strcpy(newNode->data.category, "Student from Hall");
            
            printf("Select Hall (1-4):\n");
            const char* halls[] = {
                "YKSC1", "YKSC2", "RASG1", "DSSI"
            };
            for (int i = 0; i < 4; i++) {
                printf("\t%d. %s\n", i + 1, halls[i]);
            }
            int hallChoice;
            scanf("%d", &hallChoice);

            if (hallChoice >= 1 && hallChoice <= 4) {
                // Set the selected hall for the student from the hall
                strcpy(newNode->data.route, halls[hallChoice - 1]);
            } else {
                printf("Invalid hall choice.\n");
                free(newNode);
                return;
            }

            newNode->data.user_info.student.isCleared = 0; // Initialize as not cleared
            break;
        default:
            printf("Invalid student category choice.\n");
            free(newNode);
            return;
        }
        break;
    case 2:
        strcpy(newNode->data.category, "Teacher");
        printf("Enter Teacher Name: ");
        scanf("%s", newNode->data.user_info.teacher.teacherName);
        printf("Enter Teacher ID: ");
        scanf("%d", &newNode->data.user_info.teacher.teacherID);
        break;
    case 3:
        strcpy(newNode->data.category, "Alumni");
        printf("Enter Alumni Name: ");
        scanf("%s", newNode->data.user_info.alumni.alumniName);
        printf("Enter Alumni ID: ");
        scanf("%d", &newNode->data.user_info.alumni.alumniID);
        break;
    default:
        printf("Invalid category choice.\n");
        free(newNode);
        return;
    }

    // Select Route
    printf("Select Route (1-12):\n");
    const char* routes[] = {
        "Narayanganj", "Green Model Town", "ECB", "Dhanmondi",
        "Konabari", "Tongi", "Uttara - Rajlokkhi", "Dhamrai",
        "Uttara - Khalpar", "Majar Road", "Baipail", "Savar"
    };
    for (int i = 0; i < 12; i++) {
        printf("\t%d. %s\n", i + 1, routes[i]);
    }
    int routeChoice;
    scanf("%d", &routeChoice);

    if (routeChoice >= 1 && routeChoice <= 12) {
        strcpy(newNode->data.route, routes[routeChoice - 1]);
    } else {
        printf("Invalid route choice.\n");
        free(newNode);
        return;
    }

    // Initialize balance (you can set an initial value as needed)
    newNode->data.balance = 0.0;

    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("User added successfully. Unique ID: %d\n", newNode->data.userID); // Print the unique ID
}


// Function to search and display a user's profile
void searchProfile(struct Node* head)
{
    int userID;
    printf("Enter the Unique ID of the user: ");
    if (scanf("%d", &userID) != 1) {
        printf("Invalid input. Please enter a valid user ID.\n");
        return;
    }

    struct Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (current->data.userID == userID) {
            found = 1;
            printf("\nUser Profile\n");
            printf("Unique ID: %d\n", current->data.userID);

            if (strcmp(current->data.category, "Student") == 0) {
                printf("ID: %d\n", current->data.user_info.student.studentID);
                printf("Student Name: %s\n", current->data.user_info.student.studentName);
                printf("Department: %s\n", current->data.user_info.student.department);
                if (current->data.user_info.student.isCleared) {
                    printf("Payment Status: Payment Cleared\n");
                } else {
                    printf("Payment Status: Payment Not Cleared\n");
                }
            } else if (strcmp(current->data.category, "Teacher") == 0) {
                printf("Teacher ID: %d\n", current->data.user_info.teacher.teacherID);
                printf("Teacher Name: %s\n", current->data.user_info.teacher.teacherName);
            } else if (strcmp(current->data.category, "Alumni") == 0) {
                printf("Alumni ID: %d\n", current->data.user_info.alumni.alumniID);
                printf("Alumni Name: %s\n", current->data.user_info.alumni.alumniName);
            }

            return; // User found, exit the loop
        }
        current = current->next;
    }

    if (!found) {
        printf("User with Unique ID %d does not exist.\n", userID);
    }
}


// Function to perform quick verification
void quickVerification(struct Node* head)
{
    int userID;

    printf("Enter the Unique ID of the user: ");
    if (scanf("%d", &userID) != 1) {
        printf("Invalid input. Please enter a valid user ID.\n");
        return;
    }

    struct Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (current->data.userID == userID) {
            found = 1;
            printf("\nQuick Verification\n");
            printf("Unique ID: %d\n", current->data.userID);
            printf("Category: %s\n", current->data.category);

            if (strcmp(current->data.category, "Student") == 0) {
                if (current->data.user_info.student.isCleared) {
                    printf("Payment is already cleared for this student.\n");
                } else {
                    float amountDue;

                    // Adjusted code based on route and student category
                    if ((strcmp(current->data.route, "Narayanganj") == 0 || strcmp(current->data.route, "Green Model Town") == 0) &&
                        strcmp(current->data.user_info.student.department, "Regular Student") == 0) {
                        amountDue = 6000.0; // Regular students from Narayanganj and Green Model Town pay 6000 Taka
                    } else if (strstr(current->data.route, "Hall") != NULL) {
                        amountDue = 1000.0; // Hall students pay 1000 Taka
                    } else {
                        amountDue = 5000.0; // Default charge for other routes and categories
                    }

                    printf("Amount Due: %.2f Taka\n", amountDue);

                    printf("Choose an option:\n");
                    printf("1. Pay Now\n");
                    printf("2. Go back to the main menu\n");

                    int paymentOption;
                    scanf("%d", &paymentOption);

                    if (paymentOption == 1) {
                        current->data.user_info.student.isCleared = 1; // Mark the semester as cleared
                        current->data.balance -= amountDue; // Deduct the amount from the user's balance
                        printf("Payment is successful. Updated balance: %.2f Taka\n", current->data.balance);
                    } else {
                        printf("Payment not processed. Returning to the main menu.\n");
                    }
                }
            } else if (strcmp(current->data.category, "Teacher") == 0 || strcmp(current->data.category, "Alumni") == 0 || strcmp(current->data.category, "Student Assistant") == 0) {
                printf("No payment is required for teachers, alumni, and student assistants.\n");
            } else {
                printf("This verification is only applicable to students, teachers, alumni, and student assistants.\n");
            }
            return; // User found, exit the loop
        }
        current = current->next;
    }

    if (!found) {
        printf("User with Unique ID %d does not exist.\n", userID);
    }
}


// Function to initiate the payment process
void initiatePayment(struct Node* head) {
    int userID;
    printf("Enter the Unique ID of the user: ");
    if (scanf("%d", &userID) != 1) {
        printf("Invalid input. Please enter a valid user ID.\n");
        return;
    }

    struct Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (current->data.userID == userID) {
            found = 1;

            printf("\nPayment Initiation\n");
            printf("Unique ID: %d\n", current->data.userID);
            printf("Category: %s\n", current->data.category);

            if (strcmp(current->data.category, "Student") == 0) {
                if (current->data.user_info.student.isCleared) {
                    printf("Payment is already cleared for this student.\n");
                } else {
                    float amountDue;
                    // Adjusted code based on route and student category
                    if ((strcmp(current->data.route, "Narayanganj") == 0 || strcmp(current->data.route, "Green Model Town") == 0) &&
                        strcmp(current->data.user_info.student.department, "Regular Student") == 0) {
                        amountDue = 6000.0; // Regular students from Narayanganj and Green Model Town pay 6000 Taka
                    } else if (strstr(current->data.route, "Hall") != NULL) {
                        amountDue = 1000.0; // Hall students pay 1000 Taka
                    } else {
                        amountDue = 5000.0; // Default charge for other routes and categories
                    }

                    printf("Amount Due: %.2f Taka\n", amountDue);
                    printf("Choose an option:\n");
                    printf("1. Pay Now\n");
                    printf("2. Cancel Payment\n");

                    int paymentOption;
                    scanf("%d", &paymentOption);

                    if (paymentOption == 1) {
                        // Process the payment and update the user's payment status
                        current->data.user_info.student.isCleared = 1;
                        current->data.balance -= amountDue;
                        printf("Payment successful. Updated balance: %.2f Taka\n", current->data.balance);
                    } else {
                        printf("Payment canceled.\n");
                    }
                }
            } else if (strcmp(current->data.category, "Teacher") == 0 || strcmp(current->data.category, "Alumni") == 0 || strcmp(current->data.category, "Student Assistant") == 0) {
                printf("No payment is required for teachers, alumni, and student assistants.\n");
            } else {
                printf("This verification is only applicable to students, teachers, alumni, and student assistants.\n");
            }
            return; // User found, exit the loop
        }
        current = current->next;
    }

    if (!found) {
        printf("User with Unique ID %d does not exist.\n", userID);
    }
}


// Modify the saveDataToFile function
void saveDataToFile(struct Node* head)
{
    FILE* file = fopen("user_data.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %s %.2f", current->data.userID, current->data.category, current->data.route, current->data.balance);

        if (strcmp(current->data.category, "Student") == 0) {
            fprintf(file, " %s", current->data.user_info.student.studentName);
            fprintf(file, " %d", current->data.user_info.student.isCleared ? 1 : 0); // Save the isCleared status
        } else if (strcmp(current->data.category, "Teacher") == 0) {
            fprintf(file, " %s", current->data.user_info.teacher.teacherName);
        } else if (strcmp(current->data.category, "Alumni") == 0) {
            fprintf(file, " %s", current->data.user_info.alumni.alumniName);
        }

        fprintf(file, "\n");
        current = current->next;
    }

    fclose(file);
    printf("User data saved to file.\n");
}

// Modify the loadDataFromFile function
void loadDataFromFile(struct Node** head)
{
    FILE* file = fopen("user_data.txt", "r");
    if (file == NULL) {
        printf("No user data file found. Starting with an empty list.\n");
        return;
    }

    struct Node* newNode;
    while (1) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed. Unable to load user data.\n");
            fclose(file);
            return;
        }

        int numRead = fscanf(file, "%d %19s %49s %f", &newNode->data.userID, newNode->data.category, newNode->data.route, &newNode->data.balance);

        if (numRead == EOF) {
            free(newNode);
            break;
        }

        if (strcmp(newNode->data.category, "Student") == 0) {
            fscanf(file, "%49s", newNode->data.user_info.student.studentName);
            int isCleared;
            fscanf(file, "%d", &isCleared);
            newNode->data.user_info.student.isCleared = (isCleared == 1) ? true : false; // Load the isCleared status
        } else if (strcmp(newNode->data.category, "Teacher") == 0) {
            fscanf(file, "%49s", newNode->data.user_info.teacher.teacherName);
        } else if (strcmp(newNode->data.category, "Alumni") == 0) {
            fscanf(file, "%49s", newNode->data.user_info.alumni.alumniName);
        }

        newNode->next = *head;
        *head = newNode;
    }

    fclose(file);
    printf("User data loaded from file.\n");
}

// Function to export user data to a file and open it
void exportDataToFile(struct Node* head) {
    FILE* file = fopen("exported_user_data.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %s %.2f", current->data.userID, current->data.category, current->data.route, current->data.balance);

        if (strcmp(current->data.category, "Student") == 0) {
            fprintf(file, " %s", current->data.user_info.student.studentName);
            fprintf(file, " %s", current->data.user_info.student.department);
            fprintf(file, " %d", current->data.user_info.student.isCleared ? 1 : 0);
        } else if (strcmp(current->data.category, "Teacher") == 0) {
            fprintf(file, " %s", current->data.user_info.teacher.teacherName);
        } else if (strcmp(current->data.category, "Alumni") == 0) {
            fprintf(file, " %s", current->data.user_info.alumni.alumniName);
        }

        fprintf(file, "\n");
        current = current->next;
    }

    fclose(file);
    printf("User data exported to file.\n");

    // Open the exported file using the default text editor
    printf("Opening the exported file...\n");
    #ifdef _WIN32
        system("start notepad.exe exported_user_data.txt");
    #elif __linux__
        system("xdg-open exported_user_data.txt");
    #else
        printf("File opening not supported on this platform.\n");
    #endif
}

// Function to import user data from a file
void importDataFromFile(struct Node** head) {
    FILE* file = fopen("imported_user_data.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open the file for reading.\n");
        return;
    }

    // Clear existing data
    freeList(*head);
    *head = NULL;

    struct Node* newNode;
    while (1) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed. Unable to load user data.\n");
            fclose(file);
            return;
        }

        int numRead = fscanf(file, "%d %19s %49s %f", &newNode->data.userID, newNode->data.category, newNode->data.route, &newNode->data.balance);

        if (numRead == EOF) {
            free(newNode);
            break;
        }

        if (strcmp(newNode->data.category, "Student") == 0) {
            fscanf(file, "%49s", newNode->data.user_info.student.studentName);
            fscanf(file, "%49s", newNode->data.user_info.student.department);
            int isCleared;
            fscanf(file, "%d", &isCleared);
            newNode->data.user_info.student.isCleared = (isCleared == 1) ? true : false;
        } else if (strcmp(newNode->data.category, "Teacher") == 0) {
            fscanf(file, "%49s", newNode->data.user_info.teacher.teacherName);
        } else if (strcmp(newNode->data.category, "Alumni") == 0) {
            fscanf(file, "%49s", newNode->data.user_info.alumni.alumniName);
        }

        newNode->next = *head;
        *head = newNode;
    }

    fclose(file);
    printf("User data imported from file.\n");
}

// Function to display all user profiles
void showAllProfiles(struct Node* head) {
    struct Node* current = head;

    printf("\nAll User Profiles\n");
    while (current != NULL) {
        printf("Unique ID: %d\n", current->data.userID);

        if (strcmp(current->data.category, "Student") == 0) {
            printf("ID: %d\n", current->data.user_info.student.studentID);
            printf("Student Name: %s\n", current->data.user_info.student.studentName);
            printf("Department: %s\n", current->data.user_info.student.department);
            if (current->data.user_info.student.isCleared) {
                printf("Payment Status: Payment Cleared\n");
            } else {
                printf("Payment Status: Payment Not Cleared\n");
            }
        } else if (strcmp(current->data.category, "Teacher") == 0) {
            printf("Teacher ID: %d\n", current->data.user_info.teacher.teacherID);
            printf("Teacher Name: %s\n", current->data.user_info.teacher.teacherName);
        } else if (strcmp(current->data.category, "Alumni") == 0) {
            printf("Alumni ID: %d\n", current->data.user_info.alumni.alumniID);
            printf("Alumni Name: %s\n", current->data.user_info.alumni.alumniName);
        }

        printf("\n");
        current = current->next;
    }
}

int main()
{
    struct Node* userList = NULL;
    int choice;

    // Load user data from file when the program starts
    loadDataFromFile(&userList);
    printf("              .~?5GB####BG5?~.             \n");
    printf("         .7P#&#G5?!!~~!7?5G###G7.         \n");
    printf("       7B&#Y~.              .~Y#&B7       \n");
    printf("     ?&&5:                      :5&&?     \n");
    printf("   ^#@5.                          .5@#^   \n");
    printf("  7@&~       JGGGGGGGGGGGGGGY.      ~&@7  \n");
    printf(" 7@&:     :.JBJJJJJJJJJJJJJJBP.:     :&@7 \n");
    printf(".&&^     :@PY~              ~GG@:     ^&&:\n");
    printf("5@G      :@PJ~       .      ~PP@:      B@5\n");
    printf("#@J      :&5JJ..:7^~~.......JP5&:      ?@#\n");
    printf("&@?         J@&&@&&@&&&&&&&&@P         ?@&\n");
    printf("G@P         J&BBB##?JJJ#&BBB#P         P@G\n");
    printf("^&&:        YG.::Y#7777#P:^:YG        .&@^\n");
    printf(" Y@B        :?PPPP!~~~~!YGGBY^        G@Y \n");
    printf("  5@#.       .##&Y      7&#&^       .#@5  \n");
    printf("   ?&&7                            7&&?   \n");
    printf("    .P@#7                        7#@G.    \n");
    printf("      :5&&P~.                .!P&&5:      \n");
    printf("         ~5#&#5?!^:....:^~7Y#&#P~         \n");
    do {
        printf("\n\nTransport Card Verification System\n");
        printf("\t1. Register New User\n");
        printf("\t2. See Profile\n");
        printf("\t3. Show All Profiles\n");
        printf("\t4. Quick Verification\n");
        printf("\t5. Payment\n");
        printf("\t6. Export Data\n");
        printf("\t7. Exit\n");  // Removed the import option
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addUser(&userList);
            break;
        case 2:
            searchProfile(userList);
            break;
        case 3:
            showAllProfiles(userList);
            break;
        case 4:
            quickVerification(userList);
            break;
        case 5:
            initiatePayment(userList);
            break;
        case 6:
            exportDataToFile(userList);
            break;
        case 7:
            // Save user data to a file before exiting
            saveDataToFile(userList);
            printf("User data saved to file. Exiting the system.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    freeList(userList);

    return 0;
}

