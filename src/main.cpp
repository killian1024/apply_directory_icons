/* apply_directory_icon
 * Copyright (C) 2018 Killian Poulaud.
 *
 * This file is part of apply_directory_icon.
 *
 * apply_directory_icon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * apply_directory_icon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with speed. If not, see <http://www.gnu.org/licenses/>.
 */

#include <speed/speed.hpp>

#include "program.hpp"


int main(int argc, char* argv[])
{
    // Set the argument parser.
    spdap::arg_parser ap("apply_directory_icon");
    ap.add_help_text("Options:");
    ap.add_key_value_arg({"--icon-files", "-if"}, "Icon files names.", {spdap::avt_t::STRING}, 1u,
                         ~0u);
    ap.add_help_arg({"--help"}, "Display this help and exit.");
    ap.add_gplv3_version_arg({"--version"}, "Output version information and exit", "1.0.0", "2018",
                             "Killian Poulaud");
    ap.add_foreign_arg("FILE", "File", "",
                       {spdap::avt_t::R_DIR | spdap::avt_t::W_DIR | spdap::avt_t::X_DIR});
    ap.parse_args((unsigned int)argc, argv);
    
    // Set the icon files names.
    std::unordered_set<std::string> icon_fles_nmes;
    for (auto& x : ap.get_arg_values("--icon-files"))
    {
        icon_fles_nmes.insert(x.as<std::string>());
    }
    if (icon_fles_nmes.empty())
    {
        icon_fles_nmes.insert(".icon.jpg");
        icon_fles_nmes.insert(".icon.jpeg");
        icon_fles_nmes.insert(".icon.png");
    }
    
    // Execute the program.
    apply_directory_icon::program prog(
            ap.get_front_arg_value_as<std::filesystem::path>("FILE"),
            std::move(icon_fles_nmes)
    );
    
    return prog.execute();
}