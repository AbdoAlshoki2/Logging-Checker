#include <iostream>
#include <bits/stdc++.h>
#include <conio.h>
#include <regex>
using namespace std;

bool valid_email();
bool valid_phone_number();
bool valid_password();
bool valid_name ();
void load();
void save();
bool confirm_password();

void register_user();
void enter_password();
void login();
void change_password();
void exit();

struct user_info{
    string name;
    string username;
    string password;
    string email;
    string phone;
};
string email , password , username , phone_number , name,line;
fstream login_file;
vector <user_info> users;
int main () {
    cout << "Ahlan ya user ya habibi :)\n";
    cout << "Welcome to Facebook v2.0 \n";
    cout << "Please choose one of the following :\n";
    string option ;
    while (true)
    {
        cout << "1-Register new user." << endl <<
             "2-Login." << endl <<
             "3-Change Password." << endl <<
             "4-Exit." << endl ;
        cin >> option ;
        if (option == "1") register_user();
        else if (option == "2") login();
        else if (option == "3") change_password();
        else if (option == "4") exit();
        else cout << "Please choose an option from (1-4) ! \n";
    }
}
// __________________________________
void load(){
    users.clear();
    login_file.open("login_file.txt", ios::in);
    while(getline(login_file,line)){
        string word;
        vector<string>tmp ;
        istringstream all(line);
        while(all>>word){
            tmp.push_back(word);
        }
        user_info newUser;
        newUser.name = tmp[0];
        newUser.username = tmp[1];
        newUser.password = tmp[2];
        newUser.email = tmp[3];
        newUser.phone = tmp[4];
        users.push_back(newUser);
    }
    login_file.close();
}
// __________________________________
void save(){
    login_file.open("login_file.txt", ios::out);
    for(int i =0; i< users.size(); i++){
        login_file << users[i].name << " "
                   << users[i].username << " "
                   << users[i].password << " "
                   << users[i].email << " "
                   << users[i].phone << "\n";
    }
    login_file.close();
}
// __________________________________
bool valid_email (string email) {
    regex valid ("[\\w]+[.]?[\\w]+@[\\w]+.com");
    return regex_match(email, valid);
}
// __________________________________
bool valid_name (string name) {
    regex valid ("[a-zA-Z]*");
    return regex_match(name, valid);
}
// __________________________________
bool valid_phone_number(string phone_number){
    regex valid ("01+[0-1]{1}+[0-9]{8}");
    return regex_match(phone_number, valid);
}
// __________________________________
bool valid_password (string password){
    bool valid = true;
    int up = 0 , lo = 0 , num = 0 , pun = 0 ;
    for (int i = 0; i < password.size(); i++)
    {
        if (password[i] >= 65 && password[i] <= 90) up +=1;
        else if (password[i] >=97 && password[i] <=122 ) lo +=1;
        else if (isdigit(password[i])) num+=1;
        else if (ispunct(password[i])) pun+=1;
    }
    if (lo != 0 && up != 0 && num != 0 && pun !=0 && password.length() >= 12) return valid;
}
// __________________________________
void enter_password(){
    cout << "Note that Your password must contain " << endl ;
    cout <<"-At least 12 characters long but 14 or more is better.\n"<<
         "-At combination of uppercase letters, lowercase letters, numbers, and symbols.\n";
    cout << "Enter your password : " ;
    int ch ;
    ch = getch();
    while (ch != 13){
        if (ch == 8) {
            if (!password.empty()){
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            cout << "*";
            password += ch;
        }
        ch = getch();
    }
}
// __________________________________
bool confirm_password(string conf_password){
    for (int i = 0; i < password.length(); i++) password[i] +=1;
    int ch;
    ch = getch();
    while (ch != 13){
        if (ch == 8) {
            if (!conf_password.empty()){
                conf_password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            cout << "*";
            conf_password += ch;
        }
        ch = getch();
    }
    cout << endl ;
    for (int i = 0; i < conf_password.length(); i++) conf_password[i] +=1;
    return conf_password == password;
}
// __________________________________
void register_user() {
    load();
    string conf_password;
    //login_file.open("login_file.txt",ios::app);
    string check;
    cin.clear();
    cin.sync();
    cout << "Enter your name : ";
    getline(cin,name);
    while(!valid_name(name)){
        cout<<"Please enter valid name! \n";
        getline(cin,name);
    }
    cout << "Enter your username : ";
    getline(cin,username);
    for(int i =0; i < users.size(); i++){
        while(username == users[i].username){
            cout<<"This username has been taken before! \nEnter a new one: ";
            cin.clear();
            cin.sync();
            getline(cin,username);
            i = 0;
        }
    }
    cout << "Enter your email : ";
    cin >> email;
    while(!valid_email(email)) {
        cout << "Please enter a valid email !\n";
        cin >> email;
    }
    for(int i =0; i < users.size(); i++){
        while(email == users[i].email){
            cout<<"This Email has been taken before! \nEnter a new one: ";
            cin.clear();
            cin.sync();
            getline(cin,email);
            i = 0;
        }
    }
    cout << "Enter your phone number : " ;
    cin >> phone_number;
    while(!valid_phone_number(phone_number)){
        cout << "Please enter a valid phone number !\n";
        cin >> phone_number;
    }
    enter_password();
    if (valid_password(password)) {
        cout << "\nYour password is strong :) \n";
    }
    else {
        while(!valid_password(password)){
            cout <<"\nYour password is WEAK\n";
            password.clear();
            enter_password();
        }
    }

    cout << "Please confirm your password : ";
    while (!confirm_password(conf_password)) {
        cout << "Please re-enter the password \n" ;
    }
    cout << "You have successfully registered :) \n";
    user_info newUser;
    newUser.name = name;
    newUser.username = username;
    newUser.password = password;
    newUser.email = email;
    newUser.phone = phone_number;
    users.push_back(newUser);
    save();

}
// __________________________________
void login() {
    load();
    //login_file.open("login_file.txt");
    cin.sync();
    cin.clear();
    string login_user , login_password , check_login ;
    cout << "Enter your username : " ;
    getline (cin,login_user);
    cout << "Enter your password : ";
    int ch ;
    ch = getch();
    while (ch != 13){
        if (ch == 8) {
            if (!login_password.empty()){
                login_password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            cout << "*";
            login_password += ch;
        }
        ch = getch();
    }
    for (int i = 0; i < login_password.size(); i++)
    {
        login_password[i] +=1 ;
    }

    bool success = false ;
    for(int i =0; i < users.size(); i++){
        if(login_user == users[i].username && login_password == users[i].password) {
            success = true;
            break;
        }
    }
    if (!success) cout << "\nFailed to login \nPlease check the username or password you entered \n";
    else cout<<"\nYou have successfully logged in. :)";
    cout << endl ;
}
// __________________________________
void change_password() {
    load();
    string username , line ,old_password,new_password ;
    bool success = false ;
    cin.sync();
    cin.clear();
    cout << "Please enter your username : ";
    getline (cin,username);
    cout << "Please enter your old password : ";
    int ch ,index;
    ch = getch();
    while (ch != 13){
        if (ch == 8) {
            if (!old_password.empty()){
                old_password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            cout << "*";
            old_password += ch;
        }
        ch = getch();
    }
    for (int i = 0; i < old_password.size(); i++)
    {
        old_password[i] +=1 ;
    }
    for(int i =0; i < users.size(); i++){
        if(username == users[i].username && old_password == users[i].password) {
            success = true;
            index = i;
            break;
        }
    }
    if (success) {
        cout << "\nEnter your new password : ";
        int ch ;
        ch = getch();
        while (ch != 13){
            if (ch == 8) {
                if (!new_password.empty()){
                    new_password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                cout << "*";
                new_password += ch;
            }
            ch = getch();
        }
        if (valid_password(new_password)) {
            for (int i = 0; i < new_password.size(); i++)
            {
                new_password[i] +=1 ;
            }
            users[index].password = new_password;
            cout << "\nYou have successfully changed your password \n";
        }
        else {
            while(!valid_password(new_password)){
                cout <<"\nYour password is WEAK\n";
                new_password.clear();
                cout << "\nEnter your new password : ";
                int ch ;
                ch = getch();
                while (ch != 13){
                    if (ch == 8) {
                        if (!new_password.empty()){
                            new_password.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else {
                        cout << "*";
                        new_password += ch;
                    }
                    ch = getch();
                }
            }
        }
    }
    else cout << "\nInvalid username or password \n";
    cout <<endl;
    save();

}
// __________________________________
void exit(){
    login_file.close();
    cout << "See you soon ;) " << endl;
    exit(1);
}
