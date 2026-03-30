// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

struct FRogueAttribute;
class URogueAction;
class URogueAttributeSet;


UENUM(BlueprintType)
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};

/* Native C++ Delegate*/
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag, float /* NewHealth*/, float /* OldHealth*/);

/* Blueprint Delegate*/
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAttributeDynamicChanged, FGameplayTag, AttributeTage, float , NewAttributeValue, float, OldAttributeValue);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	virtual void InitializeComponent() override;
	
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);
	
	UFUNCTION(BlueprintCallable)
	void ApplyAttributeChange(FGameplayTag AttributeTag, float NewValue, EAttributeModifyType ModifyType );
	
	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag) const;
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeValue(FGameplayTag InAttributeTag) const;

	FOnAttributeChanged& GetAttributeListener(FGameplayTag AttributeTag);
	
	UFUNCTION(BlueprintCallable, DisplayName = "Add Attribute Listener", meta = (Keywords = "events, delegate"))
	void AddDynamicAttributeListener(FOnAttributeDynamicChanged Event, FGameplayTag AttributeTag);
	
	UFUNCTION(BlueprintCallable, DisplayName = "Remove Attribute Listener", meta = (Keywords = "events, delegate"))
	void RemoveDynamicAttributeListener(FOnAttributeDynamicChanged Event);
	
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
	
	TMap<FGameplayTag, TArray<FOnAttributeDynamicChanged>> AttributeDynamicListeners;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
public:

	virtual void BeginPlay() override;
	URogueActionSystemComponent();
};
