#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		Component(GameObject* owner);
		virtual void Update() = 0;
		virtual void Render() const = 0;
	
		~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	
	protected:
	    GameObject* m_pOwner;
	};
}


