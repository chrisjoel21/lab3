#include <iostream>
#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
using namespace std;
#include <stack>


int prec(char c) {
  if (c == '/' ||  c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}

string getPostfix(string s) {
  stack<char> st;
  string postfix;
 
  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      postfix += s[i];

    else if (s[i] == '(')
      st.push('(');

    else if (s[i] == ')') {
      while (!st.empty() && st.top() != '(') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }


    else {
      while (!st.empty() && prec(s[i]) <= prec(st.top())) {
          postfix += st.top();
          st.pop();
      }
      st.push(s[i]);
    }
  

  }
  while (!st.empty()) {
    postfix += st.top();
    st.pop();
  }
 
  return postfix;
}

int evaluatePostfix(string s) {
  stack<int> st;

  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      st.push(s[i] - '0');
    else {
      int val1 = st.top(); st.pop();
      int val2 = st.top(); st.pop();
      switch (s[i]) {
        case '+': st.push(val2 + val1); break;
        case '-': st.push(val2 - val1); break;
        case '*': st.push(val2 * val1); break;
        case '/': st.push(val2 / val1); break;
      }
    }
  }
  return st.top();
}
/*string applyOp(int dig2, char op, int dig1){
  if(op == '^'){
    return to_string(pow(dig2,dig1));
  }else if(op == '*'){
    return to_string(dig2*dig1);
  }else if(op == '/'){
    return to_string(dig2/dig1);
  }else if(op == '+'){
    return to_string(dig2+dig1);
  }else if(op == '-'){
    return to_string(dig2-dig1);
  }else{
    return "-1"; 
  }
}
int evaluatePostfix(string str){
  stack<string> s;
  int solution;
  for(int i =0; i < str.length();i++){
    if(isdigit(str[i])){
      string c="";
      c+=str[i];
      s.push(c);
    }else{
      string dig1 = s.top();
      s.pop();
      string dig2 = s.top();
      s.pop();

      s.push(applyOp(stoi(dig2), str[i],stoi(dig1)));
    }
  }
  solution  =stoi(s.top());
  return solution;
}*/

int main(int argc, char *argv[])
{
    // *** You need to open files using argumentmanager when submit your
    // assignment ***
    ArgumentManager am(argc, argv);
    //ifstream input(am.get("input"));
    //ofstream out(am.get("output"));

    // *** Use this if you need to test each input individually, but you need to
    // change back to using argumentmanager when you submit the assignment ***
   ifstream input("input1.txt");
    ofstream out("output1.txt");

    string line;
           while(getline(input, line)){
            line.erase(remove(line.begin(),line.end(), '\n'),line.end());
            line.erase(remove(line.begin(),line.end(), '\r'),line.end());
            line.erase(remove(line.begin(),line.end(), ' '),line.end());
              //cout << line<<endl;
              int endind = line.find('=');
              bool front = false;
              char finalop;
              int RHS = stoi(line.substr(endind+1,line.size()-(endind+1)));
              string LHS;
              //cout <<"RHS:" <<RHS <<endl;
              //cout << "endindex:" << endind <<endl;
              if(line.find('x')==0){
                front = true;
                finalop= line[line.find('x')+1];
                //cout<< "LastOp:" << finalop<< endl;
                LHS = line.substr(2,((endind))-2);      
                //cout<< "LHS:" << LHS<< endl;
              }else if(line.find('x')==(endind-1)){
                front = false;
                finalop= line[line.find('x')-1];
                //cout<< "LastOp:" << finalop<< endl;
                LHS = line.substr(0,(endind-2));
                //cout<< "LHS:" << LHS <<endl;
              }              
                double x = 0;
                string postfix = getPostfix(LHS);
                cout << postfix << endl;
                int result = evaluatePostfix(postfix);
                cout<< result << endl;

                if (finalop == '+')
                    x = (double)RHS - (double)result;
                else if (finalop == '-') {
                    if (front)
                    x = (double)RHS + (double)result;
                    else
                    x = result - RHS;
                }
                else if (finalop == '/')
                    if (front)
                    x = (double)RHS * (double)result;
                    else
                    x = (double)result / (double)RHS;
                else {
                    x = (double)RHS / (double)result;
                }

                out <<fixed <<setprecision(2)<<x<<endl;

                return 0;
           }    
}