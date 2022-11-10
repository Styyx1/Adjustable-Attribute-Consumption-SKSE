#include "Hooks.h"
#include "Utils.h"
#include "Settings.h"

namespace Hooks
{
	void install()
	{
		logger::info("Hooking...");

		ModActorValueHook::Hook();

		logger::info("...success");

		Settings::GetSingleton()->LoadSettings();
	}

	void ModActorValueHook::DamageActorValue(RE::Actor* actor, RE::ACTOR_VALUE_MODIFIER avModifier, RE::ActorValue actorValue, float value)
	{
		RE::PlayerCharacter* playerCharacter = RE::PlayerCharacter::GetSingleton();
		const auto           settings = Settings::GetSingleton();
		if ((actor == Utils::GetPlayerMount(playerCharacter)) && settings->UseHorse() == true && RE::ACTOR_VALUE_MODIFIER::kDamage == avModifier && RE::ActorValue::kStamina == actorValue && !playerCharacter->IsInCombat() && value < 0.0f) {
			value = 0.0f;}
				
		if ((actor == playerCharacter) && RE::ACTOR_VALUE_MODIFIER::kDamage == avModifier && settings->UseMagicka() == true && RE::ActorValue::kMagicka == actorValue && !playerCharacter->IsInCombat() && value < 0.0f) {
				value = 0.0f;}
		
		if ((actor == playerCharacter) && RE::ACTOR_VALUE_MODIFIER::kDamage == avModifier && settings->UseStamina() == true && RE::ActorValue::kStamina == actorValue && !playerCharacter->IsInCombat() && value < 0.0f) {
				value = 0.0f;}

		_SetActorValueModifiers(actor, avModifier, actorValue, value);
	}
}

