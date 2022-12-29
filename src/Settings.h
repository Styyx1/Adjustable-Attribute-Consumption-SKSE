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

	[[nodiscard]] float GetHorseDrain() const;
	[[nodiscard]] float GetStaminaDrain() const;
	[[nodiscard]] float GetMagickaDrain() const;



private:
	bool useStamina{ true };
	bool useHorse{ true };
	bool useMagicka{ false };
	float horseDrain{ 0.0f };
	float staminaDrain{ 0.0f };
	float magickaDrain{ 0.0f };
};
