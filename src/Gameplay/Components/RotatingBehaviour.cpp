#include "Gameplay/Components/RotatingBehaviour.h"

#include "Gameplay/GameObject.h"

#include "Utils/ImGuiHelper.h"
#include "Utils/JsonGlmHelpers.h"

void RotatingBehaviour::Update(float deltaTime) {
	GetGameObject()->SetPostion(GetGameObject()->GetPosition() + RotationSpeed * deltaTime);
	
	if (GetGameObject()->GetPosition().x > 50 || GetGameObject()->GetPosition().x < -50)
	{
		GetGameObject()->GetParent()->SetPostion(GetGameObject()->GetParent()->GetPosition() - glm::vec3(0, 3, 0));

		for (int i = 0; i < GetGameObject()->GetParent()->GetChildren().size(); i++)
		{
			GetGameObject()->GetParent()->GetChildren()[i]->Get<RotatingBehaviour>()->Flip();
			GetGameObject()->GetParent()->GetChildren()[i]->Get<RotatingBehaviour>()->SpeedUp();
		}
	}
}


void RotatingBehaviour::Flip()
{
	RotationSpeed *= -1;
}

void RotatingBehaviour::SpeedUp()
{
	RotationSpeed.x += 1;
}

void RotatingBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat3, "Speed", &RotationSpeed.x);
}

nlohmann::json RotatingBehaviour::ToJson() const {
	return {
		{ "speed", RotationSpeed }
	};
}

RotatingBehaviour::Sptr RotatingBehaviour::FromJson(const nlohmann::json& data) {
	RotatingBehaviour::Sptr result = std::make_shared<RotatingBehaviour>();
	result->RotationSpeed = JsonGet(data, "speed", result->RotationSpeed);
	return result;
}
