#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

class task {
    public:
    int id;
    string desc;
    int status;
    string createdAt;
    string updatedAt;
};

void addTask(string newTask) {
    cout << "Task addedd successfully";
}

string getCurrTime() {
    time_t timestamp;
    time(&timestamp);
    return ctime(&timestamp);

}

int main() {
    string userInput;
    fstream file ("listOfTasks.json");

    file >> userInput;
    
    file.close();
    return 0;
}