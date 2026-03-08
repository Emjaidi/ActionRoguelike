// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "RogueActionSystemComponent.h"


URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}

void URogueAction::StartAction()
{
	float GameTime = 0.0f;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", 
		("ActionName", ActionName), 
		("WorldTime", GameTime));
}
