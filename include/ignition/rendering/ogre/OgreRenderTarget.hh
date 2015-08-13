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
#ifndef _IGNITION_RENDERING_OGRERENDERTARGET_HH_
#define _IGNITION_RENDERING_OGRERENDERTARGET_HH_

#include "gazebo/common/Color.hh"
#include "ignition/rendering/base/BaseRenderTypes.hh"
#include "ignition/rendering/base/BaseRenderTarget.hh"
#include "ignition/rendering/ogre/OgreRenderTypes.hh"
#include "ignition/rendering/ogre/OgreIncludes.hh"
#include "ignition/rendering/ogre/OgreObject.hh"

namespace Ogre
{
  class Camera;
  class RenderTarget;
  class Texture;
}

namespace ignition
{
  namespace rendering
  {
    class IGNITION_VISIBLE OgreRenderTarget :
      public virtual BaseRenderTarget<OgreObject>
    {
      protected: OgreRenderTarget();

      public: virtual ~OgreRenderTarget();

      public: virtual void GetImage(Image &_image) const;

      public: virtual Ogre::Camera *GetCamera() const;

      public: virtual void SetCamera(Ogre::Camera *_camera);

      public: virtual gazebo::common::Color GetBackgroundColor() const;

      public: virtual void SetBackgroundColor(gazebo::common::Color _color);

      public: virtual void PreRender();

      public: virtual void Render();

      public: virtual void Destroy() = 0;

      protected: virtual Ogre::RenderTarget *GetOgreRenderTarget() const = 0;

      protected: virtual void UpdateBackgroundColor();

      protected: virtual void RebuildImpl();

      protected: virtual void RebuildTarget() = 0;

      protected: virtual void RebuildViewport();

      protected: Ogre::Camera *ogreCamera;

      protected: Ogre::Viewport *ogreViewport;

      protected: Ogre::ColourValue ogreBackgroundColor;

      protected: bool colorDirty;
    };

    class IGNITION_VISIBLE OgreRenderTexture :
      public virtual BaseRenderTexture<OgreRenderTarget>
    {
      protected: OgreRenderTexture();

      public: virtual ~OgreRenderTexture();

      public: virtual unsigned int GetAntiAliasing() const;

      public: virtual void SetAntiAliasing(unsigned int _aa);

      public: virtual void Destroy();

      protected: virtual Ogre::RenderTarget *GetOgreRenderTarget() const;

      protected: virtual void RebuildTarget();

      protected: virtual void DestroyTarget();

      protected: virtual void BuildTarget();

      protected: Ogre::Texture *ogreTexture;

      protected: unsigned int antiAliasing;

      private: friend class OgreScene;
    };
  }
}
#endif