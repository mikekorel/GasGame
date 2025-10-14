#include "MyGameplayTags.h"

namespace MyGameplayTags
{
	// Primary Attributes
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Strength, "Attributes.Primary.Strength");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Resilience, "Attributes.Primary.Resilience");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Vigor, "Attributes.Primary.Vigor");
 
	// Secondary Attributes
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_Armor, "Attributes.Secondary.Armor");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana");
	
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Fire, "Attributes.Resistance.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Lightning, "Attributes.Resistance.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Arcane, "Attributes.Resistance.Arcane");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Physical, "Attributes.Resistance.Physical");

	// Input
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, "InputTag.LMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, "InputTag.RMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_1, "InputTag.1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_2, "InputTag.2");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_3, "InputTag.3");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_4, "InputTag.4");

	// Damage
	UE_DEFINE_GAMEPLAY_TAG(Damage, "Damage");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Fire, "Damage.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Lightning, "Damage.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Arcane, "Damage.Arcane");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Physical, "Damage.Physical");

	// Abilities
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Attack, "Abilities.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Summon, "Abilities.Summon");
	
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Fire_FireBolt, "Abilities.Fire.FireBolt");

	// Effects 
	UE_DEFINE_GAMEPLAY_TAG(Effects_HitReact, "Effects.HitReact");

	// Combat Sockets
	UE_DEFINE_GAMEPLAY_TAG(CombatSocket_Weapon, "CombatSocket.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(CombatSocket_RightHand, "CombatSocket.RightHand");
	UE_DEFINE_GAMEPLAY_TAG(CombatSocket_LeftHand, "CombatSocket.LeftHand");
	UE_DEFINE_GAMEPLAY_TAG(CombatSocket_Tail, "CombatSocket.Tail");

	// Montages
	UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_1, "Montage.Attack.1");
	UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_2, "Montage.Attack.2");
	UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_3, "Montage.Attack.3");
	UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_4, "Montage.Attack.4");
	


	const TMap<FGameplayTag, FGameplayTag>& DamageTypesToResistances()
	{
		static TMap<FGameplayTag, FGameplayTag> Map = {
			{ Damage_Fire, Attributes_Resistance_Fire },
			{ Damage_Lightning, Attributes_Resistance_Lightning },
			{ Damage_Arcane, Attributes_Resistance_Arcane },
			{ Damage_Physical, Attributes_Resistance_Physical }
		};
		return Map;
	}
}
