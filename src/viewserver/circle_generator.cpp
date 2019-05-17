#include "circle_generator.h"

void generateCircle(SimpleVertex* vertices, int sides, float radius)
{
	float PI = 3.14159265358979323846;
	int index = 0;
	float theta = PI / sides;

	XMFLOAT3 last = XMFLOAT3(radius * cos(theta), radius * sin(theta), 0.5f);

	for (int n = 1; n <= sides; n += 1)
	{
		float x = radius * cos(theta + 2 * PI * n / sides);
		float y = radius * sin(theta + 2 * PI * n / sides);

		SimpleVertex a = SimpleVertex();
		SimpleVertex b = SimpleVertex();
		SimpleVertex c = SimpleVertex();

		a.Pos = XMFLOAT3(x, y, 0.5f);
		b.Pos = last;
		c.Pos = XMFLOAT3(0.0f, 0.0f, 0.5f);
		last = a.Pos;

		vertices[index] = a;
		vertices[index + 1] = b;
		vertices[index + 2] = c;
		index += 3;
	}
}