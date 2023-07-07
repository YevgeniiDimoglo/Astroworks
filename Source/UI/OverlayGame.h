#pragma once

#include "Overlay.h"
#include "Widget.h"

class OverlayGame
{
public:
	OverlayGame() {}
	~OverlayGame() {}

	void initialize();

	void finalize();

	void update(float elapsedTime);

	//void render() override;

private:
	std::vector<std::shared_ptr<Widget>> widgets;
};