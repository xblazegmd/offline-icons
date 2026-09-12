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

    m_onlineCube = mod->getSavedValue<int>("online-cube");
    m_onlineShip = mod->getSavedValue<int>("online-ship");
    m_onlineBall = mod->getSavedValue<int>("online-ball");
    m_onlineUFO = mod->getSavedValue<int>("online-ufo");
    m_onlineWave = mod->getSavedValue<int>("online-wave");
    m_onlineRobot = mod->getSavedValue<int>("online-robot");
    m_onlineSpider = mod->getSavedValue<int>("online-spider");
    m_onlineSwing = mod->getSavedValue<int>("online-swing");
    m_onlineJetpack = mod->getSavedValue<int>("online-jetpack");

    m_onlineColor1 = mod->getSavedValue<int>("online-color1");
    m_onlineColor2 = mod->getSavedValue<int>("online-color2");
    m_onlineGlow = mod->getSavedValue<bool>("online-glow");
    m_onlineGlowColor = mod->getSavedValue<int>("online-glow-color");

    m_offlineCube = mod->getSavedValue<int>("offline-cube");
    m_offlineShip = mod->getSavedValue<int>("offline-ship");
    m_offlineBall = mod->getSavedValue<int>("offline-ball");
    m_offlineUFO = mod->getSavedValue<int>("offline-ufo");
    m_offlineWave = mod->getSavedValue<int>("offline-wave");
    m_offlineRobot = mod->getSavedValue<int>("offline-robot");
    m_offlineSpider = mod->getSavedValue<int>("offline-spider");
    m_offlineSwing = mod->getSavedValue<int>("offline-swing");
    m_offlineJetpack = mod->getSavedValue<int>("offline-jetpack");

    m_offlineColor1 = mod->getSavedValue<int>("offline-color1");
    m_offlineColor2 = mod->getSavedValue<int>("offline-color2");
    m_offlineGlow = mod->getSavedValue<bool>("offline-glow");
    m_offlineGlowColor = mod->getSavedValue<int>("offline-glow-color");
}

void IconManager::saveIcons() {
    auto mod = Mod::get();

    mod->setSavedValue("online-cube", m_onlineCube);
    mod->setSavedValue("online-ship", m_onlineShip);
    mod->setSavedValue("online-ball", m_onlineBall);
    mod->setSavedValue("online-ufo", m_onlineUFO);
    mod->setSavedValue("online-wave", m_onlineWave);
    mod->setSavedValue("online-robot", m_onlineRobot);
    mod->setSavedValue("online-spider", m_onlineSpider);
    mod->setSavedValue("online-swing", m_onlineSwing);
    mod->setSavedValue("online-jetpack", m_onlineJetpack);

    mod->setSavedValue("online-color1", m_onlineColor1);
    mod->setSavedValue("online-color2", m_onlineColor2);
    mod->setSavedValue("online-glow", m_onlineGlow);
    mod->setSavedValue("online-glow-color", m_onlineGlowColor);

    mod->setSavedValue("offline-cube", m_offlineCube);
    mod->setSavedValue("offline-ship", m_offlineShip);
    mod->setSavedValue("offline-ball", m_offlineBall);
    mod->setSavedValue("offline-ufo", m_offlineUFO);
    mod->setSavedValue("offline-wave", m_offlineWave);
    mod->setSavedValue("offline-robot", m_offlineRobot);
    mod->setSavedValue("offline-spider", m_offlineSpider);
    mod->setSavedValue("offline-swing", m_offlineSwing);
    mod->setSavedValue("offline-jetpack", m_offlineJetpack);

    mod->setSavedValue("offline-color1", m_offlineColor1);
    mod->setSavedValue("offline-color2", m_offlineColor2);
    mod->setSavedValue("offline-glow", m_offlineGlow);
    mod->setSavedValue("offline-glow-color", m_offlineGlowColor);
}

void IconManager::setIconsToDefault() {
    auto gman = GameManager::get();

    m_onlineCube = gman->getPlayerFrame();
    m_onlineShip = gman->getPlayerShip();
    m_onlineBall = gman->getPlayerBall();
    m_onlineUFO = gman->getPlayerBird();
    m_onlineWave = gman->getPlayerDart();
    m_onlineRobot = gman->getPlayerRobot();
    m_onlineSpider = gman->getPlayerSpider();
    m_onlineSwing = gman->getPlayerSwing();
    m_onlineJetpack = gman->getPlayerJetpack();

    m_onlineColor1 = gman->getPlayerColor();
    m_onlineColor2 = gman->getPlayerColor2();
    m_onlineGlow = gman->getPlayerGlow();
    m_onlineGlowColor = gman->getPlayerGlowColor();

    m_offlineCube = m_onlineCube;
    m_offlineShip = m_onlineShip;
    m_offlineBall = m_onlineBall;
    m_offlineUFO  = m_onlineUFO;
    m_offlineWave = m_onlineWave;
    m_offlineRobot = m_onlineRobot;
    m_offlineSpider = m_onlineSpider;
    m_offlineSwing = m_onlineSwing;
    m_offlineJetpack = m_onlineJetpack;

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
            gman->setPlayerFrame(m_onlineCube);
            gman->setPlayerShip(m_onlineShip);
            gman->setPlayerBall(m_onlineBall);
            gman->setPlayerBird(m_onlineUFO);
            gman->setPlayerDart(m_onlineWave);
            gman->setPlayerRobot(m_onlineRobot);
            gman->setPlayerSpider(m_onlineSpider);
            gman->setPlayerSwing(m_onlineSwing);
            gman->setPlayerJetpack(m_onlineJetpack);

            gman->setPlayerColor(m_onlineColor1);
            gman->setPlayerColor2(m_onlineColor2);
            gman->setPlayerGlow(m_onlineGlow);
            gman->setPlayerColor3(m_onlineGlowColor);
            break;
        case IconStatus::Offline:
            gman->setPlayerFrame(m_offlineCube);
            gman->setPlayerShip(m_offlineShip);
            gman->setPlayerBall(m_offlineBall);
            gman->setPlayerBird(m_offlineUFO);
            gman->setPlayerDart(m_offlineWave);
            gman->setPlayerRobot(m_offlineRobot);
            gman->setPlayerSpider(m_offlineSpider);
            gman->setPlayerSwing(m_offlineSwing);
            gman->setPlayerJetpack(m_offlineJetpack);

            gman->setPlayerColor(m_offlineColor1);
            gman->setPlayerColor2(m_offlineColor2);
            gman->setPlayerGlow(m_offlineGlow);
            gman->setPlayerColor3(m_offlineGlowColor);
            break;
    }

    if (updateUserScore) GameLevelManager::get()->updateUserScore();
}

int IconManager::getCube(IconStatus status) const {
    return this->getValue<int>(status, m_onlineCube, m_offlineCube);
}

int IconManager::getShip(IconStatus status) const {
    return this->getValue<int>(status, m_onlineShip, m_offlineShip);
}

int IconManager::getBall(IconStatus status) const {
    return this->getValue<int>(status, m_onlineBall, m_offlineBall);
}

int IconManager::getUFO(IconStatus status) const {
    return this->getValue<int>(status, m_onlineUFO, m_offlineUFO);
}

int IconManager::getWave(IconStatus status) const {
    return this->getValue<int>(status, m_onlineWave, m_offlineWave);
}

int IconManager::getRobot(IconStatus status) const {
    return this->getValue<int>(status, m_onlineRobot, m_offlineRobot);
}

int IconManager::getSpider(IconStatus status) const {
    return this->getValue<int>(status, m_onlineSpider, m_offlineSpider);
}

int IconManager::getSwing(IconStatus status) const {
    return this->getValue<int>(status, m_onlineSwing, m_offlineSwing);
}

int IconManager::getJetpack(IconStatus status) const {
    return this->getValue<int>(status, m_onlineJetpack, m_offlineJetpack);
}

int IconManager::getMainColor(IconStatus status) const {
    return this->getValue<int>(status, m_onlineColor1, m_offlineColor1);
}

int IconManager::getSecondaryColor(IconStatus status) const {
    return this->getValue<int>(status, m_onlineColor2, m_offlineColor2);
}

int IconManager::getGlowColor(IconStatus status) const {
    return this->getValue<int>(status, m_onlineGlowColor, m_offlineGlowColor);
}

bool IconManager::isGlowEnabled(IconStatus status) const {
    return this->getValue<bool>(status, m_onlineGlow, m_offlineGlow);
}

void IconManager::setCube(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineCube, m_offlineCube);
}

void IconManager::setShip(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineShip, m_offlineShip);
}

void IconManager::setBall(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineBall, m_offlineBall);
}

void IconManager::setUFO(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineUFO, m_offlineUFO);
}

void IconManager::setWave(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineWave, m_offlineWave);
}

void IconManager::setRobot(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineRobot, m_offlineRobot);
}

void IconManager::setSpider(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineSpider, m_offlineSpider);
}

void IconManager::setSwing(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineSwing, m_offlineSwing);
}

void IconManager::setJetpack(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineJetpack, m_offlineJetpack);
}

void IconManager::setMainColor(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineColor1, m_offlineColor1);
}

void IconManager::setSecondaryColor(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineColor2, m_offlineColor2);
}

void IconManager::setGlowColor(int id, IconStatus status) {
    this->setValue<int>(id, status, m_onlineGlowColor, m_offlineGlowColor);
}

void IconManager::setGlowEnabled(bool enabled, IconStatus status) {
    this->setValue<bool>(enabled, status, m_onlineGlow, m_offlineGlow);
}

template<class T>
T IconManager::getValue(IconStatus status, const T& online, const T& offline) const {
    switch (status) {
        case IconStatus::Online:
            return online;
        case IconStatus::Offline:
            return offline;
    }
}

template<class T>
void IconManager::setValue(T newVal, IconStatus status, T& online, T& offline) {
    switch (status) {
        case IconStatus::Online:
            online = newVal;
            break;
        case IconStatus::Offline:
            offline = newVal;
            break;
    }
}
