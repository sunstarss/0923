#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <stdexcept>
using namespace std;

struct Score
{
	int id_;
	string name_;
	int score_;

	Score(int id, const string &name, int score)
		:id_(id), name_(name), score_(score)
	{ }
};

class Comp
{
public:
	bool operator() (const Score &s1, const Score &s2)
	{
		if(s1.score_ != s2.score_)
			return s1.score_ < s2.score_;
		if(s1.name_ != s2.name_)
			return s1.name_ > s2.name_;
		return s1.id_ > s2.id_;
	} 
};

typedef priority_queue<Score, vector<Score>, Comp> ScoreList;

void readFile(const string &filename, ScoreList &scores);
void printScoreList(ScoreList &scores);

int main(int argc, char const *argv[])
{
	ScoreList scores;

	readFile("score.txt", scores);
	printScoreList(scores);
}

void readFile(const string &filename, ScoreList &scores)
{
	ifstream in(filename.c_str());
	if(!in)
		throw runtime_error("文件打开失败");

	string line;
	while(getline(in, line))
	{
		int id;
		char name[20] = {0};
		int score;
		sscanf(line.c_str(), "%d %s %d", &id, name, &score);
		scores.push(Score(id, name, score));
	}

	in.close();
}

void printScoreList(ScoreList &scores)
{
	while(!scores.empty())
	{
		Score s = scores.top();
		scores.pop();
		cout << "id = " << s.id_ << " name = " << s.name_ << " score = " << s.score_ << endl;
	}
}
