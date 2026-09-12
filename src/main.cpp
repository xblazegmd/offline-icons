#include <Geode/Geode.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GameLevelManager.hpp>

#include <Geode/modify/CharacterColorPage.hpp>

#include "IconManager.hpp"
#include <xblazegmd.geode-api/include/XblazeAPI.hpp>

using namespace geode::prelude;

inline IconStatus statusFromBool(bool offline) {
    return offline ? IconStatus::Offline : IconStatus::Online;
}

class $modify(CCPHook, CharacterColorPage) {
    struct Fields {
        bool m_offline = false;
    };

    bool init() {
        if (!CharacterColorPage::init()) return false;
        auto mainLayer = this->getChildByID("colors-layer");
        if (!mainLayer) return true;

        auto buttonMenu = mainLayer->getChildByID("buttons-menu");
        if (!buttonMenu) return true;

        auto offlineToggle = CCMenuItemToggler::create(
            CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
            CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
            this,
            menu_selector(CCPHook::onOfflineToggle)
        );
        offlineToggle->setPosition({30, 0});
        buttonMenu->addChild(offlineToggle);

        return true;
    }

    void onPlayerColor(CCObject* sender) {
        CharacterColorPage::onPlayerColor(sender);
        auto iconman = IconManager::get();

        auto colorID = sender->getTag();
        auto status = statusFromBool(m_fields->m_offline);
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
        bool enabled = !static_cast<CCMenuItemToggler*>(sender)->isOn();

        IconManager::get()->setGlowEnabled(enabled, statusFromBool(m_fields->m_offline));
        IconManager::get()->saveIcons();
    }

    void onOfflineToggle(CCObject* sender) {
        auto iconman = IconManager::get();

        auto toggler = static_cast<CCMenuItemToggler*>(sender);
        m_fields->m_offline = !toggler->isOn();

        iconman->updateIcons(statusFromBool(m_fields->m_offline), false);
        m_glowToggler->toggle(!iconman->isGlowEnabled(statusFromBool(m_fields->m_offline)));
        this->updateIconColors();
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
