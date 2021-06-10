/* Copyright 2012-2020 Matthew Reid
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include "EngineStats.h"
#include "Scenario.h"
#include "EntityFactory.h"
#include "Plugin/Plugin.h"
#include <SkyboltSim/Components/NameComponent.h>
#include <SkyboltSim/System/SystemRegistry.h>
#include <SkyboltVis/Scene.h>
#include <SkyboltVis/Shader/ShaderProgramRegistry.h>
#include <SkyboltVis/Renderable/Planet/Tile/TileSource/JsonTileSourceFactory.h>
#include <SkyboltCommon/File/FileUtility.h>

#include <memory>

namespace skybolt {

typedef std::function<PluginPtr(const PluginConfig&)> PluginFactory;

struct EngineRootConfig
{
	std::vector<PluginFactory> pluginFactories;
	vis::JsonTileSourceFactoryConfig tileSourceFactoryConfig;
};

class EngineRoot
{
private:
	// This private block is first because these objects should be disposed of last
	std::vector<PluginFactory> mPluginFactories;
	std::vector<PluginPtr> mPlugins;
	std::vector<std::string> mAssetPackageNames;

public:
	EngineRoot(const EngineRootConfig& config);
	~EngineRoot();

	const std::vector<std::string>& getAssetPackageNames() const { return mAssetPackageNames; }

	std::unique_ptr<px_sched::Scheduler> scheduler;
	vis::ShaderPrograms programs;
	vis::ScenePtr scene;
	file::FileLocator fileLocator;
	JulianDateProvider julianDateProvider;
	std::unique_ptr<sim::World> simWorld;
	std::unique_ptr<EntityFactory> entityFactory;
	sim::NamedObjectRegistryPtr namedObjectRegistry;
	EngineStats stats;
	Scenario scenario;
	sim::SystemRegistryPtr systemRegistry;
};

file::Paths getPathsInAssetPackages(const std::vector<std::string>& assetPackageNames, const std::string& relativePath);
file::Paths getFilesWithExtensionInDirectoryInAssetPackages(const std::vector<std::string>& assetPackageNames, const std::string& relativeDirectory, const std::string& extension);

} // namespace skybolt