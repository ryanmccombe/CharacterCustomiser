#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AppearanceItem.h"
#include "CustomisableCharacter.generated.h"

class UHeadComponent;
class UClothesComponent;

UCLASS()
class V1_API ACustomisableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomisableCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Equipment")
	void Equip(UAppearanceItem* Item);

	UPROPERTY(EditAnywhere, Category = "Character")
	UAppearanceItem* DefaultBody;

	UPROPERTY(EditAnywhere, Category = "Character")
	UAppearanceItem* DefaultHead;

	// TODO: Skin should be a material eventually, not just a colour
	UPROPERTY(EditAnywhere, Category = "Character")
	FLinearColor SkinTone;

	// TODO: Skin should be a material eventually, not just a colour
	UPROPERTY(EditAnywhere, Category = "Character")
	TArray<FLinearColor> SkinToneOptions;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHeadComponent* HeadComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UClothesComponent* BodyComponent;

	// TODO: Skin should be a material eventually, not just a colour
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetSkinTone(FLinearColor NewColour);

protected:
	virtual void BeginPlay() override;

private:
	TMap<EClothesSlot, UAppearanceItem*> EquippedItems;
	TMap<EClothesSlot, USkeletalMeshComponent*> ComponentBySlot;
};
