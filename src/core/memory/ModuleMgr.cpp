#include "ModuleMgr.hpp"

#include <winternl.h>

namespace YimMenu
{
	inline auto GetPebPtr()
	{
		return NtCurrentTeb()->ProcessEnvironmentBlock;
	}

    Module *ModuleMgr::GetImpl(joaat_t hash)
    {
        if (const auto& it = m_CachedModules.find(hash); it != m_CachedModules.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

	void ModuleMgr::PreloadModulesImpl(const std::vector<std::string>& preloadedModules)
	{
        for (const auto module : preloadedModules)
        {
            m_PreloadedModules.push_back(LoadLibraryA(module.c_str()));
        }
	}

	bool ModuleMgr::RefreshModuleListImpl()
    {
        const auto peb = GetPebPtr();
        if (!peb)
            return false;

        const auto ldrData = peb->Ldr;
        if (!ldrData)
            return false;

        const auto moduleList = &ldrData->InMemoryOrderModuleList;
        auto moduleEntry = moduleList->Flink;
        for (; moduleList != moduleEntry; moduleEntry = moduleEntry->Flink)
        {
            const auto tableEntry = CONTAINING_RECORD(moduleEntry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
            if (!tableEntry)
                continue;

            if (tableEntry->FullDllName.Buffer)
            {
                auto module = std::make_unique<Module>(tableEntry);

                m_CachedModules.insert({ Joaat(module->Name()), std::move(module) });
            }
        }
        
        return true;
    }
}
