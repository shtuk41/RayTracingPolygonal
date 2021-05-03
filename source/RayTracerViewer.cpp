
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/constants.hpp>

#include "RayTracerViewer.h"
#include "Lightsource.h"

Scene *Scene::scene = 0;
RayTracerViewer * RayTracerViewer::rayTracerViewer = 0;
LightSourceManager * LightSourceManager::lightSourceManager = 0;


//****************************************************************
//	Date:		03/10/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Scene
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	Initialize Scene, Cameras, Set Current Camera
//******************************************************************
void Scene::Init()
{
	eCamera = STATIC;
	cCameraStatic.Reset();

	float angle = 0.0f;//20.0f * glm::pi<float>() / 180.0f;
	glm::vec4 up = glm::rotateX(glm::vec4(0.0,1.0,0.0,0.0), angle);



	cCameraStatic.Init(glm::vec4(0,20.0,200.0,1.0),glm::vec4(0.0,0.0,0.0,1.0),up,45.0,fWindowWidth/fWindowHeight,5.0,305.0);
	cCameraChase.Init(glm::vec4(20,10,0,1.0),glm::vec4(0,10,0.0,1.0),glm::vec4(0.0,1.0,0.0,0.0),60.0,fWindowWidth/fWindowHeight,5.0,105.0);
	cCameraViewpoint.Init(glm::vec4(1,6,0,1.0),glm::vec4(-10.0,6.0,0.0,1.0),glm::vec4(0.0,10.0,0.0,0.0),60.0,fWindowWidth/fWindowHeight,5.0,105.0);

	pCameraCurrent = &cCameraStatic;

}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Scene
//	Function:	Draw
//	Inputs:		none
//	Output:		none
//	Purpose:	Draw Scene	
//******************************************************************
void	Scene::Draw(GraphObject *object)
{
	mv = pCameraCurrent ? pCameraCurrent->GetMv() : glm::mat4();
	p  = pCameraCurrent ? pCameraCurrent->GetP() : glm::mat4();

	if (object)
	{
		object->Draw(pCameraCurrent);
	}
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment4
//	Function:	Init
//	Inputs:		none
//	Output:		none
//	Purpose:	Initialize class members
//******************************************************************
void	RayTracerViewer::Init()
{
	RayTracerViewer::SceneInstance()->Init();
	//	field.Init();
	sphere.Init();
	sphereBase.Init();
	sphereBase.SetTy(-510.0);
}
//****************************************************************
//	Date:		03/02/2012
//	For:		Computer Graphics Programming SEIS 750
//	Class:		Assignment4
//	Function:	DrawObjects
//	Inputs:		none
//	Output:		none
//	Purpose:	Draw Field and Car
//******************************************************************
void	RayTracerViewer::DrawObjects()
{
	//SceneInstance()->Draw(&field);
	SceneInstance()->Draw(&sphere);
	SceneInstance()->Draw(&sphereBase);
}
