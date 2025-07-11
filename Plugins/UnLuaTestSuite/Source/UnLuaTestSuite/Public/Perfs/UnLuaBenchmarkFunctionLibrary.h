// Tencent is pleased to support the open source community by making UnLua available.
// 
// Copyright (C) 2019 Tencent. All rights reserved.
//
// Licensed under the MIT License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnLuaBenchmarkFunctionLibrary.generated.h"

UCLASS()
class UUnLuaBenchmarkFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void Start(const FString& Title, const int32 N);

    UFUNCTION(BlueprintCallable)
    static void StartTimer(const FString& Title);

    UFUNCTION(BlueprintCallable)
    static void StopTimer();

    UFUNCTION(BlueprintCallable)
    static void Stop();

private:
    static TArray<FString> Messages;
    static double StartTime;
    static FString StartTitle;
    static float BenchmarkMultiplier;
    static FString BenchmarkTitle;
};
