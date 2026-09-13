#include <Geode/Geode.hpp>

#include <Geode/ui/Layout.hpp>

#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

#include "IconManager.hpp"
#include <xblazegmd.geode-api/include/XblazeAPI.hpp>

using namespace geode::prelude;

static bool g_offline = false;

inline IconStatus statusFromBool(bool offline) {
    return offline ? IconStatus::Offline : IconStatus::Online;
}

class $modify(GJGLHook, GJGarageLayer) {
    struct Fields {
        CCMenuItemToggler* m_toggler;
        CCSprite* m_offlineOverlay;
    };

    bool init() {
        if (!GJGarageLayer::init()) return false;
        g_offline = false;

        // Toggler
        if (auto shardsMenu = this->getChildByID("shards-menu")) {
            auto sprOff = CCSprite::create("circleBtn_night.png"_spr);
            auto sprOn = CCSprite::create("circleBtn_day.png"_spr);
            sprOff->setScale(.5f);
            sprOn->setScale(.5f);

            m_fields->m_toggler = CCMenuItemToggler::create(
                sprOff,
                sprOn,
                this,
                menu_selector(GJGLHook::onOfflineToggle)
            );
            m_fields->m_toggler->setID("icon-toggler"_spr);
            shardsMenu->addChild(m_fields->m_toggler);
            shardsMenu->updateLayout();
        }

        // Overlay (if offline icons)
        m_fields->m_offlineOverlay = CCSprite::create("offlineOverlay.png"_spr);
        m_fields->m_offlineOverlay->setID("offline-overlay"_spr);

        m_fields->m_offlineOverlay->setOpacity(100);
        m_fields->m_offlineOverlay->setVisible(false);

        auto winSize = CCDirector::get()->getWinSize();
        auto overlaySize = m_fields->m_offlineOverlay->getTextureRect().size;

        m_fields->m_offlineOverlay->setAnchorPoint({0, 0});
        m_fields->m_offlineOverlay->setScaleX((winSize.width + 10.f) / overlaySize.width);
        m_fields->m_offlineOverlay->setScaleY((winSize.height + 10.f) / overlaySize.height);
        m_fields->m_offlineOverlay->setPosition({ -5.f, -5.f });
        m_fields->m_offlineOverlay->setZOrder(1000);

        this->addChild(m_fields->m_offlineOverlay);

        return true;
    }

    void onSelect(CCObject* sender) {
        int iconID = sender->getTag();
        bool selected = m_selectedIconType == m_iconType && m_iconID == iconID;
        bool unlocked = GameManager::get()->isIconUnlocked(iconID, m_selectedIconType);
        if (selected || (!unlocked && !selected)) return;

        GJGarageLayer::onSelect(sender);

        if (static_cast<int>(m_iconType) > 8) return; // If > 8 it's prob smth like a death effect idc abt

        auto iconman = IconManager::get();
        iconman->setIcon(m_iconID, m_iconType, statusFromBool(g_offline));
        iconman->saveIcons();
    }

    void onBack(CCObject* sender) {
        IconManager::get()->updateIcons(IconStatus::Online, false);
        GJGarageLayer::onBack(sender);
    }

    void onOfflineToggle(CCObject*) {
        auto iconman = IconManager::get();
        g_offline = !m_fields->m_toggler->isOn(); // Inverted logic cuz RobTop hates us all

        iconman->updateIcons(statusFromBool(g_offline), false);

        m_iconID = iconman->getIcon(m_iconType, statusFromBool(g_offline));
        m_playerObject->updatePlayerFrame(m_iconID, m_iconType);
        m_fields->m_offlineOverlay->setVisible(g_offline);
        this->updateCursor(m_iconID);
        this->updatePlayerColors();
    }

    void updateCursor(int id) {
        auto page = m_iconSelection->m_scrollLayer->m_extendedLayer->getChildByIndex(0); // Scary!
        if (!page) return;

        if (auto menu = typeinfo_cast<CCMenu*>(page->getChildByIndex(0))) {
            auto btn = menu->getChildByTag(id);
            if (!btn) {
                m_cursor1->setVisible(false);
                return;
            }

            m_cursor1->setVisible(true);
            m_cursor1->setPosition(menu->convertToWorldSpace(btn->getPosition()));
        }
    }
};

class $modify(CCPHook, CharacterColorPage) {
    void onPlayerColor(CCObject* sender) {
        CharacterColorPage::onPlayerColor(sender);
        auto iconman = IconManager::get();

        auto colorID = sender->getTag();
        auto status = statusFromBool(g_offline);
        switch (m_colorMode) {
            case 0:
                iconman->setMainColor(colorID, status);
                break;
            case 1:
                iconman->setSecondaryColor(colorID, status);
                break;
            case 2:
                iconman->setGlowColor(colorID, status);
                break;
        }
        iconman->saveIcons();
    }

    void toggleGlow(CCObject* sender) {
        CharacterColorPage::toggleGlow(sender);
        bool enabled = static_cast<CCMenuItemToggler*>(sender)->isOn();

        IconManager::get()->setGlowEnabled(enabled, statusFromBool(g_offline));
        IconManager::get()->saveIcons();
    }
};

$on_game(Loaded) {
    auto iconman = IconManager::get();
    if (!Mod::get()->setSavedValue("loaded", true)) {
        iconman->setIconsToDefault();
        FLAlertLayer::create(
            "Offline Icons",
            "Thank you for using this mod! You can customize your offline icon set in the <cy>Icon Kit</c>",
            "OK"
        )->show();
    } else {
        iconman->loadIcons();
        iconman->updateIcons(IconStatus::Online);
    }
}

$on_game(Exiting) {
    IconManager::get()->updateIcons(IconStatus::Offline);
}
