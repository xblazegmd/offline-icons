#pragma once

#include <Geode/Enums.hpp>

enum class IconStatus {
    Online,
    Offline
};

class IconManager {
public:
    static IconManager* get();

    void loadIcons();
    void saveIcons();
    void setIconsToDefault();

    void updateIcons(IconStatus status, bool updateUserScore = true);

    /// @note Defaults to cube if `type` is not a gamemode
    int getIcon(IconType type, IconStatus status) const;

    int getMainColor(IconStatus status) const;
    int getSecondaryColor(IconStatus status) const;
    int getGlowColor(IconStatus status) const;
    bool isGlowEnabled(IconStatus status) const;

    /// @note Does not do anything if `type` is not a gamemode
    void setIcon(int id, IconType type, IconStatus status);

    void setMainColor(int id, IconStatus status);
    void setSecondaryColor(int id, IconStatus status);
    void setGlowColor(int id, IconStatus status);
    void setGlowEnabled(bool enabled, IconStatus status);
private:
    int m_onlineCube = 1;
    int m_onlineShip = 1;
    int m_onlineBall = 1;
    int m_onlineUFO = 1;
    int m_onlineWave = 1;
    int m_onlineRobot = 1;
    int m_onlineSpider = 1;
    int m_onlineSwing = 1;
    int m_onlineJetpack = 1;

    int m_onlineColor1 = 0;
    int m_onlineColor2 = 3;
    bool m_onlineGlow = false;
    int m_onlineGlowColor = 0;

    int m_offlineCube = 1;
    int m_offlineShip = 1;
    int m_offlineBall = 1;
    int m_offlineUFO = 1;
    int m_offlineWave = 1;
    int m_offlineRobot = 1;
    int m_offlineSpider = 1;
    int m_offlineSwing = 1;
    int m_offlineJetpack = 1;
    
    int m_offlineColor1 = 3;
    int m_offlineColor2 = 0;
    bool m_offlineGlow = false;
    int m_offlineGlowColor = 0;

    // Don't Repeat Yourself
    template<class T>
    T getValue(IconStatus status, const T& online, const T& offline) const;

    template<class T>
    void setValue(T newVal, IconStatus status, T& online, T& offline);
};
