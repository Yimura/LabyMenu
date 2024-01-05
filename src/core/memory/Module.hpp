#pragma once
#include "util/OffsetEncryptor.hpp"
#include "util/Joaat.hpp"

#include <winternl.h>

namespace YimMenu
{
    class Module
    {
    public:
        Module(LDR_DATA_TABLE_ENTRY* dllEntry);
        ~Module() = default;

        const std::string_view Name() const;
        inline const std::uintptr_t Base() const;
        inline const std::uintptr_t Size() const;
        inline const std::uintptr_t End() const;

        /**
         * @brief Parses the EAT of the module for the requested symbolname
         * 
         * @param symbolName 
         * @return void* Function address of the exported function
         */
		template<typename T = void(*)>
        T GetExport(const std::string_view symbolName) const
        { return GetExport<T>(Joaat(symbolName)); }

        /**
         * @brief Parses the EAT of the module for the requested symbolhash
         * 
         * @param symbolHash 
         * @return T Function address of the exported function
         */
		template<typename T = void(*)>
        T GetExport(const joaat_t symbolHash) const
		{ return reinterpret_cast<T>(GetExportInternal(symbolHash)); }
        /**
         * @brief Gets the address of the import function
         * 
         * @param moduleName The module to get the import from
         * @param symbolName The function name
         * @return void** 
         */
        void** GetImport(const std::string_view moduleName, const std::string_view symbolName) const
        { return GetImport(Joaat(moduleName), Joaat(symbolName)); }
        /**
         * @brief Gets the address of the import function
         * 
         * @param moduleHash The module to get the import from
         * @param symbolHash The function name
         * @return void** 
         */
        void** GetImport(const joaat_t moduleHash, const joaat_t symbolHash) const;

        bool Valid() const;

    private:
		void* GetExportInternal(const joaat_t symbolHash) const;

        IMAGE_NT_HEADERS* GetNtHeader() const;

    private:
        const std::filesystem::path m_Path;
        const std::string m_Name;
        std::uintptr_t m_Base;
        std::uintptr_t m_Size;

    };

    inline const std::uintptr_t Module::Base() const
    {
        return m_Base;
    }

    inline const std::uintptr_t Module::Size() const
    {
        return m_Size;
    }

    inline const std::uintptr_t Module::End() const
    {
        return m_Base + m_Size;
    }
    
}
