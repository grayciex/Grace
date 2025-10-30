#include "main.hpp"

namespace CTRPluginFramework
{
    std::vector<u32> memoryviewer_addresses;
    void MemoryViewer(MenuEntry *entry) {
        u32 y = 0;
        const Color foregroundColor = Color(255, 255, 255, 128);
        const Color backgroundColor = Color(0, 0, 0, 128);
        for (int i = 0; i < memoryviewer_addresses.size(); i++) {
            u32 value;
            Process::Read32(memoryviewer_addresses[i], value);
            Screen topScreen = OSD::GetTopScreen();
            y = topScreen.Draw(Utils::Format("%08X %08X", memoryviewer_addresses[i], value), 0, y, foregroundColor, backgroundColor);
        }
    }

    void MemoryViewer_Menu(MenuEntry *entry) {
        StringVector selects = {"アドレスを追加"};
        for (int i = 0; i < memoryviewer_addresses.size(); i++) {
            selects.push_back(Utils::Format("0x%08X", memoryviewer_addresses[i]));
        }
        Keyboard keyboard("Memory Viewer", selects);
        int input = keyboard.Open();
        if (input != -1) {
            if (input == 0) {
                u32 address;
                Keyboard keyboard("アドレスを入力");
                if (keyboard.Open(address) != -1) {
                    memoryviewer_addresses.push_back(address);
                }
            } else {
                int addressIndex = input - 1;
                const u32 address = memoryviewer_addresses[addressIndex];
                Keyboard keyboard(Utils::Format("0x%08X", memoryviewer_addresses[input-1]), {"編集", "HexEditorで開く", "削除"});
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
                    memoryviewer_addresses.erase(memoryviewer_addresses.begin() + addressIndex);
                }
            }
        }
    }

    std::vector<u32> replaced_addresses;
    u32 start_address, end_address, before_value, after_value;
    void Replace(MenuEntry *entry) {
        if (replaced_addresses.size() == 0) {
            Keyboard keyboard("最初のアドレス");
            if (keyboard.Open(start_address) != -1) {
                Keyboard keyboard("最後のアドレス");
                if (keyboard.Open(end_address) != -1) {
                    Keyboard keyboard("置き換え前の値");
                    if (keyboard.Open(before_value) != -1) {
                        Keyboard keyboard("置き換え後の値");
                        if (keyboard.Open(after_value) != -1) {
                            for (u32 address=start_address; address<=end_address; address+=0x04) {
                                u32 value;
                                Process::Read32(address, value);
                                if (value == before_value) {
                                    Process::Write32(address, after_value);
                                    replaced_addresses.push_back(address);
                                }
                            }
                            MessageBox(Utils::Format("%d個見つかりました", replaced_addresses.size()))();
                        }
                    }
                }
            }
        } else {
            StringVector options = {"全部戻す"};
            for (int i=0; i < replaced_addresses.size(); i++) {
                options.push_back(Utils::Format("0x%08X", replaced_addresses[i]));
            }
            Keyboard keyboard(Utils::Format("最初のアドレス:0x%08X\n最後のアドレス:0x%08X\n置き換え前の値:0x%08X\n置き換え後の値:0x%08X", start_address, end_address, before_value, after_value), options);
            int input = keyboard.Open();
            if (input != -1) {
                if (input == 0) {
                    for (int i=0; i<replaced_addresses.size(); i++) {
                        Process::Write32(replaced_addresses[i], before_value);
                    }
                    replaced_addresses.clear();
                } else {
                    int addressIndex = input - 1;
                    Process::Write32(replaced_addresses[addressIndex], before_value);
                    replaced_addresses.erase(replaced_addresses.begin() + addressIndex);
                }
            }
        }
    }
}
