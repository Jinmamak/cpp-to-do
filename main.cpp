#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


void loadTasks(vector<string>& tasks) {
    ifstream in("tasks.txt");
    string line;
    while (getline(in, line)) {
        if (!line.empty())
            tasks.push_back(line);
    }
}


void saveTasks(const vector<string>& tasks) {
    ofstream out("tasks.txt", ios::trunc);
    for (auto& t : tasks) out << t << "\n";
}

int main() {
    vector<string> tasks;
    loadTasks(tasks);

    while (true) {
        cout << "\n=== To-Do Menu ===\n"
             << "1) List tasks\n"
             << "2) Add task\n"
             << "3) Remove task\n"
             << "4) Rename task\n"
             << "5) Exit\n"
             << "===================\n"
             << "Choose an option: ";

        int choice;
        if (!(cin >> choice)) break;
        cin.ignore();  

        if (choice == 1) {
            cout << "\nYour tasks:\n";
            for (int i = 0; i < tasks.size(); ++i)
                cout << i+1 << ") " << tasks[i] << "\n";

        } else if (choice == 2) {
            cout << "Enter new task: ";
            string task;
            getline(cin, task);
            if (!task.empty()) {
                tasks.push_back(task);
                saveTasks(tasks);
                cout << "Added!\n";
            }

        } else if (choice == 3) {
            cout << "Enter task number to remove: ";
            int idx;
            cin >> idx;
            cin.ignore();
            if (idx >= 1 && idx <= tasks.size()) {
                tasks.erase(tasks.begin() + idx - 1);
                saveTasks(tasks);
                cout << "Removed!\n";
            } else {
                cout << "Invalid number.\n";
            }

        } else if (choice == 4) {
            string newtask;
            int taskNumber;
            cout << "Which task do you want to rename: ";
            
            cin >> taskNumber;
            cout << "Enter new task name: ";
            cin.ignore();  // Clear the newline character from the input buffer
            getline(cin, newtask);
            if (taskNumber < 1 || taskNumber > tasks.size()) {
                cout << "Invalid task number.\n";
                continue;
            }
            tasks[taskNumber - 1] = newtask;
            cout << "Task renamed successfully!\n";
            saveTasks(tasks);

        } else if (choice == 5) {
            cout << "Choose a task to mark as completed (1-" << tasks.size() << "): ";
            int taskNumber;
            cin >> taskNumber;
            cin.ignore();  
            if (taskNumber < 1 || taskNumber > tasks.size()) {
                cout << "Invalid task number.\n";
                continue;
            }
            cout << "Task \"" << tasks[taskNumber - 1] << "\" marked as completed.\n";
            tasks.erase(tasks.begin() + taskNumber - 1);

            
        } else if (choice == 6) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
            

    }

    return 0;
}
