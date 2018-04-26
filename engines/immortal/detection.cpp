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
#include "common/file.h"
#include "common/savefile.h"
#include "common/system.h"
#include "graphics/thumbnail.h"
#include "engines/advancedDetector.h"

#include "immortal/immortal.h"

static const PlainGameDescriptor immortalGames[] = {
	{"immortal", "The Immortal"},
	{nullptr, nullptr}
};

namespace Immortal {
static const ADGameDescription gameDescriptions[] = {
	{
		"immortal",
		nullptr,
		AD_ENTRY1s("IMMORTAL.EXE", "ebf4660b5d8eb3370609e0b2c60d93cd", 53434),
		Common::EN_ANY,
		Common::kPlatformDOS,
		ADGF_UNSTABLE,
		GUIO1(GUIO_NONE)
	},

	AD_TABLE_END_MARKER
};
}

class ImmortalMetaEngine: public AdvancedMetaEngine {
public:
	ImmortalMetaEngine() : AdvancedMetaEngine(Immortal::gameDescriptions, sizeof(ADGameDescription), immortalGames) {
	}

	virtual const char *getName() const {
		return "The Immortal";
	}

	virtual const char *getOriginalCopyright() const {
		return "(c)1990 Will Harvey & Electronic Arts";
	}

	virtual bool hasFeature(MetaEngineFeature f) const;
	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
};

bool ImmortalMetaEngine::hasFeature(MetaEngineFeature f) const {
	switch (f) {
	case kSupportsLoadingDuringStartup:
		// fallthrough
	case kSupportsListSaves:
		// fallthrough
	case kSupportsDeleteSave:
		// fallthrough
	case kSavesSupportMetaInfo:
		// fallthrough
	case kSavesSupportThumbnail:
		// fallthrough
	case kSavesSupportCreationDate:
		// fallthrough
	case kSavesSupportPlayTime:
		return false;
	default:
		return false;
	}
}

bool ImmortalMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	if (desc) {
		*engine = new Immortal::ImmortalEngine(syst);
	}

	return desc != nullptr;
}


#if PLUGIN_ENABLED_DYNAMIC(IMMORTAL)
REGISTER_PLUGIN_DYNAMIC(IMMORTAL, PLUGIN_TYPE_ENGINE, ImmortalMetaEngine);
#else
REGISTER_PLUGIN_STATIC(IMMORTAL, PLUGIN_TYPE_ENGINE, ImmortalMetaEngine);
#endif
