// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseInGameMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);
	
	return true;
}

void UInGameMenu::CloseInGameMenu()
{

	this->Teardown();

}

void UInGameMenu::QuitPressed()
{

	if (MMenuInterface != nullptr)
	{
		Teardown();
		MMenuInterface->LoadMainMenu();
	}

}
