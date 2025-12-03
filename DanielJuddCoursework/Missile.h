#pragma once
#include "Barrier.h"
#include "GameObject.h"
#include "Alien.h"
#include <Windows.h>
#include <vector>


class Missile : public GameObject
{
private:
	int m_damage = 0;
	bool m_isActive = false;
public:
	using GameObject::GameObject;

	virtual void update() override;
	void fireMissile(Vector2 pos);

	void setMissileDamage(int damage) { m_damage = damage; }
	int getMissileDamage() const { return m_damage; }
	bool isMissileActive() const { return m_isActive; }
	void setMissileActive(bool active) { m_isActive = active; }

	//from https://www.w3schools.com/cpp/cpp_templates.asp
	template <typename T>
	bool collisionDetection(std::vector<T>& detections)
	{
		//from https://www.geeksforgeeks.org/cpp/stdis_base_of-template-in-c-with-examples/
		if (!std::is_base_of<GameObject, T>::value)
		{
			return false;
		}

		for (int i = 0; i < detections.size(); i++)
		{
			if (detections[i].getPosition() == m_position)
			{
				//swap that element to with the back then pop it 
				//this is better because we aren't shifting the rest of the vector after the index we want to remove
				std::swap(detections[i], detections.back());
				detections.pop_back();
				m_isActive = false;
				return true;
			}
		}

		return false;
	}
};

