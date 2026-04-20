#include "ClientData.hpp"

namespace YimMenu
{
	std::string ClientData_o::GetPlayerName(void* rawPtr)
	{
		auto addr = reinterpret_cast<std::uintptr_t>(rawPtr);
		if (addr < 0x10000 || addr > 0x7FFFFFFFFFFF)
			return {};

		auto* cd = reinterpret_cast<ClientData_o*>(rawPtr);
		auto* name = cd->fields._Name_k__BackingField;
		if (!name || name->IsEmpty())
			return {};

		return name->str();
	}
}
