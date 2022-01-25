#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream source(filename);
    string input;
    int a,b,c;
    char name[100];
    while(getline(source, input)){
        sscanf(input.c_str(),"%[^:]: %d %d %d",name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(scores.back()));
    }
}

void getCommand(string &command, string &key){
    string input;    
    cout << "Please input your command: ";
    getline(cin, input);
    cin.clear();

    input[input.find(" ")] = ':';
    char c[100], k[100];
    sscanf(input.c_str(),"%[^:]:%[^:]",c,k);

    command = c;
    key = k;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    for(unsigned int i = 0; i < names.size(); i++){
        if(key == toUpperStr(names[i])){
            cout << "---------------------------------" << endl;
            printf("%s's score = %d\n",names[i].c_str(),scores[i]);
            printf("%s's grade = %c\n",names[i].c_str(),grades[i]);
            cout << "---------------------------------" << endl;
            return;
        }
    }
    cout << "---------------------------------" << endl;
    cout << "Cannot found.\n";
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = 0;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < names.size(); i++){
        if(*(key.c_str()) == grades[i]){
            printf("%s (%d)\n",names[i].c_str(),scores[i]);
            found = 1;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
