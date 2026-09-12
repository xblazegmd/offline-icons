#include <Geode/Geode.hpp>
#include <Geode/ui/Layout.hpp>

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

        auto container = CCMenu::create();
        container->setID("offline-toggle"_spr);
        container->setLayout(
            RowLayout::create()
                ->setAutoScale(false)
        );
        container->setContentWidth(90);
        container->setAnchorPoint({0, .5f});
        container->setPosition({30, -8});

        auto sprOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto sprOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        sprOff->setScale(.7f);
        sprOn->setScale(.7f);

        auto offlineToggle = CCMenuItemToggler::create(
            sprOff,
            sprOn,
            this,
            menu_selector(CCPHook::onOfflineToggle)
        );
        container->addChild(offlineToggle);

        auto label = Label::create("Offline", "bigFont.fnt");
        label->setScale(.5f);
        container->addChild(label);

        container->updateLayout();
        buttonMenu->addChild(container);

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
        bool enabled = static_cast<CCMenuItemToggler*>(sender)->isOn();

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
