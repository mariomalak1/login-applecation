// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application.cpp
// Last Modification Date: 4/5/2022.
// mario malak : 20210313, section 15, 16.
// mahmoud sayed 20210370, section 15, 16.
// kirolos osama 20210303, section 15, 16.
// Teaching Assistant: Eng.Nesma
// Purpose: it's simple log in and registration system by C++
#include <iostream>
#include <conio.h>
#include <regex>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
struct user{
  string name;
  string email;
  string id;
  string phone_num;
  string password;
};
// counter that if it is equal 3 the user is for forbidden to log in or register
int counter = 0;
// functions declaration
vector<user> login(string filename, map<string,user>map_users);
void registration(string filename,map<string,user>map_users);
void change_password(string filename, map<string, user>map_users);
void main_menu(string filename);
string encryption(string word);
string decryption(string word);
bool is_id_repeat(map<string,user> map_users,string id );
string email_validation();
bool email_is_id_repeat(map<string,user> map_users,string email);
string name_validation();
string hide_password();
string strong_password();
string confirm_password();
void forgive_password(string filename);
vector<vector<string>> file_users_to_vector(string filename);
map<string,user> users_data_map(string filename);
map<string,user> add_user_map(string filename);
void write_users_file(string filename);
// end of functions declaration
// functions to print some things easily
// to print vector
ostream& operator << (ostream &out, vector <string> words){
    string vector_word;
    for (string word:words) {
        vector_word += word;
        vector_word += ",";
    }
    out << vector_word;
    return out;
}
// to print 2d vector
ostream& operator << (ostream &out, vector<vector<string>> vect){
    out << "(";
    for (int i = 0; i < vect.size(); ++i) {
        out << "{" << vect[i] << "}, ";
    }
    out << ")" <<endl;
    return out;
}
// to print user data
ostream& operator << (ostream &out, user user_data){
    out << "(" << user_data.name << "," << user_data.email << "," << user_data.id << "," << user_data.phone_num << "," << user_data.password << ")";
    return out;
}
// to print vector of users
ostream& operator << (ostream &out, vector <user> users){
    out << "{";
    for (int i = 0; i < users.size(); ++i) {
            out << users[i];
    }
    out << "}";
    return out;
}
// end of print functions

// all functions to encrypt and decrypt password
string encryption(string word){
    string enc_word;
    for (char letter:word) {
        letter += 1;
        enc_word += letter;
    }
    return enc_word;
}
string decryption(string word){
    string enc_word;
    for (char letter:word) {
        letter -= 1;
        enc_word += letter;
    }
    return enc_word;
}
// end encryption and decryption functions

// functions to handle all data of user to enter a valid data
// function to make user enter id that not be previously registered in the system by other users
bool is_id_repeat(map<string,user> map_users,string id ){
    int counter = 0;
    map<string, user>::iterator it;
    for (it = map_users.begin(); it != map_users.end(); it++){
        if((it->first) == id){
            return true;
        }else{
            counter += 1;
        }
    }
    if(counter == map_users.size()){
        return false;
    }
}
// functions to handle the email and get validated email and not be previously registered in the system by other users
string email_validation(){
    string email;
    regex email_validation("^((([A-Z])|([a-z])){1,2}((([A-Z])|([a-z]))|([0-9])|([#!%\\$‘&\\+\\*\\–\\/=\\?\\^_`\\.{\\|}~])[^\\.]){0,62})@(gmail.com)$");
    while (true) {
        cout << "please enter your email valid as (anyone@gmail.com) : ";
        getline(cin,email);
        if (regex_match(email, email_validation)) {
            return email;
        }
        else if(email == "0"){
            return "0";
        }
        else {
            cout << "please enter valid email" << endl;
        }
    }
}
bool email_is_id_repeat(map<string,user> map_users,string email){
    int counter = 0;
    map<string, user>::iterator it;
    for (it = map_users.begin(); it != map_users.end(); it++){
        if((it->second).email == email){
            return true;
        }else{
            counter += 1;
        }
    }
    if(counter == map_users.size()){
        return false;
    }
}
// function to handle username
string name_validation(){
    string user_name;
    regex name("[A-Za-z_-]{1,50}");
    while (true){
        cout << "please enter user name : " ;
        getline(cin,user_name);
        if (regex_match(user_name,name)){
            return user_name;
        }
        else{
            cout << "please enter valid name" << endl;
        }
    }
}
// function to make user enter valid phone number
string phone_num_validation(){
    string phone_num;
    regex phone_validation("01[0125][0-9]{8}");
    while (true){
        cout << "please enter your phone number : ";
        cin >> phone_num;
        if (regex_match(phone_num,phone_validation)){
            return phone_num;
        }
        else{
            cout << "please enter a valid phone number" << endl;
        }
    }
}
// functions for handle password
// function to make password hide as user typing
string hide_password(){
    char pass[250];
    char ch;
    string password;
    int i;
    for(i = 0;;) {
        ch = getch();
        // when user press enter "\n" to save the password
        if (ch == 13) {
            pass[i] = '\0';
            password.assign(pass);
            cout << endl;
            return password;
        }
        else {
            if (ch == '\b' and i > 0) { // if user press backspace
                cout << "\b \b";
                i -= 1;
            }
            else {
                pass[i] = ch;
                i += 1;
                cout << '*';
            }
        }
    }
}
// function to make the user enter a new strong password
string strong_password(){
    string password, response;
    regex strong_pass("^(?=(.*[a-z]){1,})(?=(.*[A-Z]){1,})(?=(.*[0-9]){1,})(?=(.*[!@#$%^&*()\\-__+.]){1,}).{13,250}$");
    while (true) {
        password = hide_password();
        if (regex_match(password, strong_pass)) {
            return password;
        } else {
            cout << "your password isn't strong enough, if you want to pass this step enter 1 if you want to enter a new strong password enter 2" << endl;
            while (true) {
                cout << "what's your response : ";
                cin >> response;
                if (response == "1"){
                    return password;
                }
                else if(response == "2"){
                    cout << "enter your password again : ";
                    break;
                } else{
                    cout << "please enter valid response" << endl;
                }
            }
        }
    }
}
// function to make the user write password again to confirm it, and if it is not match s\he will go to make password again
string confirm_password(){
    // message to the user of what letters are allowed/required and conditions that must apply to the password
    cout << "enter strong password,to make a strong password : ";
    cout << "you must enter at least 12 character include of them letters, numbers, punctuation, and upper and lower case. The greater the variety, the stronger your password will be"<< endl;
    cout << "please enter your password : ";
    string password = strong_password();
    cout << "please enter the password again to confirm it : ";
    string password_conformation = hide_password();
    if(password == password_conformation){
        return password;
    }
    else{
        cout << "there's no match for the password, please enter your password again" << endl;
        confirm_password();
    }
} // function that called the others functions that is to password validation
// function to change the password of the user
void change_password(string filename, map<string, user>map_users){
    string old_password,old_password2, new_password;
    cout << "welcome in change password page" << endl;
    cout << "please we need to log in first and after it we can make a new password" << endl;
    vector<user> vect = login(filename, map_users);
    old_password = vect[0].password;
    cout << "please enter your old password : ";
    old_password2 = hide_password();
    if(decryption(old_password) == old_password2){
        cout << "please enter your new password" << endl;
        new_password = confirm_password();
        // to change password in the file and map
        ofstream file;
        file.open(filename, ios::out);
        // check that the file opened
        if(file.is_open()){
            map<string, user>::iterator it;
            for (it = map_users.begin(); it != map_users.end(); it++){
                if((it->first) == vect[0].id){
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
    }else{
        string response;
        cout << "your old password isn't match your password, if you forgive it enter 1, if you want to enter it again enter 2, to go main menu enter 3" << endl;
        while (true) {
            cout << "what's your response : ";
            cin >> response;
            if (response == "1") {
                forgive_password(filename);
                break;
            } else if (response == "2") {
                change_password(filename,map_users);
                break;
            } else if (response == "3") {
                main_menu(filename);
                break;
            } else {
                cout << "please enter valid response, enter it again" << endl;
            }
        }
    }
//

}
// function to send otp to user and make a new password
void forgive_password(string filename){
    cout << "forgive password" << endl;
}
// end functions of password

// end of validation part

// functions to deal with files
// function to make all data of users in vector
vector<vector<string>> file_users_to_vector(string filename){
    // vector to save all data of all users in it
    vector <vector<string>> data_users;
    // vector to save data of user in it
    vector<string> vect;
    string name,email,id,phone,password,line;
    ifstream file;
    // to open file with mode to get from it and write to it
    file.open(filename, ios :: app);
    // to check that the file is opened
    if (file.is_open()){
        while (file.good()){
            // to get the lines in the file
            getline(file,name);
            vect.push_back(name);
            getline(file,email);
            vect.push_back(email);
            getline(file, id);
            vect.push_back(id);
            getline(file,phone);
            vect.push_back(phone);
            getline(file,password);
            vect.push_back(password);
            getline(file,line);
            data_users.push_back(vect);
            vect.clear();
        }
        file.close();
        return data_users;
    }
    else{
        cout << "error while loading users data" << endl;
        string filename;
        cout << "please enter valid filename that ends with .txt or .md to get the data : ";
        cin >> filename;
        file_users_to_vector(filename);
    }
}
// function to return all users data in vector
map<string,user> users_data_map(string filename){
    vector<user> users;
    map<string, user> users_map;
    user user_data;
    vector<vector<string>> users_data = file_users_to_vector(filename);
    if (users_data.size() > 1) {
        for (int i = 0; i < users_data.size(); ++i) {
            user_data.name = users_data[i][0];
            user_data.email = users_data[i][1];
            user_data.id = users_data[i][2];
            user_data.phone_num = users_data[i][3];
            user_data.password = users_data[i][4];
            users.push_back(user_data);
        }
        for (int i = 0; i < users.size(); ++i) {
            users_map.insert({(users[i]).id, users[i]});
        }
    }
    return users_map;
}
// function to add the users in map
map<string,user> add_user_map(string filename){
    map<string,user> map_users = users_data_map(filename);
    string id, email, name, password, phone_num;
    cout << "welcome in registration page" << endl;
    // to enter his id
    cout << "please enter a valid id : ";
    cin.ignore();
    getline(cin, id);
    if ( (!is_id_repeat(map_users,id) ) and ( (id != "\n") or (id != " ") or (id != ""))){
        // to enter his name as valid name
        name = name_validation();
        // to enter his email as valid email
        email = email_validation();
        if(!email_is_id_repeat(map_users,email) ) {
            // to enter valid phone number
            phone_num = phone_num_validation();
            // to enter strong password and must confirm it well
            password = confirm_password();
            password = encryption(password);
            user user_valid_data;
            user_valid_data.name = name;
            user_valid_data.email = email;
            user_valid_data.id = id;
            user_valid_data.phone_num = phone_num;
            user_valid_data.password = password;
            map_users.insert({user_valid_data.id, user_valid_data});
            return map_users;
        }else {
            cout << "you enter email that is entered before, please enter new one, i will directed you to begin of registration form";
            add_user_map(filename);
        }
    } else{
        cout << "you enter id that is entered before, please enter new one, i will directed you to begin of registration form";
        add_user_map(filename);
    }

}
// function to write the users in the file
void write_users_file(string filename){
    map<string,user> map_users = add_user_map(filename) ;
    map<string, user>::iterator it;
    ofstream file;
    file.open(filename, ios::out);
    // check that the file opened
    if(file.is_open()){
        for (it = map_users.begin(); it != map_users.end(); it++){
            file << (it->second).name << "\n";
            file << (it->second).email << "\n";
            file << (it->second).id << "\n";
            file << (it->second).phone_num << "\n";
            file << (it->second).password << "\n";
            file << "---------------------------------" << "\n";
        }
        // to close the file
        file.close();
    }
}
// end of functions that deal with files

// functions of registration and log in and main menu and change password
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
                    cout << "sorry, but you make more than three false entire id or password, so you forbidden from login" << endl;
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
        cout << "sorry, but you make more than three false entire id or password, so you forbidden from login" << endl;
        counter = 0;
        main_menu(filename);
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