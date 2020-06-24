#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace FluidEngine {
	class Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() {
			if (m_CoreLogger == nullptr)
			{
				Init();
			}
			return m_CoreLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
	};
}
