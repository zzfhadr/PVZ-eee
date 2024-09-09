#include <avz.h>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <synchapi.h> //玉米炮冷却时间35000ms左右 35000ms应该大了
// 完全是瞎写的程序，2024-6-1-10-30-31 自我评价，
// 一到第九波稳定发挥，access violation
// i think i shoud left this to future me to complete(cause u think he will do better), ok
// now we are working on dealing with theft and water zombies at last flag, and clear grid at 9 19 , and 20 waiting recover time,
// also maybe has other bugs too
ALogger<AMsgBox> msgBoxLogger;
int removeall()
{
    int c = 0;
    AAliveFilter<AZombie> zombieFilter;
    for (auto&& zzbi : zombieFilter) {
        if (zzbi.Abscissa() > 555)
            c++;
    }
    return c;
}
int gintainloca()
{

    int allasdf = 0;
    int notre = 0;
    int c = 0;
    int slowfuckshitihateuwatermelonnow = 0;
    AAliveFilter<AZombie> zombieFilter; // 2.1  0.9  2.0 1.1
    for (auto&& zzbi : zombieFilter) {
        allasdf++;
        if ((zzbi.Type() == AGIGA_GARGANTUAR || zzbi.Type() == AGARGANTUAR) && zzbi.ExistTime() < 1300) {
            c++;
            if (zzbi.Row() == 2 - 1 || zzbi.Row() == 5 - 1) {
                if (zzbi.Abscissa() > 773) {
                    notre++;
                    if (zzbi.SlowCountdown() > 13)
                        slowfuckshitihateuwatermelonnow++;
                }
            } else {
                if (zzbi.Abscissa() > 761) {
                    notre++;
                    if (zzbi.SlowCountdown() > 13)
                        slowfuckshitihateuwatermelonnow++;
                }
            }
        }
    }
    if (c != 0) {
        if ((1.0 - notre / c) >= 0.5) // 50% are in location
        {
            if (notre != 0) {
                if ((slowfuckshitihateuwatermelonnow / notre) >= 0.5) // 范围外超过一半的巨人都被减速
                    return 2;
            }

            return 1;

        }

        else
            return 0;

    } else
        return 520520;
}
//
// typedef int MyArrayType[][5]; https://stackoverflow.com/questions/10794825/how-to-return-a-two-dimensional-pointer-in-c
int** hahfurteft(int* c, int* internalthiefs) // return a Matrix ? info of Thiefs
{
    *c = 0;
    int** arr = new int*[2];
    // static int traxl[4][2] = {0}; // same as {0,0,0,0}; https://stackoverflow.com/questions/15520880/initializing-entire-2d-array-with-one-value
    *internalthiefs = 0;
    AAliveFilter<AZombie> zombieFilter;
    for (auto&& zzbi : zombieFilter) {
        if (zzbi.Type() == ABUNGEE_ZOMBIE) {
            if (zzbi.Abscissa() < 130) {
                arr[zzbi.Row()][(int)((zzbi.Abscissa() - 40) / 80)] = 1;
                (*c)++;
                if (zzbi.Abscissa() == 40)
                    ++(*internalthiefs);
            }
        }
    }
    return arr;
}
//{1,2,5,6}
int* getrowoftheif(int** iwelw)
{
    int c = 0;
    int i = 0;
    static int ugotbekidingme[8] = {0};
    int wtf_8_thief_u_got_be_kidding_me = 0; // from left to right up to down order gotta
    for (c = 0; c < 4; ++c) {
        for (i = 0; i < 2; ++i) {
            if (iwelw[c][i] == 1) {
                if (c <= 1) {
                    ugotbekidingme[wtf_8_thief_u_got_be_kidding_me] = c + 1;
                    ++wtf_8_thief_u_got_be_kidding_me;
                } else {
                    ugotbekidingme[wtf_8_thief_u_got_be_kidding_me] = c + 1 + 2;
                    ++wtf_8_thief_u_got_be_kidding_me;
                }
            }
        }
    }
    return ugotbekidingme;
}
bool chekgroundforspcialplan(int seedIndex, int row, float col)
{ // don't input not valid value like row=-100 col=19639680
    auto mainObject = AGetMainObject();
    auto seed = mainObject->SeedArray() + seedIndex - 1;
    col = int(col + 0.5);
    int type = seed->Type() == AIMITATOR ? seed->ImitatorType() : seed->Type();

    if (row <= 0 || row >= 7)
        return false;
    if (AAsm::GetPlantRejectType(type, row - 1, col - 1) == AAsm::NIL)
        return true;

    return false;
}
void AScript()
{
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    ASetZombies({
                    // TEST // test passed
                    AZOMBIE,
                    ACG_3,           // 撑杆
                    ATT_4,           // 铁桶
                    ABC_12,          // 冰车
                    AXC_15,          // 小丑
                    AHT_14,          // dophoin
                    AQQ_16,          // 气球
                    AFT_21,          // 扶梯
                    ABJ_20,          // thefter
                    ATL_22,          // 投篮
                    ABY_23,          // 白眼
                    AHY_32,          // 红眼
                    ATT_18,          // 跳跳
                    ADIGGER_ZOMBIE,  // digger
                    ADANCING_ZOMBIE, // MJ
                },
        ASetZombieMode::INTERNAL);

    ASelectCards({
        /// 太奇怪了，不选卡，会出现BUG
        ACHERRY_BOMB, // 樱桃炸弹
        AM_CHERRY_BOMB,
        ASQUASH,        // 倭瓜
        AUMBRELLA_LEAF, // 叶子保护伞
        AJALAPENO,      // 火爆辣椒
        ALILY_PAD,      // 荷叶
        ACOFFEE_BEAN,   // 咖啡豆
        ADOOM_SHROOM,   // 毁灭菇
        AICE_SHROOM,    // 寒冰菇
        ASPIKEROCK,     // 地刺王
    });
    AConnect('Q', [] { // 如果冻住了，按Q解冻
        ASetAdvancedPause(false);
    });
    AConnect(ATime(1, -599), [] { // only wave 1 has -599, other waves don't have it.(other wavs only have -10?some close to it)
        aCobManager.AutoSetList();
        aItemCollector.SetTypeList({4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27});
    });
    // ATimeConnectHandle keyHandle[21];
    for (auto wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) {
        AConnect(ATime(wave, 0), [] {
            aCobManager.AutoSetList();
            std::random_device rd;
            std::mt19937 g(rd());
            std::vector<AGrid> lst = aCobManager.GetList();
            std::shuffle(lst.begin(), lst.end(), g);
            aCobManager.SetList(lst);
            aItemCollector.SetTypeList({4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27});
        });
        // keyHandle[wave] =
        AConnect(ATime(wave, 331), [wave] { // UUUUUUUUUUUUUUUUUUUUU this place need to rewrite, need to consider other zombies..
            if (gintainloca() != 520520 && gintainloca() == 1) {
                if (aCobManager.GetUsablePtr() != nullptr) { // 因为是键控，同时发射，因为此处不必区分有一个还是两个，如果以后要加入延迟发射就得检查这里
                    aCobManager.Fire({{2, 7.8}, {5, 7.8}});

                } else {
                    if (AIsSeedUsable(AICE_SHROOM)) {
                        ACard(ALILY_PAD, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
                        ACard(AICE_SHROOM, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
                        ACard(ACOFFEE_BEAN, {{3, 8}, {4, 8}, {3, 9}, {4, 9}});
                    }
                }

                return false; // 直到他们就位，结束。
            }

            return true;
        });
        AConnect(ATime(wave, 336 + 555 + 555), [wave] { // 进入下一波，。，
            if (ANowWave() == wave && AIsZombieExist())
                if (AIsSeedUsable(ACHERRY_BOMB))
                    ACard(ACHERRY_BOMB, {{2, 8}});
        });
    }

    AConnect(ATime(9, 336 + 555 + 6666), [] {
        if (removeall()) {
            if (aCobManager.GetUsablePtr() != nullptr)
                aCobManager.Fire({{2, 7.8}, {5, 7.8}});
        } else
            return false;
        return true;
    });
    AConnect(ATime(19, 336 + 555 + 6666), [] {
        if (removeall()) {
            if (aCobManager.GetUsablePtr() != nullptr)
                aCobManager.Fire({{2, 7.8}, {5, 7.8}});

        } else
            return false;
        return true;
    });
    // 蹦极
    int wave9_19[2] = {9, 19};
    for (int i : wave9_19) {       // 这怎么有这么大问题，，，，无语了
        AConnect(ATime(i, 0), [] { // 主要是为了万无一失，写了好多，也不算多，毕竟是无尽。
            int* numberthief = NULL;
            int* internalthiefs = NULL;
            int** matrix = NULL;
            int* rowofthief = NULL;
            matrix = hahfurteft(numberthief, internalthiefs); //

            rowofthief = getrowoftheif(matrix); // int[8]

            if (*numberthief == 1) {
                if (*internalthiefs == 0) {
                    APlant* squash = nullptr;
                    squash = ACard(ASQUASH, rowofthief[0], 3);
                    if (squash == nullptr)
                        squash = ACard(AUMBRELLA_LEAF, {{1, 3}, {6, 3}});
                    if (squash == nullptr)
                        squash = ACard(AJALAPENO, rowofthief[0], 7);
                    if (squash == nullptr) {
                        msgBoxLogger.Info("somehing went wrong");
                        ASetAdvancedPause(true);
                    }

                    return false; // 这样写的好处是直接在这就返回了，不用呃，好像没有什么好处(因为不一定算好处？），不管了。就这样写
                } else {

                    APlant* jalapeno = nullptr;
                    jalapeno = ACard(AJALAPENO, rowofthief[0], 7);
                    if (jalapeno == nullptr) {
                        msgBoxLogger.Info("somehing went wrong");
                        ASetAdvancedPause(true);
                    }

                    return false;
                }
            }

            if (*numberthief == 2) {
                int isline = abs(rowofthief[0] - rowofthief[1]);
                if (isline == 0) // 直接辣椒烧
                {
                    APlant* jalapeno = nullptr;
                    jalapeno = ACard(AJALAPENO, rowofthief[0], 7);
                    if (jalapeno == nullptr) {
                        msgBoxLogger.Info("somehing went wrong");
                        ASetAdvancedPause(true);
                    }

                } else if (isline == 1) // 判断internalthiefs的值 然后做出相应操作
                {
                    if (*internalthiefs == 0) {
                        APlant* aumbrella = nullptr;
                        aumbrella = ACard(AUMBRELLA_LEAF, rowofthief[0], 3);
                        if (aumbrella == nullptr) {
                            msgBoxLogger.Info("somehing went wrong");
                            ASetAdvancedPause(true);
                        }

                    } else {
                        APlant* wfwefwef = nullptr;
                        wfwefwef = ACard(ACHERRY_BOMB, rowofthief[0], 3);
                        if (wfwefwef == nullptr) {
                            msgBoxLogger.Info("somehing went wrong");
                            ASetAdvancedPause(true);
                        }

                        wfwefwef = ACard(AJALAPENO, rowofthief[0], 7);
                        if (wfwefwef == nullptr) {
                            msgBoxLogger.Info("somehing went wrong");
                            ASetAdvancedPause(true);
                        }
                    }

                    return false; // 应对2个小偷的操作执行完毕，结束ACOONET 重复，我也不知道这个的原理，作者在注释中教的这样写就完了。
                }
            }
            if (*numberthief >= 3) // 超过2个小偷，实在不行就放核了。放核的情况一定要少，不然弹坑周转不过来。
            {
                for (int i = 0; i < (*numberthief); ++i) {
                    if (rowofthief[i] < 6) {
                        APlant* doomshroom = nullptr;
                        doomshroom = ACard(ADOOM_SHROOM, 2, 3);
                        if (doomshroom == nullptr) {
                            msgBoxLogger.Info("somehing went wrong");
                            ASetAdvancedPause(true);
                        }

                    } else {
                        APlant* doomshroom = nullptr;
                        doomshroom = ACard(ADOOM_SHROOM, 5, 3);
                        if (doomshroom == nullptr) {
                            msgBoxLogger.Info("somehing went wrong");
                            ASetAdvancedPause(true);
                        }
                    }
                }

                return false; // 应对3个小偷的操作执行完毕，结束ACOONET 重复，我也不知道这个的原理，作者在注释中教的这样写就完了。
            }

            return true;
        });
    }

    // 水鬼 -200灰樱桃刚刚好，
    // 但我现在不用了，我决定用炮消？？？？不然很难办。。呃，实在不行用冰消吧。
    /* AConnect(ATime(20, -200), [] {
         ACard(ALILY_PAD, {{3, 7}, {4, 7}});
         ACard(AM_CHERRY_BOMB, {{3, 7}, {4, 7}});
     });*/
}