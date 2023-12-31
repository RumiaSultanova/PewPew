﻿#pragma once

class PPUtils
{
public:
	template<typename T>
	static T* GetPPPlayerComponent(APawn* PlayerPawn)
	{
		if (!PlayerPawn) { return nullptr; }

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};