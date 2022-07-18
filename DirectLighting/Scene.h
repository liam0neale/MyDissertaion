#pragma once
#include "D12Core.h"

class Scene : public D12Core
{
public:
  Scene(unsigned int _width, unsigned int _height, std::string _name);
  ~Scene() override;

  bool onInit(LWindow* _window) override;
  bool onUpdate() override;
  bool onRender() override;
  bool onDestroy() override;

private:
  
};

