#include <cstdio>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool isnumeric(string s){
    int start = 0;
    if (s[start] == '-') start=1;

    for(int i=start; i<s.size(); i++)
        if(!isdigit(s[i])) return false;
    
    return true; 
}

int main(){
    

    map<char, string> schema;
    schema['b'] = "false";//bool
    schema['i'] = "0";//int
    schema['s'] = "";//string
    schema['n'] = "0";//int
    schema['f'] = "false";//bool

    string args;
    cout << "Introduce args string: "<<endl;
    getline (cin, args);

    vector<string> tokens;

    int start, end = -1;
    do {
        start = end + 1;
        end = args.find(" ", start);
        tokens.push_back(args.substr(start, end - start));
    } while (end != -1);

    bool needFlag = true;
    int type;//1 for number, 2 for string
    char flag;
    for (int i=0; i<tokens.size(); i++){
        cout <<"token is "<< tokens[i] << endl;
        //This indicates we have a flag (starts with -, not a number and size 1)
        if(needFlag && tokens[i][0] == '-' && !isnumeric(tokens[i]) && tokens[i].size()==2){
            flag = tokens[i][1];
            switch (flag){
                case 'b': case 'f':
                    cout << "ITS A VALID FLAG"<<endl;
                    schema[flag] = "true";
                    break;
                case 'i': case 'n':
                    type = 2;
                    needFlag = false;
                    cout << "ITS A VALID FLAG"<<endl;
                    break;
                case 's':
                    type = 3;
                    needFlag = false;
                    cout << "ITS A VALID FLAG"<<endl;
                    break;
                default: 
                    cout << "UNKNOWN FLAG " << tokens[i][1]<<endl;
            }
        }
        else if (!needFlag){
            needFlag = true;
            switch (type){
                case 1:
                    if(isnumeric(tokens[i]))
                        schema[flag] = tokens[i];
                    else
                        cout << "flag -" <<flag << " expects numeric value"<<endl; 
                break;
                case 2:
                    schema[flag] = tokens[i];
                break;
            }
        }
        else{
            cout <<"FLAG MUST BEGIN WITH a - and be one char long"<<endl;
        }
    }

    map<char, string> :: iterator it;
    for(it = schema.begin(); it != schema.end(); it++){
        cout << "flag " << it->first << " value " << it->second << endl;
    }
    return 0;
}