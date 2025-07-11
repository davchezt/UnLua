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

#include "Blueprint/UserWidget.h"
#include "UnLuaTestCommon.h"
#include "UnLuaTestHelpers.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

struct FUnLuaTest_Issue473 : FUnLuaTestBase
{
    virtual bool InstantTest() override
    {
        return true;
    }

    virtual bool SetUp() override
    {
        FUnLuaTestBase::SetUp();

        const auto Chunk = R"(
            local StubClass = UE.UClass.Load("/UnLuaTestSuite/Tests/Regression/Issue473/BP_UnLuaTestStub_Issue473.BP_UnLuaTestStub_Issue473_C")
            local Stub = NewObject(StubClass)
            print("Stub.Name=", Stub.Name)
            return Stub:TestForIssue473(Stub.Name)
        )";
        UnLua::RunChunk(L, Chunk);

        const auto Actual = lua_tostring(L, -1);
        RUNNER_TEST_EQUAL(UTF8_TO_TCHAR(Actual), TEXT("虚幻引擎"));
        return true;
    }
};

IMPLEMENT_UNLUA_INSTANT_TEST(FUnLuaTest_Issue473, TEXT("UnLua.Regression.Issue473 FName类型参数中文乱码"))

#endif
