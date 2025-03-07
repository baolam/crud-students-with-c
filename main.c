#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_SCHOOL_LENGTH 100
#define MAX_LENGTH_LINE 200

typedef struct {
	char name[MAX_NAME_LENGTH];
	int age;
	char school[MAX_SCHOOL_LENGTH];
} Student;

/// CRUD
// Create Read Update Delete
void extractInfor(char name[50], int *age, char school[100], char tempInfor[MAX_LENGTH_LINE]) {
	char *token;
	token = strtok(tempInfor, "|");
	
	// Lấy dữ liệu về name
	strcpy(name, token);
	
	// Lấy dữ liệu về 
	token = strtok(NULL, "|");
	*age = atoi(token);
	
	// Lấy dữ liệu về trường
	token = strtok(NULL, "| ");
	strcpy(school, token);
}

void readFile(Student **students, int *size) {
	FILE *f;
	
	f = fopen("students.txt", "r");
	if (f == NULL) {
		*size = 0;
		printf("No file found!");
		printf("\n");
		return;
	}
	
	char tempInfor[MAX_LENGTH_LINE];
	int tempSize = 0;
	
	while (fgets(tempInfor, sizeof(tempInfor), f)) {
		// Tiến hành cấp phát bộ nhớ cho Struct Student
		Student *tempStudents = (Student*) calloc(tempSize + 1, sizeof(Student));
		if (tempStudents == NULL) {
			printf("Error on allocating memory for student!");
			*size = 0;
			fclose(f);
			return;
		}
		
		*students = tempStudents;
		
		/// Tiến hành gán dữ liệu
		extractInfor((*students)[tempSize].name, &(*students)[tempSize].age, (*students)[tempSize].school, tempInfor);
		tempSize++;
	}	
		
	*size = tempSize;
	
	fclose(f);
}

void showStudent(Student **lst, int size) {
	Student *studentList = *lst;
	while(size--) {
		printf("Name : %s, Age: %d, School: %s", studentList->name, studentList->age, studentList->school);
		studentList++;
	}
	printf("\n");
}

void printMenu() {
	printf("-------------------------------------------\n");
	printf("1. Print student list \n");
	printf("2. Update student infor \n");
	printf("3. Delete a student \n");
	printf("4. Exit \n");
	printf("-------------------------------------------\n");
}

int main(int argc, char *argv[]) {
	int size = 0;
	Student *students;
	
	/// Nạp dữ liệu vào mảng để quản lí
	printf("Readind student's file!\n");
	readFile(&students, &size);
	printf("Reading finished successfully!\n");
	
	int menu;
	
	do {
		printMenu();
		scanf("%d", &menu);
		
		switch (menu) {
			case 1:
				showStudent(&students, size);
				break;
		}
	} while (menu != 4);
		
	free(students);
	return 0;
}
