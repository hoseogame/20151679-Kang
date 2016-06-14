#pragma once

class Scene abstract
{
public:
	virtual void Init()		= 0;
	virtual void Update()	= 0;
	virtual void Render()	= 0;
	virtual void Release()	= 0;
};