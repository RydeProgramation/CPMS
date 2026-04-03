#pragma once

#include "framework.h"
#include "InternalFactory.hpp"

#define ENCODEUR_VERSION "1.0.0"

#ifdef SHAREDENGINE_EXPORTS
#define ENCODEUR_API extern "C" __declspec(dllexport)
#else
#define ENCODEUR_API extern "C" __declspec(dllimport)
#endif

#ifndef __ENCODEUR__

namespace Encodeur
{
	/// <summary>
	/// Encodes the input string and stores the result in the output string.
	/// </summary>
	/// <param name="input"> Input </param>
	/// <param name="sizeof_input"> Size of the input string </param>
	/// <returns></returns>
	ENCODEUR_API const Data Encode(const char* input, const size_t sizeof_input);

	/// <summary>
	/// Decodes the input string and stores the result in the output string.
	/// </summary>
	/// <param name="input"> Input </param>
	/// <param name="output"> Output </param>
	/// <returns></returns>
	ENCODEUR_API const Data Decode(const char* input, const size_t sizeof_input);
}

#define __ENCODEUR__
#endif