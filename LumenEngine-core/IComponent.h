#pragma once
class IComponent
{
public:
	GameObject *owner;
	virtual void Init() = 0;
	virtual void Register() = 0;
	virtual void Update(double dt) = 0;
	virtual void Shutdown() = 0;
};

