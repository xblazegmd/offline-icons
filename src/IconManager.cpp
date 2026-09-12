#include "IconManager.hpp"

#include <Geode/Geode.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GameLevelManager.hpp>

using namespace geode::prelude;

IconManager* IconManager::get() {
    static IconManager* inst = new IconManager();
    return inst;
}

void IconManager::loadIcons() {
    auto mod = Mod::get();
    m_onlineColor1 = mod->getSavedValue<int>("online-color1");
    m_onlineColor2 = mod->getSavedValue<int>("online-color2");
    m_onlineGlow = mod->getSavedValue<bool>("online-glow");
    m_onlineGlowColor = mod->getSavedValue<int>("online-glow-color");

    m_offlineColor1 = mod->getSavedValue<int>("offline-color1");
    m_offlineColor2 = mod->getSavedValue<int>("offline-color2");
    m_offlineGlow = mod->getSavedValue<bool>("offline-glow");
    m_offlineGlowColor = mod->getSavedValue<int>("offline-glow-color");
}

void IconManager::saveIcons() {
    auto mod = Mod::get();

    mod->setSavedValue("online-color1", m_onlineColor1);
    mod->setSavedValue("online-color2", m_onlineColor2);
    mod->setSavedValue("online-glow", m_onlineGlow);
    mod->setSavedValue("online-glow-color", m_onlineGlowColor);

    mod->setSavedValue("offline-color1", m_offlineColor1);
    mod->setSavedValue("offline-color2", m_offlineColor2);
    mod->setSavedValue("offline-glow", m_offlineGlow);
    mod->setSavedValue("offline-glow-color", m_offlineGlowColor);
}

void IconManager::setIconsToDefault() {
    auto gman = GameManager::get();

    m_onlineColor1 = gman->getPlayerColor();
    m_onlineColor2 = gman->getPlayerColor2();
    m_onlineGlow = gman->getPlayerGlow();
    m_onlineGlowColor = gman->getPlayerGlowColor();

    m_offlineColor1 = m_onlineColor2;
    m_offlineColor2 = m_onlineColor1;
    m_offlineGlow = m_onlineGlow;
    m_offlineGlowColor = m_onlineGlowColor;

    this->saveIcons();
}

void IconManager::updateIcons(IconStatus status, bool updateUserScore) {
    auto gman = GameManager::get();

    switch (status) {
        case IconStatus::Online:
            gman->setPlayerColor(m_onlineColor1);
            gman->setPlayerColor2(m_onlineColor2);
            gman->setPlayerGlow(m_onlineGlow);
            gman->setPlayerColor3(m_onlineGlowColor);
            break;
        case IconStatus::Offline:
            gman->setPlayerColor(m_offlineColor1);
            gman->setPlayerColor2(m_offlineColor2);
            gman->setPlayerGlow(m_offlineGlow);
            gman->setPlayerColor3(m_offlineGlowColor);
            break;
    }

    if (updateUserScore) GameLevelManager::get()->updateUserScore();
}

int IconManager::getMainColor(IconStatus status) const {
    switch (status) {
        case IconStatus::Online:
            return m_onlineColor1;
        case IconStatus::Offline:
            return m_offlineColor1;
    }
}

int IconManager::getSecondaryColor(IconStatus status) const {
    switch (status) {
        case IconStatus::Online:
            return m_onlineColor2;
        case IconStatus::Offline:
            return m_offlineColor2;
    }
}

int IconManager::getGlowColor(IconStatus status) const {
    switch (status) {
        case IconStatus::Online:
            return m_onlineGlowColor;
        case IconStatus::Offline:
            return m_offlineGlowColor;
    }
}

bool IconManager::isGlowEnabled(IconStatus status) const {
    switch (status) {
        case IconStatus::Online:
            return m_onlineGlow;
        case IconStatus::Offline:
            return m_offlineGlow;
    }
}

void IconManager::setMainColor(int id, IconStatus status) {
    switch (status) {
        case IconStatus::Online:
            m_onlineColor1 = id;
            break;
        case IconStatus::Offline:
            m_offlineColor1 = id;
            break;
    }
}

void IconManager::setSecondaryColor(int id, IconStatus status) {
    switch (status) {
        case IconStatus::Online:
            m_onlineColor2 = id;
            break;
        case IconStatus::Offline:
            m_offlineColor2 = id;
            break;
    }
}

void IconManager::setGlowColor(int id, IconStatus status) {
    switch (status) {
        case IconStatus::Online:
            m_onlineGlowColor = id;
            break;
        case IconStatus::Offline:
            m_offlineGlowColor = id;
            break;
    }
}

void IconManager::setGlowEnabled(bool enabled, IconStatus status) {
    switch (status) {
        case IconStatus::Online:
            m_onlineGlow = enabled;
            break;
        case IconStatus::Offline:
            m_offlineGlow = enabled;
            break;
    }
}
