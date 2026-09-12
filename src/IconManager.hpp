#pragma once

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

    int getMainColor(IconStatus status) const;
    int getSecondaryColor(IconStatus status) const;
    int getGlowColor(IconStatus status) const;
    bool isGlowEnabled(IconStatus status) const;

    void setMainColor(int id, IconStatus status);
    void setSecondaryColor(int id, IconStatus status);
    void setGlowColor(int id, IconStatus status);
    void setGlowEnabled(bool enabled, IconStatus status);
private:
    int m_onlineColor1 = 0;
    int m_onlineColor2 = 3;
    bool m_onlineGlow = false;
    int m_onlineGlowColor = 0;
    
    int m_offlineColor1 = 3;
    int m_offlineColor2 = 0;
    bool m_offlineGlow = false;
    int m_offlineGlowColor = 0;
};
