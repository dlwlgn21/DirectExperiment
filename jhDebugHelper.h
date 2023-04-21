#pragma once
#include "jhEngine.h"

namespace jh
{
	namespace debuger
	{
		void CustomOutputDebugString(const char* pChar)
		{
			char buffer[64];
			if (strlen(pChar) >= 64)
			{
				assert(false);
			}
			sprintf(buffer, "%s\n", pChar);
			OutputDebugStringA(buffer);
		}

		void CustomOutputDebugStringWithNumber(const char* pChar, int number)
		{
			char buffer[64];
			if (strlen(pChar) >= 64)
			{
				assert(false);
			}
			sprintf(buffer, "%s, %d\n", pChar, number);
			OutputDebugStringA(buffer);
		}
	}
}