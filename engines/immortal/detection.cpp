/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "base/plugins.h"
#include "engines/advancedDetector.h"
#include "engines/game.h"

static const PlainGameDescriptor immortalGames[] = {
	{"immortal", "The Immortal"},
	{nullptr, nullptr}
};

namespace Immortal {
static const ADGameDescription gameDescriptions[] = {
	{
		"immortal",
		nullptr,
		{
			{"IMMORTAL.EXE", 0, "ebf4660b5d8eb3370609e0b2c60d93cd",  53434},
			{"IMM1.LIB",     0, "45933f560d9c55384e10b9a7fb797026", 181166},
			{"IMM2.LIB",     0, "ba0aa7459cff483df34506303c8b9889", 362044},
			AD_LISTEND
		},
		Common::EN_ANY,
		Common::kPlatformDOS,
		ADGF_UNSTABLE,
		GUIO1(GUIO_NONE)
	},

	AD_TABLE_END_MARKER
};
}

class ImmortalMetaEngineStatic : public AdvancedMetaEngineStatic {
public:
    ImmortalMetaEngineStatic() : AdvancedMetaEngineStatic(
        Immortal::gameDescriptions, sizeof(ADGameDescription), immortalGames) {
    }

	const char *getEngineId() const override {
		return "immortal";
	}

	const char *getName() const override {
		return "The Immortal";
	}

	const char *getOriginalCopyright() const override {
		return "(c)1990 Will Harvey & Electronic Arts";
	}
};

REGISTER_PLUGIN_STATIC(IMMORTAL_DETECTION, PLUGIN_TYPE_METAENGINE, ImmortalMetaEngineStatic);
