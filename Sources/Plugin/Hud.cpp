#include "main.hpp"

namespace CTRPluginFramework {
    int x_start = 0;
    int y_start = 0;
    int folderSelect = 0;
    int inFolderSelect = 0;
    int folderCount = 0;
    int inFolderCount = 0;
    bool folderOpened = false;

    void HudMenu(MenuEntry *entry) {
        Screen topScreen = OSD::GetTopScreen();
        topScreen.DrawSysfont(menu->Title(), 0, 0);
        const std::vector<MenuFolder*> folders = menu->GetFolderList();
        // const std::vector<MenuEntry*> entries = menu->GetEntryList();

        if (Controller::IsKeyPressed(Key::DPadDown)) {
            if (folderOpened) {
                if (inFolderSelect != inFolderCount) {
                    inFolderSelect++;
                } else {
                    inFolderSelect = 0;
                }
            } else {
                if (folderSelect != folderCount) {
                    folderSelect++;
                } else {
                    folderSelect = 0;
                }
            }
        } else if (Controller::IsKeyPressed(Key::DPadUp)) {
            if (folderOpened) {
                if (inFolderSelect != 0) {
                    inFolderSelect--;
                } else {
                    inFolderSelect = inFolderCount;
                }
            } else {
                if (folderSelect != 0) {
                    folderSelect--;
                } else {
                    folderSelect = folderCount;
                }
            }
        } else if (Controller::IsKeyPressed(Key::DPadRight)) {
            if (!folderOpened) {
                folderOpened = true;
                inFolderSelect = 0;
            } else {
                if (folders[folderSelect]->GetEntryList()[inFolderSelect]->IsActivated()) {
                    folders[folderSelect]->GetEntryList()[inFolderSelect]->Disable();
                } else {
                    folders[folderSelect]->GetEntryList()[inFolderSelect]->Enable();
                }
            }
        } else if (Controller::IsKeyPressed(Key::DPadLeft)) {
            folderOpened = false;
        }
        
        if (Controller::IsKeyDown(Key::CStickDown)) {
            y_start += 2;
        }
        if (Controller::IsKeyDown(Key::CStickUp)) {
            y_start -= 2;
        }
        if (Controller::IsKeyDown(Key::CStickRight)) {
            x_start += 2;
        }
        if (Controller::IsKeyDown(Key::CStickLeft)) {
            x_start -= 2;
        }

        // draw
        int x = x_start + 8;
        int y = y_start + 10;
        for (int i = 0; i < folders.size(); i++) {
            if (i == folderSelect) {
                topScreen.DrawSysfont("> "+folders[i]->Name(), x, y);
            } else {
                topScreen.DrawSysfont(folders[i]->Name(), x, y);
            }
            y += 10;
        }
        if (folderOpened) {
            y = y_start + 10 + folderSelect * 10;
            for (int i = 0; i < folders[folderSelect]->GetEntryList().size(); i++) {
                x = x_start + 12 + Render::GetTextWidth("> "+folders[folderSelect]->Name());
                if (i == inFolderSelect) {
                    if (folders[folderSelect]->GetEntryList()[i]->IsActivated()) {
                        topScreen.DrawSysfont("> "<<Color::Lime<<folders[folderSelect]->GetEntryList()[i]->Name(), x, y);
                    } else {
                        topScreen.DrawSysfont("> "<<Color::Red<<folders[folderSelect]->GetEntryList()[i]->Name(), x, y);
                    }
                } else {
                    if (folders[folderSelect]->GetEntryList()[i]->IsActivated()) {
                        topScreen.DrawSysfont(Color::Lime<<folders[folderSelect]->GetEntryList()[i]->Name(), x, y);
                    } else {
                        topScreen.DrawSysfont(Color::Red<<folders[folderSelect]->GetEntryList()[i]->Name(), x, y);
                    }
                }
                y += 10;
            }
        }

        folderCount = folders.size() - 1;
        inFolderCount = folders[folderSelect]->GetEntryList().size() - 1;
    }
}