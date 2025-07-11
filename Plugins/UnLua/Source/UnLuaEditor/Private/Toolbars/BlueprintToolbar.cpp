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

#include "UnLuaBase.h"
#include "BlueprintToolbar.h"
#include "BlueprintEditorModule.h"

void FBlueprintToolbar::Initialize()
{
    FUnLuaEditorToolbar::Initialize();

    auto& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
    auto& ExtenderDelegates = BlueprintEditorModule.GetMenuExtensibilityManager()->GetExtenderDelegates();
    ExtenderDelegates.Add(FAssetEditorExtender::CreateLambda(
        [&](const TSharedRef<FUICommandList>, const TArray<UObject*> ContextSensitiveObjects)
        {
            const auto TargetObject = ContextSensitiveObjects.Num() < 1 ? nullptr : Cast<UBlueprint>(ContextSensitiveObjects[0]);
            return GetExtender(TargetObject);
        }));
}
