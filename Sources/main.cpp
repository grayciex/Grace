#include <3ds.h>
#include "csvc.h"

#include "main.hpp"

namespace CTRPluginFramework
{
    const PluginMenu *menu = nullptr;
    const int version_major = 0;
    const int version_minor = 0;
    const int version_revision = 0;
    const std::string about = Utils::Format("Grayscale %d.%d.%d(%s %s)", version_major, version_minor, version_revision, __DATE__, __TIME__);

    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    void PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    void OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    void CommonMenu(PluginMenu &menu) {
        menu += new MenuFolder("Analyze", "", {
            new MenuEntry("Memory Viewer", MemoryViewer, MemoryViewer_Menu),
            new MenuEntry("Replace", nullptr, Replace4Byte),
            new MenuEntry("HudMenu", HudMenu),
        });
    }

	void FrameCallback(Time _time)
	{
  		const Screen topScreen = OSD::GetTopScreen();
        time_t unixTime = time(NULL);
        struct tm* timeStruct = gmtime((const time_t *)&unixTime);
		int year = timeStruct->tm_year + 1900;
		int month = timeStruct->tm_mon + 1;
		int day = timeStruct->tm_mday;
		int hour = timeStruct->tm_hour;
		int minute = timeStruct->tm_min;
		int second = timeStruct->tm_sec;
		const char *wday[] = {"日曜日","月曜日","火曜日","水曜日","木曜日","金曜日","土曜日"};

		std::string timeinfo = Utils::Format("%d/%02d/%02d(%s)    %02d:%02d:%02d", year, month, day, wday[timeStruct->tm_wday], hour, minute, second);
		topScreen.DrawRect(30, 0, 340, 20, Color::Black, true);
		topScreen.DrawRect(32, 2, 336, 16, Color::White, false);
		topScreen.DrawSysfont(timeinfo, 34, 4, Color::White);
	}

    int main(void)
    {
        menu = new PluginMenu("Grace", version_major, version_minor, version_revision, about);
        menu->SynchronizeWithFrame(true);
        menu->OnNewFrame = FrameCallback;
        menu->ShowWelcomeMessage(false);
        switch (Process::GetTitleID()) {
            case 0x0004000000155100:
                YW2::AppendMenu(*menu);
                break;
        }
        CommonMenu(*menu);
        OSD::Notify(Color::Red << "P" << Color::Orange << "l" << Color::Yellow << "u" << Color::Green << "g" << Color::SkyBlue << "i" << Color::Purple << "n " << Color::Red << "r" << Color::Orange << "e" << Color::Yellow << "a" << Color::Green << "d" << Color::SkyBlue << "y" << Color::Purple << "!");
        menu->Run();
        delete menu;
        return (0);
    }
}
