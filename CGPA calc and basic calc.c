//standard libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//defining constants
#define MAX_COURSES 4
#define MAX_NAME_LENGTH 100
#define PI 3.14159265358979323846 //pi

// Function prototypes
void clearInputBuffer();
int readInteger(const char* prompt);
double readDouble(const char* prompt);
void readString(const char* prompt, char* buffer, int size);

// Grade conversion functions
char gradeUsingIf(int mark);
char gradeUsingIfElse(int mark);
int getGradePoint(char grade);

// Number generation functions
void generateMarksFromStudentNumber(long long studentNum, int marks[]);
void generateCalculatorNumbers(long long studentNum, double* num1, double* num2);

// CGPA calculation functions
void calculateCGPA_For_If();
void calculateCGPA_While_IfElse();

// Calculator functions
void calculator_For_If();
void calculator_While_IfElse();

// Helper functions for calculator
double calculateSin(double angle);
double calculateCos(double angle);
double calculateTan(double angle);
double calculateLog10(double num);
double calculateLn(double num);
double calculateSqrt(double num);
double calculateCbrt(double num);

int main() {
    int choice;
    
    printf("====================BIN SULA========================\n");
    printf("    MAKERERE UNIVERSITY - CSC 1102\n");
    printf("    COURSEWORK 1 - CGPA & CALCULATOR\n");
    printf("============================================\n");
    
    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. CGPA Calculator (FOR loop + IF statements)\n");
        printf("2. CGPA Calculator (WHILE loop + IF-ELSE ladder)\n");
        printf("3. Basic Calculator (FOR loop + IF statements)\n");
        printf("4. Basic Calculator (WHILE loop + IF-ELSE ladder)\n");
        printf("0. Exit\n");
        
        choice = readInteger("Enter your choice: ");
        
        switch(choice) {
            case 1:
                calculateCGPA_For_If();
                break;
            case 2:
                calculateCGPA_While_IfElse();
                break;
            case 3:
                calculator_For_If();
                break;
            case 4:
                calculator_While_IfElse();
                break;
            case 0:
                printf("Thank you for using the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
    
    return 0;
}

// Utility functions
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInteger(const char* prompt) {
    int value;
    char buffer[100];
    
    while(1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1) {
                return value;
            }
        }
        printf("Invalid input! Please enter a valid integer.\n");
    }
}

double readDouble(const char* prompt) {
    double value;
    char buffer[100];
    
    while(1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%lf", &value) == 1) {
                return value;
            }
        }
        printf("Invalid input! Please enter a valid number.\n");
    }
}

void readString(const char* prompt, char* buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

// Grade conversion using only IF statements
char gradeUsingIf(int mark) {
    char grade = 'F';
    
    if (mark >= 90 && mark <= 100) grade = 'A';
    if (mark >= 80 && mark < 90) grade = 'B';
    if (mark >= 70 && mark < 80) grade = 'C';
    if (mark >= 60 && mark < 70) grade = 'D';
    if (mark >= 50 && mark < 60) grade = 'E';
    if (mark < 50) grade = 'F';
    
    return grade;
}

// Grade conversion using IF-ELSE ladder
char gradeUsingIfElse(int mark) {
    if (mark >= 90 && mark <= 100) {
        return 'A';
    }
    else if (mark >= 80 && mark < 90) {
        return 'B';
    }
    else if (mark >= 70 && mark < 80) {
        return 'C';
    }
    else if (mark >= 60 && mark < 70) {
        return 'D';
    }
    else if (mark >= 50 && mark < 60) {
        return 'E';
    }
    else {
        return 'F';
    }
}

int getGradePoint(char grade) {
    switch(grade) {
        case 'A': return 5;
        case 'B': return 4;
        case 'C': return 3;
        case 'D': return 2;
        case 'E': return 1;
        case 'F': return 0;
        default: return 0;
    }
}

// Generate marks from student number
void generateMarksFromStudentNumber(long long studentNum, int marks[]) {
    char numStr[20];
    sprintf(numStr, "%lld", studentNum);
    int len = strlen(numStr);
    
    for (int i = 0; i < MAX_COURSES; i++) {
        int idx1 = (i * 2) % len;
        int idx2 = (i * 2 + 1) % len;
        
        int digit1 = numStr[idx1] - '0';
        int digit2 = numStr[idx2] - '0';
        
        int rawValue = digit1 * 10 + digit2;
        int mark = 50 + (int)((rawValue / 99.0) * 50.0);
        
        // Ensure mark is between 50-100
        if (mark < 50) mark = 50;
        if (mark > 100) mark = 100;
        
        marks[i] = mark;
    }
}

// Generate calculator numbers from student number
void generateCalculatorNumbers(long long studentNum, double* num1, double* num2) {
    char numStr[20];
    sprintf(numStr, "%lld", studentNum);
    int len = strlen(numStr);
    
    if (len < 4) {
        // If student number has less than 4 digits, use default values
        *num1 = 12.34;
        *num2 = 56.78;
        return;
    }
    
    // Use last 4 digits
    int d1 = numStr[len-4] - '0';
    int d2 = numStr[len-3] - '0';
    int d3 = numStr[len-2] - '0';
    int d4 = numStr[len-1] - '0';
    
    *num1 = d1 * 10 + d2 + (d2 * 0.1 + d1 * 0.01);
    *num2 = d3 * 10 + d4 + (d4 * 0.1 + d3 * 0.01);
}

// CGPA Calculation using FOR loop and IF statements
void calculateCGPA_For_If() {
    printf("\n=== CGPA CALCULATOR (FOR LOOP + IF STATEMENTS) ===\n");
    
    char studentName[MAX_NAME_LENGTH];
    long long studentNumber;
    int marks[MAX_COURSES];
    int creditUnits[MAX_COURSES];
    
    readString("Enter student name: ", studentName, MAX_NAME_LENGTH);
    studentNumber = readInteger("Enter student number: ");
    
    printf("\nChoose input method:\n");
    printf("1. Auto-generate marks from student number\n");
    printf("2. Enter marks manually\n");
    int choice = readInteger("Enter choice (1 or 2): ");
    
    if (choice == 1) {
        generateMarksFromStudentNumber(studentNumber, marks);
        printf("Auto-generated marks: ");
        for (int i = 0; i < MAX_COURSES; i++) {
            printf("%d ", marks[i]);
        }
        printf("\n");
    } else {
        printf("Enter marks for %d courses:\n", MAX_COURSES);
        for (int i = 0; i < MAX_COURSES; i++) {
            do {
                marks[i] = readInteger("Enter mark (0-100): ");
                if (marks[i] < 0 || marks[i] > 100) {
                    printf("Mark must be between 0 and 100. Please try again.\n");
                }
            } while (marks[i] < 0 || marks[i] > 100);
        }
    }
    
    printf("\nEnter credit units for each course:\n");
    for (int i = 0; i < MAX_COURSES; i++) {
        do {
            creditUnits[i] = readInteger("Enter credit units (positive integer): ");
            if (creditUnits[i] <= 0) {
                printf("Credit units must be positive. Please try again.\n");
            }
        } while (creditUnits[i] <= 0);
    }
    
    // Calculate CGPA
    double totalGradePoints = 0.0;
    int totalCreditUnits = 0;
    
    printf("\n=== CGPA REPORT ===\n");
    printf("Student: %s\n", studentName);
    printf("Reg No: %lld\n\n", studentNumber);
    printf("Course\tMark\tGrade\tGrade Point\tCredit Units\n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < MAX_COURSES; i++) {
        char grade = gradeUsingIf(marks[i]);  // Using IF statements
        int gradePoint = getGradePoint(grade);
        
        printf("%d\t%d\t%c\t%d\t\t%d\n", 
               i + 1, marks[i], grade, gradePoint, creditUnits[i]);
        
        totalGradePoints += gradePoint * creditUnits[i];
        totalCreditUnits += creditUnits[i];
    }
    
    double cgpa = (totalCreditUnits > 0) ? totalGradePoints / totalCreditUnits : 0.0;
    
    printf("------------------------------------------------\n");
    printf("CGPA: %.2f\n", cgpa);
}

// CGPA Calculation using WHILE loop and IF-ELSE ladder
void calculateCGPA_While_IfElse() {
    printf("\n=== CGPA CALCULATOR (WHILE LOOP + IF-ELSE LADDER) ===\n");
    
    char studentName[MAX_NAME_LENGTH];
    long long studentNumber;
    int marks[MAX_COURSES];
    int creditUnits[MAX_COURSES];
    
    readString("Enter student name: ", studentName, MAX_NAME_LENGTH);
    studentNumber = readInteger("Enter student number: ");
    
    printf("\nChoose input method:\n");
    printf("1. Auto-generate marks from student number\n");
    printf("2. Enter marks manually\n");
    int choice = readInteger("Enter choice (1 or 2): ");
    
    if (choice == 1) {
        generateMarksFromStudentNumber(studentNumber, marks);
        printf("Auto-generated marks: ");
        for (int i = 0; i < MAX_COURSES; i++) {
            printf("%d ", marks[i]);
        }
        printf("\n");
    } else {
        printf("Enter marks for %d courses:\n", MAX_COURSES);
        int i = 0;
        while (i < MAX_COURSES) {
            marks[i] = readInteger("Enter mark (0-100): ");
            if (marks[i] >= 0 && marks[i] <= 100) {
                i++;
            } else {
                printf("Mark must be between 0 and 100. Please try again.\n");
            }
        }
    }
    
    printf("\nEnter credit units for each course:\n");
    int i = 0;
    while (i < MAX_COURSES) {
        creditUnits[i] = readInteger("Enter credit units (positive integer): ");
        if (creditUnits[i] > 0) {
            i++;
        } else {
            printf("Credit units must \"ONLY\" be positive. Please try again.\n");
        }
    }
    
    // Calculate CGPA
    double totalGradePoints = 0.0;
    int totalCreditUnits = 0;
    int j = 0;
    
    printf("\n=== CGPA REPORT ===\n");
    printf("Student: %s\n", studentName);
    printf("Reg No: %lld\n\n", studentNumber);
    printf("Course\tMark\tGrade\tGrade Point\tCredit Units\n");
    printf("------------------------------------------------\n");
    
    while (j < MAX_COURSES) {
        char grade = gradeUsingIfElse(marks[j]);  // Using IF-ELSE ladder
        int gradePoint = getGradePoint(grade);
        
        printf("%d\t%d\t%c\t%d\t\t%d\n", 
               j + 1, marks[j], grade, gradePoint, creditUnits[j]);
        
        totalGradePoints += gradePoint * creditUnits[j];
        totalCreditUnits += creditUnits[j];
        j++;
    }
    
    double cgpa = (totalCreditUnits > 0) ? totalGradePoints / totalCreditUnits : 0.0;
    
    printf("------------------------------------------------\n");
    printf("CGPA: %.2f\n", cgpa);
}

// Calculator mathematical functions
double calculateSin(double angle) {
    return sin(angle * PI / 180.0);  // Convert to radians
}

double calculateCos(double angle) {
    return cos(angle * PI / 180.0);  // Convert to radians
}

double calculateTan(double angle) {
    return tan(angle * PI / 180.0);  // Convert to radians
}

double calculateLog10(double num) {
    return log10(num);
}

double calculateLn(double num) {
    return log(num);
}

double calculateSqrt(double num) {
    return sqrt(num);
}

double calculateCbrt(double num) {
    return cbrt(num);
}

// Calculator using FOR loop and IF statements
void calculator_For_If() {
    printf("\n=== BASIC CALCULATOR (FOR LOOP + IF STATEMENTS) ===\n");
    
    double num1, num2;
    long long studentNumber;
    
    printf("\nChoose input method:\n");
    printf("1. Auto-generate numbers from student number\n");
    printf("2. Enter numbers manually\n");
    int choice = readInteger("Enter choice (1 or 2): ");
    
    if (choice == 1) {
        studentNumber = readInteger("Enter student number: ");
        generateCalculatorNumbers(studentNumber, &num1, &num2);
        printf("Generated numbers: %.2f and %.2f\n", num1, num2);
    } else {
        num1 = readDouble("Enter first number: ");
        num2 = readDouble("Enter second number: ");
    }
    
    // Display menu using FOR loop
    printf("\n=== CALCULATOR MENU ===\n");
    char* operations[] = {
        "1. Addition (+)",
        "2. Subtraction (-)",
        "3. Multiplication (*)",
        "4. Division (/)",
        "5. Sine (sin)",
        "6. Cosine (cos)",
        "7. Tangent (tan)",
        "8. Logarithm (base 10)",
        "9. Natural Logarithm (ln)",
        "10. Square Root",
        "11. Cube Root",
        "12. Sum of N numbers"
    };
    
    for (int i = 0; i < 12; i++) {
        printf("%s\n", operations[i]);
    }
    
    int operation;
    do {
        operation = readInteger("\nSelect operation (1-12): ");
        if (operation < 1 || operation > 12) {
            printf("Invalid choice! Please select between 1-12.\n");
        }
    } while (operation < 1 || operation > 12);
    
    double result;
    
    // Perform calculation using IF statements
    if (operation == 1) {
        result = num1 + num2;
        printf("Result: %.2f + %.2f = %.6f\n", num1, num2, result);
    }
    
    if (operation == 2) {
        result = num1 - num2;
        printf("Result: %.2f - %.2f = %.6f\n", num1, num2, result);
    }
    
    if (operation == 3) {
        result = num1 * num2;
        printf("Result: %.2f * %.2f = %.6f\n", num1, num2, result);
    }
    
    if (operation == 4) {
        if (num2 != 0) {
            result = num1 / num2;
            printf("Result: %.2f / %.2f = %.6f\n", num1, num2, result);
        } else {
            printf("Error: Division by zero is not allowed!\n");
        }
    }
    
    if (operation == 5) {
        result = calculateSin(num1);
        printf("Result: sin(%.2f°) = %.6f\n", num1, result);
    }
    
    if (operation == 6) {
        result = calculateCos(num1);
        printf("Result: cos(%.2f°) = %.6f\n", num1, result);
    }
    
    if (operation == 7) {
        result = calculateTan(num1);
        printf("Result: tan(%.2f°) = %.6f\n", num1, result);
    }
    
    if (operation == 8) {
        if (num1 > 0) {
            result = calculateLog10(num1);
            printf("Result: log10(%.2f) = %.6f\n", num1, result);
        } else {
            printf("Error: Logarithm undefined for non-positive numbers!\n");
        }
    }
    
    if (operation == 9) {
        if (num1 > 0) {
            result = calculateLn(num1);
            printf("Result: ln(%.2f) = %.6f\n", num1, result);
        } else {
            printf("Error: Natural logarithm undefined for non-positive numbers!\n");
        }
    }
    
    if (operation == 10) {
        if (num1 >= 0) {
            result = calculateSqrt(num1);
            printf("Result: sqrt(%.2f) = %.6f\n", num1, result);
        } else {
            printf("Error: Square root undefined for negative numbers!\n");
        }
    }
    
    if (operation == 11) {
        result = calculateCbrt(num1);
        printf("Result: cbrt(%.2f) = %.6f\n", num1, result);
    }
    
    if (operation == 12) {
        int n = readInteger("Enter how many numbers you want to sum: ");
        double sum = 0.0;
        
        printf("Enter %d numbers:\n", n);
        for (int i = 0; i < n; i++) {
            double num = readDouble("Enter number: ");
            sum += num;
        }
        
        printf("Sum of %d numbers = %.6f\n", n, sum);
    }
}

// Calculator using WHILE loop and IF-ELSE ladder
void calculator_While_IfElse() {
    printf("\n=== BASIC CALCULATOR (WHILE LOOP + IF-ELSE LADDER) ===\n");
    
    double num1, num2;
    long long studentNumber;
    
    printf("\nChoose input method:\n");
    printf("1. Auto-generate numbers from student number\n");
    printf("2. Enter numbers manually\n");
    int choice = readInteger("Enter choice (1 or 2): ");
    
    if (choice == 1) {
        studentNumber = readInteger("Enter student number: ");
        generateCalculatorNumbers(studentNumber, &num1, &num2);
        printf("Generated numbers: %.2f and %.2f\n", num1, num2);
    } else {
        num1 = readDouble("Enter first number: ");
        num2 = readDouble("Enter second number: ");
    }
    
    // Display menu
    printf("\n=== CALCULATOR MENU ===\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Sine (sin)\n");
    printf("6. Cosine (cos)\n");
    printf("7. Tangent (tan)\n");
    printf("8. Logarithm (base 10)\n");
    printf("9. Natural Logarithm (ln)\n");
    printf("10. Square Root\n");
    printf("11. Cube Root\n");
    printf("12. Sum of N numbers\n");
    
    int operation;
    int validChoice = 0;
    
    // Using WHILE loop for input validation
    while (!validChoice) {
        operation = readInteger("\nSelect operation (1-12): ");
        if (operation >= 1 && operation <= 12) {
            validChoice = 1;
        } else {
            printf("Invalid choice! Please select between 1-12.\n");
        }
    }
    
    double result;
    
    // Perform calculation using IF-ELSE ladder
    if (operation == 1) {
        result = num1 + num2;
        printf("Result: %.2f + %.2f = %.6f\n", num1, num2, result);
    }
    else if (operation == 2) {
        result = num1 - num2;
        printf("Result: %.2f - %.2f = %.6f\n", num1, num2, result);
    }
    else if (operation == 3) {
        result = num1 * num2;
        printf("Result: %.2f * %.2f = %.6f\n", num1, num2, result);
    }
    else if (operation == 4) {
        if (num2 != 0) {
            result = num1 / num2;
            printf("Result: %.2f / %.2f = %.6f\n", num1, num2, result);
        } else {
            printf("Error: Division by zero is not allowed!\n");
        }
    }
    else if (operation == 5) {
        result = calculateSin(num1);
        printf("Result: sin(%.2f°) = %.6f\n", num1, result);
    }
    else if (operation == 6) {
        result = calculateCos(num1);
        printf("Result: cos(%.2f°) = %.6f\n", num1, result);
    }
    else if (operation == 7) {
        result = calculateTan(num1);
        printf("Result: tan(%.2f°) = %.6f\n", num1, result);
    }
    else if (operation == 8) {
        if (num1 > 0) {
            result = calculateLog10(num1);
            printf("Result: log10(%.2f) = %.6f\n", num1, result);
        } else {
            printf("Error: Logarithm undefined for non-positive numbers!\n");
        }
    }
    else if (operation == 9) {
        if (num1 > 0) {
            result = calculateLn(num1);
            printf("Result: ln(%.2f) = %.6f\n", num1, result);
        } else {
            printf("Error: Natural logarithm undefined for non-positive numbers!\n");
        }
    }
    else if (operation == 10) {
        if (num1 >= 0) {
            result = calculateSqrt(num1);
            printf("Result: sqrt(%.2f) = %.6f\n", num1, result);
        } else {
            printf("Error: Square root undefined for negative numbers!\n");
        }
    }
    else if (operation == 11) {
        result = calculateCbrt(num1);
        printf("Result: cbrt(%.2f) = %.6f\n", num1, result);
    }
    else if (operation == 12) {
        int n = readInteger("Enter how many numbers you want to sum: ");
        double sum = 0.0;
        int count = 0;
        
        printf("Enter %d numbers:\n", n);
        // Using WHILE loop for summing numbers
        while (count < n) {
            double num = readDouble("Enter number: ");
            sum += num;
            count++;
        }
        
        printf("Sum of %d numbers = %.6f\n", n, sum);
    }
}
