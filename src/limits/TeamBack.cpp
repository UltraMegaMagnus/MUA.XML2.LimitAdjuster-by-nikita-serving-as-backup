#include "LimitAdjuster.h"

static uint8_t ReadLimitValue(const std::string& value)
{
	const uint8_t limitValue = uint8_t(std::stoi(value));

	return limitValue > 0 && limitValue <= 255 ? limitValue : 255;
}

class TeamBack: public SimpleAdjuster
{
	const char* GetLimitName()
	{
		return IsMUA() ? "TeamBack" : nullptr;
	}

	void ChangeLimit(int, const std::string& value)
	{
		injector::WriteMemory(0x6FC6D0 + 4, ReadLimitValue(value), true);
	}
} teamBackLimit;