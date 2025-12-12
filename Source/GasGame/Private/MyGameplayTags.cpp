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

	// Meta Attributes 
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Meta_IncomingXP, "Attributes.Meta.IncomingXP");

	// Input
	UE_DEFINE_GAMEPLAY_TAG(InputTag, "InputTag");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, "InputTag.LMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, "InputTag.RMB");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_1, "InputTag.1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_2, "InputTag.2");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_3, "InputTag.3");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_4, "InputTag.4");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Passive_1, "InputTag.Passive.1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Passive_2, "InputTag.Passive.2");

	// Damage
	UE_DEFINE_GAMEPLAY_TAG(Damage, "Damage");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Fire, "Damage.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Lightning, "Damage.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Arcane, "Damage.Arcane");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Physical, "Damage.Physical");
	
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Fire, "Attributes.Resistance.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Lightning, "Attributes.Resistance.Lightning");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Arcane, "Attributes.Resistance.Arcane");
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Resistance_Physical, "Attributes.Resistance.Physical");
	
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Burn, "Debuff.Burn");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Stun, "Debuff.Stun");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Arcane, "Debuff.Arcane");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Physical, "Debuff.Physical");
	
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Chance, "Debuff.Chance");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Damage, "Debuff.Damage");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Duration, "Debuff.Duration");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Frequency, "Debuff.Frequency");

	// Abilities
	UE_DEFINE_GAMEPLAY_TAG(Abilities, "Abilities");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_None, "Abilities.None");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Attack, "Abilities.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Summon, "Abilities.Summon");
	
	UE_DEFINE_GAMEPLAY_TAG(Abilities_HitReact, "Abilities.HitReact");
	
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Status, "Abilities.Status");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Status_Locked, "Abilities.Status.Locked");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Status_Eligible, "Abilities.Status.Eligible");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Status_Unlocked, "Abilities.Status.Unlocked");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Status_Equipped, "Abilities.Status.Equipped");
	
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Type_Offensive, "Abilities.Type.Offensive");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Type_Passive, "Abilities.Type.Passive");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Type_None, "Abilities.Type.None");
	
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Fire_FireBolt, "Abilities.Fire.FireBolt");
	UE_DEFINE_GAMEPLAY_TAG(Abilities_Lightning_Electrocute, "Abilities.Lightning.Electrocute");

	// Cooldowns
	UE_DEFINE_GAMEPLAY_TAG(Cooldown_Fire_FireBolt, "Cooldown.Fire.FireBolt");

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
	
	const TMap<FGameplayTag, FGameplayTag>& DamageTypesToDebuffs()
	{
		static TMap<FGameplayTag, FGameplayTag> Map = {
			{ Damage_Fire, Debuff_Burn },
			{ Damage_Lightning, Debuff_Stun },
			{ Damage_Arcane, Debuff_Arcane },
			{ Damage_Physical, Debuff_Physical }
		};
		return Map;
	}
}
