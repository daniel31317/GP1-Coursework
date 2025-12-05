#pragma once
#include "Alien.h"
class SpecialAlien : public Alien
{
	private:
		float m_moveDelay = 0.05f;
		float m_moveDelta = 0.0f;
		bool m_isActive = false;
	public:
		using Alien::Alien;
		SpecialAlien() : Alien(Vector2(0, 0), 'A', ColourCodes[White], 0) {}
		virtual void update(float deltaTime) override;
		bool isActive() const { return m_isActive; }
		void spawn(Vector2 pos);
		void kill() { m_isActive = false; };
};

