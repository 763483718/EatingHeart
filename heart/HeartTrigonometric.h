#pragma once
#include "IDrawHeart.h"
class HeartTrigonometric :
	public IDrawHeart
{
public:
	HeartTrigonometric(GLuint width, GLuint height, const char* name);
	virtual ~HeartTrigonometric();

	// Í¨¹ý IDrawHeart ¼Ì³Ð
	virtual void render() override;
	void DrawOne(float scale);
	void DrawHeard(float scale = 0.05, int seed = 1, float scaleZ = 0, float scaleXY = 0);
private:
	int current_size_;
	int current_count_;
};

