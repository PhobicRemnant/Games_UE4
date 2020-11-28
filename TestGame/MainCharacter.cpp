// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the SpringArm 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	// Set Mix-Max SpringArm lenght


	// Attach the camera to the SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);


	// Create weapon
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	// Equip the weapon
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);

	

	Health = MaxHealth;

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAim) 
	{
		float CurrentArmLen = SpringArm->TargetArmLength;
		SpringArm->TargetArmLength = FMath::FInterpTo(CurrentArmLen, AimOnArmLen, DeltaTime, ZoomSpeed);
	}
	else
	{
		float CurrentArmLen = SpringArm->TargetArmLength;
		SpringArm->TargetArmLength = FMath::FInterpTo(CurrentArmLen, AimOffArmLen, DeltaTime, ZoomSpeed);
	}

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis for looking and moving around of the character
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSideways"), this, &AMainCharacter::MoveSideways);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &APawn::AddControllerYawInput);

	// Bind actions of the character
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AMainCharacter::AimOn);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AMainCharacter::AimOff);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMainCharacter::Attack);
}

void AMainCharacter::MoveForward(float AxisValue)
{
	// If the character is aiming move at slower
	if(bAim)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * 0.4);
	}
	else
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * 0.9);
	}
}

void AMainCharacter::MoveSideways(float AxisValue)
{
	// If the character is aiming move at slower
	if (bAim)
	{
		AddMovementInput(GetActorRightVector() * AxisValue * 0.4);
	}
	else
	{
		AddMovementInput(GetActorRightVector() * AxisValue * 0.9);
	}
}

void AMainCharacter::AimOn()
{
	
	// Early return to avoid nullptr crash
	if (!SpringArm) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No SpringArm!!!"));

		return; 
	}

	UE_LOG(LogTemp, Warning, TEXT("Aiming!!!"));
	//SpringArm->TargetArmLength = FMath::FInterpTo(CurrentArmLen, AimOnArmLen, DeltaTime, ZoomSpeed);

	bAim = true;
}

void AMainCharacter::AimOff()
{

	// Early return to avoid nullptr crash
	if (!SpringArm)
	{
		UE_LOG(LogTemp, Warning, TEXT("No SpringArm!!!"));

		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("NotAiming!!!"));



	//SpringArm->TargetArmLength = FMath::FInterpTo(CurrentArmLen, AimOffArmLen, DeltaTime, ZoomSpeed);
	
	bAim = false;
}

void AMainCharacter::Attack()
{
	if (!Weapon) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon equipped") );
		return;
	}

	if (bAim) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Pew pew!!"));
		Weapon->PullTrigger();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Glorious melee!!"));
	}
}