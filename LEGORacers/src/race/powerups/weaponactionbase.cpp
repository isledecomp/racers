#include "race/powerups/weaponactionbase.h"

#include "race/powerups/powerupprojectile.h"

// FUNCTION: LEGORACERS 0x0045bbe0
WeaponActionBase::WeaponActionBase()
{
	m_activeProjectile = 0;
	m_owner = NULL;
	m_collisionWorld = 0;
	m_ownerRacer = 0;
	m_targetRacer = 0;
	m_targetPoint = 0;
}

// FUNCTION: LEGORACERS 0x0045bc10 FOLDED
void WeaponActionBase::GetProjectilePosition(GolVec3* p_position)
{
	m_activeProjectile->GetWorldEntity()->GetBoundsCenter(p_position);
}

// FUNCTION: LEGORACERS 0x0045bc30 FOLDED
void WeaponActionBase::GetProjectileVelocity(GolVec3* p_velocity)
{
	m_activeProjectile->GetVelocity(p_velocity);
}

// FUNCTION: LEGORACERS 0x0045bc40
GolWorldEntity* WeaponActionBase::GetProjectileWorldEntity()
{
	if (m_activeProjectile) {
		return m_activeProjectile->GetWorldEntity();
	}
	else {
		return NULL;
	}
}
