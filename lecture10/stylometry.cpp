#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

string fileToString(ifstream& file) {
  string ret = "";
  string line;
  while (std::getline(file, line)) {
    std::transform(line.begin(), line.end(), line.begin(), tolower);
    ret += line + " ";
  }
  return ret;
}

int countOccurrences(const string& text, const string& word) {
  string toFind = " " + word + " ";
  int count = 0;
  size_t pos = text.find(toFind);
  while (pos != string::npos) {
    count++;
    pos = text.find(toFind, pos + toFind.length());
  }
  return count;
}

int main() {
  cout << "Hello, World!" << endl;
  ifstream file("text.txt");
  string content = fileToString(file);
  cout << content << endl;
  return 0;
}