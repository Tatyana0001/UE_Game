// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;

DECLARE_MULTICAST_DELEGATE(FIsCurClipEmpty);

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMABaseWeapon();

	void Fire();
	void StopFire();
	void ChangeClip();
	bool CanReload();
	FIsCurClipEmpty OnCurClipEmpty;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float SpeedFire = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};
	
	void Shoot();

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle TimerHandleClock;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

private:
	FAmmoWeapon CurrentAmmoWeapon;
};
