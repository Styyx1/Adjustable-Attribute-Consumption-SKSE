#pragma once

class Settings
{
public:
	[[nodiscard]] static Settings* GetSingleton()
	{
		static Settings singleton;
		return std::addressof(singleton);
	}
	bool LoadSettings();

	[[nodiscard]] bool UseStamina() const;
	[[nodiscard]] bool UseMagicka() const;
	[[nodiscard]] bool UseHorse() const;



private:
	bool useStamina{ true };
	bool useHorse{ true };
	bool useMagicka{ false };
};
