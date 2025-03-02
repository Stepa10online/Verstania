#pragma once

float clamp(float x, float lowerlimit = 0.0f, float upperlimit = 1.0f) {
	if (x < lowerlimit) return lowerlimit;
	if (x > upperlimit) return upperlimit;
	return x;
}
float smootherstep(float edge0, float edge1, float x) {
	// Scale, and clamp x to 0..1 range
	x = clamp((x - edge0) / (edge1 - edge0));

	return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
}
