#pragma once
#include "PCH.h"
#include "RE/Offsets.h"
#include "Utils.h"
#include "Settings.h"
namespace Hooks
{
		struct ModActorValueHook : RE::ActorValueOwner
	    {
			static void thunk(RE::Actor* actor, RE::ACTOR_VALUE_MODIFIER avModifier, RE::ActorValue actorValue, float value)
			{
				const auto playerCharacter = RE::PlayerCharacter::GetSingleton();
				const auto settings = Settings::GetSingleton();
					if ((actor == Utils::GetPlayerMount(playerCharacter)) && settings->UseHorse() == true && RE::ACTOR_VALUE_MODIFIER::kDamage == avModifier && RE::ActorValue::kStamina == actorValue && !playerCharacter->IsInCombat() && value < 0.0f) {
					value = 0.0f;
					}
					if ((actor == playerCharacter) && RE::ACTOR_VALUE_MODIFIER::kDamage == avModifier && settings->UseMagicka() == true && RE::ActorValue::kMagicka == actorValue && !playerCharacter->IsInCombat() && value < 0.0f) {
					value = 0.0f;
					}
					if ((actor == playerCharacter) && RE::ACTOR_VALUE_MODIFIER::kDamage == avModifier && settings->UseStamina() == true && RE::ActorValue::kStamina == actorValue && !playerCharacter->IsInCombat() && value < 0.0f) {
					value = 0.0f;
			}
			func(actor, avModifier, actorValue, value);
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};
	static inline void Install() 
	{
		Settings::GetSingleton()->LoadSettings();

		REL::Relocation<std::uintptr_t> hook_addr{ RELOCATION_ID(37522, 38467), REL::Offset(0x14) };
		stl::write_thunk_call<ModActorValueHook>(hook_addr.address());
	}
}



