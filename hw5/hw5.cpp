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
//string candidate = "abcdefghijklmnopqrstuvwxyz";

inline void ed(string s, string_map sm, set<string>& cw, int level) {
    int size = s.size();
    for (int i = 0; i != size; i++) {//substitute
        for (char j = 'a'; j <= 'z'; j++) {
            string temp = s;
            temp.replace(i, 1, &j, 1);
            if (sm.count(temp)) cw.insert(temp);
            if (level != 1) {//ed(temp, sm, cw, level - 1);
                int size2 = temp.size();
                for (int i = 0; i != size2; i++) {//substitute
                    for (char j = 'a'; j <= 'z'; j++) {
                        string temp2 = temp;
                        temp2.replace(i, 1, &j, 1);
                        if (sm.count(temp2)) cw.insert(temp2);
                    }
                }
                for (int i = 0; i != size2; i++) {//delete
                    string temp2 = temp;
                    temp2.erase(i, 1);
                    if (sm.count(temp2)) cw.insert(temp2);
                }
                for (int i = 0; i <= size2; i++) {//insert
                    for (char j = 'a'; j <= 'z'; j++) {
                        string temp2 = temp;           
                        temp2.insert(temp2.begin() + i, j);
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
                for (char j = 'a'; j <= 'z'; j++) {
                    string temp2 = temp;
                    temp2.replace(i, 1, &j, 1);
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
            for (int i = 0; i != size2; i++) {//delete
                string temp2 = temp;
                temp2.erase(i, 1);
                if (sm.count(temp2)) cw.insert(temp2);
            }
            for (int i = 0; i <= size2; i++) {//insert
                for (int j = 'a'; j <= 'z'; j++) {
                    string temp2 = temp;           
                    temp2.insert(temp2.begin() + i, j);
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
        for (char j = 'a'; j <= 'z'; j++) {
            string temp = s;           
            temp.insert(temp.begin() + i, j);
            if (sm.count(temp)) cw.insert(temp);
            if (level != 1) {//ed(temp, sm, cw, level - 1);
                int size2 = temp.size();
                for (int i = 0; i != size2; i++) {//substitute
                    for (char j = 'a'; j <= 'z'; j++) {
                        string temp2 = temp;
                        temp2.replace(i, 1, &j, 1);
                        if (sm.count(temp2)) cw.insert(temp2);
                    }
                }
                for (int i = 0; i != size2; i++) {//delete
                    string temp2 = temp;
                    temp2.erase(i, 1);
                    if (sm.count(temp2)) cw.insert(temp2);
                }
                for (int i = 0; i <= size2; i++) {//insert
                    for (char j = 'a'; j <= 'z'; j++) {
                        string temp2 = temp;           
                        temp2.insert(temp2.begin() + i, j);
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
                for (char j = 'a'; j <= 'z'; j++) {
                    string temp2 = temp;
                    temp2.replace(i, 1, &j, 1);
                    if (sm.count(temp2)) cw.insert(temp2);
                }
            }
            for (int i = 0; i != size2; i++) {//delete
                string temp2 = temp;
                temp2.erase(i, 1);
                if (sm.count(temp2)) cw.insert(temp2);
            }
            for (int i = 0; i <= size2; i++) {//insert
                for (char j = 'a'; j <= 'z'; j++) {
                    string temp2 = temp;           
                    temp2.insert(temp2.begin() + i, j);
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
    //inFile.open("./cmudict-0.7b.txt");
    inFile.open("/tmp2/dsa2016_hw5/cmudict-0.7b");
    string dictionaryWord;
    char trash[100], line[300], query[300];
    string_map sm;
    sm.rehash(299087);
    while (true) {
        inFile.getline(line, 300);
        if (line[0] == ';' && line[1] == ';' && line[2] == ';') continue;
        if (inFile.eof()) break;
        dictionaryWord = strtok(line, " ");
        transform(dictionaryWord.begin(), dictionaryWord.end(), dictionaryWord.begin(), ::tolower);
        sm.insert(dictionaryWord);
    }
    inFile.close();
    //int i = 1;
    while (fgets(query, 300, stdin)) {
        //cerr << i << endl;
        //i++;
        set<string> correctWord;
        string iw = strtok(query, "\n");
        printf("%s ==>", iw.c_str());
        if (sm.count(iw)) {
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