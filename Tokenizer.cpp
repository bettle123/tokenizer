/*
   This code can be compiled and run ok.
    Goal: The goal of this part of the project is to
    implement a Tokenizer for the language Core.
    (1~11) Reserved words (11 reserved words):
        program, begin, end, int, if, then,
        else, while, loop, read, write
    (12~30) Special symbols (19 special symbols):
        ; , = ! [ ] && || ( ) + - * != == < > <= >=
    (31) Integers (unsigned) (max size of 8 digits).
        ex. 25;
    (32) Identifiers:
        ex. X,Y,z;
    (33) for end-of-life
        EOF
   usage (how to run):
     g++ -o test Tokenizer.cpp

   input file:
     coreProgram.txt

   output files:
     none

   compile (how to compile):
     g++ -o Tokenizer Tokenizer.cpp

   coded by Su, Ming Yi, OSU_ID: su.672, email: su.672@osu.edu
   date: 2017.10.04
   LinkedList is learnt from website:
   https://github.com/alrightchiu/SecondRound/blob/master/content/Algorithms%20and%20Data%20Structures/BasicDataStructures/ExampleCode/LinkedList.cpp

*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>     /* atoi */
using namespace std;
// List records each word meaning

class LinkedList;    // 為了將class LinkedList設成class ListNode的friend,
                     // 需要先宣告
class ListNode{
private:
    int data;
    ListNode *next;
public:
    ListNode():data(0),next(0){};
    ListNode(int a):data(a),next(0){};

    friend class LinkedList;
};

class LinkedList{
private:
    // int size;                // size是用來記錄Linked list的長度, 非必要
    ListNode *first;            // list的第一個node
public:
    LinkedList():first(0){};
    void PrintList();           // 印出list的所有資料
    void Push_front(int x);     // 在list的開頭新增node
    void Push_back(int x);      // 在list的尾巴新增node
    void Delete(int x);         // 刪除list中的 int x
    void Clear();               // 把整串list刪除
    void Reverse();             // 將list反轉: 7->3->14 => 14->3->7
};

// PrintList()的功能就是把Linked list中的所有資料依序印出。
void LinkedList::PrintList(){

    if (first == 0) {                      // 如果first node指向NULL, 表示list沒有資料
        cout << "List is empty.\n";
        return;
    }

    ListNode *current = first;             // 用pointer *current在list中移動
    while (current != 0) {                 // Traversal
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Push_back()的功能是在Linked list的尾巴新增資料
void LinkedList::Push_back(int x){

    ListNode *newNode = new ListNode(x);   // 配置新的記憶體

    if (first == 0) {                      // 若list沒有node, 令newNode為first
        first = newNode;
        return;
    }

    ListNode *current = first;
    while (current->next != 0) {           // Traversal
        current = current->next;
    }
    current->next = newNode;               // 將newNode接在list的尾巴
}

void token_check_int_id (string &x, LinkedList&mytokenizer,int &number){
    char uppercase_letter[26]={
        'A','B','C','D','E',
        'F','G','H','I','J',
        'K','L','M','N','O',
        'P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };
    // Integers
    char *fff;
    int i,j;
    fff= new char [x.size()];
    for(i = 0; i < x.size(); i++) {
                fff[i]=x[i];
    }
    int value =atoi (fff);
    if(value >0||value<0){
                mytokenizer.Push_back(31);number =1;
    }
    if(x=="0"){
                mytokenizer.Push_back(31);number =1;
    }
    //Identifiers
    int key=0,letter_value=0,key2=0;
    for (i=0;i<26;i++){
        if(fff[0]==uppercase_letter[i]){
        key2=1;
        }
        for (j=0; j<x.size();j++){
                if(fff[j]==uppercase_letter[i]){
                    key++;
                }
        }
    }
    for(j=0;j<x.size();j++){
    letter_value = fff[j]-'0';
        if(letter_value>=0&&letter_value<10){
                    key++;
        }
    }


    if (key==x.size()&&(key2==1)){
        mytokenizer.Push_back(32);number =1;
    }
    if ((key!=x.size())&&(number==0)){
      //  cout <<x<<" is illegal."<<endl;
    }
}


int token_check(string &x, LinkedList&mytokenizer,int &number){
    string token[30]= {
        "program", "begin", "end", "int",
        "if", "then", "else", "while", "loop",
        "read","write",
        ";", ",", "=", "!", "[", "]", "&&",
        "||", "(", ")", "+", "-", "*", "!=",
        "==", "<", ">", "<=", ">="
    };
    int token_length[30]={0};
    for(int i =0;i<30;i++){
        token_length[i]= token[i].size();
    }
    int i=0,j=0;
            // number is the controller that my identifiers won't
            // bother my other staff
            for(i =0;i<30;i++){
                if(x==token[i]){
                    mytokenizer.Push_back(i+1);number =1;
                }
            }
    token_check_int_id (x,mytokenizer,number);
    //solve the problem that "ABC;" is illegal
    // it should be "ABC" and ";"
    string x_part1,x_part2;
    int k1=0,k2=0,part1=0,part2=0;
            int x_length= x.size();
            if(number==0){
                    if(x_length>1){
                        for(i = 1;i<x_length;i++){
                            x_part1 = x_part1.assign (x,0,i);
                            x_part2 = x_part2.assign (x,i,x_length-i);
                            int part1=0,part2=0,k1,k2;
                            for(j=0;j<30;j++){
                                if(x_part1==token[j]){
                                    part1=1;
                                    k1 = j+1;
                                }
                                if(x_part2==token[j]){
                                    part2=1;
                                    k2 = j+1;
                                }
                            }
                            if ((part1==1)&&(part2==1)){
                                    mytokenizer.Push_back(k1);
                                    mytokenizer.Push_back(k2);
                                    number =1;
                            }
                        }
                    }
            }
        if((number==0)&&(x_length>1)&&(part1+part2<2)){
            string x_part,x_rest,x_rest2;
            for(i = 0;i<x_length;i++){
                for (j=0;j<30;j++){
                if(x_length>token_length[j]){
                x_part = x_part.assign (x, i,token_length[j]);
                    if(x_part==token[j]){
                        x_rest = x_rest.assign (x, token_length[j],x_length-token_length[j]);
                        if(i==0){
                        mytokenizer.Push_back(j+1);
                        //token_check_int_id (x_rest,mytokenizer,number);
                        token_check(x_rest,mytokenizer,number);
                        }
                        if(i!=0){
                        x_rest = x_rest.assign (x, 0,i);
                        //token_check_int_id(x_rest,mytokenizer,number);
                        token_check(x_rest,mytokenizer,number);
                        mytokenizer.Push_back(j+1);
                        if(x_length>(i+token_length[j]))
                        {
                            x_rest2 = x_rest2.assign (x,i+token_length[j],x_length);
                            token_check(x_rest2,mytokenizer,number);
                            break;
                        }
                        }
                    }
                }
                }
            }
        }
    return(number);
}

int main(int argc, char* argv[]){
    //Tokenizer mytokenizer;
    // initialize the tokenizer object
    LinkedList mytokenizer;     // 建立LinkedList的object
    char uppercase_letter[26]={
        'A','B','C','D','E',
        'F','G','H','I','J',
        'K','L','M','N','O',
        'P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };
    cout <<"Please input the test file."<<'\n'
         <<"ex. coreProgram.txt"<<endl;
    string filename;
    cin >>filename;
    char *fff;
    fff= new char [filename.size()];
    for(int i = 0; i < filename.size(); i++) {
        fff[i]=filename[i];
    }
    cout <<"The test filename:  "<<filename<<endl;
    ifstream file;
    file.open( filename.c_str() );
    string x;
    cout <<"Output:"<<endl;
    while (file >>x){
            // Reserved words
            int number =0;
            number = token_check(x, mytokenizer, number);
    }
    file.close();
    // EOF (for end-of-file)
    mytokenizer.Push_back(33);
    mytokenizer.PrintList();
    return 0;
}
