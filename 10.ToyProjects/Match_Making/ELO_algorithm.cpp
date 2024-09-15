#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

// ELO 점수를 계산
pair<int, int> ELO_rating(int rating1, int rating2, int winner) {
  const int K_Factor = 16;
  // 점수차이 0점: 기댓값=1/2, 점수차이 400점: 1/11
  double expected1 = 1.0 / (1.0 + pow(10, (rating2 - rating1) / 400.0));
  double expected2 = 1.0 / (1.0 + pow(10, (rating1 - rating2) / 400.0));
  if (winner == 1) {
    rating1 += K_Factor * (1 - expected1);
    rating2 += K_Factor * (0 - expected2);
  } else {
    rating1 += K_Factor * (0 - expected1);
    rating2 += K_Factor * (1 - expected2);
  }

  return make_pair(rating1, rating2);
}

// 매치를 진행
void match(unordered_map<string, int> &rating, string user1, string user2) {
  if (rating[user1] == 0 || rating[user2] == 0) {
    cout << "존재하지 않는 유저입니다." << endl;
    return;
  }

  cout << "승자를 입력하세요. " << user1 << "이 이겼다면 1, " << user2
       << "이 이겼다면 2: ";
  int winner;
  cin >> winner;
  if (winner != 1 && winner != 2) {
    cout << "잘못된 입력입니다." << endl;
    return;
  }
  pair<int, int> new_ratings = ELO_rating(rating[user1], rating[user2], winner);
  rating[user1] = new_ratings.first;
  rating[user2] = new_ratings.second;

  cout << user1 << "의 새로운 점수: " << rating[user1] << endl;
  cout << user2 << "의 새로운 점수: " << rating[user2] << endl;
}

// 신규 유저 추가
void add_new_user(unordered_map<string, int> &rating) {
  string username;
  cout << "신규 유저 이름을 입력하세요: ";
  cin >> username;

  if (rating[username] != 0) {
    cout << "이미 존재하는 사용자입니다." << endl;
    return;
  }
  rating[username] = 1000;
  cout << username << " 사용자가 추가되었습니다. 초기 점수는 1000점입니다."
       << endl;
}

// 유저 점수 조회
void get_user_rating(const unordered_map<string, int> &rating) {
  string username;
  cout << "유저 명을 입력하세요: ";
  cin >> username;

  auto it = rating.find(username);
  if (it != rating.end()) {
    cout << username << "의 현재 점수는 " << it->second << "점입니다." << endl;
  } else {
    cout << "존재하지 않는 사용자입니다." << endl;
  }
}

int main() {
  unordered_map<string, int> name_to_rating;
  ifstream inputFile("rating_log.txt");
  if (!inputFile) {
    cerr << "파일을 열 수 없습니다." << endl;
  } else {
    string line;
    while (getline(inputFile, line)) {
      stringstream ss(line);
      string username;
      int score;
      ss >> username >> score;
      name_to_rating[username] = score;
    }
    inputFile.close();
  }

  int choice;
  cout << "원하는 기능을 선택하세요:\n1. 신규 유저 추가\n2. 매치 후 점수 "
          "조정\n3. 점수 조회\n";
  cin >> choice;

  if (choice == 1) {
    add_new_user(name_to_rating);
  } else if (choice == 2) {
    string user1, user2;
    cout << "첫 번째 사용자 이름: ";
    cin >> user1;
    cout << "두 번째 사용자 이름: ";
    cin >> user2;
    match(name_to_rating, user1, user2);
  } else if (choice == 3) {
    get_user_rating(name_to_rating);
  } else {
    cout << "잘못된 선택입니다." << endl;
  }

  ofstream outputFile("rating_log.txt");
  for (const auto &entry : name_to_rating) {
    outputFile << entry.first << " " << entry.second << endl;
  }
  outputFile.close();

  return 0;
}
