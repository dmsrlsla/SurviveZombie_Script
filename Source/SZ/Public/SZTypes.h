#include "Engine/DataTable.h"
#include "SZTypes.generated.h"
#pragma once

USTRUCT()
struct FTestInfo
{
	GENERATED_USTRUCT_BODY()
};

UENUM()
enum class EStateCharacterEnum : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Move		UMETA(DisplayName = "Move"),
	Attack		UMETA(DisplayName = "Attack"),
	Death		UMETA(DisplayName = "Death"),
	Hit			UMETA(DisplayName = "Hit"),
	Interaction UMETA(DisplayName = "Interaction"),
	Reload		UMETA(DisplayName = "Reload"),
	MoveAttack  UMETA(DisplayName = "MoveAttack"),
};

UENUM()
enum class EItemEnum : uint8
{
	Normal		UMETA(DisplayName = "Normal"),
	Key			UMETA(DisplayName = "Key"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Ammo		UMETA(DisplayName = "Ammo"),
	Grande		UMETA(DisplayName = "Grande"),
	Knife		UMETA(DisplayName = "Knife"),
};

UENUM()
enum class EAmmoTypeEnum : uint8
{
	M4		UMETA(DisplayName = "M4"),
	SMG		UMETA(DisplayName = "SMG"),
	AKU		UMETA(DisplayName = "AKU"),
};

UENUM()
namespace ESZPhysMaterialType
{
	enum Type
	{
		Unknown,
		Rock,
		Sand,
		Cloth,
		Concrete,
		Water,
		Metal,
		Wood,
		Grass,
		Glass,
		Asphalt,
		Cardboard,
		Brick,
		Flesh
	};
}

namespace ESZDialogType
{
	enum Type
	{
		None,
		Generic,
		ControllerDisconnected
	};
}


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Normal = 0		UMETA(DisplayName = "Normal"),
	Battle = 1		UMETA(DisplayName = "Battle"),
	Chase = 2		UMETA(DisplayName = "Chase"),
	Dead = 3		UMETA(DisplayName = "Dead"),
};

#define SZ_SURFACE_Default		SurfaceType_Default
#define SZ_SURFACE_Rock			SurfaceType1
#define SZ_SURFACE_Sand			SurfaceType2
#define SZ_SURFACE_Cloth		SurfaceType3
#define SZ_SURFACE_Concrete		SurfaceType4
#define SZ_SURFACE_Water		SurfaceType5
#define SZ_SURFACE_Metal		SurfaceType6
#define SZ_SURFACE_Wood			SurfaceType7
#define SZ_SURFACE_Grass		SurfaceType8
#define SZ_SURFACE_Glass		SurfaceType9
#define SZ_SURFACE_Asphalt		SurfaceType10
#define SZ_SURFACE_Cardboard	SurfaceType11
#define SZ_SURFACE_Brick		SurfaceType12
#define SZ_SURFACE_Flesh		SurfaceType13



USTRUCT()
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	/** material */
	UPROPERTY(EditDefaultsOnly, Category = Decal)
	UMaterial* DecalMaterial;

	/** quad size (width & height) */
	UPROPERTY(EditDefaultsOnly, Category = Decal)
	float DecalSize;

	/** lifespan */
	UPROPERTY(EditDefaultsOnly, Category = Decal)
	float LifeSpan;

	/** defaults */
	FDecalData()
		: DecalMaterial(nullptr)
		, DecalSize(256.f)
		, LifeSpan(10.f)
	{
	}
};

USTRUCT(BlueprintType)
struct FZombieAssetTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	AssetIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class USkeletalMesh> AssetPath;

};

/** replicated information on a hit we've taken */
USTRUCT()
struct FSZTakeHitInfo
{
	GENERATED_USTRUCT_BODY()

		/** The amount of damage actually applied */
	UPROPERTY()
	float ActualDamage;

	/** The damage type we were hit with. */
	UPROPERTY()
	UClass* DamageTypeClass;

	/** Who hit us */
	UPROPERTY()
	TWeakObjectPtr<class ASZCharacter> PawnInstigator;

	/** Who actually caused the damage */
	UPROPERTY()
	TWeakObjectPtr<class AActor> DamageCauser;

	/** Specifies which DamageEvent below describes the damage received. */
	UPROPERTY()
	int32 DamageEventClassID;

	/** Rather this was a kill */
	UPROPERTY()
	uint32 bKilled : 1;

private:

	/** A rolling counter used to ensure the struct is dirty and will replicate. */
	UPROPERTY()
	uint8 EnsureReplicationByte;

	/** Describes general damage. */
	UPROPERTY()
	FDamageEvent GeneralDamageEvent;

	/** Describes point damage, if that is what was received. */
	UPROPERTY()
	FPointDamageEvent PointDamageEvent;

	/** Describes radial damage, if that is what was received. */
	UPROPERTY()
	FRadialDamageEvent RadialDamageEvent;

public:
	FSZTakeHitInfo();

	FDamageEvent& GetDamageEvent();
	void SetDamageEvent(const FDamageEvent& DamageEvent);
	void EnsureReplication();
};
