#pragma once
#include "pch.h"
#include <gtest/gtest.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Log.h"

#include "Application.h"




int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();



	FluidEngine::Application app;
	app.Init(4, 0);
	app.MainLoop();



	return 0;
}
