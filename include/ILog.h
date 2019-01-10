/*
 * Copyright 2019 Open University of the Netherlands / St. Kliment Ohridski University of Sofia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This project has received funding from the European Union’s Horizon
 * 2020 research and innovation programme under grant agreement No 644187.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ILOGGER_H
#define ILOGGER_H


 // namespace: rage
 //
 // summary:	.
namespace rage
{
#include <stdlib.h> 
#include <string>

	/// <summary>
	/// Values that represent severities.
	/// 
	/// See http://www.drdobbs.com/the-new-c-x-macros/184401387.
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

	/// <summary>
	/// Values that represent log levels.
	/// </summary>
	enum LogLevel : int
	{
		/// <summary>
		/// An enum constant representing the critical option (1).
		/// </summary>
		_Critical_ = Severity::Critical,
		/// <summary>
		/// An enum constant representing the error option (3).
		/// </summary>
		_Error_ = LogLevel::_Critical_ | Severity::Error,
		/// <summary>
		/// An enum constant representing the warning option (7).
		/// </summary>
		_Warn_ = LogLevel::_Error_ | Severity::Warning,
		/// <summary>
		/// An enum constant representing the information option (15).
		/// </summary>
		_Info_ = LogLevel::_Warn_ | Severity::Information,
		/// <summary>
		/// An enum constant representing all option (31).
		/// </summary>
		_All_ = LogLevel::_Info_ | Severity::Verbose,
	};

	/// <summary>
	/// A log interface for the Bridge (used for emitting diagnostic logging).
	/// </summary>
	class ILog
	{
	public:

		/// <summary>
		/// Logs.
		/// </summary>
		///
		/// <param name="severity"> The severity. </param>
		/// <param name="msg">	    The message. </param>
		virtual void Log(Severity severity, const std::string& msg) = 0;
	};
}

#endif // ILOGGER_H
