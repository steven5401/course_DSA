#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string> 
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ifstream in_file;
    in_file.open("/tmp2/KDDCUP2012/track1/rec_log_train.txt");
    int a[4];//a[0] = user, a[1] = item, a[2] = result, a[3] = time 
    typedef pair<int, int> user_time;
    typedef map<user_time, int> user_time_result;
    typedef map<int, user_time_result> item_user_time_result;
    typedef map<int, int> time_result;
    typedef map<int, time_result> item_time_result;
    typedef map<int, item_time_result> user_item_time_result;
    user_item_time_result data_base;
    item_user_time_result data_base2;
    int count = 0;
    int* user_total = new int[2500000];
    fill(user_total, user_total + 2500000, 0);
    while (!in_file.eof()) {
        for (int i = 0; i < 4; i++) {
            in_file >> a[i];
        }
        auto it = data_base.find(a[0]);
        if (it == data_base.end()) {//new user
            item_time_result* temp = new item_time_result();
            time_result* tempp = new time_result();
            auto p = tempp->emplace(a[3], a[2]);
            if (p.second) user_total[a[0]]++;
            temp->emplace(a[1], *tempp);
            data_base.emplace(a[0], *temp);    
        } else {//existed user
            auto itt = it->second.find(a[1]);
            if (itt == it->second.end()) {//new item
                time_result* temp = new time_result();
                auto p = temp->emplace(a[3], a[2]);
                if (p.second) user_total[a[0]]++;
                it->second.emplace(a[1], *temp);               
            } else {//existed item
                auto p = itt->second.emplace(a[3], a[2]);
                if (p.second) user_total[a[0]]++;
            }
        }
        auto it2 = data_base2.find(a[1]);
        if (it2 == data_base2.end()) {//new item
            user_time* u_t = new user_time(a[0], a[3]);
            user_time_result* temp = new user_time_result();
            temp->emplace(*u_t, a[2]);
            data_base2.emplace(a[1], *temp);
        } else {
            user_time* u_t = new user_time(a[0], a[3]);
            it2->second.emplace(*u_t, a[2]);
        }
        count++;
        if (count % 10000000 == 0)
            cerr << count << endl;
    }
    in_file.close();
    cerr << "data base have benn constructed\n";

    int query_number;
    cin >> query_number;
    cin.get();
    int accu_query = 0;
    while (query_number--) {
        string query_type, query_parameter;
        queue<int> query_parameter_queue;
        getline(cin, query_type);
        getline(cin, query_parameter);
        istringstream iss(query_parameter);
        while (iss) {
            string sub;
            iss >> sub;
            if (sub.size())
                query_parameter_queue.push(stoi(sub));
        }
        if (query_type == "accept") {
            int user = query_parameter_queue.front();
            query_parameter_queue.pop();
            int item = query_parameter_queue.front();
            query_parameter_queue.pop();
            int mytime = query_parameter_queue.front();
            query_parameter_queue.pop();
            auto it = data_base.find(user);
            if (it != data_base.end()) {
                auto itt = it->second.find(item);
                if (itt != it->second.end()) {
                    auto ittt = itt->second.find(mytime);
                    if (ittt != itt->second.end()) { 
                        cout << ittt->second << endl;
                    } else {//no this time
                        cout << 0 << endl;
                    }
                } else {//no this item
                    cout << 0 << endl;
                }
            } else {//no this user
                cout << 0 << endl;
            }
        } else if (query_type == "items") {
            int user1 = query_parameter_queue.front();
            query_parameter_queue.pop();
            int user2 = query_parameter_queue.front();
            query_parameter_queue.pop();
            int* count_item = new int[2500000];
            fill(count_item, count_item + 2500000, 0);
            vector<int> repeat_item;
            auto it1 = data_base.find(user1);
            if (it1 != data_base.end()) {
                for (auto itt1 = it1->second.begin(); itt1 != it1->second.end(); itt1++) {
                    count_item[itt1->first] = 1;
                }
            }            
            auto it2 = data_base.find(user2);
            if (it2 != data_base.end()) {               
                for (auto itt2 = it2->second.begin(); itt2 != it2->second.end(); itt2++) {
                    if (count_item[itt2->first] == 1) {
                        repeat_item.push_back(itt2->first);
                        count_item[itt2->first]--;
                    }
                }
            }           
            if (repeat_item.empty()) {
                cout << "EMPTY" << endl;
            } else {
                sort(repeat_item.begin(), repeat_item.end());
                for (auto it = repeat_item.begin(); it != repeat_item.end(); it++) {
                    cout << *it << endl;
                }
            }
            delete[] count_item;   
        } else if (query_type == "users") {
            int item1 = query_parameter_queue.front();
            query_parameter_queue.pop();
            int item2 = query_parameter_queue.front();
            query_parameter_queue.pop();
            int time1 = query_parameter_queue.front();
            query_parameter_queue.pop();
            int time2 = query_parameter_queue.front();
            query_parameter_queue.pop();
            int* count_user = new int[2500000];
            fill(count_user, count_user + 2500000, 0);
            vector<int> valid_user;
            auto it1 = data_base2.find(item1);
            if (it1 != data_base2.end()) {
                for (auto itt1 = it1->second.begin(); itt1 != it1->second.end(); itt1++) {
                    if (itt1->first.second >= time1 && itt1->first.second <= time2) {
                        count_user[itt1->first.first] = 1;
                    }
                }
            }            
            auto it2 = data_base2.find(item2);
            if (it2 != data_base2.end()) {               
                for (auto itt2 = it2->second.begin(); itt2 != it2->second.end(); itt2++) {
                    if (count_user[itt2->first.first] == 1 && itt2->first.second >= time1 && itt2->first.second <= time2) {
                        valid_user.push_back(itt2->first.first);
                        count_user[itt2->first.first]--;
                    }
                }
            }           
            if (valid_user.empty()) {
                cout << "EMPTY" << endl;
            } else {
                sort(valid_user.begin(), valid_user.end());
                for (auto it = valid_user.begin(); it != valid_user.end(); it++) {
                    cout << *it << endl;
                }
            }
            delete[] count_user;        
        } else if (query_type == "ratio") {
            int item = query_parameter_queue.front();
            query_parameter_queue.pop();
            int threshold = query_parameter_queue.front();
            query_parameter_queue.pop();
            int accept = 0, total = 0;
            for (auto it = data_base.begin(); it != data_base.end(); it++) {
                if (user_total[it->first] > threshold) {
                    total++;
                    auto itt = it->second.find(item);
                    if (itt != it->second.end()) {
                        for (auto ittt = itt->second.begin(); ittt != itt->second.end(); ittt++) {
                            if (ittt->second == 1) {
                                accept++;
                                break;
                            }
                        }
                    }
                }
            }
            cout << accept << '/' << total << endl;
        } else if (query_type == "findtime_item") {
            int item = query_parameter_queue.front();
            query_parameter_queue.pop();
            map<int, bool> time_list;
            while (!query_parameter_queue.empty()) {
                int user = query_parameter_queue.front();
                query_parameter_queue.pop();
                auto it = data_base.find(user);
                if (it != data_base.end()) {
                    auto itt = it->second.find(item);
                    if (itt != it->second.end()) {
                        for (auto ittt = itt->second.begin(); ittt != itt->second.end(); ittt++) {
                            time_list.emplace(ittt->first, 1);
                        }
                    }
                }
            }
            if (time_list.empty()) {
                cout << "EMPTY" << endl;
            } else {
                for (auto it = time_list.begin(); it != time_list.end(); it++) {
                    cout << it->first << endl;
                }
            }
        } else {
            cout << "undefined query type\n";
        }
        accu_query++;
        if (accu_query == 2000)
            break;       
    }
}