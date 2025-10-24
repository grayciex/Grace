#include "main.hpp"

namespace CTRPluginFramework {
    void YW2::AppendMenu(PluginMenu &menu) {
        menu += new MenuFolder("Movement", "", {
            new MenuEntry("Coordinate Movement", YW2::CoordinateMovement),
            new MenuEntry("Moon Jump", YW2::MoonJump),
            new MenuEntry("Walk Speed", YW2::WalkSpeed),
            new MenuEntry("Slow Falling", YW2::SlowFall),
            new MenuEntry("Wall Through", YW2::WallThrough),
            new MenuEntry("Everywhere Bicycle", YW2::EverywhereBicycle),
            new MenuEntry("Walk in Floating", YW2::WalkInFloating),
            new MenuEntry("Change Player Motion", nullptr, YW2::PlayerMotion),
        });
        menu += new MenuFolder("World", "", {
            new MenuEntry("Area Warp", nullptr, YW2::AreaWarp),
        });
        menu += new MenuFolder("Battle", "", {
            new MenuEntry("Waza Infinity", YW2::WazaInfinity),
        });
        menu += new MenuFolder("Visual", "", {
            new MenuEntry("Game Speed", YW2::GameSpeed),
            new MenuEntry("Stop Camera Moving", YW2::StopCameraMoving),
            new MenuEntry("First Person View", YW2::FirstPersonView),
        });
    }

    std::vector<U32_NAME_VALUE> motion_list = {
        {"走る", 0x60284354},
        {"歩く", 0xFFF727B4},
        {"全力疾走",0x0C9C1D8C},
        {"ふらふら", 0x05C2218D},
        {"着地", 0x0CBAE99D},
        {"落ちる", 0x01F546AE},
        {"見渡す", 0x62786A44},
        {"周りを警戒する", 0x1306EDE6},
        {"転ぶ", 0x44E24DCB},
        {"ドアを開ける", 0x93E4B56D},
        {"下を見渡す", 0xF16AA0E5},
        {"蹴る", 0x7603014A},
        {"自転車", 0x2C837095},
        {"ブロック塀", 0x4D5E8E1B},
        {"拾う", 0x0CBAE99D},
        {"スタミナ切れ", 0xFFA7DD46},
        {"ポール登る", 0xA23137F8},
        {"滑り台", 0x0BF96E0B},
        {"座る", 0x2C837095},
        {"うんがい鏡に吸い込まれる", 0xA30F8579},
        {"うんがい鏡に吐き出される", 0x38F24E98},
    };

    struct AreaCategory {
        std::string name;
        std::vector<U32_NAME_VALUE> areas;
    };

    std::vector<AreaCategory> area_list = {
        {
            "さくら住宅街",
            {
                {"さくら住宅街", 0x17DC03F6},
                {"天野家 1階", 0x6A451E6A},
                {"天野家 2階", 0xF34C4FD0},
                {"木霊家 1階", 0x844B7F46},
                {"木霊家 2階", 0x1A2FEAE5},
                {"ヨロズマートさんかく通り店", 0xB67D1DC4},
                {"こぶた銀行", 0xB110D9DD},
                {"こやぎ郵便", 0x56A8F4DA},
                {"ジャングルハンター", 0x41684DA9},
                {"アッカンベーカリー", 0x58737CE8},
                {"公民館", 0x5F1EB8F1},
                {"おもいで屋", 0x460589B0},
                {"さくら第一小学校 南校舎1階", 0x1732EA2F},
                {"さくら第一小学校 北校舎1階", 0x8E3BBB95},
                {"さくら第一小学校 2階", 0xF93C8B03},
                {"さくら第一小学校 3階", 0x105F2E36},
                {"さくら第一小学校 屋上", 0x6EEE528B},
                {"さくら第一小学校 体育館", 0x19E9621D},
                {"ねこの通り道", 0x8C93EC15},
                {"ひとなし路地", 0x65F04920},
                {"怪しい路地裏", 0x629D8D39},
                {"さびしげな水路", 0x629D8D39},
            },
        },
        {
            "そよ風ヒルズ",
            {
                {"そよ風ヒルズ", 0x8A0B3B4F},
                {"ヨロズマート そよ風ヒルズ店", 0xC5A44451},
                {"ひょうたん池博物館 1階", 0xD467E643},
                {"ひょうたん池博物館 2階", 0x4D6EB7F9},
                {"ひょうたん池博物館 資料保管庫", 0x3A69876F},
                {"今田家 1階", 0xF79226D3},
                {"今田家 2階", 0x6E9B7769},
                {"倉岩家", 0xF0FFE2CA},
                {"リリィガーデン エントランス", 0x13EC832C},
                {"リリィガーデン 地下駐車場", 0x8AE5D296},
                {"トロフィールーム", 0x2BAA257D},
                {"ジャンボスライダー", 0x9E2643FB},
                {"しおかぜトンネル", 0x6FAD8CDA},
            },
        },
        {
            "団々坂",
            {
                {"団々坂", 0xBDD5CB7D},
                {"ヨロズマート 団々坂店", 0xF517707A},
                {"正天寺", 0xEB618522},
                {"冥心漢方", 0xEC0C413B},
                {"チョーシ堂", 0xF27AB463},
                {"駄菓子屋", 0x1C74D54F},
                {"さくらの湯 ロビー", 0x02022017},
                {"さくらの湯 男湯", 0x92BD3D86},
                {"さくらの湯 女湯", 0xE5BA0D10},
                {"熊島家 1階", 0xC04CD6E1},
                {"熊島家 2階", 0x5945875B},
                {"熊島家 3階", 0x2E42B7CD},
                {"鳥飼家 大広間", 0xBD3B22A4},
                {"鳥飼家 隠し部屋", 0x53354388},
                {"ぼろやしき", 0xE3B91671},
                {"ぼろやしき 母屋", 0x0DB7775D},
                {"さすらい荘 1階 1部屋目", 0xE11141F1},
                {"さすらい荘 1階 2部屋目", 0x96167167},
                {"さすらい荘 1階 3部屋目", 0x0F1F20DD},
                {"さすらい荘 1階 4部屋目", 0x7818104B},
                {"さすらい荘 1階 5部屋目", 0xE67C85E8},
                {"さすらい荘 2階 1部屋目", 0x917BB57E},
                {"さすらい荘 2階 2部屋目", 0x0872E4C4},
                {"さすらい荘 2階 3部屋目", 0x7F75D452},
                {"さすらい荘 2階 4部屋目", 0xEFCAC9C3},
                {"さすらい荘 2階 5部屋目", 0x98CDF955},
                {"ないしょの横路", 0x269A249E},
                {"こっそり空地", 0xC89445B2},
                {"ひみつの抜け道", 0xD18F74F3},
                {"ひがん山トンネル", 0x056FE40E},
            },
        },
        {
            "おつかい横丁",
            {
                {"おつかい横丁", 0x98BE94A1},
                {"ヨロズマート おつかい横丁店", 0xD07C2FA6},
                {"コインランドリー", 0xCE0ADAFE},
                {"めっけもん", 0xC9671EE7},
                {"かげむら医院 1階", 0x8993DF6A},
                {"かげむら医院 2階", 0x679DBE46},
                {"かげむら医院 地下階段", 0x60F07A5F},
                {"かげむら医院 地下実験室", 0xF04F67CE},
                {"あんのん団地 A-101号室", 0xF4E42B2F},
                {"あんのん団地 A-201号室", 0x6DED7A95},
                {"あんのん団地 A-202号室", 0x31C719C0},
                {"あんのん団地 A-203号室", 0x1AEA4A03},
                {"あんのん団地 A-302号室", 0x41ADED4F},
                {"あんのん団地 B-102号室", 0x848EDFA0},
                {"あんのん団地 B-104号室", 0xAFA38C63},
                {"あんのん団地 B-201号室", 0xF389EF36},
                {"あんのん団地 B-204号室", 0x6A80BE8C},
                {"あんのん団地 B-301号室", 0x1D878E1A},
                {"あんのん団地 C-101号室", 0x8D38938B},
                {"あんのん団地 C-202号室", 0xA8CE487A},
                {"あんのん団地 C-203号室", 0xD8A4BCF5},
                {"あんのん団地 C-204号室", 0xDFC978EC},
                {"あんのん団地 C-302号室", 0xFA3FA31D},
                {"あんのん団地 C-303号室", 0x46C02956},
                {"桜町フラワーロード", 0xA016DB29},
                {"どっこい書店", 0xD711EBBF},
                {"お花見寿司", 0x27697FCB},
                {"タイヨー軒", 0x3E724E8A},
                {"風ラーメン", 0x391F8A93},
                {"ワククポケット", 0xD9CA638D},
                {"カリススタイル", 0x2004BBD2},
                {"商店の細道", 0xEDFF1A6E},
            },
        },
        {
            "さくら中央シティ",
            {
                {"さくら中央シティ 紹介時エリア", 0xCDBF7197},
                {"さくら中央シティ", 0x2002F3C4},
                {"ヨロズマート さくら中央シティ店", 0x98B8DCB7},
                {"福北病院 1階", 0x617604E8},
                {"福北病院 2階", 0x01B18D0D},
                {"はるこい学習塾", 0x76B6BD9B},
                {"ピコピコランド", 0x68C048C3},
                {"カフェ・オ・シャレンヌ", 0x71DB7982},
                {"さくらスポーツクラブ 1階", 0x9FD518AE},
                {"さくらスポーツクラブ 2階", 0x0F6A053F},
                {"さくらスポーツクラブ 3階", 0x786D35A9},
                {"さくらビジネスガーデンビル 1階", 0x20EC1A1D},
                {"さくらビジネスガーデンビル 4階", 0x4C584C4A},
                {"さくらビジネスガーデンビル 7階", 0xCEE27B31},
                {"さくらビジネスガーデンビル 13階", 0xA2562D66},
                {"モグモグバーガー", 0x86CE29EF},
                {"カレーハウス ナマステ", 0x39F72B5C},
                {"スナックゆきおんな", 0x81A3EDF6},
                {"うんぱん通路", 0x522EB912},
                {"塾への近道", 0x55437D0B},
                {"ゆきおんなへの裏道", 0xBB4D1C27},
            },
        },
        {
            "おおもり山",
            {
                {"おおもり山", 0x0569AC18},
                {"おおもり山 登山道", 0x702822D7},
                {"おおもり山 山頂", 0xE921736D},
                {"廃屋", 0x78F0B184},
                {"滝の裏の祠", 0x4AC6D306},
                {"廃トンネル 東", 0xC20C20AE},
                {"廃トンネル 西", 0x5B057114},
            },
        },
        {
            "さくらEXツリー",
            {
                {"さくらEXツリー", 0x32B75C2A},
                {"さくらEXツリー エントランス", 0x4F2E41B6},
                {"さくらEXツリー 展望台", 0xA120209A},
                {"エレベーター", 0xD627100C},
            },
        },
    };
    
    // WIP
    void YW2::FirstPersonView(MenuEntry *entry) {
        if (entry->IsActivated()) {
            Process::Write32(0x005B76F8, 0xE1A00000);
        } else {
            Process::Write32(0x005B76F8, 0xEB000003);
        }

        const u32 playerCoordinateOffset = 0x08851E10;
        const u32 cameraRotateOffset = 0x08BE64C8;
        const u32 cameraCoordinateOffset = 0x08BE6504;

        float playerCoordinate_x, playerCoordinate_y, playerCoordinate_z;
        Process::ReadFloat(playerCoordinateOffset, playerCoordinate_x);
        Process::ReadFloat(playerCoordinateOffset + 0x04, playerCoordinate_y);
        Process::ReadFloat(playerCoordinateOffset + 0x08, playerCoordinate_z);
        Process::WriteFloat(cameraCoordinateOffset + 0x18, playerCoordinate_x);
        Process::WriteFloat(cameraCoordinateOffset + 0x1C, playerCoordinate_z + 0.1f);
        Process::WriteFloat(cameraCoordinateOffset + 0x20, playerCoordinate_x);
    }

    void YW2::CoordinateMovement(MenuEntry *entry) {
        if (Controller::IsKeyDown(Key::A)) {
            float value;
            if (Controller::IsKeyDown(Key::DPadRight)) {
                Process::ReadFloat(0x08851E10, value);
                value += 5;
                Process::WriteFloat(0x08851E10, value);
            } else if (Controller::IsKeyDown(Key::DPadLeft)) {
                Process::ReadFloat(0x08851E10, value);
                value -= 5;
                Process::WriteFloat(0x08851E10, value);
            } else if (Controller::IsKeyDown(Key::DPadDown)) {
                Process::ReadFloat(0x08851E18, value);
                value += 5;
                Process::WriteFloat(0x08851E18, value);
            } else if (Controller::IsKeyDown(Key::DPadUp)) {
                Process::ReadFloat(0x08851E18, value);
                value -= 5;
                Process::WriteFloat(0x08851E18, value);
            }
        }
    }

    void YW2::MoonJump(MenuEntry *entry) {
        float value;
        if (Controller::IsKeyDown(Key::ZL)) {
            Process::ReadFloat(0x08851E14, value);
            value += 5;
            Process::WriteFloat(0x08851E14, value);
        } else if (Controller::IsKeyDown(Key::ZR)) {
             Process::ReadFloat(0x08851E14, value);
            value -= 5;
            Process::WriteFloat(0x08851E14, value);
        }
    }

    void YW2::SlowFall(MenuEntry *entry) {
		if (entry->IsActivated()) {
            Process::Write32(0x003D477C, 0xE1A00000);
        } else {
            Process::Write32(0x003D477C, 0xE1D56BDC);
		}
	}
    
    void YW2::EverywhereBicycle(MenuEntry *entry) {
        if (entry->IsActivated()) {
            Process::Write32(0x0039D928, 0xE3A00000);
			Process::Write32(0x0039D92C, 0xE58511A4);
        } else {
            Process::Write32(0x0039D928, 0xE3A00001);
			Process::Write32(0x0039D92C, 0xE59511A4);
        }
    }

    void YW2::WalkSpeed(MenuEntry *entry) {
        if (entry->IsActivated()) {
            Process::Write32(0x003E7C28, 0x40400000);
        } else {
            Process::Write32(0x003E7C28, 0x3F800000);
        }
    }

    void YW2::WallThrough(MenuEntry *entry) {
        bool isEnable;
		if (Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			if (isEnable) {
				isEnable = false;
				OSD::Notify("Wall Through: Disable");
				Process::Write32(0x00267F68, 0xE3A01000);
				Process::Write32(0x00267F6C, 0xE59D0170);
			} else {
				isEnable = true;
				OSD::Notify("Wall Through: Enabled");
				Process::Write32(0x00267F68, 0xE3A01001);
				Process::Write32(0x00267F6C, 0xE59D0174);
			}
		}
    }

    void YW2::WalkInFloating(MenuEntry *entry) {
        if (entry->IsActivated()) {
            Process::Write32(0x00594798, 0xE3A01001);
			Process::Write32(0x0059479C, 0xE3A02001);
        } else {
            Process::Write32(0x00594798, 0xE5D0111C);
			Process::Write32(0x0059479C, 0xE5D02120);
        }
    }

    void YW2::WazaInfinity(MenuEntry *entry) {
        if (entry->IsActivated()) {
            Process::Write32(0x00563110, 0xE3A050FF);
        } else {
            Process::Write32(0x00563110, 0x0C1A0500);
        }
    }

    void YW2::GameSpeed(MenuEntry *entry)
	{
		if (entry->IsActivated()) {
            Process::Write32(0x00858798, 0x40000000);
        } else {
            Process::Write32(0x00858798, 0x3F800000);
        }
	}

    void YW2::PlayerMotion(MenuEntry *entry) {
        Keyboard keyboard("Player Motion", {"デフォルト", "変更"});
        int input = keyboard.Open();
        if (input == 0) {
            Process::Write32(0x08001E94, 0x43C3094A);
        } else if (input == 1) {
            StringVector motion_names;
            for (const U32_NAME_VALUE i: motion_list) {
                motion_names.push_back(i.name);
            }

            Keyboard keyboard("モーションを選択してください", motion_names);
            input = keyboard.Open();
            if (input != -1) {
                Process::Write32(0x08001E94, motion_list[input].value);
            }
        }
    }

    void YW2::StopCameraMoving(MenuEntry *entry) {
        if (entry->IsActivated()) {
            Process::Write32(0x005B76F8, 0xE1A00000);
        } else {
            Process::Write32(0x005B76F8, 0xEB000003);
        }
    }

    void YW2::AreaWarp(MenuEntry *entry) {
        StringVector options;
        for (const AreaCategory i: area_list) {
            options.push_back(i.name);
        }
        Keyboard keyboard("ワープするエリアを選択", options);
        int input = keyboard.Open();
        if (input != -1) {
            int areaCategoryIndex = input;
            options.clear();
            for (const U32_NAME_VALUE i: area_list[areaCategoryIndex].areas) {
                options.push_back(i.name);
            }
            Keyboard keyboard("ワープするエリアを選択", options);
            input = keyboard.Open();
            if (input != -1) {
                Process::Write32(0x08726284, area_list[areaCategoryIndex].areas[input].value);
				Process::Write32(0x08851E14, 0xF0000000);
            }
        }
    }
}