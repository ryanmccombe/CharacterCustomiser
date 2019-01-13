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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHeadComponent* HeadComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UClothesComponent* BodyComponent;

};
