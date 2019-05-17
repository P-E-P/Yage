#pragma once

#include <stdio.h>

class Console
{
private:
	FILE* cStdout;
	FILE* cStderr;
	Console();
public:
	static Console& getInstance();
	Console(Console const&) = delete;
	void operator=(Console const&) = delete;
	~Console();
};

