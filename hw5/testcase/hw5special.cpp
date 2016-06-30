#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

// #define DEBUG
#ifdef DEBUG
  #define DBG_MSG(msg) (cerr << "[System] " << msg << endl)
#else
  #define DBG_MSG(msg) ("Hello")
#endif

#define MAX 2

class LineVector {
private:
	vector<string> line;
public:
	LineVector() { line.clear(); }
	LineVector(string str) {
		DBG_MSG("Start process line: " << str);
		string tmp;
		stringstream ss;
		ss << str;
		line.clear();
		// read and ignore spaces
		while (ss >> tmp) {
			line.push_back(tmp);
			// DBG_MSG("Get token: " << tmp);
		}
		ss.str("");
		ss.clear();
		// sort possible answers
		if (line.size() >= 2)
			sort(line.begin() + 2, line.end());
		// DBG_MSG("End line process.");
	}
	bool empty() const {
		return line.size() == 0;
	}
	size_t size() const {
		return line.size();
	}
	string getStringAt(int index) const {
		if (0 <= index && index < line.size()) {
			return line[index];
		}
		DBG_MSG("Index out of line: " << index << ", line size: " << line.size());
		return "";
	}
	bool operator == (const LineVector& another) const {
		if (this->size() != another.size())
			return false;
		for (int i = 0; i < size(); i++) {
			if (this->getStringAt(i) != another.getStringAt(i))
				return false;
		}
		return true;
	}
};

class FileVector {
private:
	vector<LineVector> file;
public:
	FileVector() { file.clear(); }
	FileVector(char* filename) {
		DBG_MSG("Start process file: " << filename);
		ifstream fin(filename);
		string tmpLineStr;
		while ( getline(fin, tmpLineStr) ) {
			LineVector line(tmpLineStr);
			if ( !line.empty() ) {
				file.push_back(line);
			}
			else {
				DBG_MSG("Line empty.");
			}
		}
		fin.close();
		DBG_MSG("End process file: " << filename);
	}
	bool empty() const {
		return file.size() == 0;
	}
	size_t size() const {
		return file.size();
	}
	LineVector getLineAt(int index) const {
		if (0 <= index && index < file.size()) {
			return file[index];
		}
		DBG_MSG("Index out of file: " << index << ", file size: " << file.size());
		return LineVector("");
	}
};

vector<FileVector> files;

#define BIT(x) (((x) + 2) & 1)

void solve() {
	FileVector solFile, testFile;
	solFile  = files[0];
	testFile = files[1];
	int len = testFile.size();
	int LCS[2][len + 1];
	memset(LCS, 0, sizeof(LCS));
	for (int i = 1; i <= solFile.size(); i++) {
		for (int j = 1; j <= testFile.size(); j++) {
			if (solFile.getLineAt(i - 1) == testFile.getLineAt(j - 1))
				LCS[BIT(i)][j] = LCS[BIT(i - 1)][j - 1] + 1;
			else
				LCS[BIT(i)][j] = max(LCS[BIT(i - 1)][j], LCS[BIT(i)][j - 1]);
		}
	}
	DBG_MSG("Result: " << LCS[BIT(solFile.size())][testFile.size()] << " " << solFile.size());
	cout << LCS[BIT(solFile.size())][testFile.size()] << " " << solFile.size() << endl;
	return ;
}

int main(int argc, char* argv[]) {
	if (3 != argc)
		DBG_MSG("Error argument number!");
	else {
		DBG_MSG("argc: " << argc);
		files.clear();
		for (int i = 1; i < min(argc, MAX + 1); i++) {
			files.push_back( FileVector(argv[i]) );
		}
		solve();
	}
}
