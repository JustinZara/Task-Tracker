#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

int numOfIDs = 0;

class task {
    public:
    int currID;
    string desc;
    int status;
    string createdAt;
    string updatedAt;

    task(){
        currID = numOfIDs;
    }
};

void addTask(string newTask) {
    cout << "Task addedd successfully";
}

void updateTask(int ID, string task) {

}

string getCurrTime() {
    time_t timestamp;
    time(&timestamp);
    return ctime(&timestamp);

}

int main() {
    string userInput;

    cin >> userInput;
    while(userInput != "end") {
        if(userInput == "add") {
            addTask(userInput);
        } else if(userInput == "update") {
            updateTask(userInput);
        }
    }
    ofstream file("tasks.json");
    file << userInput;

    file.close();
    return 0;
}