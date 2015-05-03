#ifndef CALLBACK_H
#define CALLBACK_H

#include <functional>
#include <typeinfo>

namespace rage
{
	template <typename Function>
	struct function_traits
	: public function_traits<decltype(&Function::operator())> {};


	template <typename ClassType, typename ReturnType, typename... Args>
	struct function_traits<ReturnType(ClassType::*)(Args...) const>
	{
		typedef ReturnType (*pointer)(Args...);
		typedef std::function<ReturnType(Args...)> function;
	};

	template <typename Function>
	typename function_traits<Function>::pointer
	to_function_pointer (Function& lambda)
	{
		return static_cast<typename function_traits<Function>::pointer>(lambda);
	};

	template <typename Function>
	typename function_traits<Function>::function
	to_function (Function& lambda)
	{
		return static_cast<typename function_traits<Function>::function>(lambda);
	};

	struct Callback final
	{
		void* function;
		const std::type_info* signature;
	};
}

#endif // CALLBACK_H
