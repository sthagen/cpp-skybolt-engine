/* Copyright 2012-2020 Matthew Reid
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include <SkyboltCommon/Math/QuadTree.h>

#include <osg/Image>

#include <atomic>

namespace skybolt {
namespace vis {

class TileSource
{
public:
	virtual ~TileSource() {}

	virtual osg::ref_ptr<osg::Image> createImage(const skybolt::QuadTreeTileKey& key, std::function<bool()> cancelSupplier) const = 0;
};

} // namespace vis
} // namespace skybolt
