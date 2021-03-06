#include "test.h"

#include <string>
#include <vector>
#include <fstream>
#include <execution>
#include <filesystem>
namespace fs = std::filesystem;

#include "fmt/format.h"

#include "BinaryReader.h"
#include "MDX.h"

void execute_tests() {
	fmt::print("[INFO] Parsing all MDX files\n");
	auto begin = std::chrono::steady_clock::now();
	parse_all_mdx();
	auto delta = (std::chrono::steady_clock::now() - begin).count() / 1'000'000.f;
	fmt::print("[INFO] Done parsing in {}ms\n", delta);
}

void parse_all_mdx() {
	std::vector<fs::path> paths;

	std::atomic<int> total;
	std::atomic<int> opaques;

	for (const auto i : fs::recursive_directory_iterator("C:/Users/User/Desktop/Warcraft/MPQContent/1.32.x/")) {
		if (i.is_regular_file() && (i.path().extension() == ".mdx" || i.path().extension() == ".MDX")) {
			paths.push_back(i.path());
		}
	}

	std::for_each(std::execution::par_unseq, paths.begin(), paths.end(), [&](const fs::path& path) {
		std::ifstream stream(path, std::ios::binary);
		auto buffer = std::vector<uint8_t>(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

		BinaryReader reader(buffer);
		auto mdx = mdx::MDX(reader);

		for (const auto& i : mdx.geosets) {
			bool opaque = false;
			for (const auto& j : mdx.materials[i.material_id].layers) {
				if (j.blend_mode == 0) {
					opaque = true;
					break;
				}
			}
			if (opaque) {
				opaques++;
			} else {
				fmt::print("{}\n", path.string());
			}
			total++;
		}
	});

	fmt::print("{}\t{}", total, opaques);
}