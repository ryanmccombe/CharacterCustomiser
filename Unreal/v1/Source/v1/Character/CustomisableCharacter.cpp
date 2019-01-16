#include "CustomisableCharacter.h"
#include "HeadComponent.h"
#include "ClothesComponent.h"
#include "AppearanceItem.h"

ACustomisableCharacter::ACustomisableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HeadComponent = CreateDefaultSubobject<UHeadComponent>(TEXT("Head Component"));
	HeadComponent->SetupAttachment(GetMesh());
	ComponentBySlot.Add(EClothesSlot::Head, HeadComponent);

	BodyComponent = CreateDefaultSubobject<UClothesComponent>(TEXT("Body Component"));
	BodyComponent->SetupAttachment(GetMesh());
	ComponentBySlot.Add(EClothesSlot::Body, BodyComponent);
}

// Called when the game starts or when spawned
void ACustomisableCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ensureMsgf(DefaultHead && DefaultHead->Slot == EClothesSlot::Head, TEXT("Default head slot item is missing"))) {
		Equip(DefaultHead);
	}

	if (ensureMsgf(DefaultBody && DefaultBody->Slot == EClothesSlot::Body, TEXT("Default body slot item is missing"))) {
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
	if (!ensureMsgf(Item, TEXT("Tried to equip a nullptr"))) return;
	if (!ensureMsgf(Item->SkeletalMesh, TEXT("Tried to equip an item with no skeletal mesh"))) return;

	EquippedItems.Add(Item->Slot, Item);
	ComponentBySlot[Item->Slot]->SetSkeletalMesh(Item->SkeletalMesh);

	Item->InitialiseItemOnCharacter(this);
}

// TODO: Skin should be a material eventually, not just a colour
void ACustomisableCharacter::SetSkinTone(FLinearColor NewColour) {
	for (auto Equipment : EquippedItems) {
		Equipment.Value->SetSkinTone(ComponentBySlot[Equipment.Value->Slot], NewColour);
	}
}