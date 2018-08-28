#include <studentlist.h>

#ifdef __linux__
	#include <dirent.h>
#else
	#include <io.h>
#endif

// Print the main menu
void main_menu(void);

// To guide user to creat a new file
void creat_new_file(void);

// To print out all student's information a file.
// You can choose to print by different order.
void print_all(void);

// To print out the student information whose ID number is just like you input
void print_specific(void);

// To guide user to add a new student information
void add_new_student(void);

// To guide user to delete a student in a file
void delete_student(void);

// To modify student's information in a file
void modify_student(void);

// To guide user to remove a file
void remove_file(void);