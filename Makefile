LinkListPath := LinkList
LinkListHead := linklist.h
LinkListSource := linklist.c
LinkListObject := linklist.o

StudentNodePath := StudentNode
StudentNodeHead := student.h
StudentNodeSource := student.c
StudentNodeObject := student.o

StudentListPath := StudentList
StudentListHead := studentlist.h
StudentListSource := studentlist.c
StudentListObject := studentlist.o

MenuPath := Menu
MenuHead := menu.h
MenuSource := menu.c
MenuObject := menu.o

MainPath := .
MainHead := menu.h
MainSource := main.c
MainObject := main.o
MainExe := app

DEPEND := ${LinkListObject} ${StudentNodeObject} ${StudentListObject} ${MenuObject} ${MainObject}
INCLUDE := -I ${LinkListPath} -I ${StudentNodePath} -I ${StudentListPath} -I ${MenuPath}
COMPILE := gcc -std=c99

ifeq ($(shell uname), Linux)
	Build = gcc -std=c99 *.o -o ${MainExe} -lm
else
	Build = gcc -std=c99 *.o -o ${MainExe}
endif

${MainExe}: ${DEPEND}
	${Build}

${MainObject}: ${MainPath}/${MainSource} ${MenuPath}/${MainHead}
	${COMPILE} ${INCLUDE} -c ${MainPath}/${MainSource}

${LinkListObject}: ${LinkListPath}/${LinkListSource} ${LinkListPath}/${LinkListHead}
	${COMPILE} ${INCLUDE} -c ${LinkListPath}/${LinkListSource}

${StudentNodeObject}: ${StudentNodePath}/${StudentNodeSource} ${StudentNodePath}/${StudentNodeHead}
	${COMPILE} ${INCLUDE} -c ${StudentNodePath}/${StudentNodeSource}

${StudentListObject}: ${StudentListPath}/${StudentListSource} ${StudentListPath}/${StudentListHead}
	${COMPILE} ${INCLUDE} -c ${StudentListPath}/${StudentListSource}

${MenuObject}: ${MenuPath}/${MenuSource} ${MenuPath}/${MenuHead}
	${COMPILE} ${INCLUDE} -c ${MenuPath}/${MenuSource}

clean:
	rm *.o
	rm app
