#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

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

int confOrDeny() {
    commandsToRun();

    cout << "Your list:\n";

    for(int i = 0; i < files.size(); i++){
        cout << "\n" + files[i];
    }

    int confDeny;
    cout << "\n\nConfirm (1) or deny (0) list: ";
    cin >> confDeny;

    if(confDeny == 0){
        return 0;
    }else{
        runCommands();
    }

    return 0;
}

int readFile() {
    finishFilenames();

    string nameOfFile;
    string text;
    int i = 0;
    int move;

    while(i < files.size()){
        nameOfFile = files[i];

        // Open file and read its contents line by line
        fstream readFile(nameOfFile);

        while(getline(readFile, text)){
            cout << "\n" + text;
        }

        readFile.close();

        cout << "\n\nEnter a number to move onto the next file: ";
        cin >> move;

        i++;
    }

    return 0;
}

int welcome() {
    // Get today's date and time
    time_t today;
    time(&today);

    cout << "Run* by Fransk\t" << asctime(localtime(&today)) << "\n";

    return 0;
}

int main() {
    int option;

    welcome();
    cout << "Enter 0 to type in filenames to be run or type in 1 to type in filenames to be read: ";
    cin >> option;

    if(option == 0){
        confOrDeny();
    }else{
        readFile();
    }

    return 0;
}