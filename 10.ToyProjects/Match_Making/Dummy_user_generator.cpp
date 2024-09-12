#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
  ifstream inputFile("rating_log.txt");
  int max_user_number = 0;
  if (inputFile.is_open()) {
    string line;
    regex user_regex("user(\\d+)");
    while (getline(inputFile, line)) {
      smatch match;
      if (regex_search(line, match, user_regex)) {
        int current_user_number = stoi(match[1].str());
        max_user_number = max(max_user_number, current_user_number);
      }
    }
    inputFile.close();
  }

  ofstream outputFile("rating_log.txt", ios::app);
  if (!outputFile.is_open()) {
    cerr << "파일을 열 수 없습니다." << endl;
    return 1;
  }

  srand(time(0));

  for (int i = 1; i <= 20; ++i) {
    string username = "user" + to_string(max_user_number + i);
    int random_score = 1000 + rand() % 1001;
    outputFile << username << " " << random_score << endl;
  }

  outputFile.close();
  cout << "새로운 20명의 더미 유저 데이터가 rating_log.txt 파일에 "
          "추가되었습니다."
       << endl;

  return 0;
}
