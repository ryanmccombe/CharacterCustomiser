#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AppearanceItem.h"
#include "CustomisableCharacter.generated.h"

class UHeadComponent;
class UClothesComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquippedSignature, UAppearanceItem*, EquippedItem);

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	TArray<FLinearColor> SkinToneOptions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	TMap<EClothesSlot, UAppearanceItem*> EquippedItems;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHeadComponent* HeadComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UClothesComponent* BodyComponent;

	// TODO: Skin should be a material eventually, not just a colour
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetSkinTone(FLinearColor NewColour);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemEquippedSignature OnItemEquipped;

	TMap<EClothesSlot, USkeletalMeshComponent*> ComponentBySlot;

protected:
	virtual void BeginPlay() override;
};
