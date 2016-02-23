/*
 * Copyright (c) 2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Michael X. Grey <mxgrey@gatech.edu>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OSGDART_SHAPEFRAMENODE_H
#define OSGDART_SHAPEFRAMENODE_H

#include <map>
#include <memory>
#include <osg/MatrixTransform>
#include "dart/dynamics/SmartPointer.h"

namespace dart {
namespace dynamics {
class ShapeFrame;
class Entity;
class Shape;
} // namespace dynamics
} // namespace dart

namespace osgDart
{

namespace render {
class ShapeNode;
} // namespace render

class WorldNode;

class ShapeFrameNode : public osg::MatrixTransform
{
public:

  /// Create a ShapeFrameNode. If _recursive is set to true, it will also create
  /// nodes for all child Entities and child Frames
  ShapeFrameNode(dart::dynamics::ShapeFrame* _frame,
                 WorldNode* _worldNode,
                 bool _relative,
                 bool _recursive);

  /// Pointer to the ShapeFrame associated with this ShapeFrameNode
  dart::dynamics::ShapeFrame* getShapeFrame();

  /// Pointer to the ShapeFrame associated with this ShapeFrameNode
  const dart::dynamics::ShapeFrame* getShapeFrame() const;

  WorldNode* getWorldNode();

  const WorldNode* getWorldNode() const;

  /// Update all rendering data for this ShapeFrame
  ///
  /// If _recursive is set to true, this ShapeFrameNode will also trigger refreshing
  /// on all child Entities and child Frames
  void refresh(bool _relative, bool _recursive, bool _firstTime);

  /// True iff this ShapeFrameNode has been utilized on the latest update
  bool wasUtilized() const;

  /// Set mUtilized to false
  void clearUtilization();

protected:

  virtual ~ShapeFrameNode();

  void clearChildUtilizationFlags();

  void clearUnusedNodes();

  void refreshShapeFrameNode(dart::dynamics::ShapeFrame* shapeFrame);

  void createShapeFrameNode(dart::dynamics::ShapeFrame* shapeFrame);

  void refreshShapeNode(const std::shared_ptr<dart::dynamics::Shape>& shape);

  void createShapeNode(const std::shared_ptr<dart::dynamics::Shape>& shape);

  /// Pointer to the ShapeFrame that this ShapeFrameNode is associated with
  dart::dynamics::ShapeFrame* mShapeFrame;

  /// Pointer to the WorldNode that this ShapeFrameNode belongs to
  WorldNode* mWorldNode;

  /// Map from child Frames to child ShapeFrameNodes
  std::map<dart::dynamics::ShapeFrame*, ShapeFrameNode*> mShapeFrameToNode;

  /// Map from child ShapeFrameNodes to child Frames
  std::map<ShapeFrameNode*, dart::dynamics::ShapeFrame*> mNodeToShapeFrame;

  /// Map from child Frames to child ShapeFrameNodes
  std::map<std::shared_ptr<dart::dynamics::Shape>,
           render::ShapeNode*> mShapeToNode;

  /// Map from child ShapeFrameNodes to child Frames
  std::map<render::ShapeNode*,
           std::shared_ptr<dart::dynamics::Shape>> mNodeToShape;

  /// True iff this ShapeFrameNode has been utilized on the latest update.
  /// If it has not, that is an indication that it is no longer being
  /// used and should be deleted.
  bool mUtilized;

};

} // namespace osgDart

#endif // OSGDART_SHAPEFRAMENODE_H