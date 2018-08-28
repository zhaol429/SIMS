#include <linklist.h>

// To print out all student information a student list
void studentlist_print(LinkList student_list);

// To modify a student node in a studentlist
void studentlist_modify(LinkList student_list, int n, int index, void* ptr_data);

// Write current student list to file(cover the file)
void studentlist_write(LinkList student_list, char* filename);

// Appened current student list to file(append in the end of the file)
void studentlist_append(LinkList student_list, char* fullname);

// To load a LinkList from a file
LinkList studentlist_read(char* filename);

// To sort a student list by different field
void studentlist_sort(LinkList student_list, int index);

// To guide user to input student information into a student list
LinkList studentlist_input(void);

// To search student id from a student list
Student* studentlist_search_id(LinkList student_list, char* id);

// To print out a student node
void student_node_print(Student* student);

// To print the head information before printing student information
void head_information(void);

// clear the buffer for scanf
void input_clear(void);

// To turn all upper case letter into lower case letter
void lower(char* str);

void stop(void);
void clc(void);