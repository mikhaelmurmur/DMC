#pragma once
#include "Defs.hpp"

namespace data_management 
{
	class Entity
	{
	public:
		explicit Entity(TypeID id)
			: m_id(id)
		{}

		Entity() = delete;
		Entity(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity&&) = delete;
		virtual ~Entity() = default;

		TypeID getID() const { return m_id; }

	private:
		TypeID m_id;
	};

	template<typename T>
	class TypedEntity : public Entity
	{
	public:
		TypedEntity(TypeID id, const T& value)
			: Entity(id)
			, m_value(value)
		{}

		TypedEntity() = delete;
		TypedEntity(const TypedEntity&) = delete;
		TypedEntity(TypedEntity&&) = delete;
		TypedEntity& operator=(const TypedEntity&) = delete;
		TypedEntity& operator=(TypedEntity&&) = delete;

		T& getValue() { return m_value; }

	private:
		T m_value;
	};
}