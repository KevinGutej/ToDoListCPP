#include <iostream>
#include <fstream>

using namespace std;

struct Task {
    char description[100];
    char priority[10];
    char deadline[15];
    bool completed;
};

Task tasks[100];
int taskCount = 0;

void customStrCopy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int customStrLen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

bool customStrCmp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

void saveTasks() {
    ofstream file("tasks.txt");
    for (int i = 0; i < taskCount; i++) {
        file << tasks[i].description << "|" << tasks[i].priority << "|" << tasks[i].deadline << "|" << (tasks[i].completed ? "1" : "0") << "\n";
    }
    file.close();
}

void loadTasks() {
    ifstream file("tasks.txt");
    if (!file) return;
    while (file.getline(tasks[taskCount].description, 100, '|')) {
        file.getline(tasks[taskCount].priority, 10, '|');
        file.getline(tasks[taskCount].deadline, 15, '|');
        char completedStr[2];
        file.getline(completedStr, 2);
        tasks[taskCount].completed = (completedStr[0] == '1');
        taskCount++;
    }
    file.close();
}

void showTasks() {
    if (taskCount == 0) {
        cout << "No tasks in the list!\n";
        return;
    }
    cout << "\nYour Tasks:\n";
    cout << "No.  Description                    Priority  Deadline     Status\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < taskCount; i++) {
        cout << (i + 1) << ". " << tasks[i].description;
        for (int j = customStrLen(tasks[i].description); j < 30; j++) cout << " ";
        cout << tasks[i].priority;
        for (int j = customStrLen(tasks[i].priority); j < 10; j++) cout << " ";
        cout << tasks[i].deadline;
        for (int j = customStrLen(tasks[i].deadline); j < 15; j++) cout << " ";
        cout << (tasks[i].completed ? "Completed" : "Pending") << endl;
    }
}

void addTask() {
    if (taskCount >= 100) {
        cout << "Task list is full!\n";
        return;
    }
    cout << "Enter task description: ";
    cin.ignore();
    cin.getline(tasks[taskCount].description, 100);
    cout << "Enter priority (Low, Medium, High): ";
    cin.getline(tasks[taskCount].priority, 10);
    cout << "Enter deadline (YYYY-MM-DD): ";
    cin.getline(tasks[taskCount].deadline, 15);
    tasks[taskCount].completed = false;
    taskCount++;
    saveTasks();
}

void removeTask() {
    showTasks();
    cout << "Enter task number to remove: ";
    int num;
    cin >> num;
    if (num > 0 && num <= taskCount) {
        for (int i = num - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;
        saveTasks();
    } else {
        cout << "Invalid task number!\n";
    }
}

void markTaskComplete() {
    showTasks();
    cout << "Enter task number to mark as completed: ";
    int num;
    cin >> num;
    if (num > 0 && num <= taskCount) {
        tasks[num - 1].completed = true;
        saveTasks();
    } else {
        cout << "Invalid task number!\n";
    }
}

int main() {
    loadTasks();
    int choice;

    while (true) {
        cout << "\n1. Add Task\n2. Remove Task\n3. View Tasks\n4. Mark Task as Completed\n5. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) addTask();
        else if (choice == 2) removeTask();
        else if (choice == 3) showTasks();
        else if (choice == 4) markTaskComplete();
        else if (choice == 5) break;
        else cout << "Invalid choice!\n";
    }
    return 0;
}
