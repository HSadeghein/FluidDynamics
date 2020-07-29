#pragma once




#include "pch.h"
#include <gtest/gtest.h>
#include "Log.h"

#include "Application.h"




int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();



	FluidEngine::Application::Get().Init(4, 0);
	FluidEngine::Application::Get().MainLoop();



	return 0;
}
