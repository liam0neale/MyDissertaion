#pragma once
#include <string>
#include "LWindow.h"
#include "Graphics.h"

class D12Core
{
public:
	D12Core(unsigned int _width, unsigned int _height, std::string _name);
	virtual ~D12Core();

	virtual bool onInit(LWindow* _window) = 0;
	virtual bool onUpdate() = 0;
	virtual bool onRender() = 0;
	virtual bool onDestroy() = 0;

	static int getWidth(){return m_width;}
	static int getHeight(){return m_height;}
	std::string getTitle(){return m_title;}

protected:
	static unsigned int m_width;
	static unsigned int m_height;
	float m_aspectRatio;

	Graphics* m_pGraphics = nullptr;

private:
	// Root assets path.
	std::string m_assetsPath;

	// Window title.
	std::string m_title;

	

	
};

