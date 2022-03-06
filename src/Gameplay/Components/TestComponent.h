#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/Components/RenderComponent.h"

class TestComponent : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<TestComponent> Sptr;

	std::weak_ptr<Gameplay::IComponent> Panel;

	TestComponent();
	virtual ~TestComponent();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;
	void ColorChange(int lives);

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(TestComponent);
	virtual nlohmann::json ToJson() const override;
	static TestComponent::Sptr FromJson(const nlohmann::json& blob);
	
protected:
	float test;
	int lives = 6;
	RenderComponent::Sptr _renderer;
};
