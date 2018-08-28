#include <linklist.h>

/* To generate an empty student node */
Student* new_student()
{
	Student* student = (Student*)malloc(sizeof(Student));
	if(!student)
	{
		printf("Error in \"LinkNode* linklist_node_creat()\",\n");
		printf("Failed to allocate memory!\n");
		exit(-1);
	}

	student->gender = male;
	student->grade_Math = 0;
	student->grade_English = 0;
	student->link = NULL;

	return student;
}

/* To clear a student node */
void clear_student(Student* student)
{
	if(!student)
	{
		return;
	}
	student->gender = male;
	student->grade_Math = 0;
	student->grade_English = 0;
	student->link = NULL;
}

LinkNode* linklist_node_creat()
{
	return new_student();
}

void linklist_node_delete(LinkNode* p)
{
	clear_student(p);
}

unsigned long long get_time()
{
    __asm("RDTSC");
}

float Rand(float a, float b)
{
	srand((unsigned)get_time()); 
	return (b-a) * rand() / RAND_MAX + a;
}

float intRand(int a, int b)
{
	return floor( Rand(a, b+1) );
}

char* strRand(int begin, int end, int n)
{
	char* str = (char*)malloc((n+1)*sizeof(char));
	for(int i = 0; i < n; i++)
	{
		str[i] = (char)intRand(begin, end);
	}

	return str;
}

/* To generate a random student node */
LinkNode* rand_student()
{
	LinkNode* student = (LinkNode*)malloc(sizeof(LinkNode));
	if(!student)
	{
		printf("Error in \"LinkNode* rand_student()\",\n");
		printf("Failed to allicate memory!\n");
		exit(-1);
	}

	strcpy(student->name, strRand('a', 'z', 10));
	student->gender = intRand(0, 1);
	strcpy(student->ID, strRand('0', '9', 9));
	strcpy(student->QQ, strRand('0', '9', 10));
	student->grade_Math = Rand(0, 100);
	student->grade_English = Rand(0, 100);
	student->link = NULL;

	return student;
}
