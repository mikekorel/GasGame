#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "GameAbilityTypes.h"
#include "MyGameplayTags.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/MyAbilitySystemLibrary.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct GameDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	GameDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, CritHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, CritHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, CritHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributeSet, PhysicalResistance, Target, false);

		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Secondary_CriticalHitChance, CritHitChanceDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Secondary_CriticalHitResistance, CritHitResistanceDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Secondary_CriticalHitDamage, CritHitDamageDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(MyGameplayTags::Attributes_Resistance_Physical, PhysicalResistanceDef);
	}
};

static const GameDamageStatics& DamageStatics()
{
	static GameDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, FAggregatorEvaluateParameters EvaluationParams) const
{
	for (TTuple<FGameplayTag, FGameplayTag> Pair : MyGameplayTags::DamageTypesToDebuffs())
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffTag = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage >= 0.f)
		{
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(MyGameplayTags::Debuff_Chance, false, -1.f);
			
			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = MyGameplayTags::DamageTypesToResistances()[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().TagsToCaptureDefs[ResistanceTag], EvaluationParams, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max(TargetDebuffResistance, 0.f);
			const float EffectiveDebuffChance = SourceDebuffChance * (100.f - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				// TODO 
			}
		}
	}
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}

	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}
	

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;
	
	// Debuff
	DetermineDebuff(ExecutionParams, Spec, EvaluationParams);

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	for (const TPair<FGameplayTag, FGameplayTag> Pair : MyGameplayTags::DamageTypesToResistances())
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		
		checkf(GameDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = GameDamageStatics().TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, false);
		
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParams, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;
		
		Damage += DamageTypeValue;
	}

	// Capture BlockChance on target and determine if there was a successful Block
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParams, TargetBlockChance);
	TargetBlockChance = FMath::Max(TargetBlockChance, 0.f);

	// If Block, halve the Damage
	const bool bBlocked = FMath::RandRange(1, 100) <= TargetBlockChance;
	Damage = bBlocked ? Damage / 2.f : Damage;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UMyAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	// ArmorPenetration ignores a percentage of the Target's Armor
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParams, TargetArmor);
	TargetArmor = FMath::Max(TargetArmor, 0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParams, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max(SourceArmorPenetration, 0.f);

	const UCharacterClassInfo* CharacterClassInfo = UMyAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);
	
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;
	
	float SourceCritHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritHitChanceDef, EvaluationParams, SourceCritHitChance);
	SourceCritHitChance = FMath::Max(SourceCritHitChance, 0.f);
	
	float TargetCritHitRes = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritHitResistanceDef, EvaluationParams, TargetCritHitRes);
	TargetCritHitRes = FMath::Max(TargetCritHitRes, 0.f);
	
	float SourceCritHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritHitDamageDef, EvaluationParams, SourceCritHitDamage);
	SourceCritHitDamage = FMath::Max(SourceCritHitDamage, 0.f);

	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetPlayerLevel);
	
	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	const float	EffectiveCriticalHitChance = SourceCritHitChance - TargetCritHitRes * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) <= EffectiveCriticalHitChance;

	UMyAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	// Double damage plus a bonus if critical hit 
	Damage = bCriticalHit ? 2.f * Damage + SourceCritHitDamage : Damage;
	

	// Final Damage output 
	const FGameplayModifierEvaluatedData EvaluatedData(UMainAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
