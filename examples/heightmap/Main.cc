/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#if defined(__APPLE__)
  #include <OpenGL/gl.h>
  #include <GLUT/glut.h>
#elif not defined(_WIN32)
  #include <GL/glew.h>
  #include <GL/gl.h>
  #include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

#include <ignition/common/Console.hh>
#include <ignition/common/HeightmapData.hh>
#include <ignition/common/ImageHeightmap.hh>
#include <ignition/rendering.hh>

#include "example_config.hh"
#include "GlutWindow.hh"

using namespace ignition;
using namespace rendering;

const std::string RESOURCE_PATH =
    common::joinPaths(std::string(PROJECT_BINARY_PATH), "media");

//////////////////////////////////////////////////
void buildScene(ScenePtr _scene)
{
  // initialize _scene
  _scene->SetAmbientLight(0.3, 0.3, 0.3);
  _scene->SetBackgroundColor(0.3, 0.3, 0.3);
  VisualPtr root = _scene->RootVisual();

  // create directional light
  DirectionalLightPtr light0 = _scene->CreateDirectionalLight();
  light0->SetDirection(0.5, 0.5, -1);
  light0->SetDiffuseColor(0.8, 0.8, 0.8);
  light0->SetSpecularColor(0.5, 0.5, 0.5);
  root->AddChild(light0);

//! [create a heightmap]
  auto data = std::make_shared<common::ImageHeightmap>();
  data->Load(common::joinPaths(RESOURCE_PATH, "heightmap_bowl.png"));

  HeightmapDescriptor desc;
  desc.data = data;
  desc.size = {17, 17, 10};
  desc.sampling = 2u;
  desc.useTerrainPaging = true;

  HeightmapDescriptor::Texture textureA;
  textureA.size = 1.0;
  textureA.diffuse = "../media/dirt_diffusespecular.png";
  textureA.normal = "../media/flat_normal.png";
  desc.textures.push_back(textureA);

  HeightmapDescriptor::Blend blendA;
  blendA.minHeight = 2.0;
  blendA.fadeDistance = 5.0;
  desc.blends.push_back(blendA);

  HeightmapDescriptor::Texture textureB;
  textureB.size = 1.0;
  textureB.diffuse = "../media/grass_diffusespecular.png";
  textureB.normal = "../media/flat_normal.png";
  desc.textures.push_back(textureB);

  HeightmapDescriptor::Blend blendB;
  blendB.minHeight = 4.0;
  blendB.fadeDistance = 5.0;
  desc.blends.push_back(blendB);

  HeightmapDescriptor::Texture textureC;
  textureC.size = 1.0;
  textureC.diffuse = "../media/fungus_diffusespecular.png";
  textureC.normal = "../media/flat_normal.png";
  desc.textures.push_back(textureC);

  auto heightmapGeom = _scene->CreateHeightmap(desc);

  auto vis = _scene->CreateVisual();
  vis->AddGeometry(heightmapGeom);
  root->AddChild(vis);
//! [create a heightmap]

//! [create another heightmap]
  auto data2 = std::make_shared<common::ImageHeightmap>();
  data2->Load(common::joinPaths(RESOURCE_PATH, "city_terrain.jpg"));

  HeightmapDescriptor desc2;
  desc2.data = data2;
  desc2.size = {26, 26, 20};
  desc2.sampling = 2u;
  desc2.useTerrainPaging = true;

  HeightmapDescriptor::Texture textureA2;
  textureA2.size = 1.0;
  textureA2.diffuse = "../media/fungus_diffusespecular.png";
  textureA2.normal = "../media/flat_normal.png";
  desc2.textures.push_back(textureA2);

  HeightmapDescriptor::Blend blendA2;
  blendA2.minHeight = 2.0;
  blendA2.fadeDistance = 5.0;
  desc2.blends.push_back(blendA2);

  HeightmapDescriptor::Texture textureB2;
  textureB2.size = 1.0;
  textureB2.diffuse = "../media/grass_diffusespecular.png";
  textureB2.normal = "../media/flat_normal.png";
  desc2.textures.push_back(textureB2);

  HeightmapDescriptor::Blend blendB2;
  blendB2.minHeight = 8.0;
  blendB2.fadeDistance = 5.0;
  desc2.blends.push_back(blendB2);

  HeightmapDescriptor::Texture textureC2;
  textureC2.size = 1.0;
  textureC2.diffuse = "../media/dirt_diffusespecular.png";
  textureC2.normal = "../media/flat_normal.png";
  desc2.textures.push_back(textureC2);
  desc2.position.Set(30, 0, 0);
  auto heightmapGeom2 = _scene->CreateHeightmap(desc2);

  auto vis2 = _scene->CreateVisual();
  vis2->AddGeometry(heightmapGeom2);
  root->AddChild(vis2);
//! [create another heightmap]

  // create gray material
  MaterialPtr gray = _scene->CreateMaterial();
  gray->SetAmbient(0.7, 0.7, 0.7);
  gray->SetDiffuse(0.7, 0.7, 0.7);
  gray->SetSpecular(0.7, 0.7, 0.7);

//! [create grid visual]
  VisualPtr grid = _scene->CreateVisual();
  GridPtr gridGeom = _scene->CreateGrid();
  gridGeom->SetCellCount(20);
  gridGeom->SetCellLength(1);
  gridGeom->SetVerticalCellCount(0);
  grid->AddGeometry(gridGeom);
  grid->SetLocalPosition(3, 0, 0.0);
  grid->SetMaterial(gray);
  root->AddChild(grid);
//! [create grid visual]

//! [create camera]
  CameraPtr camera = _scene->CreateCamera("camera");
  camera->SetLocalPosition(1.441, 25.787, 17.801);
  camera->SetLocalRotation(0.0, 0.588, -1.125);
  camera->SetImageWidth(800);
  camera->SetImageHeight(600);
  camera->SetAntiAliasing(2);
  camera->SetAspectRatio(1.333);
  camera->SetHFOV(IGN_PI / 2);
  root->AddChild(camera);
//! [create camera]
}

//////////////////////////////////////////////////
CameraPtr createCamera(const std::string &_engineName)
{
  // create and populate scene
  RenderEngine *engine = rendering::engine(_engineName);
  if (!engine)
  {
    ignwarn << "Engine '" << _engineName
              << "' is not supported" << std::endl;
    return CameraPtr();
  }
  ScenePtr scene = engine->CreateScene("scene");
  buildScene(scene);

  // return camera sensor
  SensorPtr sensor = scene->SensorByName("camera");
  return std::dynamic_pointer_cast<Camera>(sensor);
}

//////////////////////////////////////////////////
int main(int _argc, char** _argv)
{
  glutInit(&_argc, _argv);

  common::Console::SetVerbosity(4);
  std::vector<std::string> engineNames;
  std::vector<CameraPtr> cameras;

  engineNames.push_back("ogre");

  for (auto engineName : engineNames)
  {
    try
    {
      CameraPtr camera = createCamera(engineName);
      if (camera)
      {
        cameras.push_back(camera);
      }
    }
    catch (...)
    {
      // std::cout << ex.what() << std::endl;
      std::cerr << "Error starting up: " << engineName << std::endl;
    }
  }
  run(cameras);
  return 0;
}
