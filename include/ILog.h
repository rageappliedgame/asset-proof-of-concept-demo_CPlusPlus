#ifndef ILOGGER_H
#define ILOGGER_H

namespace rage
{
#include <stdlib.h> 
#include <string>

	/// <summary>
	/// Values that represent severities.
	/// 
	/// See http://www.drdobbs.com/the-new-c-x-macros/184401387
	/// </summary>
	enum Severity : int
	{
		/// <summary>
		/// An enum constant representing the critical option.
		/// </summary>
		Critical = 1,

		/// <summary>
		/// An enum constant representing the error option.
		/// </summary>
		Error = 2,

		/// <summary>
		/// An enum constant representing the warning option.
		/// </summary>
		Warning = 4,

		/// <summary>
		/// An enum constant representing the information option.
		/// </summary>
		Information = 8,

		/// <summary>
		/// An enum constant representing the verbose option.
		/// </summary>
		Verbose = 16
	};

	/*
	/// <summary>
	/// Values that represent log levels.
	/// </summary>
	enum LogLevel : int
	{
		/// <summary>
		/// An enum constant representing the critical option.
		/// </summary>
		Critical = Severity.Critical,
		/// <summary>
		/// An enum constant representing the error option.
		/// </summary>
		Error = Critical | Error,
		/// <summary>
		/// An enum constant representing the warning option.
		/// </summary>
		Warn = Error | Warning,
		/// <summary>
		/// An enum constant representing the information option.
		/// </summary>
		Info = Warn | Information,
		/// <summary>
		/// An enum constant representing all option.
		/// </summary>
		All = Critical | Error | Warning | Information | Verbose,
	};
	*/

	class ILog
	{
	public:
		virtual void Log(Severity severity, const std::string& msg) = 0;
	};
}

#endif // ILOGGER_H
