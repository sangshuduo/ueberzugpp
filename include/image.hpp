// Display images inside a terminal
// Copyright (C) 2023  JustKidding
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

class Dimensions;
class Terminal;

class Image
{
public:
    static auto load(const nlohmann::json& command, const Terminal& terminal) -> std::unique_ptr<Image>;
    static auto check_cache(const Dimensions& dimensions,
            const std::filesystem::path& orig_path) -> std::string;
    static auto get_dimensions(const nlohmann::json& json, const Terminal& terminal) -> std::shared_ptr<Dimensions>;

    virtual ~Image() = default;

    [[nodiscard]] virtual auto dimensions() const -> const Dimensions& = 0;
    [[nodiscard]] virtual auto width() const -> int = 0;
    [[nodiscard]] virtual auto height() const -> int = 0;
    [[nodiscard]] virtual auto size() const -> size_t = 0;
    [[nodiscard]] virtual auto data() const -> const unsigned char* = 0;
    [[nodiscard]] virtual auto channels() const -> int = 0;

    [[nodiscard]] virtual auto frame_delay() const -> int { return -1; }
    [[nodiscard]] virtual auto is_animated() const -> bool { return false; }
    [[nodiscard]] virtual auto filename() const -> std::string = 0;
    virtual auto next_frame() -> void {}

protected:
    [[nodiscard]] auto get_new_sizes(double max_width, double max_height, const std::string& scaler) const
        -> std::pair<int, int>;
};

#endif
