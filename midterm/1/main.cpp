#include <vector>
#include <iostream>
#include <map>
using namespace std;
map<vector<int>, int> ans;
void permutation(int now, int max, int push, vector<int> stack, vector<int> out) {
    //cerr << "fff" << now << "," << push << endl;
    for (auto it = stack.begin(); it != stack.end(); it++) {
        //cerr << "stack" << *it << endl;
    }
    /*if (now == max) {
        /*if (push)
            out.push_back(now);
        while (!stack.empty()) {
            int a = stack.back();
            //cerr << 'a' << a << endl;
            out.push_back(a);
            stack.pop_back();
        }
        if (!push)
            out.push_back(now);
        for (auto it = out.begin(); it != out.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
        ans.emplace(out, 1);
        return;
    }*/
    while (push != 0) {
        out.push_back(stack.back());
        stack.pop_back();
        push--;
    }
    stack.push_back(now);
    if (now == max) {
        while (!stack.empty()) {
            out.push_back(stack.back());
            stack.pop_back();
        }
        /*for (auto it = out.begin(); it != out.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;*/
        ans.emplace(out, 1);
        return;
    }
    for (int i = 0; i <= stack.size(); i++) {
        permutation(now + 1, max, i, stack, out);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> stack;
    vector<int> out;
    //permutation(1, n, 1, stack, out);
    permutation(1, n, 0, stack, out);
    for (auto it = ans.begin(); it != ans.end(); it++) {
        for (auto itt = it->first.begin(); itt != it->first.end(); itt++) {
            cout << *itt << ' ';
        }
        cout << endl;
    }
}