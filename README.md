## std-extension
std-extension is an extension of the standard template library that comes with C++.
Its main features are:
 * [bimap](#bimap)
 
### bimap

std::bimap<_KeyType, _ValueType> implements a interface that behaves similar to a map where you can make reverse lookups.
A bidirectional map contains pairs with 1 to 1 relations. Every key has only one value and every value corresponds to exactly one key.
It could be used to store Ids and pointer addresses. Thus you can lookup the Id by the pointer but also the pointer by Id.

Example:

```C++
#include <bimap.hpp>
class IdConverter
{
private:
    std::bimap<uint32_t, uint32_t> m_id_map;
public:
	template<class _Type>
	_Type* by_id(uint32_t uid) { return static_cast<_Type*>(m_id_map.get_value(uid)); }
	template<class _Type>
	uint32_t by_ptr(_Type* ptr) { return m_id_map.get_key(static_cast<uint32_t>(ptr)); }
	template<class _Type>
	uint32_t insert(_Type* ptr)
	{
	    if (m_id_map.has_value(static_cast<uint32_t>(ptr))) return 0;
		auto id = generate_id();
	}
	// Id Generator
	uint32_t generate_id()
	{
		// suppose random_generate() is a function that creates random numbers
		auto id = random_generate();
		while(m_id_map.has_key(id)) id = random_generate();
		return id;
	}
};

// ...

int main()
{
	IdConverter converter;
	// ...
}

```