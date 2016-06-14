#pragma once
class ScoreManager
{
private:
	int score;
	ScoreManager() : score(0){}
	~ScoreManager() = default;

public:
	ScoreManager(const ScoreManager&) = delete;

	static ScoreManager* Instance()
	{
		static ScoreManager* scoreManager = new ScoreManager();
		return scoreManager;
	}

	void SetScore(int _score) { score = _score; }
	const int GetScore() { return score; }
};