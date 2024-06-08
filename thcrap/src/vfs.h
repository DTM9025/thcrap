/**
  * Touhou Community Reliant Automatic Patcher
  * Main DLL
  *
  * ----
  *
  * Virtual file system.
  */

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

typedef json_t* jsonvfs_generator_t(std::unordered_map<std::string_view, json_t*>& in_data, std::string_view out_fn, size_t& out_size);

extern "C" {
	/**
	  * Add a handler to create files in the virtual file system.
	  *
	  * in_fns contains a list of json files needed to generate the virtual files.
	  *
	  * Each time a jdiff file matching out_pattern is resolved, gen will be called.
	  * If it returns a non-NULL value, the return value will be used as if a file
	  * with this content exists at the top of the patch stack.
	  */
	THCRAP_API void jsonvfs_add(const char* out_pattern, const std::vector<std::string>& in_fns, jsonvfs_generator_t *gen);

	// Same as jsonvfs_add, but all file names are game-relative.
	THCRAP_API void jsonvfs_game_add(const char* out_pattern, const std::vector<std::string>& in_fns, jsonvfs_generator_t *gen);

	/**
	  * Generate a VFS file from a JSON map file.
	  * The map file is called <filename>.map and will generate a file called <filename>.jdiff.
	  * The map file is a json file, with strings being references to JSON values in in_fn.
	  * For example, if you have this in the map file:
	  * { "key": "object.example" }
	  * and this in in_fn:
	  * { "object": { "example": 5 } }
	  * the generated jdiff file will be like this:
	  * { "key": 5 }
	  */
	THCRAP_API void jsonvfs_add_map(const char* out_pattern, const std::vector<std::string>& in_fns);

	// Same as jsonvfs_add_map, but all file names are game-relative.
	THCRAP_API void jsonvfs_game_add_map(const char* out_pattern, const std::vector<std::string>& in_fns);


	// Return a file from the vfs if it exists.
	THCRAP_API json_t *jsonvfs_get(const char* fn, size_t* size);
}
