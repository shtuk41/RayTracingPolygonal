#ifndef __RAYTRACER_VIEWER_H
#define __RAYTRACER_VIEWER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GraphObjects.h"
#include "Camera.h"
#include "Cursor.h"

class	Scene
{
public:
	enum	CAMERA {STATIC=0,VIEWPOINT,CHASE};

	void Init();
	//against OP, but seems like true according to Stroustrup
	void Draw(GraphObject *object);
	void SetWindowSize(GLfloat w, GLfloat h) {fWindowWidth = w; fWindowHeight = h;}
	CAMERA	GetCamera() const {return eCamera;}
	void	SetCameraStatic() {pCameraCurrent = &cCameraStatic;eCamera=STATIC;}
	void	SetCameraViewpoint() {pCameraCurrent = &cCameraViewpoint;eCamera=VIEWPOINT;}
	void	SetCameraChase() {pCameraCurrent = &cCameraChase;eCamera=CHASE;}
	Camera *	GetCurrentCamera() { return pCameraCurrent;}
	CameraStatic *GetStaticCamera() {return &cCameraStatic;}

	static Scene * SceneInstance() { if (scene) return scene; else return scene = new Scene();}
protected:

private:
	static Scene *scene;

	glm::mat4 mv;
	glm::mat4 p;

	CAMERA	eCamera;
	GLfloat	fFovy;

	GLfloat fWindowWidth;
	GLfloat fWindowHeight;

	CameraStatic	cCameraStatic;
	Camera			cCameraViewpoint;
	Camera			cCameraChase;

	Camera	*pCameraCurrent;

};

class	RayTracerViewer : public Scene
{
public:
	RayTracerViewer(GLfloat minx, GLfloat maxx, GLfloat minz, GLfloat maxz) : field(minx,maxx,minz,maxz), sphere(10.0f, &cCursor), sphereBase(500.0f, &cCursor) { Init();}
	static RayTracerViewer* Instance() { if (rayTracerViewer) return rayTracerViewer; else return rayTracerViewer =  new RayTracerViewer(-50,50,-50,50);}
	static void Create() {  Instance();}
	void	DrawObjects();
	Field * FieldInstance() {return &field;}
	Cursor * CursorInstance() {return &cCursor;}


	~RayTracerViewer() { if (rayTracerViewer) delete rayTracerViewer;  rayTracerViewer = 0;}
private:
	void	Init();

	static RayTracerViewer *rayTracerViewer;


	Cursor 		cCursor;

	Field field;
	Sphere sphere;
	Sphere sphereBase;
};

#endif
