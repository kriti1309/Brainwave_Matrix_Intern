#include<iostream>
using namespace std;

class ATM{
    private:
        int balance;
    public:
        ATM(int bal){
            balance=bal;
        }
        int getBalance(){
            return balance;
        }
        int withdraw(int amount){
            if(amount>balance){
                return false;
        }
            balance= balance-amount;
            return true;
        }
        void deposite(int amount){
            balance=balance+ amount;
        }





};

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Clear screen for Windows
    #else
        system("clear"); // Clear screen for Unix-like systems (Linux, macOS)
    #endif
}


int main(){
    ATM atm(1000);
    int choice, amount, success;
    char op;
    do{
    clearScreen();
    cout<<"1. View Balance"<<endl;
    cout<<"2. Cash Withdrawl"<<endl;
    cout<<"3. Cash Deposite"<<endl;
    cout<<"4. Exit"<<endl;
   
    cout<<"Enter Your Choice : ";
    cin>>choice;

    switch (choice)
    {
    case 1:
        cout<<"Your Balance is : "<<atm.getBalance();
        break;

    case 2:

        cout<<"Your Available Balance is : "<<atm.getBalance()<<endl;
        cout<<"Enter the Amount to withdraw : ";
        cin>>amount;
        success=atm.withdraw(amount);
        if(success){
            cout<<"Withdraw Successfull.....\n\n"<<endl;
        }
        else{
            cout<<"Insufficient Balance.....\n\n"<<endl;
            }
        break;

    case 3:
        cout<<"Enter the amount to Deposite : ";
        cin>>amount;
        atm.deposite(amount);
        cout<<"Deposite Successfully.....\n\n";
        break;
    
    case 4:
        cout<<"Thanks for using ATM"<<endl;
        break;
    default:
    cout<<"Invalid Choice !!!!!\n\n"<<endl;
        break;
    }
    cout<<"\nWant To Try Another Operation ??\n[Yes/No] : ";
    cin>>op;
    }while(op=='y' || op=='Y');



    
}