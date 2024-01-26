#pragma once

class Game;

class Time
{
private:
	friend class Game;
	inline static float m_deltaTimeSeconds = 0.f;

public:
	static float DeltaTimeSeconds() { return m_deltaTimeSeconds; };
};