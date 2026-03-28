// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RogueAttributeSet.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

struct FRogueAttributeSet;
class URogueAction;
class URogueAttributeSet;


UENUM()
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag, float /* NewHealth*/, float /* OldHealth*/);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	virtual void InitializeComponent() override;
	
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);
	
	void ApplyAttributeChange(FGameplayTag AttributeTag, float NewValue, EAttributeModifyType ModifyType );
	
	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag);

	FOnAttributeChanged& GetAttributeListener(FGameplayTag AttributeTag);
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
	FGameplayTagContainer ActiveGameplayTags;
	
	void OnHealthChanged(FGameplayTag AttributeTag, float NewHealth, float OldHealth);
	
protected:

	UPROPERTY()
	TObjectPtr<URogueAttributeSet> Attributes;
	
	TMap<FGameplayTag, FRogueAttribute*> CachedAttributes; 
	
	UPROPERTY(EditAnywhere, Category="Attributes", NoClear)
	TSubclassOf<URogueAttributeSet> AttributeSetClass;

	TMap<FGameplayTag, FOnAttributeChanged> AttributeListeners;
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
public:

	URogueActionSystemComponent();
};
