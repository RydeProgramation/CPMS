#pragma once

#include "framework.h"

#define FACTORY_VERSION "1.0.0"

#ifdef SHAREDENGINE_EXPORTS
#define FACTORY_API __declspec(dllexport)
#else
#define FACTORY_API __declspec(dllimport)
#endif

#ifndef __FACTORY__

namespace InternalFactory
{
	FACTORY_API void FreeBuffer();
	FACTORY_API void CreateValue(const void* ptr, const size_t sizeOf);
	FACTORY_API void DestroyValue(const void* ptr, const size_t sizeOf);

	static std::map<void*, Data> Pointers;
}

#define __FACTORY__
#endif