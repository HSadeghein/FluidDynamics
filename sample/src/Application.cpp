#include "Application.h"
#include <functional>
namespace FluidEngine
{

	void error_call_back(int error, const char *description)
	{
		Log::GetCoreLogger()->error("Error: {}", description);
	}
	int Application::Init(int majorVer, int minorVer)
#include <iostream>

		namespace FluidEngine
	{

		int Application::Init(int minorVer, int majorVer)
		{

			glfwSetErrorCallback(error_call_back);
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			WindowProps props(600, 800, "Hassan");
			m_Window = std::make_unique<Window>(props);
			//std bind --> bind a function or a member to a another function
			//in this line we binded applicaion::onevent function, the first aurgument indicates the concept of the function, second argument indicates which function exactly we want to use
			//the third argument indicates we want to pass a variables or some predefined value.
			m_Window->SetEventCallback(std::bind(&Window::OnEvent, m_Window.get(), std::placeholders::_1));

			m_Window = std::make_unique<Window>(800, 600);
			m_Imgui_Panel = std::make_unique<ImGuiPanel>();
			glfwMakeContextCurrent(m_Window->GetWindow());

			ConvAllHlslToGlsl();

			//FPS cap
			glfwSwapInterval(0);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				FluidEngine::Log::GetCoreLogger()->error("Glad was not loaded correctly");
				return -1;
			}

			m_Timer.Reset();
			return 1;
		}

		void Application::MainLoop()
		{
			GLuint program, VAO, VBO, IBO;
			ConfigureGL(&program, &VAO, &VBO, &IBO);
			m_Imgui_Panel->InitiateImgui(m_Window->GetWindow());
			while (!glfwWindowShouldClose(m_Window->GetWindow()))
			{
				m_Timer.Tick();
				glfwSwapBuffers(m_Window->GetWindow());
				glfwPollEvents();
				//auto dt = m_Timer.DeltaTime();
				//Log::GetCoreLogger()->info("delta time is {}", dt);
				CalculateFrameStats();
				glfwPollEvents();
				m_Imgui_Panel->RenderImguiFrame();
				DrawGL(program, VAO, VBO);
				glfwSwapBuffers(m_Window->GetWindow());
				m_Imgui_Panel->ClearImguiFrame(m_Window->GetWindow());
			}
			m_Imgui_Panel->TerminateImgui();
			Terminate();
		}

		void Application::ConfigureGL(GLuint * program, GLuint * VAO, GLuint * VBO, GLuint * IBO)
		{
			const float positions[] = {
				0.5f, 0.5f, 0.0f, 1.0f,
				0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, -0.5f, 0.0f, 1.0f,
				-0.5f, 0.5f, 0.0f, 1.0};
			unsigned int indices[] = {
				0, 1, 3,
				1, 2, 3};

			glGenBuffers(1, VBO);
			glGenBuffers(1, IBO);
			glGenVertexArrays(1, VAO);

			glBindVertexArray(*VAO);

			glBindBuffer(GL_ARRAY_BUFFER, *VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
			glEnableVertexAttribArray(0);

			*program = CompileProgram();
		}

		void Application::DrawGL(GLuint program, GLuint VAO, GLuint VBO)
		{
			glUseProgram(program);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		GLuint Application::LoadGlslShader(const char *filename, GLenum shaderType, bool checkErrors)
		{
			GLuint result = 0;
			FILE *fp;
			size_t filesize;
			char *data;
			fp = fopen(filename, "rb");
			if (!fp)
				return 0;
			fseek(fp, 0, SEEK_END);
			filesize = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			data = new char[filesize + 1];
			if (!data)
				return 0;
			fread(data, 1, filesize, fp);
			data[filesize] = 0;
			fclose(fp);
			result = glCreateShader(shaderType);
			if (!result)
				return 0;
			glShaderSource(result, 1, &data, NULL);
			delete[] data;
			glCompileShader(result);
			if (checkErrors)
			{
				GLint status = 0;
				glGetShaderiv(result, GL_COMPILE_STATUS, &status);
				if (status == GL_FALSE)
				{
					GLint length;
					glGetShaderiv(result, GL_INFO_LOG_LENGTH, &length);
					char *message = (char *)alloca(length * sizeof(char));
					glGetShaderInfoLog(result, length, &length, message);
					std::cout << "failed to compile a shader !" << std::endl;
					std::cout << message << std::endl;
					glDeleteShader(result);
					return 0;
				}
			}
			return result;
		}

		GLuint Application::CompileProgram()
		{
			GLuint program;
			GLuint vertexShader = LoadGlslShader("shader/vertex.vert", GL_VERTEX_SHADER, true);
			GLuint fragmentShader = LoadGlslShader("shader/pixel.frag", GL_FRAGMENT_SHADER, true);
			program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return program;
		}

		void Application::ConvAllHlslToGlsl()
		{
			LPCWSTR glslangArgs[2] = {L"glslangValidator.exe -S vert -e main -o ", L" -V -D "};
			LPCWSTR spirvArgs[2] = {L"spirv-cross.exe --version 330 --no-es ", L" --output "};
			ConvHlslToGlsl(L"shader\\VertexShader.hlsl", L"shader\\vertex.spv", L"shader\\vertex.vert", glslangArgs, spirvArgs);
			glslangArgs[0] = L"glslangValidator.exe -S frag -e main -o ";
			glslangArgs[1] = L" -V -D ";
			spirvArgs[0] = L"spirv-cross.exe --version 330 --no-es ";
			spirvArgs[1] = L" --output ";
			ConvHlslToGlsl(L"shader\\PixelShader.hlsl", L"shader\\pixel.spv", L"shader\\pixel.frag", glslangArgs, spirvArgs);
		}

		void Application::ConvHlslToGlsl(LPCWSTR sourceName, LPCWSTR targetSPVName, LPCWSTR targetName, LPCWSTR glslangArgs[2],
										 LPCWSTR spirvArgs[2])
		{
			m_HlslToGlslConverter = std::make_unique<HlslToGlslConverter>(glslangExeDir, spirvCrossExeDir, sourceName,
																		  targetSPVName, targetName);
			std::wstring wparams = glslangArgs[0] + std::wstring(m_HlslToGlslConverter->m_TargetSPVName) + glslangArgs[1] + std::wstring(m_HlslToGlslConverter->m_SourceFileName);
			m_HlslToGlslConverter->ConvertToSPVFrom(&wparams[0]);
			wparams = spirvArgs[0] + std::wstring(m_HlslToGlslConverter->m_TargetSPVName) + spirvArgs[1] + std::wstring(m_HlslToGlslConverter->m_TargetFileName);
			m_HlslToGlslConverter->ConvertWithExeFromSPVTo(&wparams[0]);
		}

		void Application::Terminate()
		{
			m_Window->Terminate();
			glfwTerminate();
		}

		void Application::CalculateFrameStats()
		{
			static int frameCount = 0;
			static float timeElapsed = 0;

			frameCount++;

			if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
			{
				float fps = (float)frameCount;
				float mspf = 1000.0f / fps;

				Log::GetCoreLogger()->info("FPS is {}", fps);
				Log::GetCoreLogger()->info("Frame per milisecond is {}", mspf);

				frameCount = 0;
				timeElapsed += 1.0f;
			}
		}
	}
