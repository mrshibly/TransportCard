# TransportCard

Transport Card Verification System
Project Overview

The Transport Card Verification System is a comprehensive application designed to manage user registration, profile verification, and payment processing for a transportation service. The system caters to different user categories, including students, teachers, alumni, and student assistants, each with specific attributes and requirements.
Features
1. User Registration

    Users can register by providing necessary details such as name, category (student, teacher, alumni), and route.
    Student registration includes additional information like student ID, department, and student category.

2. Profile Management

    Users can view their profiles, containing information relevant to their category.
    The system supports quick verification to check payment status and outstanding balances.

3. Payment Processing

    Students can initiate payments based on their route, department, and category.
    The system calculates the amount due according to predefined criteria and deducts it from the user's balance.

4. Data Export and Import

    Users can export their profile data to a file for record-keeping.
    The system allows importing user data from an external file for easy data migration.

5. Administrative Functions

    Admins can view profiles of all registered users.
    The system provides an option to export all user data for administrative purposes.

Unique Features
Dynamic Payment Calculation

    The payment amount is dynamically calculated based on the user's route, department (for students), and category.

User-Friendly Interface

    The system incorporates a user-friendly interface with clear prompts and options for easy navigation.

Persistent Unique ID Generation

    Unique IDs are generated and persisted across program runs, ensuring continuous and consistent user identification.

Robust File Handling

    The system employs robust file handling mechanisms for saving, loading, exporting, and importing user data.

Technologies Used

    Programming Language: C
    Data Storage: File-based storage (text files)
    User Interface: Console-based interaction

How to Run

To run the Transport Card Verification System:

    Compile the source code using a C compiler.
    Execute the compiled program.

Future Enhancements

Future enhancements may include the integration of a graphical user interface (GUI), a database for data storage, and additional user management features.
