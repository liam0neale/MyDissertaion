#include "Scene.h"

unsigned int Scene::m_width = 0;
unsigned int Scene::m_height = 0;
Scene::Scene(unsigned int _width, unsigned int _height, std::string _name) : D12Core(_width, _height, _name)
{
  
}

Scene::~Scene()
{
  if (m_pGraphics)
  {
    delete(m_pGraphics);
    m_pGraphics = nullptr;
  }
}

bool Scene::onInit(LWindow* _window)
{
  bool result = true;
  result = m_pGraphics->OnInit(*_window);
  return result;
}

bool Scene::onUpdate()
{
  m_pGraphics->Update();
  return true;
}

bool Scene::onRender()
{
  /*
  HRESULT hr;

  m_pGraphics->UpdatePipeline(); // update the pipeline by sending commands to the commandqueue

  // create an array of command lists (only one command list here)
  ID3D12CommandList* ppCommandLists[] = { m_pGraphics->CommandList() };

  // execute the array of command lists
  m_pGraphics->CommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

  // this command goes in at the end of our command queue. we will know when our command queue 
  // has finished because the fence value will be set to "fenceValue" from the GPU since the command
  // queue is being executed on the GPU
  hr = m_pGraphics->CommandQueue()->Signal(m_pGraphics->Fence()[m_pGraphics->FrameIndex()], m_pGraphics->FenceValue()[m_pGraphics->FrameIndex()]);
  if (FAILED(hr))
  {
    return false;
  }

  // present the current backbuffer
  hr = m_pGraphics->SwapChain()->Present(0, 0);
  if (FAILED(hr))
  {
    return false;
  }*/
  m_pGraphics->Render();

  return true;
}

bool Scene::onDestroy()
{
  return true;
}
