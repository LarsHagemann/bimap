## std-extension
std-extension is an extension of the standard template library that comes with C++.
Its main features are:
 * [bimap](#bimap)
 
### bimap

std::bimap<_KeyType, _ValueType> implements a interface that behaves similar to a map where you can make reverse lookups.
A bidirectional map contains pairs with 1 to 1 relations. Every key has only one value and every value corresponds to exactly one key.
It could be used to store Ids and pointer addresses. Thus you can lookup the Id by the pointer but also the pointer by Id.

std-extensions bimap can be used as a header only implementation. The only thing you need is the std library and C++.

Example:

```C++
#include <bimap.hpp>
#include <memory>
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
	void remove_by_ud(uint32_t uid)
	{
		m_id_map.erase_key(uid);
	}
	template<class _Type>
	void remove_by_ptr(_Type* ptr)
	{
		m_id_map.erase_value(static_cast<uint32_t>(ptr));
	}
	// Id Generator
	uint32_t generate_id()
	{
		// suppose random_generate() is a function that creates random numbers
		auto id = random_generate();
		while(m_id_map.has_key(id)) id = random_generate();
		return id;
	}
	void update_all()
	{
		// Assuming GuiObjectPtr is the base class of all elements in the IdConverter table
		for(auto& obj : m_id_map)
			static_cast<GuiObjectPtr>(obj.second)->update();
	}
	// You could also create a to_shared function that returns a smart pointer to the object
	// Remember to always keep one shared pointer so that your object isn't being destroyed by the 
	// shared pointer implementation accidently or remove the object from the converter in the
	// Base classes destructor.
	template<class _Type>
	std::shared<_Type> to_shared(uint32_t uid)
	{
		return std::make_shared<_Type>(static_cast<_Type*>(m_id_map.get_value(uid)));
	}
};

// ...

int main()
{
	IdConverter converter;
	// ...
	
}

```

Issues: 
 * Double memory usage. Could be minimized by using pointers for either map value.
	
