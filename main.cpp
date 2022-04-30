#include <iostream>
#include <conio.h>
#include <regex>
#include <map>
using namespace std;
struct user{
  string name;
  string email;
  string id;
  string phone_num;
  string password;
};
user add_user_data(string file_users,string name, string id, string email, string phone, string password){
    user user1;
    user1.name = name;
    user1.email = email;
    user1.id = id;
    user1.phone_num = phone;
    user1.password = password;
    return user1;
}

void id_repeated_handle(string id){

}
// function to handle the email and get validated email
string email_validation(){
    string email;
    regex email_validation("((([A-Z])|([a-z])){1,2}((([A-Z])|([a-z]))|([0-9])|([#!%\\$‘&\\+\\*\\–\\/=\\?\\^_`\\.{\\|}~])){0,62})@(gmail.com)");
    while (true) {
        cout << "please enter your email valid as (anyone@gmail.com) : ";
        cin.ignore();
        getline(cin,email);
        if (regex_match(email, email_validation)) {
            return email;
        } else {
            cout << "please enter valid email" << endl;
        }
    }
}
// functions for handle passwords
// function to make password hide as user typing
string hide_password(){
    cout << "enter password : " ;
    char pass[250];
    char ch;
    string password;
    int i;
    for(i = 0;;){
        ch = getch();
        if((ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or (ch >= '0' and ch <= '9')){
            pass[i] = ch;
            i += 1;
            cout << '*';
        } else if (ch == '\b' and i > 0) { // if user press backspace
            cout << "\b \b";
            i -= 1;
        }
        else if(ch == 26){ // if user press enter
            pass[i] = '\0';
            password.assign(pass);
            cout << endl;
            return password;
            break;
        }
    }
}
// function to make the user enter a new strong password
string strong_password(){
    string password, response;
    regex strong_pass("^(?=(.*[a-z]){1,})(?=(.*[A-Z]){1,})(?=(.*[0-9]){1,})(?=(.*[!@#$%^&*()\\-__+.]){1,}).{13,250}$");
    while (true) {
        cout << "please enter a strong password : ";
        cin >> password;
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
                    break;
                } else{
                    cout << "please enter valid response" << endl;
                }
            }
        }
    }
}
// function to make the user write password again to confirm it, and if it is not match s\he will go to make password again
string confirm_password(string password){
    string con_password;
    if(password == con_password){
        return password;
    }
    else{
        cout << "there's no match for the password, please enter your password again" << endl;
        strong_password();
    }
}
// end functions of password
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
int main() {
//    user mario;
//    mario.id = "20210313";
//    map<string,user>id_user = {{mario.id , mario} , };
    cout << hide_password() << endl;
    return 0;
}

//user mario;
//mario.email = "mario";
//mario.id = "20210313";
//mario.name = "malak";
//mario.phone_num = "01210104850";
//cout << mario.phone_num << endl;
