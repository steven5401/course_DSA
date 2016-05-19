#include <iostream>
#include <string> 
#include <algorithm>
#include <string> 
#include <cstdio>
#include <cstring>
#include <fstream>
#include <unordered_set>
#include <set>
using namespace std;
typedef unordered_set<string> string_map;
string candidate = "abcdefghijklmnopqrstuvwxyz";

inline void ed(string s, string_map sm, set<string>& cw, int level) {
    int size = s.size();
    for (int i = 0; i != size; i++) {//substitute
        for (int j = 0; j != 26; j++) {
            string temp = s;
            temp.replace(i, 1, candidate.substr(j, 1));
            if (sm.count(temp)) cw.insert(temp);
            if (level != 1) {//ed(temp, sm, cw, level - 1);
                int size2 = temp.size();
                for (int i = 0; i != size2; i++) {//substitute
                    for (int j = 0; j != 26; j++) {
                        string temp2 = temp;
                        temp2.replace(i, 1, candidate.substr(j, 1));
                        if (sm.count(temp2)) cw.insert(temp2);
                    }
                }
                for (int i = 0; i != size2; i++) {//delete
                    string temp2 = temp;
                    temp2.erase(i, 1);
                    if (sm.count(temp2)) cw.insert(temp2);
                }
                for (int i = 0; i <= size2; i++) {//insert
                    for (int j = 0; j != 26; j++) {
                        string temp2 = temp;           
                        temp2.insert(i, candidate.substr(j, 1));
                        if (sm.count(temp2)) cw.insert(temp2);
                    }
                }
                for (int i = 0; i != size2 - 1; i++) {//transpose
                    string temp2 = temp;
                    char t;
                    t = temp2[i];
                    temp2[i] = temp2[i + 1];
                    temp2[i + 1] = t;
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
        }
    }
    for (int i = 0; i != size; i++) {//delete
        string temp = s;
        temp.erase(i, 1);
        if (sm.count(temp)) cw.insert(temp);
        if (level != 1) {//ed(temp, sm, cw, level - 1);
            int size2 = temp.size();
            for (int i = 0; i != size2; i++) {//substitute
                for (int j = 0; j != 26; j++) {
                    string temp2 = temp;
                    temp2.replace(i, 1, candidate.substr(j, 1));
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
            for (int i = 0; i != size2; i++) {//delete
                string temp2 = temp;
                temp2.erase(i, 1);
                if (sm.count(temp2)) cw.insert(temp2);
            }
            for (int i = 0; i <= size2; i++) {//insert
                for (int j = 0; j != 26; j++) {
                    string temp2 = temp;
                    temp2.insert(i, candidate.substr(j, 1));
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
            for (int i = 0; i != size2 - 1; i++) {//transpose
                string temp2 = temp;
                char t;
                t = temp2[i];
                temp2[i] = temp2[i + 1];
                temp2[i + 1] = t;
                if (sm.count(temp2)) cw.insert(temp2);
            }
        }
    }
    for (int i = 0; i <= size; i++) {//insert
        for (int j = 0; j != 26; j++) {
            string temp = s;           
            temp.insert(i, candidate.substr(j, 1));
            if (sm.count(temp)) cw.insert(temp);
            if (level != 1) {//ed(temp, sm, cw, level - 1);
                int size2 = temp.size();
                for (int i = 0; i != size2; i++) {//substitute
                    for (int j = 0; j != 26; j++) {
                        string temp2 = temp;
                        temp2.replace(i, 1, candidate.substr(j, 1));
                        if (sm.count(temp2)) cw.insert(temp2);
                    }
                }
                for (int i = 0; i != size2; i++) {//delete
                    string temp2 = temp;
                    temp2.erase(i, 1);
                    if (sm.count(temp2)) cw.insert(temp2);
                }
                for (int i = 0; i <= size2; i++) {//insert
                    for (int j = 0; j != 26; j++) {
                        string temp2 = temp;           
                        temp2.insert(i, candidate.substr(j, 1));
                        if (sm.count(temp2)) cw.insert(temp2);
                    }
                }
                for (int i = 0; i != size2 - 1; i++) {//transpose
                    string temp2 = temp;
                    char t;
                    t = temp2[i];
                    temp2[i] = temp2[i + 1];
                    temp2[i + 1] = t;
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
        }
    }
    for (int i = 0; i != size - 1; i++) {//transpose
        string temp = s;
        char t;
        t = temp[i];
        temp[i] = temp[i + 1];
        temp[i + 1] = t;
        if (sm.count(temp)) cw.insert(temp);
        if (level != 1) {//ed(temp, sm, cw, level - 1);
            int size2 = temp.size();
            for (int i = 0; i != size2; i++) {//substitute
                for (int j = 0; j != 26; j++) {
                    string temp2 = temp;
                    temp2.replace(i, 1, candidate.substr(j, 1));
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
            for (int i = 0; i != size2; i++) {//delete
                string temp2 = temp;
                temp2.erase(i, 1);
                if (sm.count(temp2)) cw.insert(temp2);
            }
            for (int i = 0; i <= size2; i++) {//insert
                for (int j = 0; j != 26; j++) {
                    string temp2 = temp;           
                    temp2.insert(i, candidate.substr(j, 1));
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
            for (int i = 0; i != size2 - 1; i++) {//transpose
                string temp2 = temp;
                char t;
                t = temp2[i];
                temp2[i] = temp2[i + 1];
                temp2[i + 1] = t;
                if (sm.count(temp2)) cw.insert(temp2);
            }
        }
    }
   
}

int main() {
    ifstream inFile;
    inFile.open("./cmudict-0.7b.txt");
    //inFile.open("/tmp2/dsa2016_hw5/cmudict-0.7b");
    string dictionaryWord;
    char inWord[100], trash[100], line[300];
    string_map sm;
    while (true) {
        inFile.getline(line, 300);
        if (line[0] == ';' && line[1] == ';' && line[2] == ';') continue;
        if (inFile.eof()) break;
        dictionaryWord = strtok(line, " ");
        transform(dictionaryWord.begin(), dictionaryWord.end(), dictionaryWord.begin(), ::tolower);
        //printf("%s\n", dictionaryWord.c_str());
        sm.insert(dictionaryWord);
    }
    inFile.close();
    //cerr << "start cin\n";
    //ed("1234", 1);
    int i = 1;
    while (scanf("%s\t%s\t%s\t%s", inWord, trash, trash, trash) == 4) {
        //cerr << i << endl;
        //i++;
        set<string> correctWord;
        string iw = inWord;
        printf("%s ==>", inWord);
        if (sm.count(inWord)) {
            printf(" OK\n");
            continue;
        }
        ed(iw, sm, correctWord, 2);
        if (correctWord.size() == 0) {
            printf(" NONE\n");
        } else {
            for (auto it = correctWord.begin(); it != correctWord.end(); it++) {
                printf(" %s", it->c_str());
            }
            printf("\n");
        }
    }
}
