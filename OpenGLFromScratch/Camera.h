#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 

#include "MouseListener.h"
#include "KeyboardListener.h"
#include "InputEventHandler.h"

class Camera : public MouseListener, public KeyboardListener
{
	public:
		Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction, float fov, float aspect, float z_near, float z_far);

        //Accessors
		glm::mat4 GetViewProjection() const;

        glm::vec3 GetPosition();

		//Mutators
        void SetXSensitivity(float sens);
        void SetYSensitivity(float sens);
        void SetMovementSpeed(float speed);

		void SetPosition(glm::vec3 pos);
        void SetPosition(float x, float y, float z);

		void SetLookDirection(glm::vec3 look_direction);
        void SetLookDirection(float x, float y, float z);

        void SetUpDirection(glm::vec3 up_direction);
        void SetUpDirection(float x, float y, float z);

		void SetFOV(float fov);

		void SetZNear(float z_near);
		void SetZFar(float z_far);

        void NotifyMouseEvent(SDL_Event e);
        void NotifyKeyEvent(SDL_Event e);

        void NotifyScreenResize(int width, int height);

        void Update(double delta);

	private:
		//Perspective variables.
		glm::mat4 m_Perspective;
        int m_ReferenceMousePositionX;
        int m_ReferenceMousePositionY;

        float m_XSensitivity;
        float m_YSensitivity;

        //Units: m / s
        float m_Speed;

        //Units: deg / s
        float m_RotSpeed; 

        float m_ZoomFactor;

		float m_fov;
		float m_Aspect;
		float m_zNear;
		float m_zFar;

        glm::vec3 m_Position;
		glm::vec3 m_LookDirection;
		glm::vec3 m_up;

        glm::vec3 m_DesiredLookDirection;

        //The initial values for perspective, so that resetting is always consistant.
        glm::vec3 m_StartingPos;
        glm::vec3 m_StartingLookDir;
        glm::vec3 m_StartingUp;

        //A vector that stores the direction of the mouse movement.
        glm::vec2 m_MouseDelta;
        bool m_MouseMoved;

        void UpdatePerspective();

        //Updateing position and rotation.
        void UpdateRotation(double delta);
        void HandleMovement(double delta);

        //Reset the camera's position and orientation to it's origional values.
        void Reset();
};

