#include "SAC1GameMode.h"
#include "SAC1Character.h"
#include "SAC1GameState.h"
#include "SAC1PlayerState.h"
#include "SACPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ASAC1GameMode::ASAC1GameMode() : Super()
{
	static ConstructorHelpers::FClassFinder<ASAC1Character> PlayerPawnClassFinder(TEXT(
		"/Game/Blueprints/BP_FirstPersonCharacter"));
	if(PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
	PlayerStateClass = ASAC1PlayerState::StaticClass();

	GameStateClass = ASAC1GameState::StaticClass();

	PlayerControllerClass = ASACPlayerController::StaticClass();
}

void ASAC1GameMode::InitGame(const FString& MapName, const FString& Options,
	FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ASAC1GameMode::InitGameState()
{
	Super::InitGameState();
}

void ASAC1GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// auto : 대입받는 값의 타입으로 자동으로 결정된다.
	auto PlayerState = NewPlayer->GetPlayerState<ASAC1PlayerState>();

	if (IsValid(PlayerState))
		PlayerState->InitPlayerData(EPlayerJob::Magicion);
}

void ASAC1GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASAC1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
