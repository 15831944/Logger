#pragma once
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace
{
	namespace __hide_namespace__
	{
		/// <summary>
		/// File to write logs
		/// </summary>
		std::string logFileName{ "log.txt" };

		/// <summary>
		/// Mark the level of logger info
		/// </summary>
		enum class LogLevel
		{
			Info,	// for info
			Warning,// for warning
			Error,	// for error
			Fatal	// for fatal
		};
		constexpr char constexprLogLeveString[][20] =
		{
			" [INFO] ",
			" [WARNING] ",
			" [ERROR] ",
			" [FATAL] "
		};
		template <class _Elem, class _Traits>
		std::basic_ostream<_Elem, _Traits>& operator<<(std::basic_ostream<_Elem, _Traits>& os, const LogLevel& level)
		{
			return os << constexprLogLeveString[static_cast<int>(level)];
		}

		/// <summary>
		/// Mark the functional info
		/// </summary>
		enum class FunctionalInfo
		{
			Time
		};
		template <class _Elem, class _Traits>
		std::basic_ostream<_Elem, _Traits>& operator<<(std::basic_ostream<_Elem, _Traits>& os, const FunctionalInfo& func)
		{
			switch (func)
			{
			case FunctionalInfo::Time:
			{
				tm tm;
				time_t timeStamp = time(nullptr);
				localtime_s(&tm, &timeStamp);
				return os << tm.tm_year + 1900 << '-' << tm.tm_mon + 1 << '-' << tm.tm_mday << ' '
					<< std::setfill('0')
					<< std::setw(2) << tm.tm_hour
					<< ':'
					<< std::setw(2) << tm.tm_min
					<< ':'
					<< std::setw(2) << tm.tm_sec << std::endl;
			}
			default:
				break;
			}
			return os;
		}

		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_ostream<_Elem, _Traits>& os, const Arg&... args);
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_ofstream<_Elem, _Traits>& os, const Arg&... args);
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_ostringstream<_Elem, _Traits>& os, const Arg&... args);
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_iostream<_Elem, _Traits>& os, const Arg&... args);
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_fstream<_Elem, _Traits>& os, const Arg&... args);
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_stringstream<_Elem, _Traits>& os, const Arg&... args);
		template<typename T, typename ...Arg>
		void log(const T& t, const Arg&... args);

		template <class _Elem, class _Traits>
		void _log_args_(std::basic_ostream<_Elem, _Traits>& os);
		template<class _Elem, class _Traits, typename T, typename ...Arg>
		void _log_args_(std::basic_ostream<_Elem, _Traits>& os, const T& t, const Arg&... args);


		// Final
		template <class _Elem, class _Traits>
		void _log_args_(std::basic_ostream<_Elem, _Traits>& os)
		{
			os << std::endl;
		}
		// Next
		template<class _Elem, class _Traits, typename T, typename ...Arg>
		void _log_args_(std::basic_ostream<_Elem, _Traits>& os, const T& t, const Arg&... args)
		{
			_log_args_(os << t, std::forward<const Arg&>(args)...);
		}

		/// <summary>
		/// Log > basic_ostream
		/// </summary>
		/// <param name="t">Args to write</param>
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_ostream<_Elem, _Traits>& os, const Arg&... args)
		{
			_log_args_(os, FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}
		/// <summary>
		/// Log > basic_ofstream
		/// </summary>
		/// <param name="t">Args to write</param>
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_ofstream<_Elem, _Traits>& os, const Arg&... args)
		{
			_log_args_(os, FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}
		/// <summary>
		/// Log > basic_ostringstream
		/// </summary>
		/// <param name="t">Args to write</param>
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_ostringstream<_Elem, _Traits>& os, const Arg&... args)
		{
			_log_args_(os, FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}
		/// <summary>
		/// Log > basic_iostream
		/// </summary>
		/// <param name="t">Args to write</param>
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_iostream<_Elem, _Traits>& os, const Arg&... args)
		{
			_log_args_(os, FunctionalInfo::Time,std::forward<const Arg&>(args)...);
		}
		/// <summary>
		/// Log > basic_fstream
		/// </summary>
		/// <param name="t">Args to write</param>
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_fstream<_Elem, _Traits>& os, const Arg&... args)
		{
			_log_args_(os, FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}
		/// <summary>
		/// Log > basic_stringstream
		/// </summary>
		/// <param name="t">Args to write</param>
		template<class _Elem, class _Traits, typename ...Arg>
		void log(std::basic_stringstream<_Elem, _Traits>& os, const Arg&... args)
		{
			_log_args_(os, FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}
		/// <summary>
		/// Log > file and clog
		/// </summary>
		/// <param name="t">Args to write</param>
		template<typename T, typename ...Arg>
		void log(const T& t, const Arg&... args)
		{
			std::ofstream os(logFileName, std::ios::app);
			log(os, t, std::forward<const Arg&>(args)...);
			log(std::clog, t, std::forward<const Arg&>(args)...);
		}
	}
}

/// <summary>
/// Write Everywhere, Read Nowhere
/// </summary>
namespace thatboy
{
	/// <summary>
	/// For better logger
	/// </summary>
	namespace logger
	{
		using __hide_namespace__::logFileName;
		using __hide_namespace__::log;
		using __hide_namespace__::LogLevel;
		using __hide_namespace__::FunctionalInfo;
	}
}

#endif