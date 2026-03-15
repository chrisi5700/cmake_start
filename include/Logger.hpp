//
// Created by chris on 3/15/26.
//

#pragma once

#include <filesystem>
#include <source_location>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <fmt/format.h>

{
class Logger : public spdlog::logger
{
	std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_console_sink;
	std::shared_ptr<spdlog::sinks::basic_file_sink_mt>	 m_file_sink;
	Logger()
		: logger("Logger"),
		m_console_sink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>())
		, m_file_sink(std::make_shared<spdlog::sinks::basic_file_sink_mt>(LOG_FILE, true))

	{
#ifndef NDEBUG
		m_console_sink->set_level(spdlog::level::trace);
		m_file_sink->set_level(spdlog::level::trace);
#else
		m_console_sink->set_level(spdlog::level::warn);
		m_file_sink->set_level(spdlog::level::trace);
#endif
		sinks().push_back(m_console_sink);
		sinks().push_back(m_file_sink);
	}
public:
	static Logger& instance(std::source_location loc = std::source_location::current())
	{
		static Logger logger;
		std::filesystem::path path = loc.file_name();
		auto location = fmt::format("[{}:{}]", std::string{path.filename()}, loc.line());
		auto pattern = fmt::format("[Logger]{:<30}[%^%5l%$] %v", location);
		logger.set_pattern(pattern);
		return logger;
	}
};

