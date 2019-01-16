// Fill out your copyright notice in the Description page of Project Settings.

#include "AppearanceItem.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SkeletalMeshComponent.h"
#include "CustomisableCharacter.h"

void UAppearanceItem::SetSkinTone(USkeletalMeshComponent* Mesh, FLinearColor Tone)
{
	if (!ensure(Mesh)) return;

	if (bUsesSkinMaterial) {
		UMaterialInterface * SkinMaterial = Mesh->GetMaterial(SkinMaterialIndex);
		UMaterialInstanceDynamic* NewSkinMaterial = Mesh->CreateDynamicMaterialInstance(SkinMaterialIndex, SkinMaterial);

		if (ensure(NewSkinMaterial)) {
			NewSkinMaterial->SetVectorParameterValue(FName("BaseColour"), Tone);
			Mesh->SetMaterial(SkinMaterialIndex, NewSkinMaterial);
		}
	}
}

// Apply a colour option from this AppearanceItem to a SkeletalMeshComponent
void UAppearanceItem::ApplyColourOption(USkeletalMeshComponent* Component, int32 OptionIndex, FLinearColor Colour)
{
	if (!ensure(Component)) return;

	UMaterialInterface * CurrentMaterial = Component->GetMaterial(ColourOptions[OptionIndex].MaterialId);
	UMaterialInstanceDynamic* NewMaterial = Component->CreateDynamicMaterialInstance(ColourOptions[OptionIndex].MaterialId, CurrentMaterial);

	if (ensure(NewMaterial)) {
		NewMaterial->SetVectorParameterValue(ColourOptions[OptionIndex].ParameterName, Colour);
		Component->SetMaterial(1, NewMaterial);
	}
}

// Apply a colour option from this AppearanceItem to the matching slot in a CustomisableCharacter
void UAppearanceItem::ApplyColourOptionToCharacter(ACustomisableCharacter* Character, int32 OptionIndex, FLinearColor Colour)
{
	ApplyColourOption(Character->ComponentBySlot[Slot], OptionIndex, Colour);
}

void UAppearanceItem::InitialiseItemOnCharacter(ACustomisableCharacter* Character)
{
	for (auto Option : ColourOptions) {
		ApplyColourOption(Character->ComponentBySlot[Slot], 0, Option.DefaultColor);
	}

	SetSkinTone(Character->ComponentBySlot[Slot], Character->SkinTone);
}
