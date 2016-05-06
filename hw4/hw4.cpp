#include <iostream>
#include <vector>
#include <string> 
#include <sstream>
#include <functional>
#include <cstdio>
#include <set>
using namespace std;

class Bid {
public:
    Bid(unsigned bidId, unsigned clientId, unsigned action, unsigned price, unsigned shareCount) {
        _bidId = bidId;
        _clientId = clientId;
        _action = action;
        _price = price;
        _shareCount = shareCount;
    }

    bool operator>(const Bid b) {
        if (this->_price == b._price) { 
            return this->_bidId > b._bidId;
        } else {
            return this->_price > b._price;
        }
    }

    bool operator<(const Bid b) {
        if (this->_price == b._price) { 
            return this->_bidId > b._bidId;
        } else {
            return this->_price < b._price;
        }
    }

    unsigned _bidId;
    unsigned _clientId;
    unsigned _action;
    unsigned _price;
    unsigned _shareCount;
};

void Insert(Bid* p, vector<Bid*>& list) {
    if (p->_action == 0) {// buy
        list.push_back(p);
        int now_index = list.size() - 1;
        int parent_index = now_index / 2;
        while (*list[parent_index] < *p) {
            if (now_index == 1) break;
            list[now_index] = list[parent_index];
            now_index = parent_index;
            parent_index /= 2;
        }
        list[now_index] = p;
    } else if (p->_action == 1) {// sell
        list.push_back(p);
        int now_index = list.size() - 1;
        int parent_index = now_index / 2;
        while (*list[parent_index] > *p) {
            if (now_index == 1) break;
            list[now_index] = list[parent_index];
            now_index = parent_index;
            parent_index /= 2;
        }
        list[now_index] = p;
    }
}

void PopBuy(vector<Bid*>& buy) {
    Bid* last = buy[buy.size() - 1];
    delete buy[1];
    bool flag = true;
    int now_index = 1;
    while (flag) {
        flag = false;
        int left_index = 0;
        int right_index = 0;
        if (now_index * 2 < buy.size()) left_index = now_index * 2;
        if (now_index * 2 + 1 < buy.size()) right_index = now_index * 2 + 1;
        if (left_index && right_index) {
            if (*buy[left_index] < *buy[right_index]) {
                if (*last < *buy[right_index]) {
                    buy[now_index] = buy[right_index];
                    now_index = right_index;
                    flag = true;
                }
            } else {
                if (*last < *buy[left_index]) {
                    buy[now_index] = buy[left_index];
                    now_index = left_index;
                    flag = true;
                }
            }
        } else if (left_index) {
            if (*last < *buy[left_index]) {
                buy[now_index] = buy[left_index];
                now_index = left_index;
                flag = true;
            }
        } else if (right_index) {
            if (*last < *buy[right_index]) {
                buy[now_index] = buy[right_index];
                now_index = right_index;
                flag = true;
            }
        }
    }
    buy[now_index] = last;
    buy.pop_back();
}

void PopSell(vector<Bid*>& sell) {
    Bid* last = sell[sell.size() - 1];
    delete sell[1];
    bool flag = true;
    int now_index = 1;
    while (flag) {
        flag = false;
        int left_index = 0;
        int right_index = 0;
        if (now_index * 2 < sell.size()) left_index = now_index * 2;
        if (now_index * 2 + 1 < sell.size()) right_index = now_index * 2 + 1;
        if (left_index && right_index) {
            if (*sell[left_index] > *sell[right_index]) {
                if (*last > *sell[right_index]) {
                    sell[now_index] = sell[right_index];
                    now_index = right_index;
                    flag = true;
                }
            } else {
                if (*last > *sell[left_index]) {
                    sell[now_index] = sell[left_index];
                    now_index = left_index;
                    flag = true;
                }
            }
        } else if (left_index) {
            if (*last > *sell[left_index]) {
                sell[now_index] = sell[left_index];
                now_index = left_index;
                flag = true;
            }
        } else if (right_index) {
            if (*last > *sell[right_index]) {
                sell[now_index] = sell[right_index];
                now_index = right_index;
                flag = true;
            }
        }
    }
    sell[now_index] = last;
    sell.pop_back();
}

string Match(vector<Bid*>& buy, vector<Bid*>& sell, set<int> cancel) {
    string return_string = "";
    char buffer[100];
    auto it = cancel.find(buy[1]->_bidId);
    if (it != cancel.end()) {
        cancel.erase(it);
        PopBuy(buy);
        return return_string;
    }
    it = cancel.find(sell[1]->_bidId);
    if (it != cancel.end()) {
        cancel.erase(it);
        PopSell(sell);
        return return_string;
    }
    if (buy[1]->_shareCount < sell[1]->_shareCount) {//rebalance buy
        sprintf(buffer, "%d\t%d\t%d\t%d", buy[1]->_clientId, sell[1]->_clientId, 
                sell[1]->_price, buy[1]->_shareCount);
        return_string = string(buffer);
        sell[1]->_shareCount -= buy[1]->_shareCount;
        PopBuy(buy);       
    } else {//rebalance sell
        sprintf(buffer, "%d\t%d\t%d\t%d", buy[1]->_clientId, sell[1]->_clientId, 
                sell[1]->_price, sell[1]->_shareCount);
        return_string = string(buffer);
        buy[1]->_shareCount -= sell[1]->_shareCount;
        PopSell(sell);
        if (buy[1]->_shareCount == 0) {
            PopBuy(buy);
        }
    }
    return return_string;
}

int main () {
    string line;
    vector<Bid*> buy, sell;
    vector<string> transcation;
    set<int> cancel;
    Bid* dummy = new Bid(0, 0, 0, 0, 0);
    buy.push_back(dummy);
    sell.push_back(dummy);
    int transcation_time = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        unsigned bidId, clientId, action, price, shareCount;
        while (iss) {
            iss >> bidId >> clientId >> action >> price >> shareCount;
        }
        if (action == 0) {
            if (sell.size() > 1) {
                while (price >= sell[1]->_price && shareCount != 0) {
                    while (cancel.erase(sell[1]->_bidId)) {
                        PopSell(sell);
                        if (sell.size() == 1) break;
                    }
                    if (sell.size() == 1) break;
                    if (price < sell[1]->_price) break;
                    if (shareCount >= sell[1]->_shareCount) {
                        /*cout << transcation_time << '\t' << clientId << '\t' << 
                                sell[1]->_clientId << '\t' << sell[1]->_price << '\t' <<
                                sell[1]->_shareCount << endl;*/
                        printf("%u\t%u\t%u\t%u\t%u\n", transcation_time, clientId, sell[1]->_clientId,
                                sell[1]->_price, sell[1]->_shareCount);
                        shareCount -= sell[1]->_shareCount;
                        transcation_time++;
                        PopSell(sell);
                    } else {
                        /*cout << transcation_time << '\t' << clientId << '\t' << 
                                sell[1]->_clientId << '\t' << sell[1]->_price << '\t' <<
                                shareCount << endl;*/
                        printf("%u\t%u\t%u\t%u\t%u\n", transcation_time, clientId, sell[1]->_clientId,
                                sell[1]->_price, shareCount);
                        sell[1]->_shareCount -= shareCount;
                        shareCount = 0;
                        transcation_time++;
                    }
                }
            }
            if (shareCount != 0) {
                Bid* bid_pointer = new Bid(bidId, clientId, action, price, shareCount);
                Insert(bid_pointer, buy);
            }
        }
        //Bid* bid_pointer = new Bid(bidId, clientId, action, price, shareCount);
        //if (action == 0) Insert(bid_pointer, buy);
        //if (action == 1) Insert(bid_pointer, sell);
        if (action == 1) {
            if (buy.size() > 1) {
                while (price <= buy[1]->_price && shareCount != 0) {
                    while (cancel.erase(buy[1]->_bidId)) {
                        PopBuy(buy);
                        if (buy.size() == 1) break;
                    }
                    if (buy.size() == 1) break;
                    if (price > buy[1]->_price) break;
                    if (shareCount >= buy[1]->_shareCount) {
                        /*cout << transcation_time << '\t' << buy[1]->_clientId << '\t' << 
                                clientId << '\t' << price << '\t' <<
                                buy[1]->_shareCount << endl;*/
                        printf("%u\t%u\t%u\t%u\t%u\n", transcation_time, buy[1]->_clientId, clientId,
                                price, buy[1]->_shareCount);
                        shareCount -= buy[1]->_shareCount;
                        transcation_time++;
                        PopBuy(buy);
                    } else {
                        /*cout << transcation_time << '\t' << buy[1]->_clientId << '\t' << 
                                clientId << '\t' << price << '\t' <<
                                shareCount << endl;*/
                        printf("%u\t%u\t%u\t%u\t%u\n", transcation_time, buy[1]->_clientId, clientId,
                                price, shareCount);
                        buy[1]->_shareCount -= shareCount;
                        shareCount = 0;
                        transcation_time++;
                    }
                }
            }
            if (shareCount != 0) {
                Bid* bid_pointer = new Bid(bidId, clientId, action, price, shareCount);
                Insert(bid_pointer, sell);
            }
        }
        if (action == 2) cancel.emplace(price);
        if (buy.size() > 1 && sell.size() > 1 ) {
            while (buy[1]->_price >= sell[1] ->_price) {
                string temp = Match(buy, sell, cancel);
                if (temp != "") {
                    /*cout << transcation_time << '\t' << temp << endl;*/
                    printf("%u\t%s\n", transcation_time, temp.c_str());
                    transcation_time++;
                }
                if (sell.size() == 1 || buy.size() == 1)
                    break;
            }
        }
    }
}