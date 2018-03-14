#pragma once
#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include <algorithm>
#include <assert.h>

#include "Defs.hpp"
#include "Entity.hpp"


namespace data_management
{
	class DMC
	{
	public:
		DMC() = default;
		~DMC() = default;
		DMC(const DMC&) = delete;
		DMC(DMC&&) = delete;
		DMC& operator=(const DMC&) = delete;
		DMC& operator=(DMC&&) = delete;

		template<class T>
		void registerObject();

		template<class T>
		void update(TypeID id, const T& entity);

		template<class T>
		TypeID update(const T& entity);

		template<class T>
		std::shared_ptr<TypedEntity<T>> read(TypeID id);

	private:
		using TypesCollection = std::vector<std::shared_ptr<Entity>>;

		std::map<std::type_index, TypesCollection> m_entities;
		std::map<std::type_index, TypeID> m_IDs;
	};

	template<class T>
	TypeID data_management::DMC::update(const T& entity)
	{
		auto& id = m_IDs[std::type_index(typeid(T))];
		m_entities[std::type_index(typeid(T))].emplace_back(std::make_shared<TypedEntity<T>>(id, entity));
		++id;
		return (id - 1);
	}

	template<class T>
	void data_management::DMC::update(TypeID id, const T& entity)
	{
		auto& entityList = m_entities[std::type_index(typeid(T))];
		auto foundEntity = std::find_if(entityList.begin(), entityList.end(), [id](const auto& entity)
		{
			return entity->getID() == id;
		});

		if (foundEntity != entityList.end())
		{
			(*foundEntity) = std::make_shared<TypedEntity<T>>(id, entity);
		}
		else
		{
			entityList.emplace_back(std::make_shared<TypedEntity<T>>(id, entity));
		}
	}

	template<class T>
	std::shared_ptr<TypedEntity<T>> data_management::DMC::read(TypeID id)
	{
		const auto& typeCollection = m_entities[std::type_index(typeid(T))];

		auto foundElement = std::find_if(typeCollection.begin(), typeCollection.end(),
			[id](const auto& entity)
		{
			return entity->getID() == id;
		});

		if (foundElement != typeCollection.end())
		{
			return std::reinterpret_pointer_cast<TypedEntity<T>, Entity>(*foundElement);
		}
		
		assert(foundElement != typeCollection.end());

		return std::make_shared<TypedEntity<T>>(0, T());
	}

	template<class T>
	void data_management::DMC::registerObject()
	{
		auto objectsTypeIndex = std::type_index(typeid(T));
		auto foundEntry = std::find_if(m_entities.begin(), m_entities.end(), [objectsTypeIndex](const auto& entry)
		{
			return entry.first == objectsTypeIndex;
		});

		if (foundEntry == m_entities.end())
		{
			m_entities.insert(std::pair<std::type_index, TypesCollection>(objectsTypeIndex, TypesCollection()));
			m_IDs.insert(std::pair<std::type_index, TypeID>(objectsTypeIndex, 0));
		}
		
		assert(foundEntry == m_entities.end());
	}

}