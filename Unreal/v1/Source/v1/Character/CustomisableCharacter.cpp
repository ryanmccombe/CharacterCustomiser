#include "CustomisableCharacter.h"
#include "HeadComponent.h"
#include "ClothesComponent.h"
#include "AppearanceItem.h"
#include "Materials/MaterialInstanceDynamic.h"

ACustomisableCharacter::ACustomisableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	auto HeadComponent = CreateDefaultSubobject<UHeadComponent>(TEXT("Head Component"));
	HeadComponent->SetupAttachment(GetMesh());
	ComponentBySlot.Add(EClothesSlot::Head, HeadComponent);

	auto BodyComponent = CreateDefaultSubobject<UClothesComponent>(TEXT("Body Component"));
	BodyComponent->SetupAttachment(GetMesh());
	ComponentBySlot.Add(EClothesSlot::Body, BodyComponent);
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

	UE_LOG(LogTemp, Warning, TEXT("Equipping an Item"));

	EquippedItems.Add(Item->Slot, Item);
	ComponentBySlot[Item->Slot]->SetSkeletalMesh(Item->SkeletalMesh);

	Item->ApplyColourOption(ComponentBySlot[Item->Slot], 0, Item->ColourOptions[0].DefaultColor);
	Item->SetSkinTone(ComponentBySlot[Item->Slot], SkinTone);
}

// TODO: Skin should be a material eventually, not just a colour
void ACustomisableCharacter::SetSkinTone(FLinearColor NewColour) {
	UE_LOG(LogTemp, Warning, TEXT("Setting Skin Tone"));
	for (auto Equipment : EquippedItems) {
		UE_LOG(LogTemp, Warning, TEXT("Updating Skin Tone on an Item"));
		Equipment.Value->SetSkinTone(ComponentBySlot[Equipment.Value->Slot], NewColour);
	}
}