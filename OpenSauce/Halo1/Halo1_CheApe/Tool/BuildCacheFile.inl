/*
    Yelo: Open Sauce SDK
		Halo 1 (Editing Kit) Edition
    Copyright (C) 2005-2010  Kornner Studios (http://kornner.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Tool/BuildCacheFile/DataFiles.inl"
#include "Tool/BuildCacheFile/BuildGlobals.inl"
#include "Tool/BuildCacheFile/CullTags.inl"
#include "Tool/BuildCacheFile/PredictedResources.inl"

static void build_cache_file_begin_preprocess(cstring scenario_name)
{
	datum_index scenario_index = tag_load<TagGroups::scenario>(build_cache_file_for_scenario_internals.scenario_path, 0);
	if(!scenario_index.IsNull())
	{
		TagGroups::scenario* scenario = tag_get<TagGroups::scenario>(scenario_index);
		const tag_reference& yelo_reference = scenario->GetYeloReferenceHack();

		if(!yelo_reference.tag_index.IsNull())
		{
			TagGroups::project_yellow* yelo = tag_get<TagGroups::project_yellow>(yelo_reference.tag_index);

			// if there is a globals tag override, rename it to "globals/globals" so 
			// we avoid further hacks in the runtime engine code as it also explicitly 
			// looks for "globals/globals"
			if(yelo->game_globals.name_length > 0)
			{
				yelo->game_globals.tag_index = 
					tag_load(yelo->game_globals.group_tag, yelo->game_globals.name, 0);

				if(!yelo->game_globals.tag_index.IsNull())
					tag_rename(yelo->game_globals.tag_index, "globals\\globals");

				// re-set the reference just for good measure
				tag_reference_set(&yelo->game_globals, 
					yelo->game_globals.group_tag, "globals\\globals");
			}
		}
	}
}

#include "Tool/BuildCacheFile/MemoryUpgrades.inl"

namespace BuildCacheFileEx
{
	void Initialize(bool only_using_data_file_hacks)
	{
		BuildCacheFileEx::CullTags::Initialize();
		BuildCacheFileEx::PredictedResources::Initialize();
		BuildCacheFileEx::MemoryUpgrades::Initialize(only_using_data_file_hacks);
	}

	void Dispose(bool only_using_data_file_hacks)
	{
		BuildCacheFileEx::MemoryUpgrades::Dispose(only_using_data_file_hacks);
		BuildCacheFileEx::PredictedResources::Dispose();
		BuildCacheFileEx::CullTags::Dispose();
	}
};

static void PLATFORM_API build_cache_file_for_scenario_extended(void** arguments)
{
	//////////////////////////////////////////////////////////////////////////
	// Initialize arguments
	struct s_arguments {
		char* mod_name;
		cstring copy_data_files_first_str;
		cstring store_resources_str;
		cstring use_memory_upgrades_str;
		char* scenario_name;
	}* args = CAST_PTR(s_arguments*, arguments);

	bool copy_data_files_first, store_resources, use_memory_upgrades;
	copy_data_files_first = Settings::ParseBoolean(args->copy_data_files_first_str);
	store_resources = Settings::ParseBoolean(args->store_resources_str);
	use_memory_upgrades = Settings::ParseBoolean(args->use_memory_upgrades_str);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// Initialize locals and globals
	build_cache_file_for_scenario_internals.build_failed = false;
	build_cache_file_for_scenario_internals.scenario_path = args->scenario_name;

	memset(&BuildCacheFileEx::MemoryUpgrades::yelo_cache_header_globals, 0, sizeof(BuildCacheFileEx::MemoryUpgrades::yelo_cache_header_globals));
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// validate and fix the mod name if it is too long for a tag_string
	const size_t k_max_mod_set_name_length = Enums::k_tag_string_length - sizeof("-bitmaps");

	size_t mod_set_name_length = strlen(args->mod_name);

	if(mod_set_name_length > k_max_mod_set_name_length)
		args->mod_name[k_max_mod_set_name_length+1] = '\0';
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// setup the data files
	bool using_mod_sets = use_memory_upgrades && (mod_set_name_length > 0);

	c_data_files data_files;

	s_build_cache_file_for_scenario::InitializeFileSystem(data_files, args->mod_name, using_mod_sets);

	if(using_mod_sets)
	{
		// check if the user wants to copy the base data files
		if(copy_data_files_first)
			data_files.CopyStock();

		// update yelo header globals too
		BuildCacheFileEx::MemoryUpgrades::yelo_cache_header_globals.flags.uses_mod_data_files = true;
		strcpy_s(BuildCacheFileEx::MemoryUpgrades::yelo_cache_header_globals.mod_name, args->mod_name);
	}
	//////////////////////////////////////////////////////////////////////////


	if(BuildCacheFileEx::MemoryUpgrades::yelo_cache_header_globals.flags.uses_memory_upgrades = use_memory_upgrades)
		BuildCacheFileEx::MemoryUpgrades::yelo_cache_header_globals.k_memory_upgrade_increase_amount = K_MEMORY_UPGRADE_INCREASE_AMOUNT;

	// open the data files for referencing and write
	s_build_cache_file_for_scenario& bcffs = build_cache_file_for_scenario_internals;
	bcffs.DataFilesOpen(data_files, store_resources);

	BuildCacheFileEx::Initialize(!use_memory_upgrades);

	// build cache file
		bcffs._build_cache_file_for_scenario(args->scenario_name);

	BuildCacheFileEx::Dispose(!use_memory_upgrades);

	bcffs.BuildPostprocess(args->mod_name, using_mod_sets);

	bcffs.DataFilesClose(store_resources);
}