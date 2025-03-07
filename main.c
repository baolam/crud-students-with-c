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
void extractInfor(char name[MAX_NAME_LENGTH], int *age, char school[MAX_SCHOOL_LENGTH], char tempInfor[MAX_LENGTH_LINE]) {
	char *token;
	token = strtok(tempInfor, "|");
	
	// Lấy dữ liệu về name
	strcpy(name, token);
	
	// Lấy dữ liệu về 
	token = strtok(NULL, "|");
	*age = atoi(token);
	
	// Lấy dữ liệu về trường
	token = strtok(NULL, "|");
	strcpy(school, token);
}

int allocateStudentMemory(Student **students, int currentSize) {
	Student *tempStudents = (Student*) realloc(*students, (currentSize + 1) * sizeof(Student));
	if (tempStudents == NULL) {
		printf("Error on allocating memory for student!");
		return 0;
	}
	
	*students = tempStudents;
	return 1;
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
		int code = allocateStudentMemory(students, tempSize);
		if (code == 0) {
			fclose(f);
			*size = 0;
			return;
		}
		
		/// Tiến hành gán dữ liệu
		extractInfor((*students)[tempSize].name, &(*students)[tempSize].age, (*students)[tempSize].school, tempInfor);
		tempSize++;
	}	
		
	*size = tempSize;
	
	fclose(f);
}

void writeFile(Student **students, int size) {
	FILE *f;
	f = fopen("students.txt", "w");
	if (f == NULL) {
		printf("File not found!\n");
		return;
	}
	
	int i;
	for (i = 0; i < size; i++) {
		fprintf(f, "%s|%d|%s\n", (*students)[i].name, (*students)[i].age, (*students)[i].school);
	}
	
	printf("Overwritten successfully!\n");
	fclose(f);
}

// ******************************************************************* //
void showStudent(Student **lst, int size) {
	Student *studentList = *lst;
	while(size--) {
		printf("Name : %s, Age: %d, School: %s\n", studentList->name, studentList->age, studentList->school);
		studentList++;
	}
}

void createANewStudentInfor(Student **students, int *size) {
	char name[MAX_NAME_LENGTH];
	char school[MAX_SCHOOL_LENGTH];
	int age;
	printf("Enter student's name: ");
	scanf("%s", &name);
	printf("Enter student's age: ");
	scanf("%d", &age);
	printf("Enter student's school: ");
	scanf("%s", &school);
	
	int tempSize = *size;
	int code = allocateStudentMemory(students, tempSize);
	if (code == 0) {
		return;
	}
	
	/// Tiến hành ghi nhận dữ liệu
	strcpy((*students)[*size].name, name);
	(*students)[*size].age = age;
	strcpy((*students)[*size].school, school);
	
	/// Cập nhật biến dữ liệu về kích thước
	tempSize++;
	*size = tempSize;
	
	printf("Added a new student to a list successfully!\n");
	printf("Size of student'list: %d\n", *size);
	
	/// Tiến hành bổ sung dữ liệu vào File
	FILE *f;
	f = fopen("students.txt", "a");
	if (f == NULL) {
		printf("File not found! Cannot save infor!");
		return;
	}
	
	fprintf(f, "%s|%d|%s \n", name, age, school);
	fclose(f);
	
	printf("Saved new student to file successfully!\n");
}

int findStudentInfo(Student **students, int size, char name[MAX_NAME_LENGTH]) {
	for (int i = 0; i < size; i++) {
		int code = strcmp((*students)[i].name, name);
		if (code == 0)
			return i;
	}
	return -1;
}

void updateInfo(Student **students, int size) {
	char name[MAX_NAME_LENGTH];
	printf("Enter name to search: \n");
	scanf("%s", &name);
	
	int position = findStudentInfo(students, size, name);
	if (position == -1) {
		printf("Student not found!\n");
		printf("Can not update!\n");
		return;
	}
	
	int age;
	char school[MAX_NAME_LENGTH];
	printf("Overwrite student's age: ");
	scanf("%d", &age);
	printf("Overwrite student's school name: ");
	scanf("%s", &school);
	
	(*students)[position].age = age;
	strcpy((*students)[position].school, school);
	
	writeFile(students, size);
	printf("\n");
}

// ******************************************************************* //

void printMenu() {
	printf("-------------------------------------------\n");
	printf("1. Print student list \n");
	printf("2. Create a student infor \n");
	printf("3. Update a student infor \n");
	printf("4. Delete a student \n");
	printf("5. Overwrite student file \n");
	printf("6. Exit \n");
	printf("-------------------------------------------\n");
}

int main(int argc, char *argv[]) {
	int size = 0;
	Student *students;
	
	/// Nạp dữ liệu vào mảng để quản lí
	printf("Reading student's file!\n");
	readFile(&students, &size);
	printf("Reading finished successfully!\n");
	
	int menu;
	
	do {
		printMenu();
		printf("Choose option: ");
		scanf("%d", &menu);
		
		switch (menu) {
			case 1:
				showStudent(&students, size);
				break;
			case 2:
				createANewStudentInfor(&students, &size);
				break;
			case 3:
				updateInfo(&students, size);
				break;
			case 5:
				writeFile(&students, size);
				break;
		}
	} while (menu != 6);
		
	free(students);
	return 0;
}
