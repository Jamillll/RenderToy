#pragma once

class Renderer
{
private:

public:
	static void Initialise();

	static void Submit();

	static void StartFrame();
	static void EndFrame();
};