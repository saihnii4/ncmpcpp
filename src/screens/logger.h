#include <string>
#include "curses/"

struct Logger: Screen<NC::ScrollPad>, Tabbable
{
    Logger();

    virtual void resize() override;
    virtual void switchTo() override;
    virtual std::wstring title() override;
    virtual ScreenType type() override {
        return ScreenType::Lyrics;
    }

    virtual void update() override;
    virtual bool isLockable() override { return true; }
    virtual bool isMergable() override { return true; }

    void log(const char *message) { return 0; }

    void title();
};

extern Logger *myLogger;
