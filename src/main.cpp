#include "util.cpp"

bool loop = false;
string processID;
string processWindowTitle;

void changeWindowTitle_loop() {
    bool startOnce = true;

    while (loop || startOnce) {
        startOnce = false; // stop once started

        HWND processHandle = Util::find_main_window(stoi(processID));
        bool isChanged = SetWindowTextA(processHandle, processWindowTitle.c_str());
        cout << (isChanged ? "+" : "."); // give some sort of information if the process is still active
    }
}

int main(int argc, char **argv) {
    SetConsoleTitle("WindowTitleSpoofer");

    string loopYN;

    if (argv[1] == nullptr || argv[2] == nullptr) {
        cout << "Hey you can also launch using arguments. [argv[1] = processID, argv[2] = processWindowTitle]" << endl;

        cout << "Process ID: ";
        getline(cin, processID);

        cout << "Window Title: ";
        getline(cin, processWindowTitle);

        loop:
        cout << "Loop spoof [y, n]: ";
        getline(cin, loopYN);
    } else {
        processID = argv[1];
        processWindowTitle = argv[2];
        loopYN = argv[3];
    }

    // Define loop status else ask again
    if (loopYN != "y" && loopYN != "n") goto loop;
    loop = loopYN == "y";

    // Start background thread
    thread(changeWindowTitle_loop).detach();

    // If console resumed stop loop & program
    cout << "Press a key to exit from the program." << endl;
    cin.get();

    loop = false;
    exit(0);
}