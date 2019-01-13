#include "Color.h"

#include "AppearanceItemColourOption.generated.h"

USTRUCT(BlueprintType)
struct FAppearanceItemColourOption {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName OptionName;

	// The material element on the skeletal mesh to change the colour of
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
	int32 MaterialId;

	// The name of the parameter on that material to set to the colour
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
	FName ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	FLinearColor DefaultColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	TArray<FLinearColor> ColorOptions;

	FAppearanceItemColourOption() {
		OptionName = "";
		DefaultColor = FLinearColor::Red;
	}
};