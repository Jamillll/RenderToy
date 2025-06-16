#include "CameraEntity.h"

RenderToy::CameraEntity::CameraEntity(Camera* camera)
	: m_Camera(camera) {}

void RenderToy::CameraEntity::UpdateCameraPosition()
{
	m_Camera->SetPosition(Position, Front, Up);
	m_Camera->SetFov(Fov);
}

RenderToy::CameraEntity::~CameraEntity() {}
