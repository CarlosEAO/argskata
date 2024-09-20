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
    public:
        enum Type{INT, STRING, BOOL};
    private:
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
    
    public:
        struct Flag {
            char identifier; // The character identifier (e.g., 'i')
            Type type;      // The type, but we will use it internally
        };
        void addBooleanFlag(char identifier){
            addFlag(identifier, BOOL);
        }
        void addIntFlag(char identifier){
            addFlag(identifier, INT);
        }
        void addStringFlag(char identifier){
            addFlag(identifier, STRING);
        }
        Parser(vector<pair<int, Type>> flags){
            for( auto flag:flags){
                addFlag(flag.first, flag.second);
            }
        }
        void getArgs(){
                cout << "Introduce args string: "<<endl;
                getline (cin, this->args);
        }
        void parseArgs(string args){
            vector<string> tokens = splitSpace(args);
            bool expectingFlag = true;
            Type type;
            char flag;
            for (int i=0; i<tokens.size(); i++){
                cout <<"token is "<< tokens[i] << endl;
                //This indicates we have a flag (starts with -, not a number and size 1)
                if(expectingFlag && tokens[i][0] == '-' && !isnumeric(tokens[i]) && tokens[i].size()==2){
                    flag = tokens[i][1];
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
                        cout << "UNKNOWN FLAG " << tokens[i][1]<<endl;
                    }
                            
                }
                else if (!expectingFlag){
                    expectingFlag = true;
                    switch (type){
                        case INT:
                            if(isnumeric(tokens[i]))
                                this->intFlags[flag] = stoi(tokens[i]);
                            else
                                cout << "flag -" <<flag << " expects numeric value"<<endl; 
                            break;
                        case STRING:
                            stringFlags[flag] = tokens[i];
                            break;
                    }
                }
                else{
                    cout <<"FLAG MUST BEGIN WITH a - and be one char long"<<endl;
                }
            }
        }

        void parseArgs(){
            this->parseArgs(args);
        }

        void printArgs(){
            cout<<"Boolean Flags: "<<endl;
            for(auto flag:booleanFlags){
                cout << "flag " << flag.first << " value " << flag.second << endl;
            }
            cout<<"Integer Flags: "<<endl;
            for(auto flag:intFlags){
                cout << "flag " << flag.first << " value " << flag.second << endl;
            }
            cout<<"String Flags: "<<endl;
            for(auto flag:stringFlags){
                cout << "flag " << flag.first << " value " << flag.second << endl;
            }
        }
};

int main(){
    Parser parser({{'i', Parser::INT}});
    parser.addIntFlag('n');
    parser.addBooleanFlag('b');
    parser.addBooleanFlag('f');
    parser.addStringFlag('s');
    parser.addStringFlag('c');

    parser.getArgs();
    parser.parseArgs();
    parser.printArgs();

    return 0;
}