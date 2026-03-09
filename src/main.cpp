#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/SongInfoLayer.hpp>
#include <Geode/modify/SongInfoLayer.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
class $modify(showSongInf, LevelCell) {

    void loadFromLevel(GJGameLevel* level) {
        LevelCell::loadFromLevel(level);
        if (!level) return;

        auto mainLayer = this->getChildByID("main-layer");
        if (!mainLayer) return;

        auto songLabel = typeinfo_cast<CCLabelBMFont*>(
            mainLayer->getChildByID("song-name")
        );
        if (!songLabel) return;

        songLabel->removeFromParent();

        auto btn = CCMenuItemSpriteExtra::create(
            songLabel,
            this,
            menu_selector(showSongInf::onSongClicked)
        );
		btn->setScale(1.13f);
		btn->setAnchorPoint({0.f,0.5f});

        auto menu = m_mainMenu;
		btn->setPosition(-234.f,-125.f);
		if(this->m_compactView) {
			btn->setPosition(-222.f,-135.f);
		}
		menu->addChild(btn);
		auto chompo = mainLayer->getChildByID("chompo-icon");
		auto ncs = mainLayer->getChildByID("ncs-icon");
		if (chompo) {
			btn->setPositionX(-186.f);
		}else if (ncs) {
			btn->setPositionX(-190.f);
		}
    }

    void onSongClicked(CCObject* sender) {
		if (!this->m_level) return;

		int songID = this->m_level->m_songID;
		if (songID <= 0 || !songID) return;

		auto manager = MusicDownloadManager::sharedState();
		auto songObj = manager->getSongInfoObject(songID);
		if (!songObj) return;

		auto newUrl = "https://www.newgrounds.com/audio/listen/" + std::to_string(songObj->m_songID);
		SongInfoLayer::create(
			songObj->m_songName,
			songObj->m_artistName,
			songObj->m_songUrl,
			newUrl,
			songObj->m_youtubeVideo,
			"",
			songObj->m_songID,
			"",
			songObj->m_nongType
		)->show();
	}
};