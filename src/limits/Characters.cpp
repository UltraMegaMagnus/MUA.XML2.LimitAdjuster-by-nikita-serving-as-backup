#include "LimitAdjuster.h"

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define CharactersGold CCharacters<50, 350, 39, 13>
//#define CharactersGold CCharacters<39, 350, 28, 13>
#define ZoneStatsGold CZoneStats<37>

static uint8_t ReadLimitValue(const std::string& value)
{
	const uint8_t limit = uint8_t(std::stoi(value));
	return limit > 0 ? limit : std::numeric_limits<uint8_t>::max();
}

template<int characters, int statsEntries, int statsHero, int statsNPC>
struct CCharacters
{
	int field_4[characters / 32 + 1];
	char field_12[1396 * characters];
	int field_54452[characters];
	int field_54608;
	int field_54612;
	int field_54616;
	int field_54620[characters / 32 + 1];
	int field_54628;
	int field_54632[characters];
	int field_54788;
	int field_54792;
	char padding_4[4];

	char field_54800[28 * statsEntries];
	int field_64600;

	int field_64604;//vftable
	int field_64608;
	int field_64612;
	char field_64616[20 * statsEntries];
	int field_71616[statsEntries];
	int field_73016;
	int field_73020;
	int field_73024;
	char field_73028[17 * 44];

	int field_73776;
	int field_73780;
	char field_73784[544 * statsHero];
	char field_89016[544 * statsHero];
	bool field_104248;
	bool field_104249;

	char padding_2[2];

	int field_104252[statsHero / 32 + 1];
	char field_104256[88 * statsHero];
	int field_106720[statsHero];
	int field_106832;
	int field_106836;
	int field_106840;
	int field_106844[statsHero / 32 + 1];
	int field_106848;

	int field_106852;
	char field_106856[144 * statsNPC];
	int field_108728[statsNPC];
	int field_108780;
	int field_108784;
	int field_108788;
	int field_108792;
	int field_108796;

	short field_108800[statsEntries];
	int field_109500;

	short field_109504[statsEntries];
	int field_110204;
};

template<int heroes>
struct CZoneStats
{
	int field_0;
	int field_4[4];
	int field_20[4];
	int field_36[4];
	short field_52[4];
	short field_60[4];
	short field_68[4];
	short field_76[4];
	short field_84[4];
	short field_92[4];
	short field_100[4];
	short field_108[4];
	short field_116[4];
	short field_124[4];
	int field_132[heroes];
	int field_248[heroes];
	int field_364[heroes];
	short field_480[heroes];
	short field_538[heroes];
	int field_596;
	char field_600;
};

template<int heroes>
struct COptions
{
	char field_0;
	char field_1;
	char field_2;
	char field_3;
	char padding[40];
	char field_44[20 * 35];
	char kek;
};

template<typename T, typename U> constexpr size_t offsetOf(U T::* member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

class CharactersMUA : public Adjuster
{
public:
	enum
	{
		Characters
	};

	const Limit* GetLimits()
	{
		static Limit limits[] =
		{
			DEFINE_LIMIT(Characters),
			FINISH_LIMITS()
		};

		if (GetGVM().IsMUA()) return limits;
		return nullptr;
	}

	//+
	void Patch4816C0()
	{
		injector::WriteMemory(0x4816C3 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4816D6 + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4816E6 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch484F70()
	{
		injector::WriteMemory(0x484F77 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x484F84 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4850C7 + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x4850D0 + 4, offsetOf(&CharactersGold::field_109504), true);
		injector::WriteMemory(0x4850DC + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x48529B + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4852AA + 2, offsetOf(&CharactersGold::field_54800) + 53, true);
		injector::WriteMemory(0x4852C0 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4852D5 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch480840()
	{
		injector::WriteMemory(0x480850 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x48085F + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x480869 + 2, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch483680()
	{
		injector::WriteMemory(0x483690 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x48369E + 2, offsetOf(&CharactersGold::field_54800), true);
		injector::WriteMemory(0x4836E3 + 3, offsetOf(&CharactersGold::field_54800), true);
		injector::WriteMemory(0x483705 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch4833F0()
	{
		injector::WriteMemory(0x4833F4 + 2, offsetOf(&CharactersGold::field_54788), true);
		injector::WriteMemory(0x483406 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x483413 + 3, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x48341C + 3, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x483423 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x483432 + 3, offsetOf(&CharactersGold::field_54632), true);
	}

	//+
	void Patch481FD0(const uint8_t characters)
	{
		injector::WriteMemory(0x482007 + 3, offsetOf(&CharactersGold::field_54620), true);
		injector::WriteMemory(0x48200E + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x482014 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x48201C + 2, characters, true);
		injector::WriteMemory(0x48201F + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x482025 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x48202D + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x482037 + 1, characters - 1, true);
		injector::WriteMemory(0x48203F + 3, offsetOf(&CharactersGold::field_54452), true);
		injector::WriteMemory(0x482046 + 2, offsetOf(&CharactersGold::field_54628), true);
		injector::WriteMemory(0x48204E + 2, offsetOf(&CharactersGold::field_54628), true);
	}

	//+
	void Patch47F310()
	{
		injector::WriteMemory(0x47F310 + 2, offsetOf(&CharactersGold::field_54632), true);
	}

	//+
	void Patch483A50()
	{
		injector::WriteMemory(0x483A7A + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x483A96 + 3, offsetOf(&CharactersGold::field_54800), true);
		injector::WriteMemory(0x483AA4 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x483AB7 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x483ABD + 3, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x483ACD + 3, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x483AD6 + 3, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x483ADD + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x483AEC + 3, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x483B1F + 2, offsetOf(&CharactersGold::field_64616), true);
		injector::WriteMemory(0x483B25 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x483B2B + 2, offsetOf(&CharactersGold::field_64608), true);
		injector::WriteMemory(0x483B51 + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x483B58 + 2, offsetOf(&CharactersGold::field_109500), true);
	}

	//+
	void Patch483320(const uint8_t characters)
	{
		injector::WriteMemory(0x483324 + 2, offsetOf(&CharactersGold::field_54628), true);
		injector::WriteMemory(0x483330 + 2, offsetOf(&CharactersGold::field_54620), true);
		injector::WriteMemory(0x48334F + 2, offsetOf(&CharactersGold::field_54632) + 4, true);
		injector::WriteMemory(0x483360 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x483378 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x48338A + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4833A0 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4833B1 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4833C6 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4833E1 + 2, characters, true);
	}

	//+
	void Patch47FF10(const uint8_t characters)
	{
		injector::WriteMemory(0x47FF26 + 2, characters, true);
		injector::WriteMemory(0x47FF67 + 2, characters, true);
		injector::WriteMemory(0x47FF87 + 2, characters, true);
		injector::WriteMemory(0x47FFA6 + 2, characters, true);
		injector::WriteMemory(0x47FFE8 + 2, characters, true);
	}

	//+
	void Patch481F30(const uint8_t characters)
	{
		injector::WriteMemory(0x481F34 + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x481F3A + 2, offsetOf(&CharactersGold::field_54612), true);
		injector::WriteMemory(0x481F40 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x481F50 + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x481F56 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x481F5E + 2, characters, true);
		injector::WriteMemory(0x481F61 + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x481F67 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x481F6F + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x481F75 + 1, characters - 1, true);
		injector::WriteMemory(0x481F7D + 3, offsetOf(&CharactersGold::field_54452), true);
		injector::WriteMemory(0x481F85 + 2, characters, true);
	}

	//+
	void Patch481600()
	{
		injector::WriteMemory(0x481604 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481623 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x481631 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x48163B + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481663 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch483B70(const uint8_t characters)
	{
		injector::WriteMemory(0x483BB2 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x483BD0 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x483BD9 + 3, offsetOf(&CharactersGold::field_54788) - 16, true);
		injector::WriteMemory(0x483C51 + 2, offsetOf(&CharactersGold::field_64604), true);
		injector::WriteMemory(0x483C7A + 3, offsetOf(&CharactersGold::field_54800), true);
		injector::WriteMemory(0x483C9B + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x483CA5 + 2, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x483CA5 + 6, characters, true);
		injector::WriteMemory(0x483CAE + 2, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x483CC7 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x483CCD + 2, offsetOf(&CharactersGold::field_54788), true);
		injector::WriteMemory(0x483CEA + 2, offsetOf(&CharactersGold::field_54788), true);
		injector::WriteMemory(0x483CF1 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x483D1D + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x483D27 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch480A00(const uint8_t characters)
	{
		injector::WriteMemory(0x480A02 + 2, offsetOf(&CharactersGold::field_54612), true);
		injector::WriteMemory(0x480A08 + 3, offsetOf(&CharactersGold::field_54452), true);
		injector::WriteMemory(0x480A15 + 3, offsetOf(&CharactersGold::field_54620), true);
		injector::WriteMemory(0x480A2B + 2, offsetOf(&CharactersGold::field_54612), true);
		injector::WriteMemory(0x480A34 + 2, characters, true);
		injector::WriteMemory(0x480A37 + 2, offsetOf(&CharactersGold::field_54612), true);
		injector::WriteMemory(0x480A3F + 2, offsetOf(&CharactersGold::field_54612), true);
		injector::WriteMemory(0x480A49 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x480A4F + 2, offsetOf(&CharactersGold::field_54628), true);
		injector::WriteMemory(0x480A57 + 2, offsetOf(&CharactersGold::field_54628), true);
	}

	//+
	void Patch482360()
	{
		injector::WriteMemory(0x482371 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x48237B + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x482389 + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x48238F + 4, offsetOf(&CharactersGold::field_108800), true);
		injector::WriteMemory(0x482397 + 2, offsetOf(&CharactersGold::field_109500), true);
	}

	//+
	void Patch4823C0()
	{
		injector::WriteMemory(0x4823D3 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x4823E7 + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x4823F6 + 4, offsetOf(&CharactersGold::field_108800) - 2, true);
		injector::WriteMemory(0x4823FE + 4, offsetOf(&CharactersGold::field_108800), true);
		injector::WriteMemory(0x482406 + 2, offsetOf(&CharactersGold::field_109500), true);
	}

	//+
	void Patch4807E0()
	{
		injector::WriteMemory(0x4807E0 + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x4807EE + 2, offsetOf(&CharactersGold::field_108800), true);
		injector::WriteMemory(0x480806 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x48080D + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x480819 + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x480829 + 2, offsetOf(&CharactersGold::field_109500), true);
	}

	//+
	void Patch4815A0()
	{
		injector::WriteMemory(0x4815A4 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4815B2 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4815C3 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4815E4 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch483020()
	{
		injector::WriteMemory(0x483092 + 2, offsetOf(&CharactersGold::field_64608), true);
		injector::WriteMemory(0x483098 + 2, offsetOf(&CharactersGold::field_64604), true);
		injector::WriteMemory(0x4830B0 + 2, offsetOf(&CharactersGold::field_73780), true);
		injector::WriteMemory(0x4830B6 + 2, offsetOf(&CharactersGold::field_73776), true);
		injector::WriteMemory(0x4830C4 + 2, offsetOf(&CharactersGold::field_73776), true);
		injector::WriteMemory(0x4830CA + 2, offsetOf(&CharactersGold::field_73780), true);
	}

	//+
	void Patch4811B0()
	{
		injector::WriteMemory(0x4811F5 + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481223 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch47F550(const uint8_t characters)
	{
		injector::WriteMemory(0x47F550 + 2, offsetOf(&CharactersGold::field_54620), true);
		injector::WriteMemory(0x47F566 + 2, characters, true);
		injector::WriteMemory(0x47F570 + 3, offsetOf(&CharactersGold::field_54620), true);
		injector::WriteMemory(0x47F5A7 + 2, characters, true);
		injector::WriteMemory(0x47F5AC + 1, characters, true);
	}

	//+
	void Patch4843F0()
	{
		injector::WriteMemory(0x4843F0 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch484400()
	{
		injector::WriteMemory(0x484400 + 2, offsetOf(&CharactersGold::field_110204), true);
	}

	//+
	void Patch484420()
	{
		injector::WriteMemory(0x484424 + 4, offsetOf(&CharactersGold::field_109504), true);
	}

	//+
	void Patch481240()
	{
		injector::WriteMemory(0x481245 + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x481254 + 2, offsetOf(&CharactersGold::field_109504), true);
		injector::WriteMemory(0x481263 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x48126C + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481298 + 2, offsetOf(&CharactersGold::field_110204), true);
	}

	//+
	void Patch481330()
	{
		injector::WriteMemory(0x481335 + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x481345 + 2, offsetOf(&CharactersGold::field_109504), true);
		injector::WriteMemory(0x481354 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x48135D + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481393 + 2, offsetOf(&CharactersGold::field_110204), true);
	}

	//+
	void Patch4812B0()
	{
		injector::WriteMemory(0x4812B5 + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x4812C4 + 2, offsetOf(&CharactersGold::field_109504), true);
		injector::WriteMemory(0x4812D3 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4812DC + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x48130C + 2, offsetOf(&CharactersGold::field_110204), true);
	}

	//+
	void Patch484410()
	{
		injector::WriteMemory(0x484410 + 2, offsetOf(&CharactersGold::field_109500), true);
	}

	//+
	void Patch484430()
	{
		injector::WriteMemory(0x484434 + 4, offsetOf(&CharactersGold::field_108800), true);
	}

	//+
	void Patch484440()
	{
		injector::WriteMemory(0x484448 + 3, offsetOf(&CharactersGold::field_54800), true);
	}

	//+
	void Patch484460()
	{
		injector::WriteMemory(0x484468 + 3, offsetOf(&CharactersGold::field_54800) + 4, true);
	}

	//+
	void Patch484480()
	{
		injector::WriteMemory(0x484488 + 3, offsetOf(&CharactersGold::field_54800) + 8, true);
	}

	//+
	void Patch4844A0()
	{
		injector::WriteMemory(0x4844A8 + 3, offsetOf(&CharactersGold::field_54800) + 12, true);
	}

	//+
	void Patch4844C0()
	{
		injector::WriteMemory(0x4844C8 + 4, offsetOf(&CharactersGold::field_54800) + 21, true);
	}

	//+
	void Patch484630()
	{
		injector::WriteMemory(0x484638 + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x48463F + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch4844E0()
	{
		injector::WriteMemory(0x4844E9 + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
	}

	//+
	void Patch484560()
	{
		injector::WriteMemory(0x484568 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch484580()
	{
		injector::WriteMemory(0x484588 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch481680()
	{
		injector::WriteMemory(0x481688 + 3, offsetOf(&CharactersGold::field_54800), true);
		injector::WriteMemory(0x481696 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch4845A0()
	{
		injector::WriteMemory(0x4845A8 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch4845C0()
	{
		injector::WriteMemory(0x4845C8 + 4, offsetOf(&CharactersGold::field_54800) + 22, true);
	}

	//+
	void Patch4845E0()
	{
		injector::WriteMemory(0x4845E8 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x4845EF + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch484500()
	{
		injector::WriteMemory(0x484508 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch484520()
	{
		injector::WriteMemory(0x484528 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch484540()
	{
		injector::WriteMemory(0x484548 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
	}

	//+
	void Patch484170(const uint8_t statsHero)
	{
		injector::WriteMemory(0x48417F + 2, offsetOf(&CharactersGold::field_108796), true);
		injector::WriteMemory(0x484189 + 2, offsetOf(&CharactersGold::field_106852), true);
		injector::WriteMemory(0x4841A9 + 3, offsetOf(&CharactersGold::field_106856), true);
		injector::WriteMemory(0x4841B4 + 2, offsetOf(&CharactersGold::field_106848), true);
		injector::WriteMemory(0x4841B4 + 6, statsHero, true);
		injector::WriteMemory(0x4841BD + 2, offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4841CB + 3, offsetOf(&CharactersGold::field_104256), true);
	}

	//+
	void Patch483FF0()
	{
		injector::WriteMemory(0x48402C + 2, offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x484068 + 2, offsetOf(&CharactersGold::field_106852), true);
	}

	//+
	void Patch4813B0(const uint8_t statsHero)
	{
		injector::WriteMemory(0x4813B5 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4813D3 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x4813E0 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4813EA + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481402 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481423 + 2, offsetOf(&CharactersGold::field_108800), true);
		injector::WriteMemory(0x481441 + 2, offsetOf(&CharactersGold::field_104249), true);
		injector::WriteMemory(0x48144F + 2, offsetOf(&CharactersGold::field_89016), true);
		injector::WriteMemory(0x481455 + 1, statsHero, true);
	}

	//+
	void Patch484790(const uint8_t statsHero)
	{
		injector::WriteMemory(0x4847A5 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4847C3 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x4847D4 + 2, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x4847DC + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4847F6 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4847FC + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x484814 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x484835 + 2, offsetOf(&CharactersGold::field_108800), true);
		injector::WriteMemory(0x484843 + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x484857 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x48485F + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x484866 + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x48487D + 2, offsetOf(&CharactersGold::field_104249), true);
		injector::WriteMemory(0x48488B + 2, offsetOf(&CharactersGold::field_89016), true);
		injector::WriteMemory(0x484891 + 1, statsHero, true);
	}

	//+
	void Patch4822E0()
	{
		injector::WriteMemory(0x4822F3 + 2, sizeof(CharactersGold::field_73784), true);
		injector::WriteMemory(0x4822F9 + 3, offsetOf(&CharactersGold::field_73784), true);
		injector::WriteMemory(0x482308 + 3, offsetOf(&CharactersGold::field_104248), true);
	}

	//+
	void Patch481480(const uint8_t statsHero)
	{
		injector::WriteMemory(0x48148C + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481492 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4814A6 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4814C8 + 2, statsHero, true);
	}

	//+
	void Patch482320()
	{
		injector::WriteMemory(0x482331 + 3, offsetOf(&CharactersGold::field_104248), true);
		injector::WriteMemory(0x48233E + 2, sizeof(CharactersGold::field_73784), true);
		injector::WriteMemory(0x482344 + 3, offsetOf(&CharactersGold::field_73784), true);
		injector::WriteMemory(0x482353 + 3, offsetOf(&CharactersGold::field_104248), true);
	}

	//+
	void Patch4814E0(const uint8_t statsHero)
	{
		injector::WriteMemory(0x4814EC + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4814F2 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481506 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481528 + 2, statsHero, true);
	}

	//+
	void Patch481540(const uint8_t statsHero)
	{
		injector::WriteMemory(0x481543 + 2, offsetOf(&CharactersGold::field_104249), true);
		injector::WriteMemory(0x481552 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481558 + 2, offsetOf(&CharactersGold::field_89016), true);
		injector::WriteMemory(0x481560 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481574 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481596 + 2, statsHero, true);
	}

	//+
	void Patch481860()
	{
		injector::WriteMemory(0x48187C + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481887 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch4818B0()
	{
		injector::WriteMemory(0x4818CC + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x4818D7 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch481900()
	{
		injector::WriteMemory(0x481903 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481915 + 3, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481926 + 2, offsetOf(&CharactersGold::field_54792), true);
	}

	//+
	void Patch4819E0()
	{
		injector::WriteMemory(0x4819E4 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4819FD + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481A17 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481AA7 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch481AD0()
	{
		injector::WriteMemory(0x481AE6 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481B00 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481B2D + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481CE7 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch481D20()
	{
		injector::WriteMemory(0x481D24 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481D36 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481D4C + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x481D71 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch481950()
	{
		injector::WriteMemory(0x481954 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x481962 + 2, offsetOf(&CharactersGold::field_54800) + 16, true);
		injector::WriteMemory(0x481975 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4819C3 + 2, offsetOf(&CharactersGold::field_64600), true);
	}

	//+
	void Patch4838E0(const uint8_t statsHero)
	{
		injector::WriteMemory(0x4838F6 + 2, statsHero, true);
		injector::WriteMemory(0x483937 + 2, statsHero, true);
		injector::WriteMemory(0x483943 + 2, statsHero, true);
		injector::WriteMemory(0x483966 + 2, statsHero, true);
		injector::WriteMemory(0x4839A7 + 2, statsHero, true);
	}

	//+
	void Patch483D60(const uint8_t statsHero)
	{
		injector::WriteMemory(0x483D62 + 2, sizeof(CharactersGold::field_73784) * 2, true);
		injector::WriteMemory(0x483D75 + 1, statsHero, true);
		injector::WriteMemory(0x483D7C + 2, sizeof(CharactersGold::field_73784), true);
	}

	//+
	void Patch483DD0(const uint8_t statsHero)
	{
		injector::WriteMemory(0x483DE5 + 1, statsHero, true);
		injector::WriteMemory(0x483DF2 + 2, sizeof(CharactersGold::field_73784), true);
	}

	//+
	void Patch482820(const uint8_t characters)
	{
		injector::WriteMemory(0x48282D + 2, offsetOf(&CharactersGold::field_54608), true);
		injector::WriteMemory(0x482833 + 2, offsetOf(&CharactersGold::field_54612), true);
		injector::WriteMemory(0x482839 + 2, offsetOf(&CharactersGold::field_54616), true);
		injector::WriteMemory(0x482841 + 2, offsetOf(&CharactersGold::field_54620), true);
		injector::WriteMemory(0x48284C + 2, offsetOf(&CharactersGold::field_54628), true);
		injector::WriteMemory(0x482859 + 2, offsetOf(&CharactersGold::field_54788), true);
		injector::WriteMemory(0x48285F + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x482865 + 1, characters - 1, true);
		injector::WriteMemory(0x48287C + 2, offsetOf(&CharactersGold::field_54788), true);
		injector::WriteMemory(0x482882 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x48288A + 2, offsetOf(&CharactersGold::field_54632), true);
		injector::WriteMemory(0x482892 + 2, offsetOf(&CharactersGold::field_54792), true);
		injector::WriteMemory(0x4828A8 + 2, characters, true);
	}

	//+
	void Patch484700()
	{
		injector::WriteMemory(0x48470D + 1, sizeof(CharactersGold), true);
	}

	//+
	void Patch484960()
	{
		injector::WriteMemory(0x484ACE + 1, sizeof(CharactersGold), true);
	}

	//+
	void Patch4827B0()
	{
		injector::WriteMemory<uint8_t>(0x4827C1 + 3, sizeof(CharactersGold::field_4), true);
		injector::WriteMemory(0x4827E4 + 3, offsetOf(&CharactersGold::field_54632), true);
	}

	//+
	void Patch4846B0()
	{
		injector::WriteMemory(0x4846BB + 2, offsetOf(&CharactersGold::field_106852), true);
		injector::WriteMemory(0x4846C6 + 2, offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4846D1 + 2, offsetOf(&CharactersGold::field_73784), true);
	}

	//+
	void Patch484B40()
	{
		injector::WriteMemory(0x484B8D + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x484B94 + 3, offsetOf(&CharactersGold::field_54800) + 25, true);
		injector::WriteMemory(0x484BAE + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x484BBA + 2, offsetOf(&CharactersGold::field_109504), true);
	}

	//+
	void Patch6FC680(const uint8_t statsHero)
	{
		injector::WriteMemory(0x6FC6D0 + 4, statsHero - 1, true);
	}

	//+
	void Patch480A60(const uint8_t statsHero)
	{
		injector::WriteMemory(0x480A62 + 2, offsetOf(&CharactersGold::field_106836) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480A68 + 3, offsetOf(&CharactersGold::field_106720) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480A75 + 3, offsetOf(&CharactersGold::field_106844) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480A8B + 2, offsetOf(&CharactersGold::field_106836) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480A94 + 2, statsHero, true);
		injector::WriteMemory(0x480A97 + 2, offsetOf(&CharactersGold::field_106836) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480A9F + 2, offsetOf(&CharactersGold::field_106836) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480AA9 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480AAF + 2, offsetOf(&CharactersGold::field_106848) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x480AB7 + 2, offsetOf(&CharactersGold::field_106848) - offsetOf(&CharactersGold::field_104252), true);
	}

	//+
	void Patch483860(const uint8_t statsHero)
	{
		injector::WriteMemory(0x483886 + 3, offsetOf(&CharactersGold::field_106844) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48388D + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x483893 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48389B + 2, statsHero, true);
		injector::WriteMemory(0x48389E + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4838A4 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4838AC + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4838B6 + 1, statsHero - 1, true);
		injector::WriteMemory(0x4838BE + 3, offsetOf(&CharactersGold::field_106720) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4838C5 + 2, offsetOf(&CharactersGold::field_106848) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4838CD + 2, offsetOf(&CharactersGold::field_106848) - offsetOf(&CharactersGold::field_104252), true);
	}

	//+
	void Patch482060(const uint8_t statsHero)
	{
		injector::WriteMemory(0x482064 + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48206A + 2, offsetOf(&CharactersGold::field_106836) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x482070 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x482080 + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x482086 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48208E + 2, statsHero, true);
		injector::WriteMemory(0x482091 + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x482097 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48209F + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4820A5 + 1, statsHero - 1, true);
		injector::WriteMemory(0x4820AD + 3, offsetOf(&CharactersGold::field_106720) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x4820B5 + 2, statsHero, true);
	}

	//+
	void Patch47FDE0(const uint8_t statsHero)
	{
		injector::WriteMemory(0x47FE06 + 2, statsHero, true);
		injector::WriteMemory(0x47FE1A + 3, offsetOf(&CharactersGold::field_106844) - offsetOf(&CharactersGold::field_104252), true);
	}

	//+
	void Patch484280()
	{
		injector::WriteMemory(0x484292 + 2, offsetOf(&CharactersGold::field_54800) + 8, true);
		injector::WriteMemory(0x4842B1 + 2, offsetOf(&CharactersGold::field_64600), true);
		injector::WriteMemory(0x4842B7 + 2, offsetOf(&CharactersGold::field_64616), true);
		injector::WriteMemory(0x4842BD + 2, offsetOf(&CharactersGold::field_64608), true);
		injector::WriteMemory(0x4842C7 + 2, offsetOf(&CharactersGold::field_64612), true);
		injector::WriteMemory(0x4842D1 + 2, offsetOf(&CharactersGold::field_64604), true);
		injector::WriteMemory(0x4842E0 + 2, offsetOf(&CharactersGold::field_64604), true);
		injector::WriteMemory(0x4842EA + 2, offsetOf(&CharactersGold::field_73784), true);
		injector::WriteMemory(0x4842F0 + 2, offsetOf(&CharactersGold::field_73776), true);
		injector::WriteMemory(0x4842FA + 2, offsetOf(&CharactersGold::field_73780), true);
		injector::WriteMemory(0x484305 + 2, offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48430D + 2, offsetOf(&CharactersGold::field_106832) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x484313 + 2, offsetOf(&CharactersGold::field_106836) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x484319 + 2, offsetOf(&CharactersGold::field_106840) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x48431F + 2, offsetOf(&CharactersGold::field_106844) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x484325 + 2, offsetOf(&CharactersGold::field_106848) - offsetOf(&CharactersGold::field_104252), true);
		injector::WriteMemory(0x484330 + 2, offsetOf(&CharactersGold::field_106852), true);
		injector::WriteMemory(0x48435B + 2, offsetOf(&CharactersGold::field_109500), true);
		injector::WriteMemory(0x484361 + 2, offsetOf(&CharactersGold::field_110204), true);
		injector::WriteMemory(0x484367 + 3, offsetOf(&CharactersGold::field_104248), true);
	}

	//+
	void Patch4840C0()
	{
		injector::WriteMemory<uint8_t>(0x4840CE + 3, sizeof(CharactersGold::field_104252), true);
	}

	//COptions
	void Patch4EF8A0(const uint8_t statsHero)
	{
		injector::WriteMemory<uint16_t>(0x4EF8AA + 2, statsHero + 1, true);
	}

	void Patch4EF860(const uint8_t statsHero)
	{
		injector::WriteMemory<uint8_t>(0x4EF86A + 3, statsHero + 1, true);
	}

	void Patch4EF810(const uint8_t statsHero)
	{
		injector::WriteMemory<uint8_t>(0x4EF81E + 3, statsHero + 1, true);
	}

	void Patch4EF7A0(const uint8_t statsHero)
	{
		injector::WriteMemory<uint8_t>(0x4EF7AA + 3, statsHero + 1, true);
	}

	void Patch4EE660(const uint8_t statsHero)
	{
		injector::WriteMemory(0x4EE672 + 1, statsHero + 1, true);
	}

	void Patch4EDFF0(const uint8_t statsHero)
	{
		injector::WriteMemory<uint8_t>(0x4EE051 + 2, statsHero + 1, true);
	}

	void ChangeLimit(int id, const std::string& value)
	{
		const uint8_t statsHero = 39;
		const uint8_t characters = statsHero + 11;

		switch (id)
		{
			case Characters:
				Patch4816C0();
				Patch484F70();
				Patch480840();
				Patch483680();
				Patch4833F0();
				Patch481FD0(characters);
				Patch47F310();
				Patch483A50();
				Patch483320(characters);
				Patch47FF10(characters);
				Patch481F30(characters);
				Patch481600();
				Patch483B70(characters);
				Patch480A00(characters);
				Patch482360();
				Patch4823C0();
				Patch4807E0();
				Patch4815A0();
				Patch483020();
				Patch4811B0();
				Patch47F550(characters);
				Patch4843F0();
				Patch484400();
				Patch484420();
				Patch481240();
				Patch481330();
				Patch4812B0();
				Patch484410();
				Patch484430();
				Patch484440();
				Patch484460();
				Patch484480();
				Patch4844A0();
				Patch4844C0();
				Patch484630();
				Patch4844E0();
				Patch484560();
				Patch484580();
				Patch481680();
				Patch4845A0();
				Patch4845C0();
				Patch4845E0();
				Patch484500();
				Patch484520();
				Patch484540();
				Patch484170(statsHero);
				Patch480A60(statsHero);
				Patch483FF0();
				Patch483860(statsHero);
				Patch4813B0(statsHero);
				Patch484790(statsHero);
				Patch4822E0();
				Patch481480(statsHero);
				Patch482320();
				Patch4814E0(statsHero);
				Patch481540(statsHero);
				Patch481860();
				Patch4818B0();
				Patch481900();
				Patch4819E0();
				Patch481AD0();
				Patch481D20();
				Patch481950();
				Patch482060(statsHero);
				Patch484280();
				Patch4838E0(statsHero);
				Patch483D60(statsHero);
				Patch483DD0(statsHero);
				Patch482820(characters);
				Patch484700();
				Patch484960();
				Patch47FDE0(statsHero);
				Patch4827B0();
				Patch4846B0();
				Patch484B40();
				Patch6FC680(statsHero);
				Patch4840C0();

				/*Patch4EF8A0(statsHero);
				Patch4EF860(statsHero);
				Patch4EF810(statsHero);
				Patch4EF7A0(statsHero);

				Patch4EE660(statsHero);
				Patch4EDFF0(statsHero);*/

				break;
		}
	}
} charactersMUA;