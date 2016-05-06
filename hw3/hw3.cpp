#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

string toBinary(int n) {
    string r;
    if (n == 0) return "0";
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

void display(int** nonogram, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (nonogram[i][j] == 0) {
                cout << '.';
            } else if (nonogram[i][j] == 1) {
                cout << '#';
            } else if (nonogram[i][j] == -1) {
                cerr << '.';
            } else {
                cerr << "{" << nonogram[i][j] <<"}";
            }
        }
        cout << endl;
    }
}

bool check(int** nonogram, vector<vector<int>> length_array, int m, int n, bool* row_column_error) {
    //cerr << m << ',' << n << endl;
    for (auto it = length_array.begin(); it != length_array.begin() + m; it++) {
        int hold = 0;
        for (auto itt = it->begin(); itt != it->end(); itt++) {
            int fragment_length = *itt;
            bool fragment_start = false;
            for (int j = 0 + hold; j < n; j++) {
                //cerr << "nonogram[" << it - length_array.begin() << "][" << j << "]\thold = " 
                //<< hold << "\tfragment_length = " << fragment_length << endl; 
                if (nonogram[it - length_array.begin()][j] == 1) {
                    fragment_start = true;
                    fragment_length--;
                    if (fragment_length < 0) {
                        //cerr << "row " << it - length_array.begin() << "error\n";
                        row_column_error[it - length_array.begin()] = 1;
                        //return false;
                    }
                }
                if (j == n - 1 && (!fragment_start || fragment_length != 0)) {
                    //cerr << "row " << it - length_array.begin() << "error\n";
                    row_column_error[it - length_array.begin()] = 1;
                    //return false;
                }
                if (j == n - 1 && itt != it->end() - 1) {
                    //cerr << "row " << it - length_array.begin() << "error\n";
                    row_column_error[it - length_array.begin()] = 1;
                    //return false;
                }
                if (nonogram[it - length_array.begin()][j] != 1) {
                    if (fragment_length != 0 && fragment_start) {
                        //cerr << "row " << it - length_array.begin() << "error\n";
                        row_column_error[it - length_array.begin()] = 1;
                        //return false;
                    } else if (fragment_length == 0 && fragment_start) {
                        hold = j + 1;
                        if (itt != it->end() - 1) {
                            break;
                        }
                    } 
                }
            }
        }
    }
    //cerr << "all rows are checked" << endl;
    for (auto it = length_array.begin() + m; it != length_array.end(); it++) {
        int hold = 0;
        for (auto itt = it->begin(); itt != it->end(); itt++) {
            int fragment_length = *itt;
            bool fragment_start = false;
            for (int i = 0 + hold; i < m; i++) {
                //cerr << "nonogram[" << i << "][" << it - length_array.begin()-m << "]\thold = " 
                //<< hold << "\tfragment_length = " << fragment_length << endl; 
                if (nonogram[i][it - length_array.begin() - m] == 1) {
                    fragment_start = true;
                    fragment_length--;
                    if (fragment_length < 0) {
                        //cerr << "column " << it - length_array.begin() - m << "error\n";
                        row_column_error[it - length_array.begin()] = 1;
                        //return false;
                    }
                }
                if (i == m - 1 && (!fragment_start || fragment_length != 0)) {
                    //cerr << "column " << it - length_array.begin() - m << "error\n";
                    row_column_error[it - length_array.begin()] = 1;
                    //return false;
                }
                if (i == m - 1 && itt != it->end() - 1) {
                    //cerr << "column " << it - length_array.begin() - m << "error\n";
                    row_column_error[it - length_array.begin()] = 1;
                    //return false;
                }
                if (nonogram[i][it - length_array.begin() - m] != 1) {
                    if (fragment_length != 0 && fragment_start) {
                        //cerr << "column " << it - length_array.begin() - m << "error\n";
                        row_column_error[it - length_array.begin()] = 1;
                        //return false;
                    } else if (fragment_length == 0 && fragment_start) {
                        hold = i + 1;
                        if (itt != it->end() - 1) {
                            break;
                        }
                    } 
                }
            }
        }
    }
    //cerr << "all columns are checked\n";
    for (int i = 0; i < m + n; i++) {
        if (row_column_error[i] != 0) return false;
    }
    return true;
}

void easy(int** nonogram, vector<vector<int>> length_array, int m, int n, bool* row_column_error) {
    fill(row_column_error, row_column_error + m + n, 0);
    check(nonogram, length_array, m, n, row_column_error);
    for (int i = 0; i != m + n; i++) {
        //cerr << row_column_error[i] << endl;
        if (row_column_error[i] == 0) {
            if (i < m) {
                for (int j = 0; j != n; j++) {
                    if (nonogram[i][j] != 1) nonogram[i][j] = -1;
                }
            } else {
                for (int j = 0; j != m; j++) {
                    if (nonogram[j][i - m] != 1) nonogram[j][i - m] = -1;
                }
            }
        }
    }
}

void fist_last_x(int** nonogram, vector<vector<int>> length_array, int m, int n) {
    for (int i = 0; i != m; i++) {
        bool left_flag = false;
        bool right_flag = false;
        for (int j = 1; j != n - 1; j++) {
            if (nonogram[i][j] == -1 && !left_flag) {
                left_flag = true;
                auto it = length_array.begin() + i;
                if (it->size() == 1 && *(it->begin()) < j) {
                    for (int w = 1; w <= *(it->begin()); w++) {
                        if (nonogram[i][j - w] == 1) {
                            for (int k = 0; k != *(it->begin()); k++) {
                                nonogram[i][j - 1 - k] = 1;
                            }
                            break;
                        }
                    }
                } else if (*(it->begin()) == j) {
                    for (int k = 0; k != j; k++) {
                        if (nonogram[i][k] == 1) {
                            fill(nonogram[i], nonogram[i] + j - 1, 1);
                            break;
                        }
                    }
                }
            }
            if (nonogram[i][j] == -1 && !right_flag) {
                right_flag = true;
                auto it = length_array.begin() + i;
                if (it->size() == 1 && *(it->end() - 1) < n - j) {
                    for (int w = 1; w <= *(it->begin()); w++) {
                        if (nonogram[i][j + w] == 1) {
                            for (int k = 0; k != *(it->begin()); k++) {
                                nonogram[i][j + 1 + k] = 1;
                            }
                            break;
                        }
                    }
                } else if (*(it->end() - 1) == n - j) {
                    for (int k = n - 1; k != j; k--) {
                        if (nonogram[i][k] == 1) {
                            fill(nonogram[i] + j, nonogram[i] + n - 1, 1);
                            break;
                        }
                    }
                } 
            }
            if (left_flag && right_flag) break;
        }

    }
    for (int j = 0; j != n; j++) {
        bool up_flag = false;
        bool down_flag = false;
        for (int i = 1; i != m - 1; i++) {
            if (nonogram[i][j] == -1 && !up_flag) {
                up_flag = true;
                auto it = length_array.begin() + m + j;
                if (it->size() == 1 && *(it->begin()) < i) {
                    for (int w = 1; w <= *(it->begin()); w++) {
                        if (nonogram[i - w][j] == 1) {
                            for (int k = 0; k != *(it->begin()); k++) {
                                nonogram[i - 1 - k][j] = 1;
                            }
                            break;
                        }
                    }
                } else if (*(it->begin()) == i) {
                    for (int k = 0; k != i; k++) {
                        if (nonogram[k][j] == 1) {
                            for (int w = 0; w != i; w++) {
                                nonogram[w][j] = 1;
                            }
                            break;
                        }
                    }
                }
            }
            if (nonogram[i][j] == -1 && !down_flag) {
                down_flag = true;
                auto it = length_array.begin() + m + j;
                if (it->size() == 1 && *(it->end() - 1) < m - i) {
                    for (int w = 1; w <=*(it->begin()); w++) {
                        if (nonogram[i + w][j] == 1) {
                            for (int k = 0; k != *(it->begin()); k++) {
                                nonogram[i + 1 + k][j] = 1;
                            }
                            break;
                        }
                    }
                } else if (*(it->end() - 1) == m - i) {
                    for (int k = m - 1; k != i; k--) {
                        if (nonogram[k][j] == 1) {
                            for (int w = m - 1; w != i; w--) {
                                nonogram[w][j] = 1;
                            }
                            break;
                        }
                    }
                } 
            }
            if (up_flag && down_flag) break;
        }
    }
}

bool dfs(int** nonogram, vector<vector<int>> length_array, int m, int n, int level) {
    if (level == m) {
        bool* row_column_error = new bool[m + n];
        fill(row_column_error, row_column_error + m + n, 0);
        bool result = check(nonogram, length_array, m, n, row_column_error);
        delete[] row_column_error;
        return result;
    }
    vector<int> non_determined;
    int exist_black = 0;
    for (int j = 0; j!= n; j++) {
        if (nonogram[level][j] == 0) {
            non_determined.push_back(j);
        } else if (nonogram[level][j] == 1) {
            exist_black ++;
        }
    }
    auto it = length_array.begin() + level;
    int total_black = 0;
    for (auto itt = it->begin(); itt != it->end(); itt++) {
        total_black += *itt;
    }
    //cerr << exist_black << "   " << total_black << endl;
    int remain_black = total_black - exist_black;
    if (non_determined.size() != 0) {
        int* permutation = new int[non_determined.size()];
        fill(permutation, permutation + non_determined.size(), 0);
        for (int i = 0; i != remain_black; i++) {
            permutation[non_determined.size() - 1 - i] = 1;
        }
        /*for (int i = 0; i != non_determined.size(); i++) {
            cerr << permutation[i] << " ";
        }*/
        //cerr << endl;
        do {
            int i = 0;
            //cerr << level << endl;
            for (auto it = non_determined.begin(); it != non_determined.end(); it++) {
                nonogram[level][*it] = permutation[i];
                //cerr << "nonogram[" << level << "][" << *it << "] = " << permutation[i] << endl;
                i++;
            }
            bool cut_leaf = false;
            int frag = 1, max_frag = 0, min_frag = n;
            for (int j = 0; j < n - 1; j++) {
                int temp = 0;
                if (nonogram[level][j] == 1 && nonogram[level][j + 1] != 1) {
                    frag++;
                    if (temp > max_frag) max_frag = temp;
                    if (temp < min_frag) min_frag = temp;
                    temp = 0;
                } else if (nonogram[level][j] != 1 && nonogram[level][j + 1] == 1) {
                    frag++;
                    temp++;
                } else if (nonogram[level][j] == 1 && nonogram[level][j + 1] == 1) {
                    temp++;
                }
            }
            if (frag != 2 * it->size() - 1 && nonogram[level][0] == 1 && nonogram[level][n - 1] == 1) cut_leaf = true;
            if (frag != 2 * it->size() && nonogram[level][0] != 1 && nonogram[level][n - 1] == 1) cut_leaf = true;
            if (frag != 2 * it->size() + 1 && nonogram[level][0] != 1 && nonogram[level][n - 1] != 1) cut_leaf = true;
            if (frag != 2 * it->size() && nonogram[level][0] == 1 && nonogram[level][n - 1] != 1) cut_leaf = true;
            //if (max_frag > *max_element(it->begin(), it->end())) cut_leaf = true;
            //if (min_frag < *min_element(it->begin(), it->end())) cut_leaf = true;
            if (cut_leaf) {
                //cerr << "cut\n";
            } else if (dfs(nonogram, length_array, m, n, level + 1)) {
                return true;
            }
            for (auto it = non_determined.end() - 1; it >= non_determined.begin(); it--) {
                nonogram[level][*it] = 0;
            }
        } while (next_permutation(permutation, permutation + non_determined.size()));
    } else {
        if (dfs(nonogram, length_array, m, n, level + 1))
            return true;
    }
    return false;   
}

int main() {
    int m, n;
    cin >> m;
    cin >> n;
    vector<vector<int>> length_array; 
    cin.get();
    for (int i = 0; i < m + n; i++) {
        string line_discription;
        vector<int> length_segment;
        getline(cin, line_discription);
        istringstream iss(line_discription);
        while (iss) {
            string sub;
            iss >> sub;
            if (sub.size())
                length_segment.push_back(stoi(sub));
        }
        length_array.push_back(length_segment);
    }
    //length_array check
    /*cerr << length_array.size() << endl;
    for (auto it = length_array.begin(); it != length_array.end(); it++) {
        for (auto itt = it->begin(); itt != it->end(); itt++) {
            cerr << *itt << ' ';
        }
        cerr << endl;
    }*/
    int** nonogram = new int*[m];
    for (int i = 0; i < m; i++) {
        nonogram[i] = new int[n];
        fill(nonogram[i], nonogram[i] + n, 0);
    }
    //cerr << "fewfwef\n";
    for (auto it = length_array.begin(); it != length_array.begin() + m; it++) {
        //cerr << endl;
        if (it->size() == 1) {
            if ((*it)[0] > n / 2) {
                for (int j = n - (*it)[0]; j != (*it)[0]; j++) {
                    nonogram[it - length_array.begin()][j] = 1;
                }
            }
        }
        if (it->size() >= 2) {
            vector<int> left_boundary;
            int count = n;
            int hold = 0;
            for (auto itt = it->end() - 1; itt >= it->begin(); itt--) {
                //cerr << *itt << endl;
                left_boundary.push_back(n - *itt - hold);
                hold = hold + *itt + 1;
            }
            auto itt = it->begin();
            hold = 0;
            for (auto jt = left_boundary.end() - 1; jt >= left_boundary.begin(); jt--) {
                //cerr << *jt << endl;
                for (int j = *jt; j <= hold + *itt - 1; j++) {
                    nonogram[it - length_array.begin()][j] = 1;
                }
                hold = hold + *itt + 1;
                itt++;
            }
        }
    }
    for (auto it = length_array.begin() + m; it != length_array.end(); it++) {
        //cerr /*<< it - length_array.begin() - m*/ << endl;
        if (it->size() == 1) {
            if ((*it)[0] > m / 2) {
                for (int i = m - (*it)[0]; i != (*it)[0]; i++) {
                    nonogram[i][it - length_array.begin()- m] = 1;
                }
            }
        }
        if (it->size() >= 2) {
            vector<int> left_boundary;
            int count = m;
            int hold = 0;
            for (auto itt = it->end() - 1; itt >= it->begin(); itt--) {
                //cerr << *itt << endl;
                left_boundary.push_back(m - *itt - hold);
                hold = hold + *itt + 1;
            }
            auto itt = it->begin();
            hold = 0;
            for (auto jt = left_boundary.end() - 1; jt >= left_boundary.begin(); jt--) {
                //cerr << *jt << endl;
                for (int i = *jt; i <= hold + *itt - 1; i++) {
                    nonogram[i][it - length_array.begin() - m] = 1;
                }
                hold = hold + *itt + 1;
                itt++;
            }
        }
    }
    bool* row_column_error = new bool[m + n];
    //cerr << "fefefe\n";
    for (int i = 0; i != 3; i++) {
        easy(nonogram, length_array, m, n, row_column_error);
        //display(nonogram, m , n);
        //cerr << endl;
        fist_last_x(nonogram, length_array, m, n);
    }
    //dfs(nonogram, length_array, m, n, 0);
    //nonogram display
    display(nonogram, m , n);
    fill(row_column_error, row_column_error + m + n, 0);
    //cerr << "finally check  " << check(nonogram, length_array, m, n, row_column_error) << endl;
}