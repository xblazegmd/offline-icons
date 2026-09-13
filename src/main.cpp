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
        CCLayerColor* m_offlineOverlay;
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

            auto offlineToggle = CCMenuItemToggler::create(
                sprOff,
                sprOn,
                this,
                menu_selector(GJGLHook::onOfflineToggle)
            );
            shardsMenu->addChild(offlineToggle);

            shardsMenu->updateLayout();
        }

        // Overlay (if offline icons)
        m_fields->m_offlineOverlay = CCLayerColor::create({0, 1, 31, 100});
        m_fields->m_offlineOverlay->setVisible(false);
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
        auto status = statusFromBool(g_offline);
        switch (m_iconType) {
            case IconType::Cube:
                iconman->setCube(m_iconID, status);
                break;
            case IconType::Ship:
                iconman->setShip(m_iconID, status);
                break;
            case IconType::Ball:
                iconman->setBall(m_iconID, status);
                break;
            case IconType::Ufo:
                iconman->setUFO(m_iconID, status);
                break;
            case IconType::Wave:
                iconman->setWave(m_iconID, status);
                break;
            case IconType::Robot:
                iconman->setRobot(m_iconID, status);
                break;
            case IconType::Spider:
                iconman->setSpider(m_iconID, status);
                break;
            case IconType::Swing:
                iconman->setSpider(m_iconID, status);
                break;
            case IconType::Jetpack:
                iconman->setJetpack(m_iconID, status);
                break;
            default:
                return; // This should be unreachable cuz of the earlier check but just in case
        }
        iconman->saveIcons();
    }

    void onBack(CCObject* sender) {
        IconManager::get()->updateIcons(IconStatus::Online, false);
        GJGarageLayer::onBack(sender);
    }

    void onOfflineToggle(CCObject* sender) {
        auto iconman = IconManager::get();
        auto toggler = static_cast<CCMenuItemToggler*>(sender);
        g_offline = !toggler->isOn(); // Inverted logic cuz RobTop hates us all

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
    } else {
        iconman->loadIcons();
        iconman->updateIcons(IconStatus::Online);
    }
}

$on_game(Exiting) {
    IconManager::get()->updateIcons(IconStatus::Offline);
}
