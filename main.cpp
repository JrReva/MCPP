#include <iostream>
#include "engine.h"
#include "tool.h"
#include "define.h"

#ifdef _WIN32
	#include <windows.h>
#endif

int main()
{
	#ifdef _WIN32
		if(!IN_DEBUG)
			FreeConsole();
	#endif

    Tool::CheckTypes();

    Engine engine;
	engine.SetMaxFps(MAX_FPS);
    engine.Start(WINDOW_NAME, DEFAULT_WIDTH, DEFAULT_HEIGHT, false);
}
