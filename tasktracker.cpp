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

        task(string newDesc){//constructor for task object
            currID = numOfIDs++;
            createdAt = getCurrTime();
            updatedAt = getCurrTime();
            desc = newDesc;
            status = "todo";
            store_vars();
        }

        void store_vars() {//store variables of task in string taskVariables
            taskVariables = 
            "\t{\n \t \"id\": \""      +to_string(currID)  +"\",\n"+
            "\t \"description\": "     +desc               +",\n"+
            "\t \"status\": \""        +status             +"\",\n"+
            "\t \"createdAt\": \""     +createdAt          +"\",\n"+
            "\t \"updatedAt\": \""     +updatedAt          +"\"\n"+
            "\t}";
        }

        void updateTask(string newDesc) {
            desc = newDesc;
            updatedAt = getCurrTime();
            store_vars();
        }

        void set_status(string newStatus) {
            status = newStatus;
            updatedAt = getCurrTime();
            store_vars();
        }

};

bool strIsValidTask(string input) {//checks if user's inputted task is a valid string to store in the json file (has quotes like "this")
    return  ((input.find("\"") == 0) && //valid if first char is "
            (input.substr(input.length()-1) == "\"") && //if char at last index is "
            ((input.substr(1, input.length()-2).find("\"")) == std::string::npos));// if chars in between arent "
}

void update_json(string filename, vector<task> list) {
    ofstream write_file;

    write_file.open(filename);
    if (write_file.fail() == true) {//if file fails to open
        cout << "error opening file\n";
        return;
    }

    write_file << "[\n";
    for(int i = 0; i < list.size();i++) {
        if (i != 0) {
            write_file << ",\n";
        }
        write_file << list[i].taskVariables;
    }
    write_file << "\n]";
    write_file.close();
}

void read_file(string filename){
    fstream read_file;
    string line;

    read_file.open(filename);
    if (read_file.fail() == true) {//if file fails to open
        cout << "error opening file\n";
        return;
    }
    while(getline(read_file, line)){
        cout << line << "\n";
    }
    read_file.close();
}

int main() {
    string userInput;
    vector<task> tasks;

    while(userInput != "end") {
        cout <<"task-cli ";
        getline(cin, userInput);
        if(userInput.substr(0, 4) == "add " && strIsValidTask(userInput.substr(4))) {
            task newTask = task(userInput.substr(4));
            tasks.push_back(newTask);
            cout << "Task added successfully (ID: "+to_string(newTask.currID)+")\n";
            update_json("tasks.json", tasks);
        } else if(userInput.length() > 8 && userInput.substr(0, 7) == "update " && tasks.size() > 0 && strIsValidTask(userInput.substr(9))) {//update 0 "..."
            int index = userInput.at(7) - '0';//subtract ascii value of '0' from character, getting actual integer value
            tasks[index].updateTask(userInput.substr(9));
            update_json("tasks.json", tasks);
        } else if(userInput == "list") {//read lines of file
            read_file("tasks.json");
        } else if(userInput.substr(0, 7) == "delete " && isdigit(userInput.at(7)) && (tasks.size() > 0)) {
            int index = (int)userInput.at(7);
            tasks.erase(tasks.begin()+index-1);
            update_json("tasks.json", tasks);
        } else if(userInput.substr(0, 17) == "mark-in-progress " && isdigit(userInput.at(17))) {
            int index = userInput.at(17) - '0';
            tasks[index].set_status("in-progress");
            update_json("tasks.json", tasks);
        } else if(userInput.substr(0, 10) == "mark-done " && isdigit(userInput.at(10))) {
            int index = userInput.at(10) - '0';
            tasks[index].set_status("done");
            update_json("tasks.json", tasks);
        }
    }

    return 0;
}