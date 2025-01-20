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
        /*
        taskVariables = 
        "{\n\t\"id\": \""         +to_string(currID)  +"\",\n"+
        "\t\"description\": "   +desc               +",\n"+
        "\t\"status\": \""        +status             +"\",\n"+
        "\t\"createdAt\": \""     +createdAt          +"\",\n"+
        "\t\"updatedAt\": \""     +updatedAt          +"\"\n"+
        "}";
        */
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
        /*
        string newTaskVariables = 
        "{\n\t\"id\": \""         +to_string(currID)  +"\",\n"+
        "\t\"description\": "   +desc               +",\n"+
        "\t\"status\": \""        +status             +"\",\n"+
        "\t\"createdAt\": \""     +createdAt          +"\",\n"+
        "\t\"updatedAt\": \""     +updatedAt          +"\"\n"+
        "}";
        */
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

bool strIsValidTask(string input) {//checks if user's inputted task is a valid string to store in the json file
   bool isValid =   ((input.find("\"") == 0) && //first char is "
                    (input.substr(input.length()-1) == "\"") && //char at last index is "
                    ((input.substr(1, input.length()-2).find("\"")) == std::string::npos));//chars in between arent "
    return isValid;
}

int main() {
    string userInput;
    ofstream file("tasks.json");
    //ifstream inFile("tasks.json");
    //string filename = "tasks.json";
    vector<task> tasks = {};
    string newString;
    file << "[\n";

    while(userInput != "end") {
        //cin >> userInput;
        getline(cin, userInput);
        if(userInput.substr(0, 4) == "add " && strIsValidTask(userInput.substr(4))) {
            task newTask = task(userInput.substr(4), file);
            tasks.push_back(newTask);
            cout << "Task added successfully (ID: "+to_string(newTask.currID)+")\n";
        } else if(userInput == "update") {
            newString = userInput.substr(8);
            cout << newString << " " << to_string(strIsValidTask(newString)) << "\n";
            //tasks.at(stoi(userInput.substr(7, 1))).updateTask(newString, file, inFile);
        } else if(userInput == "list")
            for (int i = 0; i < tasks.size();i++) {
                cout << tasks[i].desc << " ";
            }
    }
    //ofstream file(filename);
    file << "\n]";
    file.close();

    string lineInFile;
    string lineToCompare = tasks[1].taskVariables;
    int numOfLines = 0;
    ifstream inFile("tasks.json");
    while (getline(inFile, lineInFile)){
        if(lineInFile == lineToCompare || lineInFile == lineToCompare+",") {
            cout << "at line 0: " << lineToCompare << "\n";
        }
        cout << numOfLines++ << " ";
        cout <<lineInFile << "\n";
    }
    inFile.close();
    return 0;
}