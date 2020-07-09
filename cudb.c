#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 5

typedef struct
{
    char name[NAME_SIZE];
    int data;
} student_t;

//funtion called new student that returns a pointer to the struct student_t
// it has 4 arguments
student_t *newStudent(char *name, int year, int semester, int grade)
{
    student_t *myStudent = malloc(sizeof(student_t)); // declaring a varible called myStudent of type pointer to student_t. It makes space in memory for a student_t
    memcpy(myStudent->name, name, NAME_SIZE); //copying memory(source, destination to put it, size)
    int yearToEncode = year - 2009;
    int semesterShifted = semester << 5;//shifted with 5
    int gradeShifted = grade << 6;

    myStudent->data = yearToEncode + semesterShifted + gradeShifted; //put it all in the data box

    return myStudent;
}

int getYear(student_t *student_p)
{
    int yearMask = 0x0000001F; // last byte is 0001 1111 -> hex number, 8 digits with 4 bits each -> 32 bits
    int yearExtracted = student_p->data & yearMask; //& operation
    int yearDecoded = yearExtracted + 2009;
    return yearDecoded;
}

int getSemester(student_t *student_p)
{
    int semesterMask = 0x00000020; // last byte is 0010 0000
    int semesterExtracted = student_p->data & semesterMask;
    int semesterDecoded = semesterExtracted >> 5;
    return semesterDecoded;
}

int getGrade(student_t *student_p)
{
    int gradeMask = 0x00007FC0; // last 2 bytes are: 0111 1111, 1100 0000
    int gradeExtracted = student_p->data & gradeMask;
    int gradeDecoded = gradeExtracted >> 6;
    return gradeDecoded;
}

void listStudents(student_t *students[], int arraySize)//array of pointers to students and the size of the array
{
    int i;
    int gpaSoFar = 0;
    int nrOfStudents = 0;
    int totalGpa;
    for (i = 0; i < arraySize; i++)
    {
        int year = getYear(students[i]);
        int grade = getGrade(students[i]);
        int semester = getSemester(students[i]);
        printf("s%04d ", i);
        printf("%s ", students[i]->name);
        printf("%d ", year);
        if (semester == 0)
        {
            printf("Autumn ");
        }
        else if (semester == 1)
        {
            printf("Spring ");
        }
        printf("%d \n", grade);
        gpaSoFar = gpaSoFar + grade;
        nrOfStudents = nrOfStudents + 1;
    }
    totalGpa = gpaSoFar / nrOfStudents;
    printf("Average GPA = %d\n", totalGpa);
}

student_t *addNewStudent()
{
    char name[NAME_SIZE];
    int year;
    int semester;
    int gpa;
    printf("Enter name (4 characters only) \n");
    scanf("%s", &name);
    printf("Enter start year (2009-2040) \n");
    scanf("%d", &year);
    printf("Enter start semester (0=Autumn/1=Spring) \n");
    scanf("%d", &semester);
    printf("Enter GPA (0-255)\n");
    scanf("%d", &gpa);

    student_t *myStudent = newStudent(name, year, semester, gpa);
    return myStudent;
}

int main()
{
    printf("Welcome to CUDB - The C University Data Base\n\n");
    printf("0: Halt\n1: List all students\n2: Add a new student\n\n");

    //creating an array of students with space 10.000
    student_t *students[10000];
    int size_students_array = 0;
    int action;

    //infinit loop. anything that is not 0 means true.
    while (1)
    {
        printf("Enter action:\n");
        scanf("%d", &action);

        if (action == 0)
        {
            printf("Bye");
            exit(0);
        }
        else if (action == 1)
        {
            listStudents(students, size_students_array);
        }
        else if (action == 2)
        {
            student_t *student = addNewStudent();
            students[size_students_array] = student;
            size_students_array++;
        }
        else
        {
            printf("value not valid, try again\n");
        }
    }

    return 0;
}
