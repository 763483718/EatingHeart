#pragma once
#include "IDrawHeart.h"
class heartLevels :
	public IDrawHeart
{
public:
	heartLevels(GLuint width, GLuint height, const char* name);
	~heartLevels();

	// Í¨¹ý IDrawHeart ¼Ì³Ð
	virtual void render() override;
	void DrawOneLevel(float scale);
	void DrawHeard(float scale = 0.05, int seed = 1, float z = 0);
private:
	int current_size_;
	int current_count_;
};

