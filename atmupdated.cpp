#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

class BankSystem {
private:
    float accBalance;
    int securityPin;
    string password, userId, fullName, fatherName, addr, phoneNum;
public:
    void displayMenu();
    void manageBank();
    void registerUser();
    void existingUser();
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
};

char getInput() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void BankSystem::displayMenu() {
    p:
    system("clear");
    int userChoice;
    string pin, password, email;
    cout << "\n\n\t\tControl Panel";
    cout << "\n\n1. Manage Bank";
    cout << "\n2. Exit";
    cout << "\n\nEnter Your Choice: ";
    cin >> userChoice;
    switch (userChoice) {
        case 1:
            system("clear");
            cout << "\n\n\n\t\t\tLogin Account";
            cout << "\n\nEnter your details one by one->\nEmail\nPin\nPassword\n";
            cout << "\n\n E-mail: ";
            cin >> email;
            cout << "\n\n Pin Code: ";
            for (int i = 0; i < 5; i++) {
                char ch = getInput();
                pin += ch;
                cout << "*";
            }
            cout << "\n\n Password: ";
            for (int i = 0; i < 5; i++) {
                char ch = getInput();
                password += ch;
                cout << "*";
            }
            if (email == "bikecar@gmail.com" && pin == "12345" && password == "54321") {
                manageBank();
            } else {
                cout << "\nInvalid User\nXXXXXXXXXXXXXXXXXXXXXXXX\n";
            }
            break;
        case 2:
            exit(0);
        default:
            cout << "\n\n Invalid Value...Please Try Again";
    }
    getInput();
    goto p;
}

void BankSystem::manageBank() {
    p:
    int userChoice;
    system("clear");
    cout << "\n\nBank Management System";
    cout << "\n\n1. Register New User";
    cout << "\n2. Existing User";
    cout << "\n3. Deposit";
    cout << "\n4. Withdraw";
    cout << "\n5. Transfer";
    cout << "\n6. Go Back";
    cout << "\nEnter Your Choice: ";
    cin >> userChoice;
    switch (userChoice) {
        case 1:
            registerUser();
            break;
        case 2:
            existingUser();
            break;
        case 3:
            depositMoney();
            break;
        case 4:
            withdrawMoney();
            break;
        case 5:
            transferMoney();
            break;
        case 6:
            displayMenu();
            break;
        default:
            cout << "\nInvalid Choice\nXXXXXXXXXXXXXXXXXXXX";
    }
    getInput();
    goto p;
}

void BankSystem::registerUser() {
    p:
    system("clear");
    fstream file;
    int pin;
    float balance;
    string name, fName, pwd, addr, phone, id;

    cout << "\n\n\t\tRegister New User";
    cout << "\nUser ID: ";
    cin >> userId;
    cout << "\nName: ";
    cin >> fullName;
    cout << "\nFather's Name: ";
    cin >> fatherName;
    cout << "\nAddress: ";
    cin >> addr;
    cout << "\nPin Code: ";
    cin >> securityPin;
    cout << "\nPassword: ";
    cin >> password;
    cout << "\nPhone No.: ";
    cin >> phoneNum;
    cout << "\nBalance: ";
    cin >> accBalance;

    file.open("bank.txt", ios::in);
    if (!file) {
        file.open("bank.txt", ios::app | ios::out);
        file << " " << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
             << password << " " << phoneNum << " " << accBalance << "\n";
        file.close();
    } else {
        file >> id >> name >> fName >> addr >> pin >> pwd >> phone >> balance;
        while (!file.eof()) {
            if (id == userId) {
                cout << "\n\nUser ID Already Exists...";
                getInput();
                goto p;
            }
            file >> id >> name >> fName >> addr >> pin >> pwd >> phone >> balance;
        }
        file.close();
        file.open("bank.txt", ios::app | ios::out);
        file << " " << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
             << password << " " << phoneNum << " " << accBalance << "\n";
        file.close();
    }
    cout << "\n\nNew User Registered Successfully.....\n\n";
}

void BankSystem::existingUser() {
    system("clear");
    fstream file;
    string userId;
    int found = 0;
    cout << "\n\nExisting User Account";
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\nFile Opening Error";
    } else {
        cout << "\nUser ID: ";
        cin >> userId;
        file >> userId >> fullName >> fatherName >> addr >> securityPin >> password >> phoneNum >> accBalance;
        while (!file.eof()) {
            if (userId == this->userId) {
                system("clear");
                cout << "\nRegistered User Account";
                cout << "\nUser ID: " << this->userId << "\nPin Code: " << securityPin << "\nPassword: " << password << "\n";
                found++;
            }
            file >> userId >> fullName >> fatherName >> addr >> securityPin >> password >> phoneNum >> accBalance;
        }
        file.close();
        if (found == 0)
            cout << "\n\nCannot Find User ID.....";
    }
}

void BankSystem::depositMoney() {
    system("clear");
    fstream file, tempFile;
    float depositAmount;
    string userId;
    int found = 0;

    cout << "\n\nDeposit Amount\n";
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\nFile Opening Error\n";
        return;
    }

    cout << "User ID: ";
    cin >> userId;
    tempFile.open("temp.txt", ios::app | ios::out);
    if (!tempFile) {
        cout << "\nTemporary File Opening Error\n";
        file.close();
        return;
    }

    file >> userId >> fullName >> fatherName >> addr >> securityPin >> password >> phoneNum >> accBalance;
    while (!file.eof()) {
        if (userId == this->userId) {
            cout << "Amount To Be Deposited: ";
            cin >> depositAmount;
            accBalance += depositAmount;
            tempFile << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
                     << password << " " << phoneNum << " " << accBalance << "\n";
            found++;
            cout << "\n\t\t\tYour Amount " << depositAmount << " Successfully Deposited....\n";
        } else {
            tempFile << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
                     << password << " " << phoneNum << " " << accBalance << "\n";
        }
        file >> userId >> fullName >> fatherName >> addr >> securityPin >> password >> phoneNum >> accBalance;
    }

    file.close();
    tempFile.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (found == 0) {
        cout << "\n\nCannot Find User ID.....\n";
    }
}

void BankSystem::withdrawMoney() {
    system("clear");
    fstream file, tempFile;
    float withdrawAmount;
    string userId;
    int found = 0;

    cout << "\n\nWithdraw Amount\n";
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\nFile Opening Error\n";
        return;
    }

    cout << "User ID: ";
    cin >> userId;
    tempFile.open("temp.txt", ios::app | ios::out);
    if (!tempFile) {
        cout << "\nTemporary File Opening Error\n";
        file.close();
        return;
    }

    file >> userId >> fullName >> fatherName >> addr >> securityPin >> password >> phoneNum >> accBalance;
    while (!file.eof()) {
        if (userId == this->userId) {
            cout << "Amount To Be Withdrawn: ";
            cin >> withdrawAmount;
            if (withdrawAmount <= accBalance) {
                accBalance -= withdrawAmount;
                tempFile << " " << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
                         << password << " " << phoneNum << " " << accBalance << "\n";
                found++;
                cout << "\n\n\t\tYour Amount Rs " << withdrawAmount << " Successfully Withdrawn....\n";
            } else {
                cout << "\n\nYou have Only Rs " << accBalance << " In Your Account\n";
                tempFile << " " << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
                         << password << " " << phoneNum << " " << accBalance << "\n";
                found++;
            }
        } else {
            tempFile << " " << userId << " " << fullName << " " << fatherName << " " << addr << " " << securityPin << " "
                     << password << " " << phoneNum << " " << accBalance << "\n";
        }
        file >> userId >> fullName >> fatherName >> addr >> securityPin >> password >> phoneNum >> accBalance;
    }

    file.close();
    tempFile.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (found == 0) {
        cout << "\n\nCannot Find User ID.....\n";
    }
}

void BankSystem::transferMoney() {
    fstream file, tempFile;
    string senderId, receiverId;
    float transferAmount;
    bool senderFound = false, receiverFound = false;

    system("clear");
    cout << "\n\nMoney Transfer\n";

    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\n\nFile Opening Error...." << endl;
        return;
    }

    cout << "\n\nSender's User ID: ";
    cin >> senderId;
    cout << "\n\nReceiver's User ID: ";
    cin >> receiverId;
    cout << "\nEnter The Amount To Be Transferred: ";
    cin >> transferAmount;

    vector<string> lines;
    string line;
    float senderBalance = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name, fname, addr, pin, pass, phone;
        float balance;
        iss >> id >> name >> fname >> addr >> pin >> pass >> phone >> balance;

        if (id == senderId) {
            senderFound = true;
            if (transferAmount <= balance) {
                senderBalance = balance;
            } else {
                cout << "\nInsufficient balance for sender." << endl;
                file.close();
                usleep(2000000); 
                return;
            }
        }
        if (id == receiverId) {
            receiverFound = true;
        }

        lines.push_back(line);
    }
    file.close();

    if (!senderFound) {
        cout << "\nSender ID not found." << endl;
        usleep(2000000); 
        return;
    }
    if (!receiverFound) {
        cout << "\nReceiver ID not found." << endl;
        usleep(2000000); 
        return;
    }

    tempFile.open("temp.txt", ios::out);
    for (const string& line : lines) {
        istringstream iss(line);
        string id, name, fname, addr, pin, pass, phone;
        float balance;
        iss >> id >> name >> fname >> addr >> pin >> pass >> phone >> balance;

        if (id == senderId) {
            balance -= transferAmount;
            tempFile << id << " " << name << " " << fname << " " << addr << " " << pin << " "
                     << pass << " " << phone << " " << balance << "\n";
        } else if (id == receiverId) {
            balance += transferAmount;
            tempFile << id << " " << name << " " << fname << " " << addr << " " << pin << " "
                     << pass << " " << phone << " " << balance << "\n";
        } else {
            tempFile << line << "\n";
        }
    }
    tempFile.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    cout << "\n\nTransaction successful. Amount " << transferAmount << " transferred from " << senderId << " to " << receiverId << "." << endl;
    usleep(2000000); 
}

int main() {
    BankSystem obj;
    obj.displayMenu();
    return 0;
}