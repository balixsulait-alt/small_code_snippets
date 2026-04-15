/*MAKERERE UNIVERSITY
 * CSC 1102:Structured Programming and OOP
 * COURSEWORK 1 -BIST
 * Group members: [BALIKOOWA SULAIMAN ,KIYOMBO ALVIN, BALUKA LETICIA CONSTANCE,   KINYIRI HUZAIRU ]
 * Reg No: [25/U/03705/PS, 25/U/03831/PSA,25/U/03707/PS, 25/U/03815/PS, ]
 *students No: [2500703705 , 2500703831, 2500703707, 2500703815]*/


//libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Constants
#define NUM_COURSES 4
#define MAX_NAME 100

/* Global shared data */
char studentName[MAX_NAME] = "";
long long studentNumber = 0;
int marks[NUM_COURSES];
int creditUnits[NUM_COURSES];
double calcNum1 = 0.0, calcNum2 = 0.0;

/* input helpers */
void read_line(char *buf, int n) {
    if (!fgets(buf, n, stdin)) { buf[0] = '\0'; return; }
    buf[strcspn(buf, "\n")] = '\0';
}

long long read_ll(const char *prompt) {
    char buf[128];
    long long v;
    while (1) {
        if (prompt) printf("%s", prompt);
        read_line(buf, sizeof(buf));
        if (sscanf(buf, "%lld", &v) == 1) return v;
        printf("Invalid integer. Try again.\n");
    }
}

int read_int(const char *prompt) {
    char buf[128];
    int v;
    while (1) {
        if (prompt) printf("%s", prompt);
        read_line(buf, sizeof(buf));
        if (sscanf(buf, "%d", &v) == 1) return v;
        printf("Invalid integer. Try again.\n");
    }
}

double read_double(const char *prompt) {
    char buf[128];
    double v;
    while (1) {
        if (prompt) printf("%s", prompt);
        read_line(buf, sizeof(buf));
        if (sscanf(buf, "%lf", &v) == 1) return v;
        printf("Invalid number. Try again.\n");
    }
}

/* Auto-generation */
void generate_marks_from_student_number(long long stu, int out_marks[NUM_COURSES]) {
    int digits[64];
    int n = 0;
    long long tmp = llabs(stu);
    if (tmp == 0) tmp = 12345;    

    while (tmp > 0 && n < 64) {
        digits[n++] = tmp % 10;
        tmp /= 10;
    }
    if (n == 0) { digits[n++] = 1; digits[n++] = 2; digits[n++] = 3; }

    for (int i = 0; i < NUM_COURSES; ++i) {
        int a = digits[(i * 2) % n];
        int b = digits[(i * 2 + 1) % n];
        int raw = a * 10 + b;           /* 0..99 */
        int mark = 50 + (int)round((raw / 99.0) * 50.0);
        if (mark < 50) mark = 50;
        if (mark > 100) mark = 100;
        out_marks[i] = mark;
    }
}

void generate_calculator_numbers_from_student_number(long long stu, double *a, double *b) {
    int digits[16];
    int n = 0;
    long long tmp = llabs(stu);
    if (tmp == 0) tmp = 7689; //fallback

    while (tmp > 0 && n < 16) {
        digits[n++] = tmp % 10;
        tmp /= 10;
    }
    if (n < 4) {
        for (int i = n; i < 4; ++i) digits[n++] = (i+3) % 10 + 1;
    }
    int d1 = digits[(n - 1) % n];
    int d2 = digits[(n - 2 + n) % n];
    int d3 = digits[(n - 3 + n) % n];
    int d4 = digits[(n - 4 + n) % n];

    *a = (d2 * 10 + d1) + (d1 * 0.1 + d2 * 0.01);
    *b = (d4 * 10 + d3) + (d3 * 0.1 + d4 * 0.01);
}

/*Grade conversion functions IF-only (multiple independent ifs) */
char gradeUsingIf(int mark) {
    if (mark >= 90 && mark <= 100) return 'A';
    if (mark >= 80 && mark <= 89)  return 'B';
    if (mark >= 70 && mark <= 79)  return 'C';
    if (mark >= 60 && mark <= 69)  return 'D';
    if (mark >= 50 && mark <= 59)  return 'E';
    if (mark < 50)                 return 'F';
    return 'F';
}

// IF-ELSE ladder
char gradeUsingIfElse(int mark) {
    if (mark >= 90 && mark <= 100) return 'A';
    else if (mark >= 80 && mark <= 89) return 'B';
    else if (mark >= 70 && mark <= 79) return 'C';
    else if (mark >= 60 && mark <= 69) return 'D';
    else if (mark >= 50 && mark <= 59) return 'E';
    else return 'F';
}

int gradePoint(char g) {
    if (g == 'A') return 5;
    if (g == 'B') return 4;
    if (g == 'C') return 3;
    if (g == 'D') return 2;
    if (g == 'E') return 1;
    return 0;
}
   
   //CGPA: FOR loop + IF-only
void calculateCGPA_ForLoop_If() {
    double totalPoints = 0.0, totalCredits = 0.0;

    printf("\nCGPA (FOR loop + IF-only)\n");
    printf("Enter Name: ");
    read_line(studentName, MAX_NAME);
    if (strlen(studentName) == 0) strcpy(studentName, "(unknown)");

    studentNumber = read_ll("Enter Student Number (digits only): ");

    printf("Choose marks source:\n1) Auto-generate from student number\n2) Enter marks manually\n");
    int src = read_int("Choice (1 or 2): ");
    if (src == 1) {
        generate_marks_from_student_number(studentNumber, marks);
        printf("Auto-generated marks: ");
        for (int i = 0; i < NUM_COURSES; ++i) printf("%d%s", marks[i], (i==NUM_COURSES-1)?"\n":" ");
    } else {
        for (int i = 0; i < NUM_COURSES; ++i) {
            int m;
            do {
                m = read_int("Enter mark (0-100): ");
                if (m < 0 || m > 100) printf("Mark must be 0..100. Try again.\n");
            } while (m < 0 || m > 100);
            marks[i] = m;
        }
    }

    for (int i = 0; i < NUM_COURSES; ++i) {
        double cu;
        do {
            cu = read_double("Enter credit units (positive number): ");
            if (cu <= 0) printf("Credit units must be > 0. Try again.\n");
        } while (cu <= 0);
        creditUnits[i] = (int)round(cu);
    }

    printf("\n--- CGPA REPORT ---\n");
    printf("Name: %s | Reg No: %lld\n", studentName, studentNumber);
    printf("Crs | Mark | Grade | GP | CU | Points\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < NUM_COURSES; ++i) {
        char g = gradeUsingIf(marks[i]); /* IF-only */
        int gp = gradePoint(g);
        double pts = gp * creditUnits[i];
        totalPoints += pts;
        totalCredits += creditUnits[i];
        printf(" %d  |  %3d |   %c   |  %d |  %2d |  %.1f\n",
               i+1, marks[i], g, gp, creditUnits[i], pts);
    }

    double cgpa = (totalCredits > 0.0) ? (totalPoints / totalCredits) : 0.0;
    printf("----------------------------------------\n");
    printf("CGPA = %.2f\n\n", cgpa);
}

  // CGPA: WHILE loop + IF-ELSE ladder//
void calculateCGPA_WhileLoop_IfElse() {
    double totalPoints = 0.0, totalCredits = 0.0;
    int i = 0;

    printf("\n CGPA  using WHILE loop and  IF-ELSE ladder\n");
    printf("Enter Name: ");
    read_line(studentName, MAX_NAME);
    if (strlen(studentName) == 0) strcpy(studentName, "(unknown)");

    studentNumber = read_ll("Enter Student Number (digits only): ");

    printf("Choose marks source:\n1) Auto-generate from student number\n2) Enter marks manually\n");
    int src = read_int("Choice (1 or 2): ");
    if (src == 1) {
        generate_marks_from_student_number(studentNumber, marks);
        printf("Auto-generated marks: ");
        for (int k = 0; k < NUM_COURSES; ++k) printf("%d%s", marks[k], (k==NUM_COURSES-1)?"\n":" ");
    } else {
        i = 0;
        while (i < NUM_COURSES) {
            int m = read_int("Enter mark (0-100): ");
            if (m < 0 || m > 100) { printf("Mark must be 0..100.\n"); continue; }
            marks[i++] = m;
        }
    }

    i = 0;
    while (i < NUM_COURSES) {
        double cu = read_double("Enter credit units (positive number): ");
        if (cu <= 0) { printf("Credit units must be > 0.\n"); continue; }
        creditUnits[i++] = (int)round(cu);
    }

    printf("\n--- CGPA REPORT ---\n");
    printf("Name: %s | Reg No: %lld\n", studentName, studentNumber);
    printf("Crs | Mark | Grade | GP | CU | Points\n");
    printf("----------------------------------------\n");

    i = 0;
    while (i < NUM_COURSES) {
        char g = gradeUsingIfElse(marks[i]); // IF-ELSE ladder
        int gp = gradePoint(g);
        double pts = gp * creditUnits[i];
        totalPoints += pts;
        totalCredits += creditUnits[i];
        printf(" %d  |  %3d |   %c   |  %d |  %2d |  %.1f\n",
               i+1, marks[i], g, gp, creditUnits[i], pts);
        i++;
    }

    double cgpa = (totalCredits > 0.0) ? (totalPoints / totalCredits) : 0.0;
    printf("----------------------------------------\n");
    printf("CGPA = %.2f\n\n", cgpa);
}

  // Calculator: FOR loop + IF-only
void basicCalculator_ForLoop_If() {
    printf("\nCALCULATOR using FOR loop and  IF-only\n");

    printf("Choose number source:\n1) Auto-generate from student number\n2) Enter numbers manually\n");
    int src = read_int("Choice (1 or 2): ");
    if (src == 1) {
        if (studentNumber == 0) {
            studentNumber = read_ll("Student number not set. Enter Student Number to generate numbers: ");
        }
        generate_calculator_numbers_from_student_number(studentNumber, &calcNum1, &calcNum2);
        printf("Using generated numbers: %.2f and %.2f\n", calcNum1, calcNum2);
    } else {
        calcNum1 = read_double("Enter first number: ");
        calcNum2 = read_double("Enter second number: ");
    }

    int choice = 0;
    for (;;) {
        printf("\nMENU (angles in degrees):\n");
        printf("1.+  2.-  3.*  4./  5.sin  6.cos  7.tan\n");
        printf("8.log10  9.ln  10.sqrt  11.cbrt  12.Sum N numbers\n");
        choice = read_int("Choose (1-12): ");
        if (choice >= 1 && choice <= 12) break;
        printf("Invalid choice. Try again.\n");
    }

    if (choice == 1) {
        double r = calcNum1 + calcNum2;
        printf("Result: %.6g\n", r);
    }
    if (choice == 2) {
        double r = calcNum1 - calcNum2;
        printf("Result: %.6g\n", r);
    }
    if (choice == 3) {
        double r = calcNum1 * calcNum2;
        printf("Result: %.6g\n", r);
    }
    if (choice == 4) {
        if (calcNum2 == 0.0) { printf("Error: division by zero\n"); return; }
        double r = calcNum1 / calcNum2;
        printf("Result: %.6g\n", r);
	}
    if (choice == 5) { printf("sin(%.6g deg) = %.6g\n", calcNum1, sin(calcNum1 * M_PI / 180.0)); return; }
    if (choice == 6) { printf("cos(%.6g deg) = %.6g\n", calcNum1, cos(calcNum1 * M_PI / 180.0)); return; }
    if (choice == 7) { printf("tan(%.6g deg) = %.6g\n", calcNum1, tan(calcNum1 * M_PI / 180.0)); return; }
    if (choice == 8) { if (calcNum1 > 0.0) printf("log10(%.6g) = %.6g\n", calcNum1, log10(calcNum1)); else printf("Invalid input for log10\n"); return; }
    if (choice == 9) { if (calcNum1 > 0.0) printf("ln(%.6g) = %.6g\n", calcNum1, log(calcNum1)); else printf("Invalid input for ln\n"); return; }
    if (choice == 10) { if (calcNum1 >= 0.0) printf("sqrt(%.6g) = %.6g\n", calcNum1, sqrt(calcNum1)); else printf("Invalid input for sqrt\n"); return; }
    if (choice == 11) { printf("cbrt(%.6g) = %.6g\n", calcNum1, cbrt(calcNum1)); return; }

    if (choice == 12) {
        printf("Enter numbers one by one (enter 0 to stop and compute sum):\n");
        double sum = 0.0;
        for (int i = 1;; ++i) {
            double v = read_double("Number: ");
            if (v == 0.0) break;
            sum += v;
        }
        printf("Sum = %.6g\n", sum);
        return;}
}

 //  Calculator: WHILE loop + IF-ELSE ladder
void basicCalculator_WhileLoop_IfElse() {
    printf("\nCALCULATOR using WHILE loop and  IF-ELSE ladder\n");
    printf("Choose number source:\n1) Auto-generate from student number\n2) Enter numbers manually\n");
    int src = read_int("Choice (1 or 2): ");
    if (src == 1) {
        if (studentNumber == 0) {
            studentNumber = read_ll("Student number not set. Enter Student Number to generate numbers: ");
        }
        generate_calculator_numbers_from_student_number(studentNumber, &calcNum1, &calcNum2);
        printf("Using generated numbers: %.2f and %.2f\n", calcNum1, calcNum2);
    } else {
        calcNum1 = read_double("Enter first number: ");
        calcNum2 = read_double("Enter second number: ");}

    int choice = 0, valid = 0;
    while (!valid) {
        printf("\nMENU (angles in degrees):\n");
        printf("1.+  2.-  3.*  4./  5.sin  6.cos  7.tan\n");
        printf("8.log10  9.ln  10.sqrt  11.cbrt  12.Sum N numbers\n");
        choice = read_int("Choose (1-12): ");
        if (choice >= 1 && choice <= 12) valid = 1;
        else printf("Invalid choice. Try again.\n");}

    if (choice == 1) {
        double r = calcNum1 + calcNum2;
        printf("Result: %.6g\n", r);
    } else if (choice == 2) {
        double r = calcNum1 - calcNum2;
        printf("Result: %.6g\n", r);
    } else if (choice == 3) {
        double r = calcNum1 * calcNum2;
        printf("Result: %.6g\n", r);
    } else if (choice == 4) {
        if (calcNum2 == 0.0) { printf("Error: division by zero\n"); return; }
        double r = calcNum1 / calcNum2;
        printf("Result: %.6g\n", r);
    } else if (choice == 5) {
        printf("sin(%.6g deg) = %.6g\n", calcNum1, sin(calcNum1 * M_PI / 180.0));
    } else if (choice == 6) {
        printf("cos(%.6g deg) = %.6g\n", calcNum1, cos(calcNum1 * M_PI / 180.0));
    } else if (choice == 7) {
        printf("tan(%.6g deg) = %.6g\n", calcNum1, tan(calcNum1 * M_PI / 180.0));
    } else if (choice == 8) {
        if (calcNum1 > 0.0) printf("log10(%.6g) = %.6g\n", calcNum1, log10(calcNum1));
        else printf("Invalid input for log10\n");
    } else if (choice == 9) {
        if (calcNum1 > 0.0) printf("ln(%.6g) = %.6g\n", calcNum1, log(calcNum1));
        else printf("Invalid input for ln\n");
    } else if (choice == 10) {
        if (calcNum1 >= 0.0) printf("sqrt(%.6g) = %.6g\n", calcNum1, sqrt(calcNum1));
        else printf("Invalid input for sqrt\n");
    } else if (choice == 11) {
        printf("cbrt(%.6g) = %.6g\n", calcNum1, cbrt(calcNum1));
    } else if (choice == 12) {
        printf("Enter numbers one by one (enter 0 to stop and compute sum):\n");
        double sum = 0.0;
        while (1) {
            double v = read_double("Number: ");
            if (v == 0.0) break;
            sum += v;
        }
        printf("Sum = %.6g\n", sum);}
}

  // Main menu
int main(void) {
    int choice = -1;
    printf("\nDear Mr. Lwomwa Joseph ; kindly receive our group work ,thank you for your time and mentorship\n");
    printf("\n======================================\n");
    printf("  MAKERERE UNIVERSITY \n");
    printf("  COURSEWORK 1         BIST\n");
    printf("======================================\n");
	printf("Group menbers \n BALIKOOWA SULAIMAN : 25/U/03705/PS \n KIYOMBO ALVIN : 25/U/03831/PSA \n BALUKA LETICIA CONSTANCE : 25/U/03707/PS \n KINYIRI HUZAIRU : 25/U/03815/PS");
    printf("\n======================================\n");

    for (;;) {
        printf("\nMAIN MENU\n");
        printf("1. CGPA (FOR loop + IF-only)\n");
        printf("2. CGPA (WHILE loop + IF-ELSE ladder)\n");
        printf("3. Calculator (FOR loop + IF-only)\n");
        printf("4. Calculator (WHILE loop + IF-ELSE ladder)\n");
        printf("0. Exit\n");
        choice = read_int("Choose: ");
        if (choice == 0) break;

        switch (choice) {
            case 1: calculateCGPA_ForLoop_If(); break;
            case 2: calculateCGPA_WhileLoop_IfElse(); break;
            case 3: basicCalculator_ForLoop_If(); break;
            case 4: basicCalculator_WhileLoop_IfElse(); break;
            default: printf("Invalid menu option.\n"); break;}
    }
	printf("\nDone ; thankyou\n");
    return 0;
}
