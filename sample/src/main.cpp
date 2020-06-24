#pragma once

#include <gtest/gtest.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Log.h"
#include <iostream>
#include "Window.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	FluidEngine::Window window(800, 600);
	//GLFWwindow* window = glfwCreateWindow(800, 700, "Title", NULL, NULL);
	if (window.GetWindow() == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window.GetWindow());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 700);
	glfwSetFramebufferSizeCallback(window.GetWindow(), framebuffer_size_callback);



	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;



}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


