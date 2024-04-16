// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaTransporte.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_USFX_L01_API ANaveEnemigaTransporte : public ANaveEnemiga
{
	GENERATED_BODY()
private:
	float capacidadCargaPeso;
	float capacidadCargaVolumen;
	bool debeDisparar;
	bool debeDobleDisparo;
	bool debeAmetralladora;
	bool debeBigBala;
public:
	ANaveEnemigaTransporte();
	FORCEINLINE float GetCapacidadCargaPeso() const { return capacidadCargaPeso; }
	FORCEINLINE void SetCapacidadCargaPeso(float capacidad) { capacidadCargaPeso = capacidad; }
	FORCEINLINE float GetCapacidadCargaVolumen() const { return capacidadCargaVolumen; }
	FORCEINLINE void SetCapacidadCargaVolumen(float capacidad) { capacidadCargaVolumen = capacidad; }

protected:
	virtual void Mover(float DeltaTime);
	virtual void Disparar();
	virtual void DobleDisparo();
	//virtual void DispararProyectil();
	virtual void Ametralladora();
	virtual void DispararBigBala();
	virtual void ActivArmaAzar();
private:
	FTimerHandle timerDisparo;
	FTimerHandle timerDobleDisparo;
	FTimerHandle timerAmetralladora;
	FTimerHandle timerBigBala;
	FTimerHandle timerArmaAzar;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
