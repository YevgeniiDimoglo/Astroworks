#pragma once

#include <iostream>

#define VK_CHECK(x)														\
	do																	\
	{																	\
		VkResult err = x;												\
		if (err)														\
		{																\
			std::cout <<"Detected Vulkan error: " << err << std::endl;	\
			abort();													\
		}																\
	} while (0)

template<typename ...Args>
static void LOG(Args && ...args)
{
	(std::cout << ... << args);
}