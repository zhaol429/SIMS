#include <menu.h>

// Print the main menu
void main_menu(void)
{
	system("clear");
	printf("(1) Create a new file to store students' information;\n");
	printf("(2) Print all students' information;\n");
	printf("(3) Print specific students' information;\n");
	printf("(4) Add new student information to existing file;\n");
	printf("(5) Delete existing student information from existing file;\n");
	printf("(6) Modify existing student information;\n");
	printf("(7) Remove file;\n");
	printf("(8) Exit.\n\n");

	printf("Please choose an operation from the list: ");
	int choice = 0;
	while(choice <= 0 || choice >= 9)
	{
		scanf("%d", &choice);
		input_clear();
		switch(choice)
		{
			case 1: creat_new_file(); break;
			case 2: print_all(); break; 
			case 3:	print_specific(); break;
			case 4:	add_new_student(); break;
			case 5: delete_student(); break;
			case 6: modify_student(); break;
			case 7: remove_file(); break;
			case 8: exit(-1);
			default: printf("\nThe number you choose is not in the list.\nPlease input again: ");
		}
	}
}

// To judge if a file exists or not.
bool exist(char* filename)
{
	char fullname[50] = "Students_Information/";
	strcat(fullname, filename);
	FILE* fp = fopen(fullname, "r");
	bool flag_exist = (bool)fp;
	if(flag_exist)
	{
		fclose(fp);
	}

	return flag_exist;
}

// To print out all files in the directory "Students_Information/"
void ls(char* directory)
{
	printf("\n");
	#ifdef __linux__
		DIR *dirp; 
	    struct dirent *dp;
	    dirp = opendir(directory);

	    while((dp = readdir(dirp)) != NULL)
	    {
	    	if( strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..") )
	    	{
	        	printf("%s\n", dp->d_name);
	    	}
	    }

	    closedir(dirp);
	#else
	    struct _finddata_t data;
	    long hnd = _findfirst(directory, &data);
	    if( hnd < 0 )
	    {
	        perror( path );
	    }

	    int nRet = (hnd < 0) ? -1 : 1;
	    while( nRet >= 0 )
	    {
			printf("%s\n", data.name);
			nRet = _findnext( hnd, &data );
	    }

	    _findclose( hnd );
	#endif
	printf("\n");
}

// To guide user to input file.
char* choose_file(void)
{
	printf("Now we have following files storing the students' information:\n");
	ls("Students_Information");

	printf("Please choose a file that you want to open: ");
	char* filename = (char*)malloc(20 * sizeof(char));
	scanf("%s", filename);
	while(!exist(filename))
	{
		printf("The file you choose is not in the list!\nPlease choose again: ");
		scanf("%s", filename);
	}
	char* fullname = (char*)malloc(50 * sizeof(char));
	strcpy(fullname, "Students_Information/");
	strcat(fullname, filename);

	return fullname;
}

// To guide user to creat a new file
void creat_new_file(void)
{
	system("clear");

	printf("Now we have following files storing the students' information:\n");
	ls("Students_Information");

	printf("Please creat a name for the new file: ");
	char filename[20];
	scanf("%s", filename);
	while(exist(filename))
	{
		printf("\nThe name you choose is already exist!\n");
		printf("please creat another filename: ");
		scanf("%s", filename);
	}
	system("clear");
	printf("Now please input students' information:\n");
	LinkList student_list = studentlist_input();

	char fullname[50] = "Students_Information/";
	strcat(fullname, filename);

	studentlist_write(student_list, fullname);
	linklist_clear(student_list);

	stop();
}

// To guide user to add a new student information
void add_new_student(void)
{
	system("clear");

	char* fullname = choose_file();

	printf("Now please input students' information:\n");
	LinkList student_list = studentlist_input();

	studentlist_append(student_list, fullname);

	linklist_clear(student_list);

	stop();
}

// To print out all student's information a file.
// You can choose to print by different order.
void print_all(void)
{
	system("clear");
	char* fullname = choose_file();
	system("clear");
	printf("There are 6 order type for printing:\n\n");

	printf("(1) Sort by name\n");
	printf("(2) Sort by gender\n");
	printf("(3) Sort by ID number\n");
	printf("(4) Sort by QQ number\n");
	printf("(5) Sort by Math grade\n");
	printf("(6) Sort by English grade\n\n");

	printf("Please choose an order type for printing: ");
	int order_type = 0;

	LinkList student_list = studentlist_read(fullname);
	while(order_type <= 0 || order_type >= 7)
	{
		input_clear();
		scanf("%d", &order_type);
		if(order_type >= 1 && order_type <= 6)
		{
			studentlist_sort(student_list, order_type-1);
			break;
		}
		else
		{
			printf("The order type is not in the list, please choose again: ");
		}
	}
	system("clear");
	studentlist_print(student_list);
	linklist_clear(student_list);

	stop();
}

// To print out the student information whose ID number is just like you input
void print_specific(void)
{
	clc();
	char* fullname = choose_file();

	LinkList student_list = studentlist_read(fullname);

	printf("\nWhich student's information do you want to print out?\n");
	printf("Please input his or her ID number: ");
	char id_number[20];
	input:
	scanf("%s", id_number);

	Student* student = studentlist_search_id(student_list, id_number);
	if(!student)
	{
		printf("\nThe ID number you input is not exist!");
		printf("Please input again: ");
		goto input;
		return;
	}

	clc();
	printf("His information is as follow:\n\n");

	head_information();
	student_node_print(student);
	printf("\n");
	linklist_clear(student_list);

	stop();
}

// To guide user to delete a student in a file
void delete_student(void)
{
	clc();
	char* fullname = choose_file();
	LinkList student_list = studentlist_read(fullname);
	clc();
	printf("All students' information is as follow:\n\n");
	studentlist_print(student_list);

	printf("Which student's information do you want to delete?\n");
	printf("Please input his or her ID number: ");
	char id_number[20];
	scanf("%s", id_number);

	Student* student = studentlist_search_id(student_list, id_number);
	if(!student)
	{
		printf("\nThe ID number you input is not exist!\n");
		return;
	}
	printf("\nHis information is as follow:\n\n");

	head_information();
	student_node_print(student);

	printf("\nDo you realy want to delete his information?(Y/N) ");
	char choice[2];
	scanf("%s", choice);
	if(!strcmp(choice, "Y"))
	{
		linklist_erase(student_list, student);
		studentlist_write(student_list, fullname);
		printf("\nDelete successful!\n\n");
	}
	else
	{
		printf("You give up deleting his information!\n");
		return;
	}

	linklist_clear(student_list);

	stop();
}

// To modify student's information in a file
void modify_student(void)
{
	clc();
	char* fullname = choose_file();
	LinkList student_list = studentlist_read(fullname);
	clc();
	printf("All students' information is as follow:\n\n");
	studentlist_print(student_list);

	printf("Which student's information do you want to modify?\n");
	printf("Please input his or her ID number: ");
	char id_number[20];

	input:
	scanf("%s", id_number);

	Student* student = studentlist_search_id(student_list, id_number);
	if(!student)
	{
		printf("\nThe ID number you input is not exist!\n");
		printf("Please input again: ");
		goto input;
	}

	clc();
	printf("His information is as follow:\n\n");

	head_information();
	student_node_print(student);

	printf("\nHe/Her has 6 information:\n");
	printf("(1) Name\n");
	printf("(2) Gender\n");
	printf("(3) ID number\n");
	printf("(4) QQ number\n");
	printf("(5) Math Grade\n");
	printf("(6) English Grade\n");
	printf("(7) Change all information of him/her\n");

	printf("\nWhich information do you want to modify? ");
	int index = 0;
	while(index < 1 || index > 7)
	{
		scanf("%d", &index);
		switch(index)
		{
			case 1: // name
			{
				printf("\nPlease input his/her new name:\nName: ");
				scanf("%s", student->name);
				break;
			}

			case 2: // Gender
			{
				printf("\nPlease input his/her new gender: ");

				char str_gender[10] = "nogender";
				while( strcmp(str_gender, "male") && strcmp(str_gender, "female") &&
					strcmp(str_gender, "man") && strcmp(str_gender, "woman") &&
					strcmp(str_gender, "boy") && strcmp(str_gender, "girl") )
				{
					printf("Gender: ");
					input_clear();
					scanf("%s", str_gender);
					lower(str_gender);
					if(!strcmp(str_gender, "male") || !strcmp(str_gender, "man") || !strcmp(str_gender, "boy"))
					{
						student->gender = male;
						break;
					}
					else if(!strcmp(str_gender, "female") || !strcmp(str_gender, "woman") || !strcmp(str_gender, "girl"))
					{
						student->gender = female;
						break;
					}
					else
					{
						printf("\nThe gender you input is illegal!\n");
						printf("You can only input \"male\", \"female\", \"man\", \"woman\", \"boy\" or \"girl\"!\n");
						printf("Please input again!\n\n");
					}
				}
				break;
			}

			case 3: // ID
			{
				printf("\nPlease input his new ID number:\nID: ");
				scanf("%s", student->ID);
				break;
			}

			case 4: // QQ
			{
				printf("\nPlease input his new QQ number:\nQQ: ");
				scanf("%s", student->QQ);
				break;
			}

			case 5: // Math Grade
			{
				printf("\nPlease input his new Math Grade:\nMath Grade: ");
				scanf("%f", &student->grade_Math);
				break;
			}

			case 6: // English Grade
			{
				printf("\nPlease input his new English Grade:\nEnglish Grade: ");
				scanf("%f", &student->grade_English);
				break;
			}

			case 7: // All
			{
				printf("\nPlease input all information of him/her:\n\n");
				printf("Name: ");
				scanf("%s", student->name);

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
						break;
					}
					lower(str_gender);
					if(!strcmp(str_gender, "male") || !strcmp(str_gender, "man") || !strcmp(str_gender, "boy"))
					{
						student->gender = male;
						break;
					}
					else if(!strcmp(str_gender, "female") || !strcmp(str_gender, "woman") || !strcmp(str_gender, "girl"))
					{
						student->gender = female;
						break;
					}
					else
					{
						printf("\nThe gender you input is illegal!\n");
						printf("You can only input \"male\", \"female\", \"man\", \"woman\", \"boy\" or \"girl\"!\n");
						printf("Please input again!\n\n");
					}
				}

				printf("ID: ");
				input_clear();
				scanf("%s", student->ID);

				printf("QQ: ");
				input_clear();
				scanf("%s", student->QQ);

				printf("Math Grade: ");
				input_clear();
				scanf("%f", &student->grade_Math);

				printf("English Grade: ");
				input_clear();
				scanf("%f", &student->grade_English);
				break;
			}

			default:
			{
				printf("\nThe field that you want to modify is not in the list!\n");
				printf("Please choose again: ");
				break;
			}
		}
		printf("I am here!\n");
	}
	clc();
	printf("Modify successful!\n");
	printf("\nAfter modified, his/her information changed into:\n\n");
	head_information();
	student_node_print(student);
	studentlist_write(student_list, fullname);

	linklist_clear(student_list);
	printf("\n");
	stop();
}

// To guide user to remove a file
void remove_file(void)
{
	clc();

	char* filename = choose_file();
	remove(filename);
	clc();
	printf("\nDelete successful!\n");
	printf("\nNow we have only following files:\n");
	ls("Students_Information");

	stop();
}
