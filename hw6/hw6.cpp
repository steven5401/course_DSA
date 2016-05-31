#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class dp {
public:
    dp() {dist = 0; prevNoteIndex = 0;}
    float dist;
    int prevNoteIndex;
};

int main() {
    int pitchNum, noteNum;
    cin >> pitchNum;
    float* pitch = new float[pitchNum];
    for (int i = 0; i != pitchNum; i++) {
        cin >> pitch[i];
    }
    cin >> noteNum;
    float* note = new float[noteNum];
    for (int i = 0; i != noteNum; i++) {
        cin >> note[i];
    }
    dp** table = new dp*[pitchNum];
    for (int i = 0; i != pitchNum; i++) {
        table[i] = new dp[noteNum];
    }
    table[0][0].dist = abs(pitch[0] - note[0]);
    for (int i = 0; i != pitchNum; i++) {
        for (int j = 0; j != noteNum; j++) {
            if (j > i) {
                table[i][j].dist = 999999;
                continue;
            }
            if (i == 0 && j == 0) continue;
            if (j == 0) {
                table[i][j].dist = table[i - 1][j].dist + abs(pitch[i] - note[j]);
                table[i][j].prevNoteIndex = j;
                continue;
            }
            float left = table[i - 1][j].dist;
            float lowerLeft = table[i - 1][j - 1].dist;
            float current = abs(pitch[i] - note[j]);
            if (left >= lowerLeft) {
                table[i][j].dist = lowerLeft + current;
                table[i][j].prevNoteIndex = j - 1;
            } else {
                table[i][j].dist = left + current;
                table[i][j].prevNoteIndex = j;
            }
        }
    }


    float min = 999999;
    int key = 0;
    for (int j = 0; j != noteNum; j++) {
        if (table[pitchNum - 1][j].dist < min) {
            key = j;
            min = table[pitchNum - 1][j].dist;
        }
    }
    dp backtrace = table[pitchNum - 1][key];
    int thisDpJIndex = key;
    int thisDpIIndex = pitchNum - 1;
    vector<int> aligment;
    aligment.push_back(0);
    while (backtrace.dist != table[0][0].dist) {
        if (backtrace.prevNoteIndex != thisDpJIndex) {
            aligment.push_back(thisDpIIndex);
            thisDpJIndex = backtrace.prevNoteIndex;
        }
        thisDpIIndex--;
        backtrace = table[thisDpIIndex][backtrace.prevNoteIndex];
    }

    sort(aligment.begin(), aligment.end());
    cout << table[pitchNum - 1][key].dist << endl;
    for (auto it = aligment.begin(); it != aligment.end(); it++) {
        cout << *it << ' ';
    }
}