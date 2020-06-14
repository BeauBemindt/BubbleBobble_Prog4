#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <Memory>

namespace dae
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
        void destroy();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

        // template functions
        template <typename T>
        std::shared_ptr<T> AddComponent()
        {
            // This ensures that we only try to add a class the derives 
            // from Component. This is tested at compile time.
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

                // Check that we don't already have a component of this type.
                for (auto& exisitingComponent : m_spComponents)
                {
                    // Currently we prevent adding the same component twice. 
                    // This may be something we will change in future.
                    if (std::dynamic_pointer_cast<T>(exisitingComponent))
                    {
                        return std::dynamic_pointer_cast<T>(exisitingComponent);
                    }
                }

            // The object does not have this component so we create it and 
            // add it to our list.
            std::shared_ptr<T> newComponent = std::make_shared<T>(this);
            m_spComponents.push_back(newComponent);

            return newComponent;
        };

        template <typename T>
        std::shared_ptr<T> GetComponent()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

                // Check that we don't already have a component of this type.
                for (auto& exisitingComponent : m_spComponents)
                {
                    if (std::dynamic_pointer_cast<T>(exisitingComponent))
                    {
                        return std::dynamic_pointer_cast<T>(exisitingComponent);
                    }
                }

            return nullptr;
        };

        Transform m_Transform;
	private:
		std::shared_ptr<Texture2D> m_Texture{};
        std::vector<std::shared_ptr<Component>> m_spComponents;
	};
}
