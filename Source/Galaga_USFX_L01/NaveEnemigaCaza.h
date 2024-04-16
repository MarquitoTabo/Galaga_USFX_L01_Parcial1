// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaCaza.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_USFX_L01_API ANaveEnemigaCaza : public ANaveEnemiga
{
	GENERATED_BODY()
private:
	int cantidadBombas;

public:
	//typedef void (ANaveEnemigaCaza::* FuncionDisparo)();
	//FuncionDisparo funcionesDisparo[4];

	ANaveEnemigaCaza();
	FORCEINLINE int GetCantidadBombas() const { return cantidadBombas; }
	FORCEINLINE void SetCantidadBombas(int _cantidadBombas) { cantidadBombas = _cantidadBombas; }
	


protected:
	virtual void Mover(float DeltaTime);
	virtual void Disparar();
	virtual void DobleDisparo();
	//virtual void DispararProyectil();
	virtual void Ametralladora();
	virtual void DispararBigBala();
	virtual void ActivArmAzar();
private: 
	FTimerHandle timerDisparo;
	FTimerHandle timerDobleDisparo;
	FTimerHandle timerAmetralladora;
	FTimerHandle timerBigBala;
	FTimerHandle timerArmAzar;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
