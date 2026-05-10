// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMassage.h"

void UScreenMassage::SetMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	MessageTextBlock->SetText(MessageText);
}
