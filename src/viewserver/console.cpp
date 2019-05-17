#include "console.h"

#include <windows.h>


Console::Console()
{
	AllocConsole();
	freopen_s(&cStdout, "CONOUT$", "w", stdout);
	freopen_s(&cStderr, "CONOUT$", "w", stderr);
}


Console::~Console()
{
	fclose(cStderr);
	fclose(cStdout);
	FreeConsole();
}

Console& Console::getInstance()
{
	static Console instance;
	return instance;
}
