// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaTransporte.h"
#include "Galaga_USFX_L01Projectile.h"

ANaveEnemigaTransporte::ANaveEnemigaTransporte()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);
	debeDisparar = false;
	debeDobleDisparo = false;
	debeAmetralladora = false;
	debeBigBala = false;

}

void ANaveEnemigaTransporte::Mover(float DeltaTime)
{
	// Obtiene la posici�n actual del actor
	FVector PosicionActual = GetActorLocation();

	// Genera nuevas coordenadas X e Y aleatorias
	float NuevaX = FMath::RandRange(0.0f, 0.0f) * (DeltaTime / 1000.0f);
	float NuevaY = FMath::RandRange(0.0f, 0.0f) * (DeltaTime / 1000.0f);
	float NuevaZ = FMath::RandRange(0.0f, 0.0f) * DeltaTime;

	// Crea un nuevo vector de posici�n con las coordenadas aleatorias y la misma Z que la posici�n actual
	FVector NuevaPosicion = FVector(PosicionActual.X + NuevaX, PosicionActual.Y + NuevaY, PosicionActual.Z + NuevaZ);

	// Establece la nueva posici�n del actor
	SetActorLocation(NuevaPosicion);
}

void ANaveEnemigaTransporte::Disparar()
{
	//if (!debeDisparar)
	//{
	//	return;
	//}
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
//void ANaveEnemigaTransporte::DispararProyectil()
//{
//	Disparar();
//}
void ANaveEnemigaTransporte::DobleDisparo()
{
	//if (!debeDobleDisparo)
	//{
	//	return;
	//}
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
void ANaveEnemigaTransporte::Ametralladora()
{
	//if (!debeAmetralladora)
	//{
	//	return;
	//}
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
void ANaveEnemigaTransporte::DispararBigBala()
{
	//if (!debeBigBala)
	//{
	//	return;
	//}
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
 void ANaveEnemigaTransporte::ActivArmaAzar()
{
	 GetWorld()->GetTimerManager().ClearTimer(timerDisparo);
	 GetWorld()->GetTimerManager().ClearTimer(timerDobleDisparo);
	 GetWorld()->GetTimerManager().ClearTimer(timerAmetralladora);
	 GetWorld()->GetTimerManager().ClearTimer(timerBigBala);

	int32 ArmaAzar = FMath::RandRange(0, 3);
	switch (ArmaAzar)
	{
	case 0:
		GetWorld()->GetTimerManager().SetTimer(timerDisparo, this, &ANaveEnemigaTransporte::Disparar, 3.0f, true);
		break;
	case 1:
		GetWorld()->GetTimerManager().SetTimer(timerDobleDisparo, this, &ANaveEnemigaTransporte::DobleDisparo, 2.0f, true);
		break;
	case 2:
		GetWorld()->GetTimerManager().SetTimer(timerAmetralladora, this, &ANaveEnemigaTransporte::Ametralladora, 0.25f, true);
		break;
	case 3:
		GetWorld()->GetTimerManager().SetTimer(timerBigBala, this, &ANaveEnemigaTransporte::DispararBigBala, 3.0f, true);
		break;
	}
}
void ANaveEnemigaTransporte::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetTimerManager().SetTimer(timerDisparo, this, &ANaveEnemigaTransporte::Disparar, 3.0f, false);
	//GetWorld()->GetTimerManager().SetTimer(timerDobleDisparo, this, &ANaveEnemigaTransporte::DobleDisparo, 4.0f, false);
	//GetWorld()->GetTimerManager().SetTimer(timerAmetralladora, this, &ANaveEnemigaTransporte::Ametralladora, 0.1f, false);
	//GetWorld()->GetTimerManager().SetTimer(timerBigBala, this, &ANaveEnemigaTransporte::DispararBigBala, 5.0f, false);
	GetWorld()->GetTimerManager().SetTimer(timerArmaAzar, this, &ANaveEnemigaTransporte::ActivArmaAzar, 5.0f, true);
}
void ANaveEnemigaTransporte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}
