#include "CustomisableCharacter.h"
#include "HeadComponent.h"
#include "ClothesComponent.h"
#include "AppearanceItem.h"
#include "Materials/MaterialInstanceDynamic.h"

ACustomisableCharacter::ACustomisableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HeadComponent = CreateDefaultSubobject<UHeadComponent>(TEXT("Head Component"));
	HeadComponent->SetupAttachment(GetMesh());

	BodyComponent = CreateDefaultSubobject<UClothesComponent>(TEXT("Body Component"));
	BodyComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void ACustomisableCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ensure(DefaultBody))
	{
		Equip(DefaultBody);
	}
	
}

// Called every frame
void ACustomisableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomisableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomisableCharacter::Equip(UAppearanceItem* Item) {
	if (!ensure(Item)) return;
	if (!ensure(Item->SkeletalMesh)) return;

	if (Item->Slot == EClothesSlot::Body)
	{
		BodyComponent->SetSkeletalMesh(Item->SkeletalMesh);

		// TODO: stop hardcoding to first option - should be a loop over all colour options
		UMaterialInterface * Material = BodyComponent->GetMaterial(1);
		UMaterialInstanceDynamic* NewMaterial = BodyComponent->CreateDynamicMaterialInstance(1, Material);

		if (ensure(NewMaterial))
		{
			NewMaterial->SetVectorParameterValue(Item->ColourOptions[0].ParameterName, Item->ColourOptions[0].DefaultColor);

			BodyComponent->SetMaterial(1, NewMaterial);
		}
	}
}
