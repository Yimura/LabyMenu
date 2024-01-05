#pragma once
#include "Module.hpp"

namespace YimMenu
{
    using joaat_t = std::uint32_t;

    class ModuleMgr
    {
    private:
        std::unordered_map<std::uint32_t, std::unique_ptr<Module>> m_CachedModules;
        std::vector<HMODULE> m_PreloadedModules;

        ModuleMgr() = default;
    public:
        virtual ~ModuleMgr() = default;
        ModuleMgr(const ModuleMgr&) = delete;
        ModuleMgr(ModuleMgr&&) noexcept  = delete;
        ModuleMgr& operator=(const ModuleMgr&) = delete;
        ModuleMgr& operator=(ModuleMgr&&) noexcept  = delete;

        static Module* Get(const std::string_view name)
        { return GetInstance().GetImpl(Joaat(name)); }
        static Module* Get(joaat_t hash)
        { return GetInstance().GetImpl(hash); }

        /**
         * @brief This function will make sure that certain DLL's are present for when they're fetched
         * @param preloadedModules 
         */
        static void PreloadModules(const std::vector<std::string>& preloadedModules)
        { GetInstance().PreloadModulesImpl(preloadedModules); }

        /**
         * @brief Loads the modules from PEB and caches them.
         * 
         * @return true If the peb is found and modules have been cached.
         * @return false If the peb or peb->Ldr pointer were invalid. 
         */
        static bool RefreshModuleList()
        { return GetInstance().RefreshModuleListImpl(); }

    private:
        static ModuleMgr& GetInstance()
        {
            static ModuleMgr i{};
            return i;
        }

        Module* GetImpl(joaat_t hash);
        void PreloadModulesImpl(const std::vector<std::string>& preloadedModules);
        bool RefreshModuleListImpl();

    };
}
