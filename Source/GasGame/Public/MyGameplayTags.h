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

	// Input
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_4);

	// Damage
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Fire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Lightning);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Arcane);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Physical);

	// Abilities
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Attack);

	// Effects
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effects_HitReact);

	// Montages
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_Weapon);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_RightHand);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_LeftHand);

	
	const TMap<FGameplayTag, FGameplayTag>& DamageTypesToResistances();
	
}
