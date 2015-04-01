#ifndef GroundArea_h__
#define GroundArea_h__

/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ParticleWall.h"
#include "Object3D.h"

//Visible "wall" representing the ground
//TODO: in this case, GroundArea really should contain an Object3D instead of subclassing, as position of GroundArea can be freely altered, and the Object3D position will need to be updated.
class GroundArea :
	public ParticleWall, public Object3D
{
public:
	GroundArea(float width, float length, float height = 0.0f, bool defaultGround = true)
		: ParticleWall(width, length, UP), Object3D()
	{
		setWorldPosition(Vector3f(0.0f, height, 0.0f));
		if(defaultGround)
		{
			InitializeDefault();
		}
	};
	virtual ~GroundArea()
	{};

	//Initialization
	void InitializeDefault()
	{
		//setBatchPlane(width, length, UP);
		setBatchCube(getWidth(), 0.01f, getLength());
	}
	void Initialize();

	//Actions
	//HACK: implementation done as temporary replacement for ParticleWall, use that instead once finished
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const;
};

#endif // GroundArea_h__
