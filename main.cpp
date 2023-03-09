#include<iostream>
#include<fstream>
#include <cstring>
#include <string>
using namespace std;
void get_records(string owner){
    /*This function gets the records of a owner */
    //Checking if the OS is linux or Win
    #if __linux__
        system(("ls -l Records | grep  -i \""+owner+"\" >test.txt").c_str());//shell command to get all files with owner name
    #elif _WIN32
        system(("dir Records | findstr /ilc:\""+owner+"\" >test.txt").c_str());//cmd command to get all files with owner name
    #endif
    
    ifstream file_name;
    file_name.open("test.txt");
    string content("");
    string line(""); 
    while(getline(file_name,line)){
        content+=line.substr(line.find(owner)+owner.length()+1,line.find(".txt")-line.find(owner)-owner.length()-1)+"\n";
    }
    file_name.close();
    ofstream file_2;
    file_2.open("Owner_Record\\"+owner+".txt");
    file_2<<content;
    file_2.close();
}
void Refresh(){
    /*Refresh all logs*/
    ifstream file_name;
    file_name.open("users.txt");
    string content("");
    string line(""); 
    while(getline(file_name,line)){
        get_records(line);
    }
    //removing the temp test file
    #if __linux__
        system("rm test.txt");
    #elif _WIN32
        system("del test.txt");
    #endif
    
}
class record{
    private:
    string owner;
    string title;
    public:
    record(string owner_name){
        ofstream owner_log;
        owner_log.open("Owner_Record\\"+owner_name+".txt",ios::out | ios::app);
        owner=owner_name;
        cout<<"Enter the title\n";
        cin>>title;
        owner_log<<title<<endl;
        owner_log.close();
        ofstream file_name;
        file_name.open("Records\\"+owner_name+"_"+title+".txt");
        string line;
        while(1){
            getline(cin,line);
            if(line=="-1"){
                break;
            }
            file_name<<line<<endl;
        }
        file_name.close();
    }
    record(string owner_name,string title_name){
        owner=owner_name;
        title=title_name;
        ifstream owner_log;
        owner_log.open("Owner_Record\\"+owner+".txt");
        int found=0;
        string line;
        while(getline(owner_log,line)){
            if(title==line){
                found=1;
                break;
            }
        }
        owner_log.close();
        if(!found){
            cout<<"MEMO NOT FOUND\n";
        }
    }
    void read_from(){
        ifstream file_name;
        file_name.open("Records\\"+owner+"_"+title+".txt");
        string content;
        string line(""); 
        while(getline(file_name,line)){
            cout<<line<<endl;
        }
        file_name.close();
        line="";
    }
    void erase(){
        ofstream file_name;
        file_name.open("Records\\"+owner+"_"+title+".txt");
        file_name<<"";
        file_name.close();
    }
    void append(){
        ofstream file_name("Records\\"+owner+"_"+title+".txt",ios::out | ios::app);
        string line;
        while(1){
            getline(cin,line);
            if(line=="-1"){
                break;
            }
            file_name<<line<<endl;
        }
        file_name.close();
    }
    void rem(){
        string s="Records\\"+owner+"_"+title+".txt";
        int n=s.length();
        char cmd[n+1];
        strcpy(cmd, s.c_str());
        remove(cmd);
    }
};
class owner{
    private:
    string owner_name;
    public:
    owner(){
    }
    owner(string own){
        owner_name=own;
        ifstream owner_lst;
        owner_lst.open("users.txt");
        string line("");
        int found=0;
        while(getline(owner_lst,line)){
            if(own==line){
                found=1;
                break;
            }
        }
        owner_lst.close();
        if(!found){
            cout<<"User not found\n";
            cout<<"Creating new user\n";
            create_owner();
        }
    }
    void getmemos(){
        ifstream owner_log;
        owner_log.open("Owner_Record\\"+owner_name+".txt");
        string line("");
        while(getline(owner_log,line)){
            cout<<line<<endl;
        }
        owner_log.close();
    }
    void create_owner(){
        ofstream owner_lst("users.txt",ios::out | ios::app);
        owner_lst<<owner_name<<endl;
        owner_lst.close();
        ofstream owner_log;
        owner_log.open("Owner_Record\\"+owner_name+".txt");
        owner_log<<"";
        owner_log.close();
    }
};
void get_user(){
    ifstream owner_lst;
        owner_lst.open("users.txt");
        string line("");
        int found=0;
        while(getline(owner_lst,line)){
            cout<<line<<endl;
        }
}
int main(){
    int runner=1;
    int menu1;
    cout<<"________________"<<endl;
    cout<<"|               |"<<endl;
    cout<<"|    WELCOME    |"<<endl;
    cout<<"|_______________|"<<endl;
    Refresh();
    while(runner){
        cout<<" __________________"<<endl; 
        cout<<"|                  |"<<endl;
        cout<<"|1.List users      |"<<endl;
        cout<<"|2.Login           |"<<endl;
        cout<<"|3.Quit            |"<<endl;
        cout<<"|__________________|"<<endl; 
        cin>>menu1;
        switch(menu1){
            case 1:
                {cout<<" _______________"<<endl;
                cout<<"|               |"<<endl;  
                cout<<"| LIST OF USERS |"<<endl;  
                cout<<"|_______________|"<<endl;
                get_user();
                break;}
            case 2:
                {cout<<" ______________"<<endl;
                cout<<"|              |"<<endl;
                cout<<"|    LOGIN     |"<<endl;
                cout<<"|______________|"<<endl;
                cout<<"Username: ";
                string name;
                cin>>name;
                owner o1(name);
                cout<<"------------------"<<endl;
                cout<<"Welcome Back "<<name<<"!"<<endl;
                cout<<"------------------"<<endl;
                int menu2,run=1;
                while(run){
                    cout<<" _______________________________"<<endl; 
                    cout<<"|                               |"<<endl;
                    cout<<"|1.List Records                 |"<<endl;
                    cout<<"|2.Read a Memo                  |"<<endl;
                    cout<<"|3.Write a new Memo             |"<<endl;
                    cout<<"|4.Update a old memo            |"<<endl;
                    cout<<"|5.Clear a memo                 |"<<endl;
                    cout<<"|6.Delete a memo                |"<<endl;
                    cout<<"|7.Return to main menu          |"<<endl;
                    cout<<"|_______________________________|"<<endl; 
                    cin>>menu2;
                    switch(menu2){
                        case 1:
                            {cout<<" _______________"<<endl;
                            cout<<"|               |"<<endl;  
                            cout<<"| LIST OF MEMOS |"<<endl;  
                            cout<<"|_______________|"<<endl;
                            o1.getmemos();
                            break;
                        }
                        case 2:
                            {cout<<" _______________"<<endl;
                            cout<<"|               |"<<endl;  
                            cout<<"|   READ MEMO   |"<<endl;  
                            cout<<"|_______________|"<<endl;
                            cout<<"Which Memo DO You Want To Read: ";
                            string title;
                            cin>>title;
                            record r1(name,title);
                            r1.read_from();
                            break;
                        }
                        case 3:
                            {cout<<" _______________"<<endl;
                            cout<<"|               |"<<endl;  
                            cout<<"|   NEW   MEMO  |"<<endl;  
                            cout<<"|_______________|"<<endl;
                            record r1(name);
                            r1.read_from();
                            break;
                        }
                        case 4:
                            {cout<<" _______________"<<endl;
                            cout<<"|               |"<<endl;  
                            cout<<"|  UPDATE MEMO  |"<<endl;  
                            cout<<"|_______________|"<<endl;
                            cout<<"Which Memo DO You Want To Update: ";
                            string title;
                            cin>>title;
                            record r1(name,title);
                            r1.append();
                            break;
                        }
                        case 5:{
                            cout<<" _______________"<<endl;
                            cout<<"|               |"<<endl;  
                            cout<<"|  CLEAR  MEMO  |"<<endl;  
                            cout<<"|_______________|"<<endl;
                            cout<<"Which Memo DO You Want To Clear: ";
                            string title;
                            cin>>title;
                            record r1(name,title);
                            r1.erase();
                            break;
                        }
                        case 6:{
                            cout<<" _______________"<<endl;
                            cout<<"|               |"<<endl;  
                            cout<<"|  DELETE MEMO  |"<<endl;  
                            cout<<"|_______________|"<<endl;
                            cout<<"Which Memo DO You Want To Delete: ";
                            string title;
                            cin>>title;
                            record r1(name,title);
                            r1.rem();
                            Refresh();
                            break;
                        }
                        case 7:{
                            run=0;
                            break;
                        }
                        default:{
                            run=0;
                            cout<<"INVALID\n";
                            break;
                        }
                    }
                }
                break;}
            case 3:
                {runner=0;
                break;}
            default:
                {
                cout<<"INVALID\n";
                runner=0;
                break;}
        }
    }
    return 0;
}