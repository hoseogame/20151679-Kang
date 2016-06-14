#pragma once

class LevelManager
{
private:
	int level;
	LevelManager() : level(0) {}
	~LevelManager() = default;

public:
	LevelManager(const LevelManager&) = delete;

	static LevelManager* Instance()
	{
		static LevelManager* levelManager = new LevelManager();
		return levelManager;
	}

	void SetLevel(int _level) { level = _level; }
	const int GetLevel() { return level; }
};