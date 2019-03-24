#pragma once
#include <unordered_map>
#include <map>
#include <memory>

namespace stde
{
	using namespace std;
	template<
		class _KeyType,
		class _ValueType,
		class _Container_Type = std::map<_KeyType, _ValueType>,
		class _Reverse_Container_Type = std::map<_ValueType, _KeyType>>
	class bimap
	{
	public:
		using key_type = _KeyType;
		using value_type = _ValueType;
		using rkey_type = _ValueType;
		using rvalue_type = _KeyType;
	private:
		using _Tree = _Container_Type;
		using _RTree = _Reverse_Container_Type;
		using _Tree_Node = std::pair<key_type, value_type>;
		using _RTree_Node = std::pair<rkey_type, rvalue_type>;
	private:
		// Test for the container types
		static_assert(
			is_same_v<key_type, typename _Tree::key_type>,
			"bimap::key_type has to match _Container_Type::key_type!");
		static_assert(
			is_same_v<value_type, typename _Tree::mapped_type>,
			"bimap::value_type has to match _Container_Type::value_type!");
		static_assert(
			is_same_v<rkey_type, typename _RTree::key_type>,
			"bimap::rkey_type has to match _Reverse_Container_Type::key_type!");
		static_assert(
			is_same_v<rvalue_type, typename _RTree::mapped_type>,
			"bimap::rvalue_type has to match _Reverse_Container_Type::value_type!");
	private:
		_Tree m_tree;
		_RTree m_rtree;
	public:
		/* Iterator functions */
		auto begin()	const	{ return m_tree.cbegin();	}
		auto begin()			{ return m_tree.begin();	}
		auto end  ()	const	{ return m_tree.cbegin();	}
		auto end  ()			{ return m_tree.end();		}
	public:
		/* Modification functions */
		void insert(_Tree_Node&& node)
		{
			m_tree.insert({ node.first, node.second });
			m_rtree.insert({ node.second, node.first });
		}
		void insert(const _Tree_Node& node)
		{
			m_tree.insert({ node.first, node.second });
			m_rtree.insert({ node.second, node.first });
		}
		void insert(const key_type& key, const value_type& value)
		{
			insert({ key, value });
		}
		void erase_key(const key_type& key)
		{
			auto value = get_value(key);
			m_tree.erase(key);
			m_rtree.erase(value);
		}
		void erase_value(const value_type& value)
		{
			auto key = get_key(value);
			m_tree.erase(key);
			m_rtree.erase(value);
		}
	public:
		/* Helper functions */
		bool has_key(const key_type& key) const
		{
			return m_tree.find(key) != m_tree.end();
		}
		bool has_value(const value_type& value) const
		{
			return m_rtree.find(value) != m_rtree.end();
		}
		const value_type& get_value(const key_type& key) const
		{
			return m_tree.at(key);
		}
		const key_type& get_key(const value_type& value) const
		{
			return m_rtree.at(value);
		}
		size_t size() const
		{
			if (m_tree.size() != m_rtree.size()) 
				throw(std::exception("Tree sizes do not match!"));
			return m_tree.size();
		}
	};

	template<
		class _KeyType,
		class _ValueType>
		using unordered_bimap = bimap<
			_KeyType, 
			_ValueType,
			std::unordered_map<_KeyType, _ValueType>,
			std::unordered_map<_ValueType, _KeyType>>;

}
