#pragma once

PROJECTB_API DECLARE_LOG_CATEGORY_EXTERN(LogPB, Log, All);

namespace Debug
{
	static void Log(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1, ELogVerbosity::Type Verbosity = ELogVerbosity::Log)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.0f, Color, Msg);

			switch (Verbosity)
			{
			case ELogVerbosity::Error:
				UE_LOG(LogPB, Error, TEXT("%s"), *Msg);
				break;
			case ELogVerbosity::Warning:
				UE_LOG(LogPB, Warning, TEXT("%s"), *Msg);
				break;
			default:
				UE_LOG(LogPB, Log, TEXT("%s"), *Msg);
				break;
			}
		}
	}
	
	static void Log_Float(const FString& FloatTitle, float FloatValueToPrint, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1 , ELogVerbosity::Type Verbosity = ELogVerbosity::Log)
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(" : ") +  FString::SanitizeFloat(FloatValueToPrint);
			
			Log(FinalMsg, Color, InKey, Verbosity);
		}
	}
}
