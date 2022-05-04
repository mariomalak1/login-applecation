// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Text Editor.cpp
// Last Modification Date: 1/5/2022.
// mario malak : 20210313, section 15, 16.
// mahmoud sayed 20210370, section 15, 16.
// kirolos osama 20210303, section 15, 16.
// Teaching Assistant: Eng.Nesma
// Purpose: It is a simple console-based Text Editor to make some function.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
// function to get from the user right input as file name and if he want to create new file with the same name
string if_file(){
    string filename, response;
    // get from the user file name
    cout << "please enter the file name with it's extension like .txt : ";
    cin >> filename;
    ifstream file(filename);
    // if it's a real file it will open else, so he put a wrong file name
    if(! (file.is_open()) ){
        cout << "you enter invalid name for file, if you want to create a file with this name press 1, if you want to return to enter file name enter 2." << endl;
        // to enter a valid response 1 or 2
        while(true) {
            cout << "what's your response : ";
            cin >> response;
            if (response == "1") {
                // create a new file with extension txt
                if (filename.find(".txt") != string::npos) {
                    ofstream file;
                    file.open(filename, ios::app);
                    file.close();
                }
                else{
                    filename += ".txt";
                    ofstream file;
                    file.open(filename, ios::app);
                    file.close();
                }
                cout << "file is created" << endl;
                return filename;
            } else if (response == "2") {
                // i will make him to enter file name again
                if_file();
                break;
            } else {
                cout << "please enter 1 or 2 only" << endl;
            }
        }
    } else{
        return filename;
    }
}
// function to put all the words in file in vector
vector <string> make_file_vector(string filename){
    vector <string> file_words;
    string line, word;
    ifstream file;
    // to open file with mode to get from it and write to it
    file.open(filename, ios::in | ios ::out);
    // to check that the file is opened
    if (file.is_open()){
        int j = 0;
        while (file.good()){
            // to get the lines in the file
            getline(file,line);
            for (int i = 0; i < line.length(); ++i) {
                word += line[i];
                if (line[i] == ' ') {
                    file_words.push_back(word);
                    j += 1;
                    word = "";
                }
            }
            file_words.push_back(word);
            file_words.push_back("\n");
            word = "";
        }
        // to delete last breakline in the vector
        file_words.pop_back();
        // to close the file
        file.close();
    }
    else{
        cout << "it make an error while opening the file " << endl;
    }
    return file_words;
}
// function to put all words in vector to file
void make_vector_file(vector <string> file_words ,string filename){
    string response;
    // to ask him if he want to save in the same file or in another one
    cout << "if you want to save in the same file enter 1, if you want to save in another file enter 2" << endl;
    while(true) {
        cout << "what is your response : ";
        cin >> response;
        if (response == "1"){
            break;
        }
        else if(response == "2"){
            cin  >> filename;
            if (filename.find(".txt") != string::npos) {
                ofstream file;
                file.open(filename, ios::app);
                file.close();
            }
            else{
                filename += ".txt";
                ofstream file;
                file.open(filename, ios::app);
                file.close();
            }
        }
        else{
            cout << "please enter valid response" << endl;
        }
    }
    ofstream file(filename);
    // check that the file opened
    if(file.is_open()){
        for (string word:file_words) {
            // to write on the file
            file << word;
        }
        // to close the file
        file.close();
        cout << "file saved " << endl;
    }else{
        cout << "happen problem while saving the file" << endl;
    }
}
// function to print to vector
ostream& operator << (ostream &out, vector <string> words){
    string vector_word;
    for (string word:words) {
        vector_word += word;
        vector_word += ",";
    }
    out << vector_word;
    return out;
}
// function to Count the number of times a word exists in the file
int num_times_word(vector<string> words){
    string word_find;
    cout << "please enter the word you want to get how times it repeated : ";
    cin >> word_find;
    int num = 0;
    for (string word:words) {
        if(strstr(word.c_str(),word_find.c_str())){
            num += 1;
        }
    }
    return num;
}
// function to remove spaces and breaklines from vector
vector<string> remove_S_B(vector<string> vect){
    vector<string> vect2;
    string word1;
    for (string word:vect) {
        if (!((word == " ") or (word == "\n") or (word == ""))) {
            for (int i = 0; i < word.length(); ++i) {
                if (!((word[i] == ' ') or (word[i] == '\n') or (word == ""))) {
                    word1 += word[i];
                }
            }
            vect2.push_back(word1);
            word1 = "";
        }
    }
    return vect2;
}
// function to count the number of words in the file --> 7
int num_words(vector <string>vect){
    vector <string> words = remove_S_B(vect);
    return words.size();
}
// function to merge two vectors and add them to the first vector and return it
vector<string> merge_vectors(vector<string> file1, vector<string> file2){
    vector<string> merge_file;
    for (string word:file1) {
        merge_file.push_back(word);
    }
    for (string word:file2) {
        merge_file.push_back(word);
    }
    file1.clear();
    for (string word:merge_file) {
        file1.push_back(word);
    }
    return file1;
}
// function to merge two files --> 6
vector<string> merge_files(vector<string> file1){
    cout << "we need second file" << endl;
    string filename2 = if_file();
    vector <string> file2 = make_file_vector(filename2);
    file1 =  merge_vectors(file1,file2);
    return file1;
}
// function to return number of characters in the file -->8
int num_char(vector<string> vect){
    int char_num = 0;
    for (string word:vect) {
        if (! ( (word == "") or (word == "\n") ) ) {
            for (int i = 0; i < word.length(); ++i) {
                if (!(word[i] == '\n')){
                    char_num += 1;
                }
            }
        }
    }
    return char_num;
}
// function to return number of lines in the file --> 9
int num_lines(vector<string> vect){
    int lines_num = 0;
    if(!(vect.empty())) {
        for (string word: vect) {
            if (word == "\n") {
                lines_num += 1;
            }
        }
        lines_num += 1;
        return lines_num;
    }
    else{
        return lines_num;
    }
}
// function to empty the vector --> 3
vector<string> empty_vector(vector<string>vect){
    vect.clear();
    return vect;
}
// function to display all the content in the file by print the vector content --> 2
void display_file(vector<string>vect){
    for (string word:vect) {
        cout << word;
    }
    cout << endl;
}
// function to make user append to the file from the console --> 1
vector<string> line_vector(string line) {
    string word;
    vector<string> words;
    for (int i = 0; i < line.length(); ++i) {
        word += line[i];
        if (line[i] == ' ') {
            words.push_back(word);
            word = "";
        }
        words.push_back(word);
        word = "";
    }
    return words;
}
vector<string> append_file(string filename, vector<string> vect){
    string all_words;
    char ch;
    fstream file;
    // to append on the file
    file.open(filename,  ios :: app);
    bool cond = file.eof();
    if(file.is_open()) {
        cout << "please enter what you want to append to the file and to stop writen press control z (^z) to end of the line" << endl;
        cout << "enter what you want to write it : ";
        while (!cond) {
            cin.get(ch);
            if ((ch == 26) or (ch == '?')) {
                break;
            }
            all_words += ch;
        }
        file << all_words;
    }
    file.close();
    vect = make_file_vector(filename);
    return vect;
}
// function to make string word encrypted by adding 1 to it's ascii code
string encryption(string word){
    string enc_word;
    for (char letter:word) {
        letter += 1;
        enc_word += letter;
    }
    return enc_word;
}
// function to encrypt the all file --> 4
vector<string> encryption_file (vector <string> vect) {
    string enc_word;
    vector<string> enc_vect;
    for (string word:vect) {
        enc_word = encryption(word);
        enc_vect.push_back(enc_word);
    }
    vect.clear();
    for (string word:enc_vect) {
        vect.push_back(word);
    }
    return vect;
}
// function to make string word encrypted by subtracting 1 from it's ascii code
string decryption(string word){
    string enc_word;
    for (char letter:word) {
        letter -= 1;
        enc_word += letter;
    }
    return enc_word;
}
// function to decrypt the all file --> 5
vector<string> decryption_file (vector <string> vect) {
    string enc_word;
    vector<string> enc_vect;
    for (string word:vect) {
        enc_word = decryption(word);
        enc_vect.push_back(enc_word);
    }
    vect.clear();
    for (string word:enc_vect) {
        vect.push_back(word);
    }
    return vect;
}
// function to make the string x in lower case
string All_Lower (string x){
    string word;
    for (int i =0 ; i< x.length();++i) {
        if (int(x[i]) >= 65 && int(x[i]) <= 90) {
            x[i] = int(x[i]) - 'A' + 'a';
            word += x[i];
        } else if (int(x[i]) >= 97 && int(x[i]) <= 121) {
            x[i] = x[i];
            word += x[i];
        }
        else {
            word += x[i];
        }
    }
    return word;
}
// function to make all the file in lower case --> 13
vector<string> lower_file(vector<string> words){
    vector<string> words_lower;
    for (string word:words) {
        words_lower.push_back(All_Lower(word));
    }
    words.clear();
    for (string word:words_lower) {
        words.push_back(word);
    }
    return words;
}
// function to capitalize the first letter in the word
string First_Upper(string word){
    string word_first;
    for (int i = 0; i < word.length(); ++i) {
        if(i == 0){
            word_first += toupper(word[i]);
        }
        else{
            word_first += tolower(word[i]);
        }
    }
    return word_first;
}
// function to make all file capitalize the first letter in any word --> 14
vector<string> first_upper_file(vector<string> words){
    vector<string> words_first;
    for (string word:words) {
        words_first.push_back(First_Upper(word));
    }
    words.clear();
    for (string word:words_first) {
        words.push_back(word);
    }
    return words;
}
// function to make the string x in upper case
string All_Upper (string x){
    string word;
    for (int i =0 ; i< x.length();++i) {
        if (int(x[i]) >= 65 && int(x[i]) <= 90) {
            x[i] = x[i];
            word += x[i];
        } else if (int(x[i]) >= 97 && int(x[i]) <= 121) {
            x[i] = int(x[i]) - 'a' + 'A';
            word += x[i];
        }
        else {
            word += x[i];
        }
    }
    return word;
}
// function to make the all file in upper case --> 12
vector<string> upper_file(vector<string> words){
    vector<string> words_upper;
    for (string word:words) {
        words_upper.push_back(All_Upper(word));
    }
    words.clear();
    for (string word:words_upper) {
        words.push_back(word);
    }
    return words;
}
// function to scearch for word if it found return true else return false --> 10
void word_search(vector<string> words){
    string search_word;
    int count = 0;
    cout << "please enter word to search for it : ";
    cin >> search_word;
    for (string word:words) {
        if(strstr((All_Lower(word)).c_str(), (All_Lower(search_word)).c_str())){
            cout << "Word was found in the file" << endl;
            break;
        }
        else{
            count += 1;
        }
    }
    if(count == words.size()){
        cout << "Word was not found in the file" << endl;
    }
}
void menu_text_editor(){
    cout << "1 -> Adding new text to the end of the file" << endl;
    cout << "2 -> Display the content of the file" << endl;
    cout << "3 -> Empty the file" << endl;
    cout << "4 -> Encrypt the file content" << endl;
    cout << "5 -> Decrypt the file content" << endl;
    cout << "6 -> Merge another file" << endl;
    cout << "7 -> Count the number of words in the file" << endl;
    cout << "8 -> Count the number of characters in the file" << endl;
    cout << "9 -> Count the number of lines in the file" << endl;
    cout << "10 -> Search for a word in the file" << endl;
    cout << "11 -> Count the number of times a word exists in the file" << endl;
    cout << "12 -> Turn the file content to upper case" << endl;
    cout << "13 -> Turn the file content to lower case" << endl;
    cout << "14 -> Turn file content to 1st caps (1st char of each word is capital)" << endl;
    cout << "s -> Save" << endl;
    cout << "0 -> Exit" << endl;
}
void take_response(){
    // this function make user input filename and if it does'nt exist it make a new one to him and return the filename
    string filename = if_file();
    // vector to put in it all words in the file and work on it
    vector<string> vect = make_file_vector(filename);
    // string to take response from user in it
    string response;
    // infinty loop end by user when he enter 0 to exit from the program, else it will continue to get a valid response from him
    while (true){
        menu_text_editor();
        cout << "what is your response : ";
        cin >> response;
        if (response == "0"){
            cout << "End of the program " << endl;
            break;
        }
        else if(response == "1"){
            vect = append_file(filename, vect);
        }
        else if(response == "2"){
            display_file(vect);
        }
        else if(response == "3"){
            vect = empty_vector(vect);
            cout << "file is empty" << endl;
        }
        else if(response == "4"){
            vect = encryption_file(vect);
            cout << "file is encrypted" << endl;
        }
        else if(response == "5"){
            vect = decryption_file(vect);
            cout << "file is decrypted" << endl;
        }
        else if(response == "6"){
            vect = merge_files(vect);
            cout << "the two files now is merged" << endl;
        }
        else if(response == "7"){
            cout << "number of words in this file is : " << num_words(vect) << endl;
        }
        else if(response == "8"){
            cout << "number of characters in this file is : " << num_char(vect) << endl;
        }
        else if(response == "9"){
            cout << "number of lines in this file is : " << num_lines(vect) << endl;
        }
        else if(response == "10"){
            word_search(vect);
        }
        else if(response == "11"){
            cout << "the number of times a word exists in the file is : " << num_times_word(vect) << endl;
        }
        else if (response == "12"){
            vect = upper_file(vect);
            cout << "file is all in upper case" << endl;
        }
        else if(response == "13"){
            vect = lower_file(vect);
            cout << "file is all in lower case" << endl;
        }
        else if(response == "14"){
            vect = first_upper_file(vect);
            cout << "all file content is first caps" << endl;
        }
        else if(response == "s"){
            make_vector_file(vect, filename);
        }
        else{
            cout << "please enter valid response "<< endl;
        }
    }
}
int main() {
    take_response();
    return 0;
}
