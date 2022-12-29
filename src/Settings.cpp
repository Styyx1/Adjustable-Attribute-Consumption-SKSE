#include "Settings.h"

bool Settings::LoadSettings()
{
	constexpr auto path = L"Data/SKSE/Plugins/AdjustableAttributes.ini";

	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(path);

	const auto get_value = [&]<class T>(T& a_value, const char* a_section, const char* a_key, const char* a_comment) {
		if constexpr (std::is_same_v<bool, T>) {
			a_value = ini.GetBoolValue(a_section, a_key, a_value);
			ini.SetBoolValue(a_section, a_key, a_value, a_comment);
		} else {
			a_value = static_cast<float>(ini.GetDoubleValue(a_section, a_key, a_value));
			a_value = max(min(a_value, 1.0f), 0.0f); // Cap it to 0.0-1.0
			ini.SetDoubleValue(a_section, a_key, a_value, a_comment);
		}
	};

	get_value(useStamina, "Settings", "useStamina", ";Use infinte stamina on the player outside of combat");
	get_value(useHorse, "Settings", "use Horse", ";Use infinite stamina for your horse outside of combat");
	get_value(useMagicka, "Settings", "useMagicka", ";Use infinite Magicka on the player outside of combat");

	get_value(staminaDrain, "Settings", "staminaDrain", ";Percentage of stamina consumed outside of combat. 0.0 is for no consumption (Range: 0.0-1.0)");
	get_value(magickaDrain, "Settings", "magickaDrain", ";Percentage of magicka consumed outside of combat. 0.0 is for no consumption (Range: 0.0-1.0)");
	get_value(horseDrain, "Settings", "horseDrain", ";Percentage of stamina for your horse consumed outside of combat. 0.0 is for no consumption (Range: 0.0-1.0)");

	(void)ini.SaveFile(path);

	return true;
}

bool Settings::UseStamina() const
{
	return useStamina;
}

bool Settings::UseMagicka() const
{
	return useMagicka;
}

bool Settings::UseHorse() const
{
	return useHorse;
}

float Settings::GetHorseDrain() const
{
	return horseDrain;
}

float Settings::GetStaminaDrain() const
{
	return staminaDrain;
}

float Settings::GetMagickaDrain() const
{
	return magickaDrain;
}
