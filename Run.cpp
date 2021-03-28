#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> files;
vector<string> commands;

int getFilenames() {
    string filename;
    string substring = "*";

    cout << "Enter filename (e.g. file.exe): ";
    cin >> filename;

    if(filename.find(substring) != string::npos){
        // Remove asterisk and add to the top of the list
        filename.erase(filename.end() - 1, filename.end());
        files.insert(files.begin(), filename);
    }else{
        files.push_back(filename);
    }
    
    return 0;
}

int finishFilenames() {
    int finish;

    getFilenames();
    do{
        cout << "Enter '0' to finish list or type another number to continue entering in your list: ";
        cin >> finish;

        if(finish == 0) { return 0; }

        getFilenames();
    }while(finish != 0);

    return 0;
}

int commandsToRun() {
    finishFilenames();
    
    for(int i = 0; i < files.size(); i++){
        string curtCmd = ".\\" + files[i];
        commands.push_back(curtCmd);
    }

    return 0;
}

int runCommands() {
    commandsToRun();

    int i = 0;

    while(i < commands.size()){
        // Get exit code of the command and go to the next command, or return
        string curtCmd_ = commands[i];
        int curtExitcode = system((curtCmd_).c_str());

        if(curtExitcode == 0){
            i++;
        }else{
            cout << "A problem has occured!";
            return 0;
        }
    }

    cout << "Done!";
    
    return 0;
}

int main() {
    runCommands();

    return 0;
}