#pragma once
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>

namespace {
	namespace __hide_namespace__
	{
		namespace item
		{
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

			std::ostream& operator<<(std::ostream& logger, const LogLevel& level)
			{
				return logger << constexprLogLeveString[static_cast<int>(level)];
			}

			/// <summary>
			/// Mark the functional info
			/// </summary>
			enum class FunctionalInfo
			{
				Time
			};

			std::ostream& operator<<(std::ostream& logger, const FunctionalInfo& func)
			{
				switch (func)
				{
				case FunctionalInfo::Time:
				{
					tm tm;
					time_t timeStamp = time(nullptr);
					localtime_s(&tm, &timeStamp);
					return logger << tm.tm_year + 1900 << '-' << tm.tm_mon + 1 << '-' << tm.tm_mday << ' '
						<< std::setfill('0')
						<< std::setw(2) << tm.tm_hour
						<< ':'
						<< std::setw(2) << tm.tm_min
						<< ':'
						<< std::setw(2) << tm.tm_sec
						<< ' ';
				}
				default:
					break;
				}
				return logger;
			}
		}

		struct Logger;
		struct FileLogger;
		void _log_args_(std::ostream&);
		template<typename T, typename ...Arg>
		void _log_args_(std::ostream&, const T& t, const Arg&...);
		template <typename ...Arg>
		void log(Logger&, const Arg&...);
		template <typename ...Arg>
		void log(Logger&&, const Arg&...);
		template <typename ...Arg>
		void log(FileLogger&, const Arg&...);
		template <typename ...Arg>
		void log(FileLogger&&, const Arg&...);

		// Final
		void _log_args_(std::ostream& logger)
		{
			logger << std::endl;
		}
		// Next
		template<typename T, typename ...Arg>
		void _log_args_(std::ostream& logger, const T& t, const Arg&... args)
		{
			_log_args_(logger << t, std::forward<const Arg&>(args)...);
		}

		/// <summary>
		/// Logger
		/// </summary>
		struct Logger
			: protected std::mutex
		{
		protected:
			std::ostream* os = nullptr;
		public:
			Logger() = default;
			Logger(std::ostream& os_) :os(&os_) {}
			void bind(std::ostream& os_) { os = &os_; }
			void unbind() { os = nullptr; }

			template <typename ...Arg>
			friend void log(Logger&, const Arg&...);
			template <typename ...Arg>
			friend void log(Logger&&, const Arg&...);

			/// <summary>
			/// Log
			/// </summary>
			template <typename ...Arg>
			void log(const Arg&... args)
			{
				__hide_namespace__::log(*this, std::forward<const Arg&>(args)...);
			}
		};

		struct FileLogger
			: protected std::mutex
		{
		protected:
			std::ofstream os;

		public:
			FileLogger() = default;
			FileLogger(const char* file)
				: os(file, std::ios::app | std::ios::out)
			{}
			void open(const char* _Filename, std::ios_base::open_mode _Mode)
			{
				return os.open(_Filename, std::ios_base::out | std::ios_base::app | _Mode);
			}
			void open(const wchar_t* _Filename, std::ios_base::open_mode _Mode)
			{
				return os.open(_Filename, std::ios_base::out | std::ios_base::app | _Mode);
			}
			void open(const unsigned short* _Filename, std::ios_base::open_mode _Mode)
			{
				return os.open(_Filename, std::ios_base::out | std::ios_base::app | _Mode);
			}
			void open(const char* _Filename, std::ios_base::openmode _Mode = std::ios_base::out | std::ios_base::app, int _Prot = std::ios_base::_Default_open_prot)
			{
				return os.open(_Filename, std::ios_base::out | std::ios_base::app | _Mode, _Prot);
			}
			void open(const wchar_t* _Filename, std::ios_base::openmode _Mode = std::ios_base::out | std::ios_base::app, int _Prot = std::ios_base::_Default_open_prot)
			{
				return os.open(_Filename, std::ios_base::out | std::ios_base::app | _Mode, _Prot);
			}
			void open(const unsigned short* _Filename, std::ios_base::openmode _Mode = std::ios_base::out | std::ios_base::app, int _Prot = std::ios_base::_Default_open_prot)
			{
				return os.open(_Filename, std::ios_base::out | std::ios_base::app | _Mode, _Prot);
			}
			void open(const std::string& _Str, std::ios_base::openmode _Mode = std::ios_base::out | std::ios_base::app, int _Prot = std::ios_base::_Default_open_prot)
			{
				return os.open(_Str, std::ios_base::out | std::ios_base::app | _Mode, _Prot);
			}
			void open(const std::wstring& _Str, std::ios_base::openmode _Mode = std::ios_base::out | std::ios_base::app, int _Prot = std::ios_base::_Default_open_prot)
			{
				return os.open(_Str, std::ios_base::out | std::ios_base::app | _Mode, _Prot);
			}

			bool is_open() const
			{
				return os.is_open();
			}
			operator bool() const
			{
				return os.operator bool();
			}
			bool operator!() const
			{
				return !os;
			}
			bool fail() const
			{
				return os.fail();
			}
			bool good() const
			{
				return os.good();
			}
			bool bad() const
			{
				return os.bad();
			}
			void close()
			{
				return os.close();
			}

			template <typename ...Arg>
			friend void log(FileLogger&, const Arg&...);
			template <typename ...Arg>
			friend void log(FileLogger&&, const Arg&...);

			/// <summary>
			/// Log
			/// </summary>
			template <typename ...Arg>
			void log(const Arg&... args)
			{
				__hide_namespace__::log(*this, std::forward<const Arg&>(args)...);
			}
		};

		/// <summary>
		/// Log
		/// </summary>
		template <typename ...Arg>
		void log(Logger& logger, const Arg&... args)
		{
			if (logger.os == nullptr || logger.os->fail())
				return;
			std::lock_guard<std::mutex> lock(logger);
			_log_args_(*logger.os, item::FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}

		/// <summary>
		/// Log
		/// </summary>
		template <typename ...Arg>
		void log(Logger&& logger, const Arg&... args)
		{
			if (logger.os == nullptr || logger.os->fail())
				return;
			std::lock_guard<std::mutex> lock(logger);
			_log_args_(*logger.os, item::FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}

		/// <summary>
		/// Log
		/// </summary>
		template<typename ...Arg>
		void log(FileLogger& logger, const Arg& ...args)
		{
			if (!logger.os)
				return;
			std::lock_guard<std::mutex> lock(logger);
			_log_args_(logger.os, item::FunctionalInfo::Time, std::forward<const Arg&>(args)...);
		}

		/// <summary>
		/// Log
		/// </summary>
		template <typename ...Arg>
		void log(FileLogger&& logger, const Arg&... args)
		{
			if (!logger.os)
				return;
			std::lock_guard<std::mutex> lock(logger);
			_log_args_(logger.os, item::FunctionalInfo::Time, std::forward<const Arg&>(args)...);
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
		using __hide_namespace__::log;
		using __hide_namespace__::item::FunctionalInfo;
		using __hide_namespace__::item::LogLevel;
		using __hide_namespace__::Logger;
		using __hide_namespace__::FileLogger;
	}
}

#endif