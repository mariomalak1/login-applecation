// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.cpp
// first Modification Date: 2/5/2022.
// Last Modification Date: 4/5/2022.
// mario malak : 20210313, section 15, 16.
// mahmoud sayed 20210370, section 15, 16.
// kirolos osama 20210303, section 15, 16.
// Teaching Assistant: Eng.Nesma
// Purpose: it's simple log in and registration system by C++
#include <iostream>
#include <vector>
#include <map>
#include "Loginapp.h"
using namespace std;
vector<user> login(string filename, map<string,user>map_users);
void registration(string filename,map<string,user>map_users);
void change_password(string filename, map<string, user>map_users);
void main_menu(string filename);
// functions of registration and log in and main menu and change password and forgive password
// function to change the password of the user
void change_password(string filename, map<string, user>map_users){
    string old_password,old_password2, new_password;
    cout << "welcome in change password page" << endl;
    cout << "please we need to log in first and after it we can make a new password" << endl;
    vector<user> vect = login(filename, map_users);
    if (!(vect[0].id == "none")) {
        old_password = vect[0].password;
        cout << "please enter your old password : ";
        old_password2 = hide_password();
        if (decryption(old_password) == old_password2) {
            cout << "please enter your new password" << endl;
            new_password = confirm_password();
            // to change password in the file and map
            ofstream file;
            file.open(filename, ios::out);
            // check that the file opened
            if (file.is_open()) {
                map<string, user>::iterator it;
                for (it = map_users.begin(); it != map_users.end(); it++) {
                    if ((it->first) == vect[0].id) {
                        (it->second).password = encryption(new_password);
                    }
                    file << (it->second).name << "\n";
                    file << (it->second).email << "\n";
                    file << (it->second).id << "\n";
                    file << (it->second).phone_num << "\n";
                    file << (it->second).password << "\n";
                    file << "---------------------------------" << "\n";
                }
                cout << "password is changed now" << endl;
                // to close the file
                file.close();
                main_menu(filename);
            }
        } else {
            string response;
            cout
                    << "your old password isn't match your password, if you forgive it enter 1, if you want to enter it again enter 2, to go main menu enter 3"
                    << endl;
            while (true) {
                cout << "what's your response : ";
                cin >> response;
                if (response == "1") {
                    forgive_password(filename);
                    break;
                } else if (response == "2") {
                    change_password(filename, map_users);
                    break;
                } else if (response == "3") {
                    main_menu(filename);
                    break;
                } else {
                    cout << "please enter valid response, enter it again" << endl;
                }
            }
        }
    }
}
// function to send otp to user and make a new password
void forgive_password(string filename){
    cout << "forgive password" << endl;
}
// function to put all users in the map in the file
void registration(string filename,map<string,user>map_users ){
    fstream file;
    file.open(filename, ios::app);
    // check that the file opened
    if(file.is_open()){
        // to close the file
        write_users_file(filename);
        file.close();
    }else{
        cout << "happen problem while saving the user " << endl;
        string response;
        while(true) {
            cout << "if you want to register again enter 1 if you want main menu enter 2" << endl;
            cout << "what's your response : ";
            cin >> response;
            if (response == "1"){
                registration(filename,map_users);
                break;
            }
            else if(response == "2"){
                main_menu(filename);
                break;
            }
            else{
                cout << "please enter a valid response" << endl;
            }
        }
    }
    cout << "registration done" << endl;
    main_menu(filename);
}
// function to make user log in the system
vector<user> login(string filename, map<string,user>map_users){
    vector<user> current_user_data;
    string id, password;
    cout << "please enter your id : ";
    cin.ignore();
    getline(cin, id);
    map<string,user> ::iterator it;
    it = map_users.find(id);
    bool cond = true;
    if(counter < 4) {
        if (it != map_users.end()) {
            while (cond) {
                cout << "please enter your password : ";
                password = hide_password();
                if (password == decryption((it->second).password)) {
                    cout << "Successful login, welcome " << (it->second).name << endl;
                    current_user_data.push_back(it->second);
                    return current_user_data;
                } else if (password == "0") {
                    counter += 1;
                    login(filename,map_users);
                } else if (password == "1") {
                    counter += 1;
                    change_password(filename,map_users);
                    cond = false;
                } else if (password == "2") {
                    counter += 1;
                    registration(filename,map_users);
                    cond = false;
                }else {
                    counter += 1;
                    if (counter != 4) {
                        cout << "password is false, please enter it again and if you want to quit and enter another id enter 0 instead of password" << endl;
                        cout << "if you want to change password of this id enter 1 instead of password" << endl;
                        cout << "if you want to make a new user enter 2 instead of password" << endl;
                    }
                }
                if (counter == 4){
                    cond = false;
                    cout << "sorry, but you make more than three false entire id or password, so you forbidden from login, i will directed you to main menu" << endl;
                    counter = 0;
                    user none = {"none", "none","none","none","none"};
                    current_user_data.push_back(none);
                    main_menu(filename);
                    return current_user_data;
                }
            }
        } else {
            string response;
            while (true) {
                cout << "your id is not found, if you to try again to enter a correct id enter 1, if you want to make new user enter 2" << endl;
                cout << "what is your response : ";
                cin >> response;
                if (response == "1") {
                    counter += 1;
                    login(filename, map_users);
                    break;
                } else if (response == "2") {
                    counter += 1;
                    registration(filename, map_users);
                    break;
                }
                else{
                    cout << "please enter valid response " << endl;
                }
            }
        }
    }
    else{
        cout << "sorry, but you make more than three false entire id or password, so you forbidden from login, i will directed you to main menu" << endl;
        counter = 0;
        user none = {"none", "none","none","none","none"};
        current_user_data.push_back(none);
        main_menu(filename);
        return current_user_data;
    }
}
// function that has all functions as log in and registration and change password
void main_menu(string filename){
    map<string , user> map_users = users_data_map(filename);
    string response;
    while(true) {
        cout << "1 --> Register" << endl;
        cout << "2 --> Login" << endl;
        cout << "3 --> Change Password" << endl;
        cout << "4 --> Exit" << endl;
        cout << "what's your response : " ;
        cin >> response;
        if(response == "1"){
            registration(filename,map_users);
            break;
        }else if (response == "2"){
            login(filename,map_users);
            break;
        }else if (response == "3"){
            change_password(filename,map_users);
            break;
        }else if(response == "4"){
            cout << "Program End" << endl;
            break;
        }
    }
}
int main() {
    main_menu("users.txt");
    return 0;
}