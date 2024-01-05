#include "Module.hpp"

namespace YimMenu
{
    Module::Module(LDR_DATA_TABLE_ENTRY *dllEntry) :
        m_Path(dllEntry->FullDllName.Buffer),
        m_Name(m_Path.filename().string()),
        m_Base(reinterpret_cast<std::uintptr_t>(dllEntry->DllBase)),
        m_Size(0)
    {
        const auto ntHeader = GetNtHeader();
        if (ntHeader)
        {
            const auto optionalHeader = ENCRYPT_OFFSET(IMAGE_NT_HEADERS, OptionalHeader).Decrypt<IMAGE_OPTIONAL_HEADER*>(ntHeader);
            m_Size = *ENCRYPT_OFFSET(IMAGE_OPTIONAL_HEADER, SizeOfCode).Decrypt<DWORD*>(optionalHeader);
        }
    }

    const std::string_view Module::Name() const
    {
        return m_Name;
    }

#pragma optimize("", off)
    void* Module::GetExportInternal(const joaat_t symbolHash) const
    {
        const auto ntHeader = GetNtHeader();
        if (!ntHeader)
            return nullptr;

        const auto optionalHeader = ENCRYPT_OFFSET(IMAGE_NT_HEADERS, OptionalHeader).Decrypt<IMAGE_OPTIONAL_HEADER*>(ntHeader);
        const auto imageDataDirectory = ENCRYPT_OFFSET(IMAGE_OPTIONAL_HEADER, DataDirectory).Decrypt<IMAGE_DATA_DIRECTORY*>(optionalHeader)[IMAGE_DIRECTORY_ENTRY_EXPORT];
        const auto exportDirectory = m_Base + *ENCRYPT_OFFSET(IMAGE_DATA_DIRECTORY, VirtualAddress).Decrypt<DWORD*>((void*)&imageDataDirectory);

        const auto nameOffsetArray = reinterpret_cast<DWORD*>(m_Base + *ENCRYPT_OFFSET(IMAGE_EXPORT_DIRECTORY, AddressOfNames).Decrypt<DWORD*>(exportDirectory));
        const auto ordinalArray = reinterpret_cast<WORD*>(m_Base + *ENCRYPT_OFFSET(IMAGE_EXPORT_DIRECTORY, AddressOfNameOrdinals).Decrypt<DWORD*>(exportDirectory));
        const auto functionOffsetArray = reinterpret_cast<DWORD*>(m_Base + *ENCRYPT_OFFSET(IMAGE_EXPORT_DIRECTORY, AddressOfFunctions).Decrypt<DWORD*>(exportDirectory));

        const auto numberOfFunctions = *ENCRYPT_OFFSET(IMAGE_EXPORT_DIRECTORY, NumberOfFunctions).Decrypt<DWORD*>(exportDirectory);

        for (std::size_t i = 0; i < numberOfFunctions; i++)
        {
            const auto functionName = reinterpret_cast<const char*>(m_Base + nameOffsetArray[i]);
            if (Joaat(functionName) != symbolHash)
                continue;
            
            return reinterpret_cast<void*>(m_Base + functionOffsetArray[ordinalArray[i]]);
        }
        return nullptr;
    }
#pragma optimize("", on)

#pragma optimize("", off)
    void** Module::GetImport(const joaat_t moduleHash, const joaat_t symbolHash) const
    {
        const auto ntHeader = GetNtHeader();
        if (!ntHeader)
            return nullptr;

        const auto optionalHeader = ENCRYPT_OFFSET(IMAGE_NT_HEADERS, OptionalHeader).Decrypt<IMAGE_OPTIONAL_HEADER*>(ntHeader);
        const auto imageDataDirectory = ENCRYPT_OFFSET(IMAGE_OPTIONAL_HEADER, DataDirectory).Decrypt<IMAGE_DATA_DIRECTORY*>(optionalHeader)[IMAGE_DIRECTORY_ENTRY_IMPORT];
        
        auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(m_Base + *ENCRYPT_OFFSET(IMAGE_DATA_DIRECTORY, VirtualAddress).Decrypt<DWORD*>((void*)&imageDataDirectory));
        for (; importDescriptor->Name; importDescriptor++)
        {
            if (const auto modName = reinterpret_cast<const char*>(m_Base + importDescriptor->Name); Joaat(modName) != moduleHash)
                continue;

            auto firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(m_Base + *ENCRYPT_OFFSET(IMAGE_IMPORT_DESCRIPTOR, FirstThunk).Decrypt<DWORD*>(importDescriptor));
            auto origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(m_Base + *ENCRYPT_OFFSET(IMAGE_IMPORT_DESCRIPTOR, OriginalFirstThunk).Decrypt<DWORD*>(importDescriptor));

            for (; origThunk->u1.AddressOfData != 0; firstThunk++, origThunk++)
            {
                if (const auto importData = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(m_Base + origThunk->u1.AddressOfData); Joaat(importData->Name) != symbolHash)
                    continue;
                return reinterpret_cast<void**>(&firstThunk->u1.Function);
            }
        }
        return nullptr;
    }
#pragma optimize("", on)

    bool Module::Valid() const
    {
        return m_Size;
    }

#pragma optimize("", off)
    IMAGE_NT_HEADERS* Module::GetNtHeader() const
    {
        if (!m_Base)
            return nullptr;

        const auto ntHeaderOffset = *ENCRYPT_OFFSET(IMAGE_DOS_HEADER, e_lfanew).Decrypt<LONG*>(m_Base);
        return reinterpret_cast<IMAGE_NT_HEADERS*>(m_Base + ntHeaderOffset);
    }
#pragma optimize("", on)
}
