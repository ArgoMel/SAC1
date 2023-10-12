#include "AIState.h"

UAIState::UAIState()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIState::BeginPlay()
{
	Super::BeginPlay();
}

void UAIState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FAIDataTable* UAIState::GetData()
{
	return &m_Data;
}


