#include <studentlist.h>

void stop(void)
{
	#ifdef __linux__
		system("echo Press any key to continue... && read line");
	#else
		system("pause");
	#endif
}

void clc(void)
{
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif
}

// To print the head information before printing student information
void head_information()
{
	printf("%-17s%-8s%-12s%-15s%-12s%-12s\n\n", "Name", "Gender", "ID", "QQ", "Math Grade", "English Grade");
}

// To print out a student node
void student_node_print(Student* student)
{
	printf("%-17s", student->name);
	switch(student->gender)
	{
		case 0: printf("%-8s", "Male"); break;
		case 1: printf("%-8s", "Female"); break;
	}
	printf("%-12s", student->ID);
	printf("%-15s", student->QQ);
	printf("%-12.1f", student->grade_Math);
	printf("%-12.1f\n", student->grade_English);
}

// To print out all student information a student list
void studentlist_print(LinkList student_list)
{
	head_information();

	LinkNode* p = student_list.head;
	p = p->link;
	while(p)
	{
		student_node_print(p);
		p = p->link;
	}
	printf("\n");
}

// To modify a student node in a studentlist
void studentlist_modify(LinkList student_list, int n, int index, void* ptr_data)
{
	int N = linklist_length(student_list);
	if(n < 0 || n >= N)
	{
		return position_warning(n, N, "void studentlist_modify(LinkList student_list, int n, int index, void* data)");
	}

	LinkNode* student = linklist_getnode(student_list, n);
	switch(index)
	{
		case 0: // name
		{
			strcmp(student->name, (char*)ptr_data);
			break;
		}
		case 1: // gender
		{
			student->gender = *((Gender*)ptr_data);
			break;
		}
		case 2: // ID
		{
			strcmp(student->ID, (char*)ptr_data);
			break;
		}
		case 3: // QQ
		{
			strcmp(student->QQ, (char*)ptr_data);
			break;
		}
		case 4: // grade_Math
		{
			student->grade_Math = *((int*)ptr_data);
			break;
		}
		case 5: // grade_Englist
		{
			student->grade_English = *((float*)ptr_data);
			break;
		}
		case 6: // all information
		{
			*student = *((LinkNode*)ptr_data);
			break;
		}
		default:
		{
			printf("Error in \"void studentlist_modify(LinkList student_list, int n, int index, void* ptr_data)\"\nindex is invalid!\n");
			exit(-1);
		}
	}
}

bool studentnode_isempty(LinkNode* p)
{
	return (!p->name && !p->gender && !p->ID && !p->QQ && !p->grade_Math && !p->grade_English);
}

// Write current student list to file(cover the file)
void studentlist_write(LinkList student_list, char* filename)
{
	if(linklist_empty(student_list))
	{
		return;
	}

	FILE* fptr = fopen(filename, "w");

	LinkNode* p = student_list.head;
	p = p->link;
	while(p)
	{
		if(!studentnode_isempty(p))
		{
			fprintf(fptr, "%s\t%d\t%s\t%s\t%.1f\t%.1f\n", p->name, p->gender, p->ID, p->QQ, p->grade_Math, p->grade_English);
		}

		p = p->link;
	}
	fclose(fptr);
}

// Appened current student list to file(append in the end of the file)
void studentlist_append(LinkList student_list, char* filename)
{
	if(linklist_empty(student_list))
	{
		return;
	}

	FILE* fptr = fopen(filename, "a");

	LinkNode* p = student_list.head->link;
	while(p)
	{
		if(!studentnode_isempty(p))
		{
			fprintf(fptr, "%s\t%d\t%s\t%s\t%.1f\t%.1f\n", p->name, p->gender, p->ID, p->QQ, p->grade_Math, p->grade_English);
		}
		p = p->link;
	}

	fclose(fptr);
}

// To extract a substring from a string
char* substr(char* str_initial, int i_begin, int i_end)
{
	char* str_result = (char*)malloc( (i_end - i_begin + 2) * sizeof(char) );
	for(int i = i_begin; i <= i_end; i++)
	{
		str_result[i-i_begin] = str_initial[i];
	}
	str_result[i_end-i_begin+1] = '\0';

	return str_result;
}

// To load a LinkList from a file
LinkList studentlist_read(char* filename)
{
	LinkList student_list = linklist_creat(0);
	FILE* fptr = fopen(filename, "r"); 
	char line[100];  
	int filesize; 
	if(!fptr)
	{  
		printf("Failed to open file!\n");  
		exit(-1);
	}  

	fseek(fptr, 0, SEEK_END);   

	filesize = ftell(fptr);
	// 不读行
	rewind(fptr);
	while( fgets(line, 100, fptr) )
	{  
		int it_end = 0, it_begin = 0, index = 0;
		char* element;

		Student student;
		while(line[it_end] != '\n')
		{
			if(line[it_end+1] == '\t' || line[it_end+1] == '\n')
			{
				element = substr(line, it_begin, it_end);
				switch(index)
				{
					case 0: strcpy(student.name, element); break;
					case 1: student.gender = atoi(element); break;
					case 2: strcpy(student.ID, element); break;
					case 3: strcpy(student.QQ, element); break;
					case 4: student.grade_Math = atof(element); break;
					case 5: student.grade_English = atof(element); break;
					default: break;
				}
				it_begin = it_end + 2;
				index++;
			}

			it_end++;
		}
		linklist_push_back(student_list, student);
	}
	fclose(fptr);

	return student_list; 
}

// To sort a student list by different field
void studentlist_sort(LinkList student_list, int index)
{
	bool swap_condition = false;

	int n = linklist_length(student_list);
	for(int j = n-2; j >= 0; j--)
	{
		LinkNode* p_before = student_list.head;
		for(int i = 0; i <= j; i++)
		{
			LinkNode* p = p_before->link;
			switch(index)
			{
				case 0: swap_condition = ( strcmp(p->name, p->link->name) > 0 ); break;
				case 1: swap_condition = ( p->gender > p->link->gender ); break;
				case 2: swap_condition = ( strcmp(p->ID, p->link->ID) > 0 ); break;
				case 3: swap_condition = ( strcmp(p->QQ, p->link->QQ) > 0 ); break;
				case 4: swap_condition = ( p->grade_Math < p->link->grade_Math ); break;
				case 5: swap_condition = ( p->grade_English < p->link->grade_English ); break;
				default: printf("Error in studentlist_sort! index is wrong!\n"); return;
			}
			if(swap_condition)
			{
				linklist_node_swap(p_before, p);
			}

			p_before = p_before->link;
		}
	}
}

// To turn all upper case letter into lower case letter
void lower(char* str)
{
	int n = strlen(str);
	int delta = 'A' - 'a';
	for(int i = 0; i < n; i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] -= delta;
		}
	}
}

// clear the buffer for scanf
void input_clear(void)
{
	while('\n' != getchar()){;}
}

// To guide user to input student information into a student list
LinkList studentlist_input(void)
{
	LinkList student_list = linklist_creat(0);
	while(1)
	{
		Student student;
		printf("\n(End inputing with \"Ctrl + D\")\n\n");
		printf("Name: ");
		if(scanf("%s", student.name) == -1)
		{
			printf("\n\nInput end!\n\n");
			break;
		}

		bool flag_break = false;
		char str_gender[10] = "nogender";
		while( strcmp(str_gender, "male") && strcmp(str_gender, "female") &&
			strcmp(str_gender, "man") && strcmp(str_gender, "woman") &&
			strcmp(str_gender, "boy") && strcmp(str_gender, "girl") )
		{
			printf("Gender: ");
			input_clear();
			if(scanf("%s", str_gender) == -1)
			{
				printf("\n\nInput end!\n\n");
				flag_break = true;
				break;
			}
			lower(str_gender);
			if(!strcmp(str_gender, "male") || !strcmp(str_gender, "man") || !strcmp(str_gender, "boy"))
			{
				student.gender = male;
				break;
			}
			else if(!strcmp(str_gender, "female") || !strcmp(str_gender, "woman") || !strcmp(str_gender, "girl"))
			{
				student.gender = female;
				break;
			}
			else
			{
				printf("\nThe gender you input is illegal!\n");
				printf("You can only input \"male\", \"female\", \"man\", \"woman\", \"boy\" or \"girl\"!\n");
				printf("Please input again!\n\n");
			}
		}
		if(flag_break)
		{
			break;
		}

		printf("ID: ");
		input_clear();
		if(scanf("%s", student.ID) == -1)
		{
			printf("\n\nInput end!\n\n");
			break;
		}

		printf("QQ: ");
		input_clear();
		if(scanf("%s", student.QQ) == -1)
		{
			printf("\n\nInput end!\n\n");
			break;
		}

		printf("Math Grade: ");
		input_clear();
		if(scanf("%f", &student.grade_Math) == -1)
		{
			printf("\n\nInput end!\n\n");
			break;
		}

		printf("English Grade: ");
		input_clear();
		if(scanf("%f", &student.grade_English) == -1)
		{
			printf("\n\nInput end!\n\n");
			break;
		}

		linklist_push_back(student_list, student);
	}
	clc();
	printf("All information you have input is as follow:\n\n");
	studentlist_print(student_list);

	return student_list;
}

// To search student id from a student list
Student* studentlist_search_id(LinkList student_list, char* id)
{
	Student* student = student_list.head->link;
	while(student)
	{
		if(!strcmp(student->ID, id))
		{
			break;
		}
		student = student->link;
	}

	return student;
}