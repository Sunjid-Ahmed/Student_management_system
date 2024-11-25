#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define INF 9999

typedef struct {
    char name[50];
    int score;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function to add a student
void addStudent(char *name, int score) {
    if (studentCount < MAX_STUDENTS) {
        strcpy(students[studentCount].name, name);
        students[studentCount].score = score;
        studentCount++;
    } else {
        printf("Student list is full!\n");
    }
}

// Function to search for a student by name
int searchStudent(char *name) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to sort students by score using Bubble Sort
void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].score < students[j + 1].score) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Graph representation
int graph[MAX_STUDENTS][MAX_STUDENTS];

// Function to initialize the graph
void initializeGraph() {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        for (int j = 0; j < MAX_STUDENTS; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }
}

// Function to add a relationship between two students
void addRelationship(int student1, int student2, int distance) {
    graph[student1][student2] = distance;
    graph[student2][student1] = distance; // Assuming undirected graph
}

// Function to find the shortest path using Floyd-Warshall algorithm
void floydWarshall() {
    for (int k = 0; k < studentCount; k++) {
        for (int i = 0; i < studentCount; i++) {
            for (int j = 0; j < studentCount; j++) {
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

// Function to print the shortest path
void printShortestPath(int start, int end) {
    if (graph[start][end] == INF) {
        printf("No path exists between %s and %s.\n", students[start].name, students[end].name);
    } else {
        printf("Shortest path between %s and %s is %d.\n", students[start].name, students[end].name, graph[start][end]);
    }
}

int main() {
    int choice;
    char name[50];
    int score;

    // Initialize the graph
    initializeGraph();

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Sort Students\n");
       // printf("4. Add Relationship\n");
        printf("5. Find Shortest Path\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter score: ");
                scanf("%d", &score);
                addStudent(name, score);
                break;
            case 2:
                printf("Enter name to search: ");
                scanf("%s", name);
                int index = searchStudent(name);
                if (index != -1) {
                    printf("Student found: %s, Score: %d\n", students[index]. name, students[index].score);
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 3:
                sortStudents();
                printf("Students sorted by score.\n");
                break;
            case 4: {
                int student1, student2, distance;
                printf("Enter the index of the first student: ");
                scanf("%d", &student1);
                printf("Enter the index of the second student: ");
                scanf("%d", &student2);
                printf("Enter the distance between them: ");
                scanf("%d", &distance);
                addRelationship(student1, student2, distance);
                break;
            }
            case 5: {
                int start, end;
                printf("Enter the index of the start student: ");
                scanf("%d", &start);
                printf("Enter the index of the end student: ");
                scanf("%d", &end);
                floydWarshall();
                printShortestPath(start, end);
                break;
            }
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
