#include <iostream>
#include <vector>

using namespace std;

void showTasks(const vector<string>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks in the list!" << endl;
        return;
    }
    cout << "Your tasks:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i] << endl;
    }
}

int main() {
    vector<string> tasks;
    int choice;

    while (true) {
        cout << "\n1. Add Task\n2. Remove Task\n3. View Tasks\n4. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter task: ";
            string task;
            cin.ignore();
            getline(cin, task);
            tasks.push_back(task);
        }
        else if (choice == 2) {
            showTasks(tasks);
            cout << "Enter task number to remove: ";
            int num;
            cin >> num;
            if (num > 0 && num <= tasks.size()) {
                tasks.erase(tasks.begin() + num - 1);
            } else {
                cout << "Invalid task number!" << endl;
            }
        }
        else if (choice == 3) {
            showTasks(tasks);
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
