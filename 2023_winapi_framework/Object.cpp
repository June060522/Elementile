#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Animator.h"
Object::Object()
	: m_vPos{}
	, m_vScale{}
	, m_IsAlive(true)
	, m_pAnimator(nullptr)
{
}

Object::~Object()
{
	if (nullptr != m_pAnimator)
		delete m_pAnimator;

}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::Update()
{

}

void Object::FinalUpdate()
{
}

void Object::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);

}

