#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
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

    task(string newDesc, ofstream &file){//constructor for task object
        currID = numOfIDs++;
        createdAt = getCurrTime();
        updatedAt = getCurrTime();
        desc = newDesc;
        status = "todo";
        string taskVariables = 
        "{\n\t\"id\": \""         +to_string(currID)  +"\",\n"+
        "\t\"description\": "   +desc               +",\n"+
        "\t\"status\": \""        +status             +"\",\n"+
        "\t\"createdAt\": \""     +createdAt          +"\",\n"+
        "\t\"updatedAt\": \""     +updatedAt          +"\"\n"+
        "}";

        if(currID != 0)
            file << ",\n";
        file << taskVariables;//store variables in task file
    }
};

bool strIsValidTask(string input) {//checks if user's inputted task is a valid string to store in the json file
   bool isValid =  ((input.find("\"") == 0) && //first char is "
                    (input.substr(input.length()-1) == "\"") && //char at last index is "
                    ((input.substr(1, input.length()-2).find("\"")) == std::string::npos));//chars in between arent "
    return isValid;
}

int main() {
    string userInput;
    ofstream file("tasks.json");

    file << "[\n";
    while(userInput != "end") {
        //cin >> userInput;
        getline(cin, userInput);
        if(userInput.substr(0, 4) == "add " && strIsValidTask(userInput.substr(4))) {
            task newTask = task(userInput.substr(4), file);
            cout << "Task added successfully (ID: "+to_string(newTask.currID)+")\n";
        } else if(userInput == "update") {

        }
    }

    file << "\n]";
    file.close();
    return 0;
}