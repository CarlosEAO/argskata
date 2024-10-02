#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool isnumeric(string s){
    int start = 0;
    if (s[start] == '-') start=1;

    for(int i=start; i<s.size(); i++)
        if(!isdigit(s[i])) return false;
    
    return true; 
}
vector<string> splitSpace(string s){
    vector<string> tokens;
    int start, end = -1;
    do {
        start = end + 1;
        end = s.find(" ", start);
        tokens.push_back(s.substr(start, end - start));
    } while (end != -1);
    return tokens;
}
class Parser{        
    private:
        enum Type{INT, STRING, BOOL};
        string args;
        unordered_map<char, Type> schema;
        vector<string> tokens;

        unordered_map<char, bool> booleanFlags;
        unordered_map<char, int> intFlags;
        unordered_map<char, string> stringFlags;

        string typeAsString(Type type){
            string typeString;
            switch (type){
                case BOOL:
                    typeString = "boolean";
                    break;
                case INT:
                    typeString = "int";
                    break;
                case STRING:
                    typeString = "string";
                    break;
                default:
                    typeString =  "UNKNOWN";
                    break;
            }
            return typeString;
        }

        void addFlag(char identifier, Type type){
            if(schema.find(identifier)!=schema.end()){
                cout << "FLAG "<< identifier << " is already in the schema as a "<< typeAsString(schema[identifier]) <<" flag"<<endl;
            }
            else{
                switch (type){
                    case INT:
                        schema[identifier] = INT;
                        intFlags[identifier] = 0;
                        break;
                    case STRING:
                        schema[identifier] = STRING;
                        stringFlags[identifier] = "";
                        break;
                    case BOOL:
                        schema[identifier] = BOOL;
                        booleanFlags[identifier] = false;
                        break;
                }
            }
        }
        template <typename T> void printFlags(T flags){
            for(auto flag:flags){
                cout << "flag " << flag.first << " value " << flag.second << endl;
            }
        }
        void printBooleanFlags(){
            printFlags(booleanFlags);
        }
        void printIntFlags(){
            printFlags(intFlags);
        }
        void printStringFlags(){
            printFlags(stringFlags);
        }
    
    public:
        Parser(){}
        void addBooleanFlag(char identifier){
            addFlag(identifier, BOOL);
        }
        void addIntFlag(char identifier){
            addFlag(identifier, INT);
        }
        void addStringFlag(char identifier){
            addFlag(identifier, STRING);
        }
        
        void getArgs(){
                cout << "Introduce args string: "<<endl;
                getline (cin, this->args);
        }
        void parseArgs(){
            vector<string> tokens = splitSpace(args);
            bool expectingFlag = true;
            Type type;
            char flag;
            for (auto token:tokens){
                cout <<"token is "<< token << endl;
                //This indicates we have a flag (starts with -, not a number and size 1)
                if(expectingFlag && token[0] == '-' && !isnumeric(token) && token.size()==2){
                    flag = token[1];
                    if(booleanFlags.count(flag)){
                        cout << "ITS A VALID FLAG"<<endl;
                        this->booleanFlags[flag] = true;
                    }
                    else if(intFlags.count(flag)){
                        type = INT;
                        expectingFlag = false;
                        cout << "ITS A VALID FLAG"<<endl;
                    }
                    else if(stringFlags.count(flag)){
                        type = STRING;
                        expectingFlag = false;
                        cout << "ITS A VALID FLAG"<<endl;
                    }
                    else{
                        cout << "UNKNOWN FLAG " << token[1]<<endl;
                    }
                            
                }
                else if (!expectingFlag){
                    expectingFlag = true;
                    switch (type){
                        case INT:
                            if(isnumeric(token))
                                this->intFlags[flag] = stoi(token);
                            else
                                cout << "flag -" <<flag << " expects numeric value"<<endl; 
                            break;
                        case STRING:
                            stringFlags[flag] = token;
                            break;
                    }
                }
                else{
                    cout <<"FLAG MUST BEGIN WITH a - and be one char long"<<endl;
                }
            }
        }

        void printFlagValues(){   
            cout<<"BOOLEAN Flags: "<<endl;
            printBooleanFlags();
            cout<<"INTEGER Flags: "<<endl;
            printIntFlags();
            cout<<"STRING Flags: "<<endl;
            printStringFlags();
        }
};

int main(){
    Parser parser;
    parser.addIntFlag('i');
    parser.addIntFlag('n');
    parser.addBooleanFlag('b');
    parser.addBooleanFlag('f');
    parser.addStringFlag('s');
    parser.addStringFlag('c');

    parser.getArgs();
    parser.parseArgs();
    parser.printFlagValues();

    return 0;
}