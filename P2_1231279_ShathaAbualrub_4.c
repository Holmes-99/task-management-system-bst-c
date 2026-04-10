#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TNode {
    int id;
    char name[100];
    char date[20];
    float duration;
    int performed;
    struct TNode* Left;
    struct TNode* Right;
};

typedef struct TNode* Task;

Task Root = NULL;
Task all[200];
int count = 0;

Task createTask(int id, char name[], char date[], float duration) {
    Task newTask = malloc(sizeof(struct TNode));
    newTask->id = id;
    strcpy(newTask->name, name);
    strcpy(newTask->date, date);
    newTask->duration = duration;
    newTask->performed = 0;
    newTask->Left = newTask->Right = NULL;
    return newTask;
}

Task FindMin(Task T) {
    if (T == NULL) return NULL;
    if (T->Left == NULL) return T;
    return FindMin(T->Left);
}

Task AddANewTask(Task root, Task newTask) {
    if (root == NULL) return newTask;
    if (newTask->id < root->id)
        root->Left = AddANewTask(root->Left, newTask);
    else if (newTask->id > root->id)
        root->Right = AddANewTask(root->Right, newTask);
    return root;
}

Task DeleteATask(int id, Task T) {
    Task tmp;
    if (T == NULL) return NULL;
    if (id < T->id)
        T->Left = DeleteATask(id, T->Left);
    else if (id > T->id)
        T->Right = DeleteATask(id, T->Right);
    else {
        if (T->Left && T->Right) {
            tmp = FindMin(T->Right);
            T->id = tmp->id;
            strcpy(T->name, tmp->name);
            strcpy(T->date, tmp->date);
            T->duration = tmp->duration;
            T->performed = tmp->performed;
            T->Right = DeleteATask(tmp->id, T->Right);
        } else {
            tmp = T;
            if (T->Left == NULL)
                T = T->Right;
            else
                T = T->Left;
            free(tmp);
        }
    }
    return T;
}

Task searchByName(Task root, char name[]) {
    if (root == NULL) return NULL;
    if (strcasecmp(root->name, name) == 0) return root;
    Task leftSearch = searchByName(root->Left, name);
    if (leftSearch) return leftSearch;
    return searchByName(root->Right, name);
}

void SearchForTask(Task root) {
    char name[100];
    printf("Enter task name: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    Task search = searchByName(root, name);
    if (search)
        printf("%d %s %s %.2f\n", search->id, search->name, search->date, search->duration);
    else
        printf("Task not found.\n");
}

void PerformTask(Task root) {
    int id;
    printf("Enter ID to perform: ");
    scanf("%d", &id);
    while (root) {
        if (id == root->id) {
            root->performed = 1;
            printf("Task performed.\n");
            return;
        }
        root = id < root->id ? root->Left : root->Right;
    }
    printf("Task not found.\n");
}

void gatherUnperformed(Task root, Task result[], int* index, int max) {
    if (!root || *index >= max) return;
    gatherUnperformed(root->Left, result, index, max);
    if (!root->performed) result[(*index)++] = root;
    gatherUnperformed(root->Right, result, index, max);
}

void displayUnperformed(Task root) {
    Task list[150];
    int c = 0;
    gatherUnperformed(root, list, &c, 150);
    if (c == 0) {
        printf("No unperformed tasks.\n");
        return;
    }
    for (int i = 0; i < c - 1; i++)
        for (int j = 0; j < c - i - 1; j++)
            if (strcasecmp(list[j]->name, list[j + 1]->name) > 0) {
                Task t = list[j]; list[j] = list[j + 1]; list[j + 1] = t;
            }
    for (int i = 0; i < c; i++)
        printf("%d %s %s %.2f\n", list[i]->id, list[i]->name, list[i]->date, list[i]->duration);
}

void collectDoneTasks(Task root, Task result[], int* index, int max) {
    if (!root || *index >= max) return;
    collectDoneTasks(root->Left, result, index, max);
    if (root->performed) result[(*index)++] = root;
    collectDoneTasks(root->Right, result, index, max);
}

void VeiwPerformedTasks(Task root) {
    Task list[150];
    int c = 0;
    collectDoneTasks(root, list, &c, 150);
    if (c == 0) {
        printf("No performed tasks.\n");
        return;
    }
    for (int i = 0; i < c - 1; i++)
        for (int j = 0; j < c - i - 1; j++)
            if (list[j]->id > list[j + 1]->id) {
                Task t = list[j]; list[j] = list[j + 1]; list[j + 1] = t;
            }
    for (int i = 0; i < c; i++)
        printf("%d %s %s %.2f\n", list[i]->id, list[i]->name, list[i]->date, list[i]->duration);
}

void collect(Task root) {
    if (root == NULL) return;
    collect(root->Left);
    all[count++] = root;
    collect(root->Right);
}

Task buildTree(int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    Task node = all[mid];
    node->Left = buildTree(start, mid - 1);
    node->Right = buildTree(mid + 1, end);
    return node;
}

void sortByName() {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (strcmp(all[j]->name, all[j + 1]->name) > 0) {
                Task t = all[j]; all[j] = all[j + 1]; all[j + 1] = t;
            }
}

void sortByDate() {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (strcmp(all[j]->date, all[j + 1]->date) > 0) {
                Task t = all[j]; all[j] = all[j + 1]; all[j + 1] = t;
            }
}

void sortByDuration() {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (all[j]->duration > all[j + 1]->duration) {
                Task t = all[j]; all[j] = all[j + 1]; all[j + 1] = t;
            }
}

Task Restructure(Task root) {
    count = 0;
    collect(root);
    if (count == 0) return root;
    int ch;
    printf("Restructure by:\n1. Name\n2. Date\n3. Duration\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1) sortByName();
    else if (ch == 2) sortByDate();
    else if (ch == 3) sortByDuration();
    else {
        printf("Invalid choice.\n");
        return root;
    }
    return buildTree(0, count - 1);
}

int calculateHeight(Task root) {
    if (!root) return -1;
    int l = calculateHeight(root->Left);
    int r = calculateHeight(root->Right);
    return (l > r ? l : r) + 1;
}

int countNodes(Task root) {
    if (!root) return 0;
    return 1 + countNodes(root->Left) + countNodes(root->Right);
}

int countLeaves(Task root) {
    if (!root) return 0;
    if (!root->Left && !root->Right) return 1;
    return countLeaves(root->Left) + countLeaves(root->Right);
}

int countInternals(Task root) {
    if (!root || (!root->Left && !root->Right)) return 0;
    return 1 + countInternals(root->Left) + countInternals(root->Right);
}

void showTreeStats(Task root) {
    printf("Tree Height: %d\n", calculateHeight(root));
    printf("Total Nodes: %d\n", countNodes(root));
    printf("Leaves: %d\n", countLeaves(root));
    printf("Internal Nodes: %d\n", countInternals(root));
}

void Exit(Task root) {
    if (!root) return;
    Exit(root->Left);
    Exit(root->Right);
    free(root);
}

void LoadTasksFile() {
    FILE* file = fopen("tasks.txt", "r");
    if (!file) {
        printf("Could not open tasks.txt\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id;
        char name[100], date[20];
        float duration;

        char* token = strtok(line, "#");
        if (!token) continue;
        id = atoi(token);

        token = strtok(NULL, "#");
        if (!token) continue;
        strcpy(name, token);

        token = strtok(NULL, "#");
        if (!token) continue;
        strcpy(date, token);

        token = strtok(NULL, "#\n");
        if (!token) continue;
        duration = atof(token);

        Task newTask = createTask(id, name, date, duration);
        Root = AddANewTask(Root, newTask);
    }

    fclose(file);
    printf("Tasks loaded successfully.\n");
}


int main() {
    int choice = 0;

    while (choice != 10) {
       printf("\n============== Task Management Menu ==============\n");
printf("1. Load Tasks from File\n");
printf("2. Add a New Task\n");
printf("3. Delete a Task by ID\n");
printf("4. Search for a Task by Name\n");
printf("5. Perform a Task by ID\n");
printf("6. View All Unperformed Tasks (sorted by Name)\n");
printf("7. View All Performed Tasks (sorted by ID)\n");
printf("8. Restructure the BST (by Name / Date / Duration)\n");
printf("9. View BST Information (Height, Size, Leaves, Internal Nodes)\n");
printf("10. Exit the Program\n");
printf("===================================================\n");
printf("Enter your choice: ");

        scanf("%d", &choice);
        switch (choice) {
       case 1: LoadTasksFile();
        break;

            case 2: {
                int id;
                char name[100];
                 char date[20];
                 float d;

                printf("ID: "); scanf("%d", &id);
                getchar();

                printf("Name: "); fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Date: "); scanf("%s", date);
                printf("Duration: "); scanf("%f", &d);

                Root = AddANewTask(Root, createTask(id, name, date, d));
                break;
            }
            case 3: {
                int id; printf("ID to delete: "); scanf("%d", &id);
                Root = DeleteATask(id, Root);
                break;
            }
            case 4: SearchForTask(Root);
             break;

            case 5: PerformTask(Root);
             break;

            case 6: displayUnperformed(Root);
             break;

            case 7: VeiwPerformedTasks(Root);
             break;

            case 8: Root = Restructure(Root);
            break;

            case 9: showTreeStats(Root);
             break;

            case 10: Exit(Root);
             break;

            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
