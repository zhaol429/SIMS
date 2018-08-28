#include <string.h>
#include <time.h>
#include <sys/unistd.h>
#include <math.h>

// Define a new type Gender store just male and female
typedef enum Gender
{
	male = 0,
	female = 1
}Gender;

// Creat a struct to store student information
typedef struct Student
{
	char name[20];
	Gender gender;
	char ID[16];
	char QQ[15];
	float grade_Math;
	float grade_English;
	struct Student* link;
}Student;

// To define the linked list node as type Student
typedef Student LinkNode;

// To generate a empty student node
Student* new_student();

// To generate a random student node
Student* rand_student();

// To clear a student node
void clear_student(Student* student);
