#include "main.hpp"

namespace CTRPluginFramework {
    int folderSelect = 0;
    int inFolderSelect = 0;
    int entriesCount = 0;
    int folderCount = 0;
    int inFolderCount = 0;
    bool isOpenFolder = false;
    void HudMenu(MenuEntry *entry) {
        Screen topScreen = OSD::GetTopScreen();
        topScreen.DrawSysfont("Grace v0.0.0", 0, 0);
        const std::vector<MenuFolder*> folders = menu->GetFolderList();
        const std::vector<MenuEntry*> entries = menu->GetEntryList();

        if (Controller::IsKeyPressed(Key::DPadDown)) {
            if (isOpenFolder) {
                if (inFolderSelect != inFolderCount) {
                    inFolderSelect += 1;
                } else {
                    inFolderSelect = 0;
                }
            } else {
                if (folderSelect != folderCount) {
                    folderSelect += 1;
                } else {
                    folderSelect = 0;
                }
            }
        } else if (Controller::IsKeyPressed(Key::DPadUp)) {
            if (isOpenFolder) {
                if (inFolderSelect != 0) {
                    inFolderSelect -= 1;
                } else {
                    inFolderSelect = inFolderCount;
                }
            } else {
                if (folderSelect != 0) {
                    folderSelect -= 1;
                } else {
                    folderSelect = folderCount;
                }
            }
        } else if (Controller::IsKeyPressed(Key::DPadRight)) {
            if (!isOpenFolder) {
                isOpenFolder = true;
                inFolderSelect = 0;
            } else {
                if (folders[folderSelect]->GetEntryList()[inFolderSelect]->IsActivated()) {
                    folders[folderSelect]->GetEntryList()[inFolderSelect]->Disable();
                } else {
                    folders[folderSelect]->GetEntryList()[inFolderSelect]->Enable();
                }
            }
        } else if (Controller::IsKeyPressed(Key::DPadLeft)) {
            isOpenFolder = false;
        }


        // draw
        int y = 10;
        for (int i = 0; i < folders.size(); i++) {
            if (i == folderSelect) {
                topScreen.DrawSysfont(" > "+folders[i]->Name(), 8, y);
            } else {
                topScreen.DrawSysfont(folders[i]->Name(), 8, y);
            }
            y += 10;
        }
        if (isOpenFolder) {
            int y = 10 + folderSelect*10;
            for (int i = 0; i < folders[folderSelect]->GetEntryList().size(); i++) {
                if (i == inFolderSelect) {
                    if (folders[folderSelect]->GetEntryList()[i]->IsActivated()) {
                        topScreen.DrawSysfont(" > "<<Color::Lime<<folders[folderSelect]->GetEntryList()[i]->Name(), 12+Render::GetTextWidth(" > "+folders[folderSelect]->Name()), y);
                    } else {
                        topScreen.DrawSysfont(" > "<<Color::Red<<folders[folderSelect]->GetEntryList()[i]->Name(), 12+Render::GetTextWidth(" > "+folders[folderSelect]->Name()), y);
                    }
                } else {
                    if (folders[folderSelect]->GetEntryList()[i]->IsActivated()) {
                        topScreen.DrawSysfont(Color::Lime<<folders[folderSelect]->GetEntryList()[i]->Name(), 12+Render::GetTextWidth(" > "+folders[folderSelect]->Name()), y);
                    } else {
                        topScreen.DrawSysfont(Color::Red<<folders[folderSelect]->GetEntryList()[i]->Name(), 12+Render::GetTextWidth(" > "+folders[folderSelect]->Name()), y);
                    }
                }
                y += 10;
            }
        }
        folderCount = folders.size() - 1;
        inFolderCount = folders[folderSelect]->GetEntryList().size() - 1;
    }
}