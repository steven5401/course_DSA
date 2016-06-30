#include <iostream>
#include <string> 
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

string prep[20] = {"of", "to", "in", "for", "with", "on", "at", "by", 
                   "from", "up", "about", "than", "after", "before", 
                   "down", "between", "under", "since", "without", "near"};
unordered_map<string, int> dict[4];
vector<pair<int, string>> candidate;

void editA (int querySize, string* queryArray, string query) {
    if (querySize > 5) {
        return;
    } else if (querySize == 5) {
        auto it = dict[3].find(query);
        if (it != dict[3].end()) {
            candidate.push_back(make_pair(it->second, it->first));
        }
    } else if (querySize == 4) {
        auto it = dict[querySize - 2].find(query);
        if (it != dict[querySize - 2].end()) {
            candidate.push_back(make_pair(it->second, it->first));
        }
        for (int i = 0; i != 20; i++) {
            for (int j = 0; j != querySize + 1; j++) {
                string temp = "";
                for (int k = 0; k != j; k++) {
                    temp += queryArray[k];
                    temp += " ";
                }
                temp += prep[i];
                if (j != querySize) temp += " ";
                for (int k = j; k != querySize; k++) {
                    temp += queryArray[k];
                    if (k != querySize - 1) temp += " ";
                }
                auto it = dict[querySize - 1].find(temp);
                if (it != dict[querySize - 1].end()) {
                    candidate.push_back(make_pair(it->second, it->first));
                }
            }
        }
    } else {
        if (querySize >= 2) {
            auto it = dict[querySize - 2].find(query);
            if (it != dict[querySize - 2].end()) {
                candidate.push_back(make_pair(it->second, it->first));
            }
        }
        if (querySize < 1) return;
        for (int i = 0; i != 20; i++) {
            for (int j = 0; j != querySize + 1; j++) {
                string temp = "";
                string tempArray[querySize + 1];
                for (int k = 0; k != j; k++) {
                    temp += queryArray[k];
                    temp += " ";
                    tempArray[k] = queryArray[k];
                }
                temp += prep[i];
                if (j != querySize) temp += " ";
                tempArray[j] = prep[i];
                for (int k = j; k != querySize; k++) {
                    temp += queryArray[k];
                    if (k != querySize - 1) temp += " ";
                    tempArray[k + 1] = queryArray[k];
                }
                auto it = dict[querySize - 1].find(temp);
                if (it != dict[querySize - 1].end()) {
                    candidate.push_back(make_pair(it->second, it->first));
                }
                for (int i = 0; i != 20; i++) {//edita**2
                    for (int j = 0; j != querySize + 2; j++) {
                        string ttemp = "";
                        for (int k = 0; k != j; k++) {
                            ttemp += tempArray[k];
                            ttemp += " ";
                        }
                        ttemp += prep[i];
                        if (j != querySize + 1) ttemp += " ";
                        for (int k = j; k != querySize + 1; k++) {
                            ttemp += tempArray[k];
                            if (k != querySize) ttemp += " ";
                        }
                        auto it = dict[querySize].find(ttemp);
                        if (it != dict[querySize].end()) {
                            candidate.push_back(make_pair(it->second, it->first));
                        }
                    }
                }
            }
        }
    }
}

void combine(int segment, vector<string>* editSequence, int* prepPosition,
             string* queryArray, string temp, int index, int querySize, int prepSegment) {
    bool flag = false;
    int i = index;
    int lastZero = 0;
    for (int k = 0; k != querySize; k++) {
        if (prepPosition[k] == 0) lastZero = k;
    }
    for (; i != querySize; i++) {
        if (prepPosition[i] == 0) {
            temp += queryArray[i];
            flag = true;
            if (i != lastZero) {
                temp += " ";
            } else {
                if (i == querySize -1) {
                    int spaceNum = 0;
                    for (int j = 0; j != temp.size(); j++) {
                        if (temp[j] == ' ') spaceNum++;
                    }
                    if (spaceNum > 4 || spaceNum < 1) return;
                    auto it = dict[spaceNum - 1].find(temp);
                    if (it != dict[spaceNum - 1].end()) {
                        candidate.push_back(make_pair(it->second, it->first));
                    }
                    return;
                }
            }
        } else if (prepPosition[i] == 1 && (flag || i == 0)) {
            flag = true;
            break;
        }
    }
    if (flag) {
        string ttemp = temp;
        for (auto it = editSequence[segment].begin(); it != editSequence[segment].end(); it++) {
            if (*it != "") temp += " ";
            temp += *it;
            if (prepPosition[querySize - 1] == 0) {
                if (*it != "") temp += " ";
            } else if (segment != prepSegment - 1) {
                if (*it != "") temp += " ";
            } else {
                int spaceNum = 0;
                for (int j = 0; j != temp.size(); j++) {
                    if (temp[j] == ' ') spaceNum++;
                }
                if (spaceNum > 4 || spaceNum < 1) return;
                auto it = dict[spaceNum - 1].find(temp);
                if (it != dict[spaceNum - 1].end()) {
                    candidate.push_back(make_pair(it->second, it->first));
                }
            }
            if (segment != prepSegment - 1 || i < lastZero)
                combine(segment + 1, editSequence, prepPosition, queryArray, temp, i + 1, querySize, prepSegment);
            temp = ttemp;
        }
    }
} 

void editB (int querySize, string* queryArray, string query, int* prepPosition) {
    /*if (querySize < 6 && querySize > 1) {
        auto it = dict[querySize - 2].find(query);
        if (it != dict[querySize - 2].end()) {
            candidate.push_back(make_pair(it->second, it->first));
        }
    }*/
    int prepSegment = 0;
    for (int i = 0; i != querySize - 1; i++) {
        if (prepPosition[i] != prepPosition[i + 1]) prepSegment++;
    }
    if (prepPosition[0] == 1 && prepPosition[querySize - 1] == 1) prepSegment++;
    prepSegment = (prepSegment + 1) / 2;
    vector<string>* prepSequence = new vector<string>[prepSegment];
    vector<string>* editSequence = new vector<string>[prepSegment];
    bool flag = false;
    int increase = 0;
    for (int i = 0; i != querySize; i++) {
        if (prepPosition[i] == 1) {
            flag = true;
            prepSequence[increase].push_back(queryArray[i]);
        } else if (prepPosition[i] == 0 && flag) {
            flag = false;
            increase++;
        }
    }
    for (int i = 0; i != prepSegment; i++) {
        int size = prepSequence[i].size();
        string temp = "";
        for (int j = 0; j != size; j++) {//delete
            for (int k = 0; k != size; k++) {
                if (k != j) {
                    temp += prepSequence[i][k];
                    if (k != size - 1 && (j != size - 1 || k != size - 2)) temp += " ";
                }               
            }
            editSequence[i].push_back(temp);
            temp = "";
        }
        for (int j = 0; j != 20; j++) {//substitue
            for (int k = 0; k != size; k++) {
                for (int l = 0; l != size; l++) {
                    if (l != k) temp += prepSequence[i][l];
                    if (l == k) temp += prep[j];
                    if (l != size - 1) temp += " ";
                }
                editSequence[i].push_back(temp);
                temp = "";
            }
        }
        for (int j = 0; j != 20; j++) {//add
            for (int k = 0; k != size + 1; k++) {
                for (int l = 0; l != k; l++) {
                    temp += prepSequence[i][l];
                    temp += " ";
                }
                temp += prep[j];
                if (k != size) temp += " ";
                for (int l = k; l != size; l++) {
                    temp += prepSequence[i][l];
                    if (k != size - 1) temp += " ";
                }
                editSequence[i].push_back(temp);
                temp = "";
            }
        }
    }
    combine(0, editSequence, prepPosition, queryArray, "", 0, querySize, prepSegment);
}

bool mysort(pair<int, string> one, pair<int, string> two) {
    if (one.first > two.first) {
        return true;
    } else if (one.first < two.first) {
        return false;
    } else {
        if (one.second.compare(two.second) > 0) {
            return false;
        } else {
            return true;
        }
    }
}

int main () {
    ifstream inFile;
    inFile.open("/tmp2/dsa2016_project/2gm.small.txt");
    char line[500];
    string word;
    int freq;
    dict[0].rehash(299087);
    while (true) {
        inFile.getline(line, 500);
        if (inFile.eof()) break;
        word = strtok(line, "\t");
        freq = atoi(strtok(NULL, "\t"));
        dict[0].emplace(word, freq);
    }
    inFile.close();
    inFile.open("/tmp2/dsa2016_project/3gm.small.txt");
    dict[1].rehash(299087);
    while (true) {
        inFile.getline(line, 500);
        if (inFile.eof()) break;
        word = strtok(line, "\t");
        freq = atoi(strtok(NULL, "\t"));
        dict[1].emplace(word, freq);
    }
    inFile.close();
    inFile.open("/tmp2/dsa2016_project/4gm.small.txt");
    dict[2].rehash(299087);
    while (true) {
        inFile.getline(line, 500);
        if (inFile.eof()) break;
        word = strtok(line, "\t");
        freq = atoi(strtok(NULL, "\t"));
        dict[2].emplace(word, freq);
    }
    inFile.close();
    inFile.open("/tmp2/dsa2016_project/5gm.small.txt");
    dict[3].rehash(299087);
    while (true) {
        inFile.getline(line, 500);
        if (inFile.eof()) break;
        word = strtok(line, "\t");
        freq = atoi(strtok(NULL, "\t"));
        dict[3].emplace(word, freq);
    }
    inFile.close();
    char queryLine[100];
    while (fgets(queryLine, 100, stdin)) {
        string query = strtok(queryLine, "\n");
        int querySize = 1;
        size_t count = query.find_first_of(" ");
        while (count != string::npos) {
            querySize++;
            count = query.find_first_of(" ", count + 1);
        }
        string* queryArray = new string[querySize];
        queryArray[0] = strtok(queryLine, " ");
        for (int i = 1; i != querySize; i++) {
            queryArray[i] = strtok(NULL, " ");
        }
        /*for (int i = 0; i != querySize; i++) {
            cout << queryArray[i] << endl;
        }*/
        int* prepPosition = new int[querySize];
        fill(prepPosition, prepPosition + querySize, 0);
        bool useEditA = true;
        for (int j = 0; j != querySize; j++) {
            for (int i = 0; i != 20; i++) {
                if (prep[i].compare(queryArray[j]) == 0) {
                    useEditA = false;
                    prepPosition[j] = 1;
                }
            }
        }
        if (useEditA) {
            editA(querySize, queryArray, query);
        } else {
            editB(querySize, queryArray, query, prepPosition);
        }
        sort(candidate.begin(), candidate.end(), mysort);
        cout << "query: " << query << endl;
        if (candidate.size() < 10) {
            cout << "output: " << candidate.size() << endl;
        } else {
            cout << "output: 10" << endl;
        }
        int top10 = 0;
        for (auto it: candidate) {
            if (top10 == 10) break;
            cout << it.second << "\t" << it.first << endl;
            top10++;
        }
        candidate.clear();
    }
}