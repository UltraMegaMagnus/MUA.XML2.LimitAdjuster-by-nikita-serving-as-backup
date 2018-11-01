#include "LimitAdjuster.h"

static const uint8_t ReadLimitValue(const std::string& value)
{
	const uint8_t limitValue = uint8_t(std::stoi(value));

	return limitValue > 0 && limitValue <= 255 ? limitValue : 255;
}

class Herostat: public SimpleAdjuster
{
	const char* GetLimitName()
	{
		return IsMUA() ? "Herostat" : nullptr;
	}

	void ChangeLimit(int, const std::string& value)
	{
		const uint8_t limitValue = ReadLimitValue(value);

		injector::WriteMemory(0x4841B4 + 6, limitValue, true);

	}
} herostatLimit;