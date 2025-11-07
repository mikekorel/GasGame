#pragma once
#include "NativeGameplayTags.h"

namespace MyGameplayTags
{
	// Primary Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Resilience);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor);
 
	// Secondary Attributes
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BlockChance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Fire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Lightning);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Arcane);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Resistance_Physical);

	// Meta Attributes 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Meta_IncomingXP);

	// Input
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_4);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Passive_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Passive_2);

	// Damage
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Fire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Lightning);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Arcane);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Physical);

	// Abilities
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_None);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Summon);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_HitReact);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Status);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Status_Locked);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Status_Eligible);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Status_Unlocked);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Status_Equipped);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Type_Offensive);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Type_Passive);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Type_None);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Fire_FireBolt);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Lightning_Electrocute);

	// Cooldowns
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_Fire_FireBolt);
	
	// Effects
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effects_HitReact);

	// Combat Sockets
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_Weapon);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_RightHand);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_LeftHand);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_Tail);

	// Montages
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_4);
	
	
	const TMap<FGameplayTag, FGameplayTag>& DamageTypesToResistances();
	
}
