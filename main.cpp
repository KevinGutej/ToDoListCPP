#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Task {
    string description;
    string priority;
    string deadline;
    bool completed;
};

vector<Task> tasks;

void saveTasks() {
    ofstream file("tasks.txt");
    for (size_t i = 0; i < tasks.size(); i++) {
        file << tasks[i].description << "|" << tasks[i].priority << "|" << tasks[i].deadline << "|" << (tasks[i].completed ? "1" : "0") << "\n";
    }
    file.close();
}

void loadTasks() {
    ifstream file("tasks.txt");
    Task task;
    string completedStr;
    while (true) {
        getline(file, task.description, '|');
        getline(file, task.priority, '|');
        getline(file, task.deadline, '|');
        getline(file, completedStr);
        if (file.eof()) break;
        task.completed = (completedStr == "1");
        tasks.push_back(task);
    }
    file.close();
}

void showTasks() {
    if (tasks.size() == 0) {
        cout << "No tasks in the list!\n";
        return;
    }
    cout << "\nYour Tasks:\n";
    cout << "No.  Description                          Priority  Deadline     Status" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << (i + 1) << ". " << tasks[i].description;
        for (size_t j = tasks[i].description.size(); j < 35; j++) cout << " ";
        cout << tasks[i].priority;
        for (size_t j = tasks[i].priority.size(); j < 10; j++) cout << " ";
        cout << tasks[i].deadline;
        for (size_t j = tasks[i].deadline.size(); j < 15; j++) cout << " ";
        cout << (tasks[i].completed ? "Completed" : "Pending") << endl;
    }
}

void addTask() {
    Task task;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, task.description);
    cout << "Enter priority (Low, Medium, High): ";
    getline(cin, task.priority);
    cout << "Enter deadline (YYYY-MM-DD): ";
    getline(cin, task.deadline);
    task.completed = false;
    tasks.push_back(task);
    saveTasks();
}

void removeTask() {
    showTasks();
    cout << "Enter task number to remove: ";
    int num;
    cin >> num;
    if (num > 0 && num <= (int)tasks.size()) {
        for (size_t i = num - 1; i < tasks.size() - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        tasks.pop_back();
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
    if (num > 0 && num <= (int)tasks.size()) {
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
