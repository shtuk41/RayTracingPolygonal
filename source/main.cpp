
#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

#include "../include/shader.h"
#include "../include/texture.h"
#include "controls.hpp"
#include "common.h"

#include "RayTracerViewer.h"


GLFWwindow* g_window;

const int WINDOWS_WIDTH = 1024;
const int WINDOWS_HEIGHT = 1024;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void Init();

int main(int argc, char **argv)
{
        if (!glfwInit())
        {
        	fprintf(stderr, "Failed to initialize GLFW\n");
            return 0;
        }

        //enable anti-alising 4x with GLFW
        glfwWindowHint(GLFW_SAMPLES,4);

        //specify the client API version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        //make the GLFW forward compatible
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        //enable the OpenGL core profile for GLFW
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

        //create a GLFW window object
        g_window = glfwCreateWindow(WINDOWS_WIDTH,WINDOWS_HEIGHT, "Ray Tracing OpenGL", NULL, NULL);

        if (!g_window)
        {
        	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.  Try the 2.1 version of the tutorials.\n");
            glfwTerminate();
            return 0;
        }

       /*make the context of the specified window current for the calling thread */
        glfwMakeContextCurrent(g_window);
        glfwSwapInterval(1);

        glewExperimental = true; // needed for core profile

        if (glewInit() != GLEW_OK)
        {
                 std::cout << "Failed to Initialize GLEW" << std::endl;
                 glfwTerminate();
                 return 0;
        }

        glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetKeyCallback(g_window, key_callback);
        glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(g_window, cursor_pos_callback);

        //setup ray tracing viewer

        Init();


        do
        {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			RayTracerViewer::Instance()->DrawObjects();

			//swap buffers

			glfwSwapBuffers(g_window);
			glfwPollEvents();
        }
        while (!glfwWindowShouldClose(g_window) && glfwGetKey(g_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS);

        // Close OpenGL window and terminate GLFW
        glfwDestroyWindow(g_window);
        glfwTerminate();
        return 0;

}

void Init()
{
	RayTracerViewer::Create();

	RayTracerViewer::Instance()->SceneInstance()->SetWindowSize(GLfloat(WINDOWS_WIDTH),GLfloat(WINDOWS_HEIGHT));
	RayTracerViewer::Instance()->SceneInstance()->GetCurrentCamera()->SetAspect(GLfloat(WINDOWS_WIDTH)/GLfloat(WINDOWS_HEIGHT));

	static bool ii = true;

	if (ii)
	{
		RayTracerViewer::Instance()->SceneInstance()->Init();
		ii = false;
	}

	glViewport(0,0,WINDOWS_WIDTH,WINDOWS_HEIGHT);


	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "x: " << xpos << " y: " << ypos << std::endl;
	RayTracerViewer::Instance()->CursorInstance()->Set(xpos, ypos);

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
        if (action != GLFW_PRESS && action != GLFW_REPEAT)
        	return;

        switch (key)
        {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;

			case GLFW_KEY_SPACE:
				break;

			case GLFW_KEY_Z:
				RayTracerViewer::Instance()->SceneInstance()->GetCurrentCamera()->ZoomOutPosition();
				break;

			case GLFW_KEY_X:
				RayTracerViewer::Instance()->SceneInstance()->GetCurrentCamera()->ZoomInPosition();
				break;

			case GLFW_KEY_A:
				break;

			case GLFW_KEY_S:
				RayTracerViewer::Instance()->SceneInstance()->GetCurrentCamera()->ZoomOutLens();
				break;

			case GLFW_KEY_W:
				RayTracerViewer::Instance()->SceneInstance()->GetCurrentCamera()->ZoomInLens();
				break;

			default:
				break;
        }
}
