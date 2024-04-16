// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaCaza.h"
#include "Galaga_USFX_L01Projectile.h"

ANaveEnemigaCaza::ANaveEnemigaCaza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));
	//// Create the mesh component
	//mallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);
	
	//funcionesDisparo[0] = &ANaveEnemigaCaza::Disparar;
	//funcionesDisparo[1] = &ANaveEnemigaCaza::DobleDisparo;
	//funcionesDisparo[2] = &ANaveEnemigaCaza::Ametralladora;
	//funcionesDisparo[3] = &ANaveEnemigaCaza::DispararBigBala;
}

void ANaveEnemigaCaza::Mover(float DeltaTime)
{
	// Obtiene la posición actual del actor
	FVector PosicionActual = GetActorLocation();

	// Genera nuevas coordenadas X e Y aleatorias
	float NuevaX = FMath::RandRange(0.0f, 0.0f) * DeltaTime * velocidad;
	float NuevaY = FMath::RandRange(0.0f, 0.0f) * DeltaTime * velocidad;

	// Crea un nuevo vector de posición con las coordenadas aleatorias y la misma Z que la posición actual
	FVector NuevaPosicion = FVector(PosicionActual.X + NuevaX, PosicionActual.Y + NuevaY, PosicionActual.Z);

	// Establece la nueva posición del actor
	SetActorLocation(NuevaPosicion);
}

void ANaveEnemigaCaza::Disparar()
{
	FVector Posicion = GetActorLocation();
	FVector Offset = FVector(90, 0, 0);
	FRotator Rotacion = FRotator (0, 0, 0);
	// Spawn the projectile at the muzzle.
	UWorld* const World = GetWorld();
	if (World)
	{
		World -> SpawnActor<AGalaga_USFX_L01Projectile>(Posicion + Offset, Rotacion);
	}
}
//void ANaveEnemigaCaza::DispararProyectil()
//{
//	Disparar();
//	DobleDisparo();
//}
void ANaveEnemigaCaza::DobleDisparo()
{
	FVector Posicion = GetActorLocation();
	FVector Offset = FVector(90, -50, 0);
	FVector Offset2 = FVector(90, 50, 0);
	FRotator Rotacion = FRotator(0, 0, 0);
	// Spawn the projectile at the muzzle.
	UWorld* const World = GetWorld();
	if (World)
	{
		World->SpawnActor<AGalaga_USFX_L01Projectile>(Posicion + Offset, Rotacion);
		World->SpawnActor<AGalaga_USFX_L01Projectile>(Posicion + Offset2, Rotacion);
	}
}
void ANaveEnemigaCaza::Ametralladora()
{
	FVector Posicion = GetActorLocation();
	FVector Offset = FVector(90, 0, 0);
	FRotator Rotacion = FRotator(0, 0, 0);
	// Spawn the projectile at the muzzle.
	UWorld* const World = GetWorld();
	if (World)
	{
		World->SpawnActor<AGalaga_USFX_L01Projectile>(Posicion + Offset, Rotacion);
	}
}

void ANaveEnemigaCaza::DispararBigBala()
{
	FVector Posicion = GetActorLocation();
	FVector Offset = FVector(90, 0, 0);
	FRotator Rotacion = FRotator(0, 0, 0);
	// Spawn the projectile at the muzzle.
	UWorld* const World = GetWorld();
	if (World)
	{
		AGalaga_USFX_L01Projectile* Proyectil = World->SpawnActor<AGalaga_USFX_L01Projectile>(Posicion + Offset, Rotacion);


		Proyectil->SetActorScale3D(FVector(3.2f));
	}
}

//void ANaveEnemigaCaza::DisparoAleatorio()
//{
//	int indiceFuncionAleatoria = FMath::RandRange(0, 3);
//
//	// Llama a la función de disparo seleccionada
//	(this->*funcionesDisparo[indiceFuncionAleatoria])();
//}

void ANaveEnemigaCaza::ActivArmAzar()
{
	GetWorld()->GetTimerManager().ClearTimer(timerDisparo);
	GetWorld()->GetTimerManager().ClearTimer(timerDobleDisparo);
	GetWorld()->GetTimerManager().ClearTimer(timerAmetralladora);
	GetWorld()->GetTimerManager().ClearTimer(timerBigBala);

	int32 ArmaAzar = FMath::RandRange(0, 3);
	switch (ArmaAzar)
	{
	case 0:
		GetWorld()->GetTimerManager().SetTimer(timerDisparo, this, &ANaveEnemigaCaza::Disparar, 3.0f, true);
		break;
	case 1:
		GetWorld()->GetTimerManager().SetTimer(timerDobleDisparo, this, &ANaveEnemigaCaza::DobleDisparo, 2.0f, true);
		break;
	case 2:
		GetWorld()->GetTimerManager().SetTimer(timerAmetralladora, this, &ANaveEnemigaCaza::Ametralladora, 0.25f, true);
		break;
	case 3:
		GetWorld()->GetTimerManager().SetTimer(timerBigBala, this, &ANaveEnemigaCaza::DispararBigBala, 3.0f, true);
		break;
	}
}

void ANaveEnemigaCaza::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetTimerManager().SetTimer(timerDisparo, this, &ANaveEnemigaCaza::Disparar, 3.0f, true);
	//GetWorld()->GetTimerManager().SetTimer(timerDobleDisparo, this, &ANaveEnemigaCaza::DobleDisparo, 8.0f, true);
	//GetWorld()->GetTimerManager().SetTimer(timerAmetralladora, this, &ANaveEnemigaCaza::Ametralladora, 0.25f, true);
	//GetWorld()->GetTimerManager().SetTimer(timerBigBala, this, &ANaveEnemigaCaza::DispararBigBala, 5.0f, true);
	GetWorld()->GetTimerManager().SetTimer(timerArmAzar, this, &ANaveEnemigaCaza::ActivArmAzar, 10.0f, true);
}

void ANaveEnemigaCaza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}
