#include "InternalFactory.hpp"

using namespace std;

void InternalFactory::FreeBuffer()
{
	for (auto& [ptr, data] : Pointers) 
	{
		delete[data.size] static_cast<char*>(ptr);
	}
}

void InternalFactory::CreateValue(const void* ptr, const size_t sizeOf)
{
	Pointers.emplace(const_cast<void*>(ptr), Data{ sizeOf, const_cast<void*>(ptr) });
}

void InternalFactory::DestroyValue(const void* ptr, const size_t sizeOf)
{
	delete[sizeOf] static_cast<char*>(const_cast<void*>(ptr));
}

