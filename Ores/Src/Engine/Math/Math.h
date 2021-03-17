#pragma once

float lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}