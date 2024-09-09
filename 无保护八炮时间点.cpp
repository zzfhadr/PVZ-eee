#include <avz.h>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <synchapi.h> //玉米炮冷却时间35000ms左右 35000ms应该大了(玉米炮冷却36秒（34.75）)
// 玉米炮种下后 625 可用, 发射到分离 205, 发射到命中 373, 冷却时间 3475（单位cs
//  完全是瞎写的程序，2024-6-1-10-30-31 自我评价，
//  i think i shoud left this to future me to complete(cause u think he will do better), ok
//  now we are working on dealing with theft and water zombies at last flag, and clear grid at 9 19 , and 20 waiting recover time,
//  also maybe has other bugs too


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
        AM_ICE_SHROOM,
        ASQUASH,        // 倭瓜
        AUMBRELLA_LEAF, // 叶子保护伞
        AJALAPENO,      // 火爆辣椒
        ALILY_PAD,      // 荷叶
        ACOFFEE_BEAN,   // 咖啡豆
        ASPIKEWEED,     // 毁灭菇
        AICE_SHROOM,    // 寒冰菇
        ASPIKEROCK,     // 地刺王
    });
    AConnect(ATime(1, -599), [] { // only wave 1 has -599, other waves don't have it.(other wavs only have -10?some close to it)
        aCobManager.AutoSetList();
        aItemCollector.SetTypeList({4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27});
    });
    for (auto wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) {
        AConnect(ATime(wave, 0), [] {
            std::random_device rd;
            std::mt19937 g(rd());
            std::vector<AGrid> lst = aCobManager.GetList();
            std::shuffle(lst.begin(), lst.end(), g);
            aCobManager.SetList(lst);
            aItemCollector.SetTypeList({4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27});
        });
        AConnect(ATime(wave, 400), [] { // 444 a lttile bit dophine won't die
            aCobManager.Fire({{2, 7.7}, {5, 7.7}});
        });
    }

    int cdif = 1;
    for (auto wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) {
        cdif = 1;
        while (cdif < 5) {
            AConnect(ATime(wave, 400 + 946 * cdif), [wave] { // 946 can be 1019(maybe)
                if (ANowWave() == wave) {
                    if (wave == 9 || wave == 19) {
                        if ((!(AIsZombieExist(23, 1) || AIsZombieExist(32, 1) || AIsZombieExist(23, 2) || AIsZombieExist(32, 2))) && (AIsZombieExist(23) || AIsZombieExist(32)))
                            aCobManager.Fire({{5, 7.7}});
                        else if ((!(AIsZombieExist(23, 5) || AIsZombieExist(32, 5) || AIsZombieExist(23, 6) || AIsZombieExist(32, 6))) && (AIsZombieExist(23) || AIsZombieExist(32)))
                            aCobManager.Fire({{2, 7.7}});
                        else if ((AIsZombieExist(23) || AIsZombieExist(32)))
                            aCobManager.Fire({{2, 7.7}, {5, 7.7}});
                    } else if ((AIsZombieExist(23) || AIsZombieExist(32)))
                        aCobManager.Fire({{2, 7.7}, {5, 7.7}});
                }
            });
            ++cdif;
        }
    }
    // theft i need a thing to detect if theft exist. if not exist all those no need to run 
    bool* icecold=(bool*)malloc(sizeof *icecold);
    int wave9_19[2] = {10, 20};
    for (int i : wave9_19) {
     AConnect(ATime(i, 152), [icecold] {
             *icecold = false;
            std::vector<APlant*> lst = aCobManager.GetUsableList();
            if (lst.size() >= 4)
            {
                aCobManager.Fire({{2, 1}, {5, 1}});
                *icecold= true;
            }
                
            else if (lst.size() == 3) {
                *icecold=true;
                aCobManager.Fire({{5, 1}});
            } else {
                
            }
        });
    }
    for (int i : wave9_19) {
        AConnect(ATime(i, 3057-400), [icecold]{
            if(*icecold==true)
            {
                 ACard(AM_ICE_SHROOM, {{2, 3}});
                 ACard(AICE_SHROOM, {{5, 3}});
                 
            }
        });
    }


    // coral

    AConnect(ATime(20, 222), [] {
        ACard(ALILY_PAD, {{3, 7}, {4, 7}});
        ACard(ACHERRY_BOMB, {{3, 7}, {4, 7}});
    });

    /*就差小偷相关的了，我发现，第9波和第19波可能会浪费炮，如果把这浪费的炮节约下来，可能就不怕小偷了
        AConnect(ATime(9, 0), [] {
        ACard(ALILY_PAD, {{3, 7}, {4, 7}});
        ACard(AM_CHERRY_BOMB, {{3, 7}, {4, 7}});
    });*/

    // 放两个冰看能不能干死小偷，对没测试过 （很显然不能。。。）
    /*
    AConnect(ATime(20, -666), [] {
        ACard(AM_ICE_SHROOM, {{2, 3}});
        ACard(AICE_SHROOM, {{5, 3}});
    });
    AConnect(ATime(20, 152), [] {
        ACard(ACOFFEE_BEAN, {{5, 3}});
    });
    AConnect(ATime(20, 911), [] {
        ACard(ACOFFEE_BEAN, {{2, 3}});
    });*/
}