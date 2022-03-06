#include "Gameplay/Components/TestComponent.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"

void TestComponent::Awake()
{
	_renderer = GetComponent<RenderComponent>();
	std::cout << "TEST COMPONENT WORKING\N";
}

void TestComponent::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &test, 13.6f);
}

nlohmann::json TestComponent::ToJson() const {
	return {
		{ "test", test }
	};
}

TestComponent::TestComponent() :
	IComponent(),
	_renderer(nullptr),
	test(10.0f)
{ }

TestComponent::~TestComponent() = default;

TestComponent::Sptr TestComponent::FromJson(const nlohmann::json& blob) {
	TestComponent::Sptr result = std::make_shared<TestComponent>();
	result->test = blob["test"];
	return result;
}

void TestComponent::Update(float deltaTime)
{
	if (InputEngine::GetKeyState(GLFW_KEY_1) == ButtonState::Pressed) {
		std::cout << "1 was pressed\n";
		if (lives != 1)
		{
			lives--;
		}
		if (_renderer)
		{
			_renderer->GetMaterial()->Set("u_InvaderMaterial.selection", lives);
		}
		else
		{
			std::cout << "THERE'S NO RENDERER!\n";
		}
	}
}

void TestComponent::ColorChange(int lives)
{
	_renderer->GetMaterial()->Set("u_InvaderMaterial.selection", lives);
}