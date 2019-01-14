#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AppearanceItemColourOption.h"
#include "ClothesSlot.h"

#include "AppearanceItem.generated.h"

UCLASS(BlueprintType)
class V1_API UAppearanceItem : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	EClothesSlot Slot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMesh* SkeletalMesh;

	// Does this item use the skin material from the character?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	bool bUsesSkinMaterial;

	// Which material index is the skin?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	int32 SkinMaterialIndex;

	// This is needed to work around a UE bug
	// https://answers.unrealengine.com/questions/550486/how-can-i-make-my-custom-struct-have-fields-editab.html
	UPROPERTY()
	FAppearanceItemColourOption TestField;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Options")
	TArray<FAppearanceItemColourOption> ColourOptions;

	UFUNCTION()
	void SetSkinTone(USkeletalMeshComponent* Mesh, FLinearColor Tone);

	UFUNCTION()
	void ApplyColourOption(USkeletalMeshComponent* Component, int32 OptionIndex, FLinearColor Colour);
};
