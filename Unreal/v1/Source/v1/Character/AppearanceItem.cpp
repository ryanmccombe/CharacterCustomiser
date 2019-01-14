// Fill out your copyright notice in the Description page of Project Settings.

#include "AppearanceItem.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

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

void UAppearanceItem::ApplyColourOption(USkeletalMeshComponent* Component, int32 OptionIndex, FLinearColor Colour)
{
	if (!ensure(Component)) return;

	UMaterialInterface * CurrentMaterial = Component->GetMaterial(ColourOptions[OptionIndex].MaterialId);
	UMaterialInstanceDynamic* NewMaterial = Component->CreateDynamicMaterialInstance(ColourOptions[OptionIndex].MaterialId, CurrentMaterial);

	if (ensure(NewMaterial)) {
		NewMaterial->SetVectorParameterValue(ColourOptions[OptionIndex].ParameterName, ColourOptions[OptionIndex].DefaultColor);
		Component->SetMaterial(1, NewMaterial);
	}
}
