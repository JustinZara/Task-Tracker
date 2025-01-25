#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int numOfIDs = 0;

string getCurrTime() {
    time_t timestamp;
    string timeString;
    time(&timestamp);
    timeString = ctime(&timestamp);
    return timeString.substr(0, timeString.length()-1);//remove \n char from end of time_t variable
}

class task {
    public:
    int currID;
    string status;
    string desc;
    string createdAt;
    string updatedAt;
    string taskVariables;

    task(string newDesc, ofstream &file){//constructor for task object
        currID = numOfIDs++;
        createdAt = getCurrTime();
        updatedAt = getCurrTime();
        desc = newDesc;
        status = "todo";
        taskVariables = 
        "{\"id\": \""           +to_string(currID)  +"\","+
        "\"description\": "     +desc               +","+
        "\"status\": \""        +status             +"\","+
        "\"createdAt\": \""     +createdAt          +"\","+
        "\"updatedAt\": \""     +updatedAt          +"\""+
        "}";

        if(currID != 0)
            file << ",\n";
        file << taskVariables;//store variables in task file
    }

    void updateTask(string newDesc, ofstream &file, ifstream &inFile) {
        desc = newDesc;
        updatedAt = getCurrTime();
        string nextLineOfFile;
        while(nextLineOfFile != taskVariables) {
            inFile >> nextLineOfFile;
            cout <<nextLineOfFile;            
        }
        inFile.close();

        if(currID != 0)
            file << ",\n";
        file << taskVariables;//store variables in task file
    }
};

bool strIsValidTask(string input) {//checks if user's inputted task is a valid string to store in the json file (has quotes like "this")
   bool isValid =   ((input.find("\"") == 0) && //valid if first char is "
                    (input.substr(input.length()-1) == "\"") && //if char at last index is "
                    ((input.substr(1, input.length()-2).find("\"")) == std::string::npos));// if chars in between arent "
    return isValid;
}

int main() {
    string userInput;
    ofstream file("tasks.json");
    vector<task> tasks;

    string newString;
    file << "[\n";

    while(userInput != "end") {
        getline(cin, userInput);
        if(userInput.substr(0, 4) == "add " && strIsValidTask(userInput.substr(4))) {
            task newTask = task(userInput.substr(4), file);
            tasks.push_back(newTask);
            cout << "Task added successfully (ID: "+to_string(newTask.currID)+")\n" << tasks.size() << " size\n";
        } else if(userInput.substr(0, 7) == "update ") {
            int index = (int)userInput.at(8);
            //tasks.at(index).updateTask(newString, file, inFile);
        } else if(userInput == "list")
            for (int i = 0; i < tasks.size();i++) {
                cout << tasks[i].desc << " ";
        } else if(userInput.substr(0, 7) == "delete " && isdigit(userInput.at(7)) && (tasks.size() > 0)) {
            int index = (int)userInput.at(7);
            tasks.erase(tasks.begin()+index-1);
        }
    }
    //ofstream file(filename);
    file << "\n]";
    file.close();
    return 0;
}