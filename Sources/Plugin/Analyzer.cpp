#include "main.hpp"

namespace CTRPluginFramework
{
    std::vector<u32> addresses;

    void MemoryViewer(MenuEntry *entry) {
        u32 y = 0;
        const Color foregroundColor = Color(255, 255, 255, 128);
        const Color backgroundColor = Color(0, 0, 0, 128);
        for (int i = 0; i < addresses.size(); i++) {
            u32 value;
            Process::Read32(addresses[i], value);
            Screen topScreen = OSD::GetTopScreen();
            y = topScreen.Draw(Utils::Format("%08X %08X", addresses[i], value), 0, y, foregroundColor, backgroundColor);
        }
    }

    void MemoryViewer_Menu(MenuEntry *entry) {
        StringVector selects = {"アドレスを追加"};
        for (int i = 0; i < addresses.size(); i++) {
            selects.push_back(Utils::Format("0x%08X", addresses[i]));
        }
        Keyboard keyboard("Memory Viewer", selects);
        int input = keyboard.Open();
        if (input != -1) {
            if (input == 0) {
                u32 address;
                Keyboard keyboard("アドレスを入力");
                if (keyboard.Open(address) != -1) {
                    addresses.push_back(address);
                }
            } else {
                int addressIndex = input - 1;
                const u32 address = addresses[addressIndex];
                Keyboard keyboard(Utils::Format("0x%08X", addresses[input-1]), {"編集", "HexEditorで開く", "削除"});
                input = keyboard.Open();
                if (input == 0) {
                    u32 value;
                    Keyboard keyboard("値を入力");
                    if (keyboard.Open(value) != -1) {
                        Process::Write32(address, value);
                    }
                } else if (input == 1) {
                    Utils::OpenInHexEditor(address);
                } else if (input == 2) {
                    addresses.erase(addresses.begin() + addressIndex);
                }
            }
        }
    }
}
