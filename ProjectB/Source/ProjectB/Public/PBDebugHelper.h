#pragma once

namespace Debug
{
	static void Log(const FString& Msg, const FColor& Color = FColor::Green, int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.0f, Color, Msg);
			UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
		}
	}
}
