#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
    class YW2 {
        public:
            static void AppendMenu(PluginMenu &menu);

        private:
            static void FirstPersonView(MenuEntry *entry);
            static void CoordinateMovement(MenuEntry *entry);
            static void MoonJump(MenuEntry *entry);
            static void SlowFall(MenuEntry *entry);
            static void EverywhereBicycle(MenuEntry *entry);
            static void WalkSpeed(MenuEntry *entry);
            static void WallThrough(MenuEntry *entry);
            static void WalkInFloating(MenuEntry *entry);
            static void WazaInfinity(MenuEntry *entry);
            static void GameSpeed(MenuEntry *entry);
            static void PlayerMotion(MenuEntry *entry);
            static void StopCameraMoving(MenuEntry *entry);
            static void AreaWarp(MenuEntry *entry);
            static void Test(MenuEntry *entry);
    };
}