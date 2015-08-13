/*
 * Copyright (C) 2015 Open Source Robotics Foundation
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
#include "ignition/rendering/MeshDescriptor.hh"
#include "gazebo/common/Mesh.hh"
#include "gazebo/common/MeshManager.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
MeshDescriptor::MeshDescriptor() :
  mesh(NULL),
  meshName(""),
  subMeshName(""),
  centerSubMesh(false)
{
}

//////////////////////////////////////////////////
MeshDescriptor::MeshDescriptor(const std::string &_meshName) :
  mesh(NULL),
  meshName(_meshName),
  subMeshName(""),
  centerSubMesh(false)
{
}

//////////////////////////////////////////////////
MeshDescriptor::MeshDescriptor(const gazebo::common::Mesh *_mesh) :
  mesh(_mesh),
  meshName(""),
  subMeshName(""),
  centerSubMesh(false)
{
}

//////////////////////////////////////////////////
MeshDescriptor MeshDescriptor::Normalize() const
{
  MeshDescriptor norm = *this;

  if (norm.mesh)
  {
    norm.meshName = norm.mesh->GetName();
  }
  else
  {
    norm.mesh = gazebo::common::MeshManager::Instance()->GetMesh(norm.meshName);
  }

  return norm;
}