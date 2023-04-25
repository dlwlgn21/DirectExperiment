#pragma once
#include "jhEngine.h"

namespace jh
{
	namespace debuger
	{
		static void CustomOutputDebugString(const char* pChar)
		{
			char buffer[64];
			if (strlen(pChar) >= 64)
			{
				assert(false);
			}
			sprintf(buffer, "%s\n", pChar);
			OutputDebugStringA(buffer);
		}

		static void CustomOutputDebugString(const char* pChar, int number)
		{
			char buffer[64];
			if (strlen(pChar) >= 64)
			{
				assert(false);
			}
			sprintf(buffer, "%s, %d\n", pChar, number);
			OutputDebugStringA(buffer);
		}

		static void CustomOutputDebugString(const char* pChar, float number)
		{
			char buffer[64];
			if (strlen(pChar) >= 64)
			{
				assert(false);
			}
			sprintf(buffer, "%s, %.3f\n", pChar, number);
			OutputDebugStringA(buffer);
		}
	}
}