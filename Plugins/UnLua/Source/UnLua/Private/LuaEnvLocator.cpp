﻿// Tencent is pleased to support the open source community by making UnLua available.
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

#include "Engine/World.h"
#include "LuaEnvLocator.h"

UnLua::FLuaEnv* ULuaEnvLocator::Locate(const UObject* Object)
{
    if (!Env)
    {
        Env = MakeShared<UnLua::FLuaEnv, ESPMode::ThreadSafe>();
        Env->Start();
    }
    return Env.Get();
}

void ULuaEnvLocator::HotReload()
{
    if (!Env)
        return;
    Env->HotReload();
}

void ULuaEnvLocator::Reset()
{
    Env.Reset();
}

UnLua::FLuaEnv* ULuaEnvLocator_ByGameInstance::Locate(const UObject* Object)
{
    if (!Object)
        return GetDefault();

    UGameInstance* GameInstance;
    if (Object->IsA(UGameInstance::StaticClass()))
    {
        GameInstance = (UGameInstance*)Object;
    }
    else
    {
        const auto Outer = Object->GetOuter();
        if (!Outer)
            return GetDefault();

        const auto World = Outer->GetWorld();
        if (!World)
            return GetDefault();

        GameInstance = World->GetGameInstance();
        if (!GameInstance)
            return GetDefault();
    }

    const auto Exists = Envs.Find(GameInstance);
    if (Exists)
        return (*Exists).Get();

    const TSharedPtr<UnLua::FLuaEnv, ESPMode::ThreadSafe> Ret = MakeShared<UnLua::FLuaEnv, ESPMode::ThreadSafe>();
    Ret->SetName(FString::Printf(TEXT("Env_%d"), Envs.Num() + 1));
    Ret->Start();
    Envs.Add(GameInstance, Ret);
    return Ret.Get();
}

void ULuaEnvLocator_ByGameInstance::HotReload()
{
    if (Env)
        Env->HotReload();
    for (const auto& Pair : Envs)
        Pair.Value->HotReload();
}

void ULuaEnvLocator_ByGameInstance::Reset()
{
    Env.Reset();
    for (auto Pair : Envs)
        Pair.Value.Reset();
    Envs.Empty();
}

UnLua::FLuaEnv* ULuaEnvLocator_ByGameInstance::GetDefault()
{
    if (!Env)
    {
        Env = MakeShared<UnLua::FLuaEnv, ESPMode::ThreadSafe>();
        Env->Start();
    }
    return Env.Get();
}
