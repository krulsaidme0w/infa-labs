#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool f(string s){
    int length = s.length(), count = 0;
    char vowels[6] = {'a','e','i','o','u', 'y'};
    for (int i = 0; s[i] != '\0'; i++) { 
        char ch = s[i]; 
        for(int j = 0; j < 6; j++){ 
            if(tolower(ch) == vowels[j])
                count++;
        }
    } 
    if(count >= length - count)
        return 1;
    else
        return 0;
}

int main(){

    try {
        ifstream i("input.txt");
        ofstream o("output.txt");
        

        while(i){
            string s;
            i >> s;
            if(f(s)){
                o << s << ' ';
            }
        }
        
        
        o.close();
        i.close();
    }
    catch(const char* exception) {
        cout << "bad";
    }
}
