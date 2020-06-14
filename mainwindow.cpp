#include "mainwindow.h"
#include <QDebug>
#include "globalstruct.h"       //选择框按钮全局结构
#include <math.h>               //数学
#include "greenturret.h"        //绿色防御塔类
#include "fireturret.h"         //火防御塔类
#include "lightturret.h"        //光炮防御塔类
#include "bigturret.h"          //大炮防御塔类
#include "magic.h"              //法术类
#include <QPushButton>

#define PI 3.1416

//鼠标点击区域宏
#define MouClickRegion(X, Width, Y, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

//计算两点之间距离宏
#define DistBetPoints(X1, Y1, X2, Y2)           \
sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2))))

//用于方便通过格子确定路径点坐标
#define X40(num) ((num) - 1) * 40 + 10

//插入怪物  路径点数组名、怪物初始坐标、怪物编号
#define InsterMonster(PathNum, StaCoorNum, MonsterId)     \
MonsterVec.push_back(new Monster(pointarr[PathNum], PathLength[PathNum], X40(staco[StaCoorNum].x), X40(staco[StaCoorNum].y), MonsterId));

//判断金钱是否足够并刷新标签
inline bool MainWindow::DeductionMoney(int money)
{
    if(this->money - money < 0) return true; //判断金钱是否足够
    this->money -= money; //扣除金钱
    moneylable->setText(QString("%1").arg(this->money)); //刷新标签文本
    return false;
}

//构造
MainWindow::MainWindow(int LevelNumber) : LevelNumber(LevelNumber)
{
    //设置固定窗口大小
    setFixedSize(1040, 640);

    //设置标题
    setWindowTitle("游戏界面");

    //提示胜利标签
    QLabel *victorylable = new QLabel(this);
    victorylable->move(176, 180);
    victorylable->setFont(QFont("楷体", 110));
    victorylable->setText(QString("游戏胜利"));
    victorylable->hide();   //先行隐藏，等到胜利的时候再显示出来

    //提示失败标签
    QLabel *loselabel = new QLabel(this);
    loselabel->move(176, 180);
    loselabel->setFont(QFont("楷体", 110));
    loselabel->setText(QString("游戏失败"));
    loselabel->hide();   //先行隐藏，等到失败的时候再显示出来

    QTimer* timer2 = new QTimer(this);      //用于插入怪物定时器
    timer2->start(2000);   //怪物等待2秒才出现

    connect(timer2,&QTimer::timeout,[=]()
    {
        switch (LevelNumber) {
        case 0:
        {
            //设置路径点
            CoorStr* Waypointarr1[] = {new CoorStr(X40(8), X40(6)), new CoorStr(X40(2), X40(6)),
                                       new CoorStr(X40(2), X40(13)), new CoorStr(X40(19), X40(13)), new CoorStr(X40(19), X40(9)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(20), X40(5)), new CoorStr(X40(14), X40(5)),
                                       new CoorStr(X40(14), X40(9)), new CoorStr(X40(8), X40(9)), new CoorStr(X40(8), X40(6)), new CoorStr(X40(2), X40(6)),
                                             new CoorStr(X40(2), X40(13)), new CoorStr(X40(19), X40(13)),
                                       new CoorStr(X40(19), X40(9)), new CoorStr(homecoor->x, homecoor->y)}; //最后的路径点设为家
            //怪物的四个起始点
            CoorStr staco[] = {CoorStr(8, 0), CoorStr(20, 0), CoorStr(8, -1), CoorStr(20, -1)};

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案

            break;
        }
        case 1:
        {
            //设置路径点
            CoorStr* Waypointarr1[] = {new CoorStr(X40(4), X40(8)), new CoorStr(X40(20), X40(8)),
                                       new CoorStr(X40(20), X40(13)), new CoorStr(X40(6), X40(13)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(11), X40(8)), new CoorStr(X40(20), X40(8)),
                                       new CoorStr(X40(20), X40(13)), new CoorStr(X40(6), X40(13)), new CoorStr(homecoor->x, homecoor->y)};

                                      //怪物的四个起始点
            CoorStr staco[] = {CoorStr(4, 0), CoorStr(11, 0), CoorStr(4, -1), CoorStr(11, -1)};

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案
            break;
        }

        case 2:
        {
            //设置路径点
            CoorStr* Waypointarr1[] = {new CoorStr(X40(12), X40(9)), new CoorStr(X40(8), X40(9)),
                                       new CoorStr(X40(8), X40(0)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(12), X40(9)), new CoorStr(X40(16), X40(9)),
                                       new CoorStr(X40(16), X40(0)), new CoorStr(homecoor->x, homecoor->y)};

            //怪物的四个起始点
            CoorStr staco[] = {CoorStr(12, 16), CoorStr(12, 16), CoorStr(12, 17), CoorStr(12, 18)};

            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路的产生怪物方案
            break;
        }
        default:
            break;
        }
    });

    //显示防御塔范围按钮
    QPushButton* disranpush = new QPushButton(this);
    disranpush->setStyleSheet("QPushButton{color:yellow; background:blue}");
    disranpush->setGeometry(20,120, 150, 45);
    disranpush->setFont(QFont("微软雅黑", 14));
    disranpush->setText("显示全部范围");

    connect(disranpush,&QPushButton::clicked,[=]()
    {
        DisplayAllRange ? DisplayAllRange = false : DisplayAllRange = true;  //通过改变标识令防御塔攻击范围显示或关闭
        update();
    });

    //金钱标签
    moneylable->move(80, 20);       //位置
    setStyleSheet("color:white");   //设置颜色
    moneylable->setFont(QFont("微软雅黑", 20));             //设置金钱标签属性
    moneylable->setText(QString("%1").arg(money));    //显示金钱信息

    //生命值标签
    QLabel *lifelable = new QLabel(this);
    lifelable->setGeometry(80, 60, 220, 40);   //设置控件位置和大小
    lifelable->setFont(QFont("微软雅黑", 20));
    lifelable->setText(QString("%1").arg(life));

    //定时器每时每刻执行防御塔父类数组的活动函数
    QTimer* timer = new QTimer(this);
    timer->start(120);

    connect(timer,&QTimer::timeout,[=]()
    {
        //防御塔寻找目标怪物的规律：找到最后一个怪物作为目标，目标丢失后找再继续找最后一个目标
        for (auto defei : DefeTowerVec)      //遍历防御塔
        {
            if (!defei->GetAimsMonster())   //目标怪物为空时从后往前遍历怪物数组寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)
                    //这里以防御塔中心店和怪物中心点判断
                    if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                        MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),
                        MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= defei->GetRange())
                    {
                        defei->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;  //找到后跳出循环
                    }
            }
            else                //当前防御塔拥有目标且怪物在防御塔范围之内时时攻击怪物
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) <= defei->GetRange())
                {
                    //根据每个防御塔的目标怪物计算旋转角度
                    defei->SetRotatAngle(
                        atan2
                        (
                            defei->GetAimsMonster()->GetY() - defei->GetUpLeftY() + 40,
                            defei->GetAimsMonster()->GetX() - defei->GetUpLeftX()
                        ) * 180 / PI );

                     defei->InterBullet();           //拥有目标时一直创建子弹
                }

            //每次循环都判断目标怪物距离防御塔的距离，写在上面可能会不太好
            if (defei->GetAimsMonster())    //目标怪物不为空
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) > defei->GetRange())
                        defei->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }

        //防御塔子弹移动
        for (auto defei : DefeTowerVec)
            defei->BulletMove();

        //怪物移动
        for (auto Moni = MonsterVec.begin(); Moni != MonsterVec.end(); Moni++)
            if((*Moni)->Move()) //怪物走到终点
            {
                delete *Moni;
                MonsterVec.erase(Moni);         //怪物走到终点则删除这个怪物

                life--;                         //我们的生命值-1
                if(life<=9 && life>=6)
                    lifelable->setStyleSheet("color:yellow");   //设置颜色为黄色
                else if(life>=3)
                    lifelable->setStyleSheet("color:orange");   //设置颜色为橘色
                else
                    lifelable->setStyleSheet("color:red");   //设置颜色为红色
                lifelable->setText(QString("%1").arg(life));

                if (life <= 0)
                {
                    loselabel->show();  //显示失败标签
                    QTimer::singleShot(2000, this, SLOT(close()));  //等待两秒后自动关闭界面
                }

                break;
            }

        //判断子弹击中怪物
        for (auto defei : DefeTowerVec)  //防御塔
        {
            auto &tbullvec = defei->GetBulletVec();    //临时存储子弹
            for (auto bullit = tbullvec.begin(); bullit != tbullvec.end(); bullit++)    //子弹
                for (auto monit = MonsterVec.begin(); monit != MonsterVec.end(); monit++)//怪物
                    if ((*bullit)->GetX() + (defei->GetBulletWidth() >> 1) >= (*monit)->GetX() && (*bullit)->GetX() <= (*monit)->GetX() + (*monit)->GetWidth() &&
                       (*bullit)->GetY() + (defei->GetBulletHeight() >> 1) >= (*monit)->GetY() && (*bullit)->GetY() <= (*monit)->GetY() + (*monit)->GetHeight())
                    {   //击中怪物时
                        tbullvec.erase(bullit);     //删除子弹

                        (*monit)->SetHealth((*monit)->GetHealth() - defei->GetAttack());      //敌人血量 = 本身血量减去当前炮塔攻击力

                        if ((*monit)->GetHealth() <= 0) //生命值为空时
                        {
                            //判断一下其他防御塔的目标怪物是否和当前防御塔消灭的怪物重复，如果重复，则将那一个防御塔的目标怪物也设为空
                            for (auto defei2 : DefeTowerVec)
                                if (defei2->GetAimsMonster() == *monit)
                                    defei2->SetAimsMonster(NULL);

                            MonsterVec.erase(monit);    //删除怪物
                            money += RewardMoney;       //击败怪物增加金钱
                            moneylable->setText(QString("%1").arg(money));//刷新标签
                        }

                        //这里不能将防御塔目标怪物设为空，因为防御塔的子弹攻击到的怪物不一定是该防御塔的目标怪物
                        goto L1;
                    }
            L1:;
        }

        update();   //绘图
    });
}

//预设的两条路产生怪物方案
void MainWindow::IrodMonsProgDefa(CoorStr** Waypointarr1, CoorStr** Waypointarr2, CoorStr* staco, int* PathLength, QLabel* victorylable)
{
    /*两条路径*/
    CoorStr** pointarr[] = {Waypointarr1, Waypointarr2};

    /*插入怪物*/
    if(counter >= 1 && counter <= 14)
    {//插入绵羊
        InsterMonster(0, 0, 1); //第几条路径、第几个起始点、怪物编号
    }
    /*else if(counter > 14 && counter <= 34)
    {//在、两路插入绵羊和眼镜蛇
        InsterMonster(0, 0, 1);
        InsterMonster(1, 1, 2);
    }
    else if (counter > 34 && counter <= 35)
    {//两路插入老鹰
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);
    }
    else if (counter > 35 && counter <= 52)
    {//两路插入犀牛、犀牛、绵羊
        InsterMonster(0, 2, 4);
        InsterMonster(0, 0, 4);
        InsterMonster(1, 1, 1);
    }
    if(counter > 52 && counter <= 56)
    {//插入老鹰
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);
    }
    if (counter > 52 && counter <= 71)
    {//插入眼镜蛇，绵羊
        InsterMonster(0, 2, 2);
        InsterMonster(0, 0, 5);
        InsterMonster(1, 3, 1);
        InsterMonster(1, 1, 4);
    }*/

    if (counter > 14 && MonsterVec.empty())   //时间大于71且怪物数组为空时游戏胜利
        victorylable->show();

    counter++;          //计数器+1
    update();
}

//根据数组画出地图函数
//由绘图函数调用
void MainWindow::DrawMapArr(QPainter& painter)
{
    //地图数组  第一关
    int Map_1[16][26] =
    {
        9, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        8, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 3, 6, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 6, 0, 1, 1, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 3, 6, 0, 1, 1, 0, 6, 6, 0, 1, 1, 0, 3, 6, 0, 6, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 6, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 6, 1, 1, 1, 1, 1, 1, 5, 1,
        0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 0, 3, 6, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0,
        0, 1, 1, 0, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 11, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //第二关
    int Map_2[16][26] =
    {
        9, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        8, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 6, 6, 1, 1, 0, 0, 3, 6, 0, 1, 1, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 6, 6, 0, 1, 1, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 11, 0, 12, 0, 5, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //第三关
    int Map_3[16][26] =
    {
        9, 0, 0, 0, 0, 3, 6, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        8, 0, 0, 0, 0, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 6, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 3, 6, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 6, 6, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 11, 0, 12, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map[16][26];    //用于拷贝不同的关卡数组

    switch (LevelNumber)
    {
    case 0:
        memcpy(Map, Map_1, sizeof(Map));
        break;
    case 1:
        memcpy(Map, Map_2, sizeof(Map));
        break;
    case 2:
        memcpy(Map, Map_3, sizeof(Map));
        break;
    default:
        break;
    }

    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:     /*草地*/
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/草地块.png"));
                break;
            case 1:     /*地面*/
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/地面.png"));
                break;
            case 3:     /*防御塔坑*/
                painter.drawPixmap(i * 40, j * 40, 80, 80,
                    QPixmap(":/image/石砖块.png"));
                //防御塔坑坐标初始化塔坑坐标，插入到塔坑对象数组
                TowerPitVec.push_back(new DefenseTowerPit(i * 40, j * 40));
                break;
            case 5:     //家在循环中也输出地面
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/地面.png"));
                homecoor->x = i * 40, homecoor->y = j * 40;
                break;
            case 9:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/草地块.png"));
                moneycoor->x = i * 40+10, moneycoor->y = j * 40;
                break;
            case 8:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/草地块.png"));
                lifecoor->x = i * 40+10, lifecoor->y = j * 40;
                break;
            case 11:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                     QPixmap(":/image/草地块.png"));
                thundercoor->x = i * 40+10, thundercoor->y = j * 40;
                break;
            case 12:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                     QPixmap(":/image/草地块.png"));
                slowcoor->x = i * 40 + 10, slowcoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 80,
                       QPixmap(":/image/房子.png")); //画出房子
    painter.drawPixmap(moneycoor->x, moneycoor->y, 80, 80,
                       QPixmap(":/image/金钱.png"));  //画出金钱标签
    painter.drawPixmap(lifecoor->x, lifecoor->y, 80, 80,
                       QPixmap(":/image/生命.png"));  //画出生命标签
}

//画出选择框
void MainWindow::DrawSelectionBox(QPainter& painter)
{
    //显示选择框
    if (!SelBox->GetDisplay())
        return;

   //画出选择框
    painter.drawPixmap(SelBox->GetX(), SelBox->GetY(), SelBox->GetWidth(), SelBox->GetHeight(),
        QPixmap(SelBox->GetImgPath()));

    //画出子按钮
    SubbutStr *ASubBut = SelBox->GetSelSubBut();    //接收子按钮结构数组
    for (int i = 0; i < 4; i++)
        painter.drawPixmap(ASubBut[i].SubX, ASubBut[i].SubY, ASubBut[i].SubWidth, ASubBut[i].SubHeight,
            QPixmap(ASubBut[i].SubImgPath));

    painter.setPen(QPen(Qt::yellow, 6, Qt::SolidLine));     //设置画笔
    painter.drawRect(QRect(SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 80));
}

//画出防御塔
void MainWindow::DrawDefenseTower(QPainter& painter)
{
    //画出防御塔
    for (auto defei : DefeTowerVec)  //遍历防御塔数组
    {
        //画出底座
        painter.drawPixmap(defei->GetUpLeftX(), defei->GetUpLeftY(), 80, 80, QPixmap(defei->GetBaseImgPath()));

        //画出所有防御塔的攻击范围
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40), defei->GetRange(), defei->GetRange());

        //画出所有防御塔子弹
        for (auto bulli : defei->GetBulletVec())
            painter.drawPixmap(bulli->coor.x, bulli->coor.y, defei->GetBulletWidth(), defei->GetBulletHeight(),QPixmap(defei->GetBulletPath()));

        //画出防御塔
        painter.translate(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40);          //设置旋转中心
        painter.rotate(defei->GetRotatAngle());             //旋转角度
        painter.translate(-(defei->GetUpLeftX() + 40), -(defei->GetUpLeftY() + 40));    //原点复位
        painter.drawPixmap(defei->GetX(), defei->GetY(), defei->GetWidth(), defei->GetHeight(), QPixmap(defei->GetDefImgPath())/*图片路径*/);

        painter.resetTransform();   //重置调整
    }
}

//画出怪物
void MainWindow::DrawMonster(QPainter& painter)
{
    for (auto moni : MonsterVec)//画出怪物
        painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
}

//画出防御塔和升级按钮
void MainWindow::DrawRangeAndUpgrade(QPainter& painter)
{
    //根据条件画出防御塔攻击范围和升级按钮
    for (auto defei : DefeTowerVec)
    {
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {   //画出防御塔攻击范围
            painter.setPen(QPen(Qt::red));  //使用红色画出范围
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            if(defei->GetGrade() == 0)
                painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/image/等级1.png"));
            if(defei->GetGrade() == 1)
                painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/image/等级2.png"));
            if(defei->GetGrade() == 2)
                painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/image/等级3.png"));
        }
    }
}

//画出法术
void MainWindow::DrawMagicImg(QPainter &painter)
{
    if(ThunderTime)
        painter.drawPixmap(thundercoor->x, thundercoor->y, 60, 60,
                           QPixmap(":/image/闪电药剂.png")); //画出闪电药剂图片
    if(!ThunderTime || ThunderReadyToPut)
        painter.drawPixmap(thundercoor->x, thundercoor->y, 60, 60,
                           QPixmap(":/image/闪电药剂准备状态.png")); //画出闪电药剂图片
    if(SlowTime)
        painter.drawPixmap(slowcoor->x, slowcoor->y, 60, 60,
                           QPixmap(":/image/缓慢药剂.png"));  //画出缓慢药剂图片
    if(!SlowTime || SlowReadyToPut)
        painter.drawPixmap(slowcoor->x, slowcoor->y, 60, 60,
                           QPixmap(":/image/缓慢药剂准备状态.png")); //画出缓慢药剂图片
}

//绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类

    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    DrawMapArr(painter);        //画出地图

    DrawDefenseTower(painter);  //画出防御塔和子弹

    DrawMonster(painter);       //画出怪物

    DrawRangeAndUpgrade(painter);//画出攻击范围和升级按钮

    DrawSelectionBox(painter);  //画出选择框

    DrawMagicImg(painter);    //画出法术
}

//鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton) //右键取消
    {
        DisplayRange = false;           //取消显示防御塔攻击范围
        DisplayAllRange = false;      //取消显示防御塔所有攻击范围
        SelBox->SetDisplay(false);      //取消显示选择框
        ThunderReadyToPut = false;   //取消准备释放闪电药剂
        SlowReadyToPut = false;    //取消准备释放缓慢药剂
        update();
    }
    if(ev->button() != Qt::LeftButton) return; //非左键同样取消

    //判断升级按钮的点击
    if (DisplayRange)
    {
        if (MouClickRegion(DisplayRangeX + 10, 60 , DisplayRangeY - 80, 60))
        {
            //设置防御塔宽高，攻击力，微调坐标
            for (auto defei : DefeTowerVec)
                if (defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if(defei->GetGrade() == 3) return;  //最高3段

                    //光炮升级技术
                    if(typeid(*(defei->GetTypeid())) == typeid(LightTurret))  //原价240
                    {
                        if(defei->GetGrade() == 0)
                        {
                            if (DeductionMoney(300)) return;        //升级防御塔需要花费300
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/二级光炮.png");
                            defei->SetGrade(1);
                            break;
                        }
                        if(defei->GetGrade() == 1)
                        {
                            if (DeductionMoney(350)) return;        //升级防御塔需要花费350
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/三级光炮.png");
                            defei->SetGrade(2);
                            break;
                        }
                        if(defei->GetGrade() == 2)
                        {
                            if (DeductionMoney(400)) return;        //升级防御塔需要花费400
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //防御塔宽高增加
                            defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetGrade(3);
                            break;
                        }
                    }

                    //绿瓶升级技术
                    if(typeid(*(defei->GetTypeid())) == typeid(LightTurret))  //原价100
                    {
                        if(defei->GetGrade() == 0)
                        {
                            if (DeductionMoney(150)) return;        //升级防御塔需要花费150
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/二级绿瓶.png");
                            defei->SetGrade(1);
                            break;
                        }
                        if(defei->GetGrade() == 1)
                        {
                            if (DeductionMoney(200)) return;        //升级防御塔需要花费200
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/三级绿瓶.png");
                            defei->SetGrade(2);
                            break;
                        }
                        if(defei->GetGrade() == 2)
                        {
                            if (DeductionMoney(300)) return;        //升级防御塔需要花费300
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //防御塔宽高增加
                            defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetGrade(3);
                            break;
                        }
                    }

                    //火瓶升级技术
                    if(typeid(*(defei->GetTypeid())) == typeid(FireTurret))  //原价150
                    {
                        if(defei->GetGrade() == 0)
                        {
                            if (DeductionMoney(200)) return;        //升级防御塔需要花费200
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/二级火瓶.png");
                            defei->SetGrade(1);
                            break;
                        }
                        if(defei->GetGrade() == 1)
                        {
                            if (DeductionMoney(250)) return;        //升级防御塔需要花费250
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/三级火瓶.png");
                            defei->SetGrade(2);
                            break;
                        }
                        if(defei->GetGrade() == 2)
                        {
                            if (DeductionMoney(300)) return;        //升级防御塔需要花费300
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //防御塔宽高增加
                            defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetGrade(3);
                            break;
                        }
                    }

                    //大炮升级技术
                    if(typeid(*(defei->GetTypeid())) == typeid(BigTurret))  //原价400
                    {
                        if(defei->GetGrade() == 0)
                        {
                            if (DeductionMoney(450)) return;        //升级防御塔需要花费450
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/二级大炮.png");
                            defei->SetGrade(1);
                            break;
                        }
                        if(defei->GetGrade() == 1)
                        {
                            if (DeductionMoney(500)) return;        //升级防御塔需要花费500
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetDefImgPath(":/image/三级大炮.png");
                            defei->SetGrade(2);
                            break;
                        }
                        if(defei->GetGrade() == 2)
                        {
                            if (DeductionMoney(600)) return;        //升级防御塔需要花费600
                            defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                            defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //防御塔宽高增加
                            defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                            defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                            defei->SetRange() += 14;                            //设置防御塔的攻击范围
                            defei->SetGrade(3);
                            break;
                        }
                    }
                }

        SelBox->SetDisplay(false);      //取消显示新建防御塔框
        DisplayRange = false;           //取消显示自己
        update();
        return;
    }

    if (MouClickRegion(thundercoor->x + 10, 60 , thundercoor->y - 80, 60))
    {
        if(ThunderTime && money>=400)  //闪电药剂刷新完毕并且金钱不少于400
        {
            ThunderReadyToPut = true;
            Thunder->SetMagicImgPath(":/image/闪电药剂准备状态.png");
        }
        update();
        return;
    }

    if (MouClickRegion(slowcoor->x + 10, 60 , slowcoor->y - 80, 60))
    {
        if(SlowTime && money>=400)  //缓慢药剂刷新完毕并且金钱不少于400
        {
            SlowReadyToPut = true;
            Slow->SetMagicImgPath(":/image/缓慢药剂准备状态.png");
        }
        update();
        return;
    }

}

//判断选择框四个子按钮的点击
SubbutStr *ASubBut = SelBox->GetSelSubBut();
for (int i = 0; i < 4; i++)
    if (MouClickRegion(ASubBut[i].SubX, ASubBut[i].SubWidth, ASubBut[i].SubY, ASubBut[i].SubHeight) && SelBox->GetDisplay())
    {
        SelBox->SetDisplay(false);      //取消显示选择框

        //根据点击的不同的按钮，将防御塔子类插入到防御塔父类数组
        switch (i)
        {
        case 0: //绿瓶
            if (DeductionMoney(100)) return;    //扣除金钱
            DefeTowerVec.push_back(new GreenTurret(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
            break;
        case 1: //火瓶
            if (DeductionMoney(150)) return;
            DefeTowerVec.push_back(new FireTurret(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
            break;
        case 2: //光炮
            if (DeductionMoney(250)) return;
            DefeTowerVec.push_back(new LightTurret(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 76, 50));
            break;
        case 3: //大炮
            if (DeductionMoney(400)) return;
            DefeTowerVec.push_back(new BigTurret(SelBox->GetX() + 110, SelBox->GetY() + 104, SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 70));
            break;
        default:
            break;
        }

        update();
        return;
    }

    //遍历所有塔坑
    for (auto APit : TowerPitVec)
        //判断点击塔坑
        if (MouClickRegion(APit->GetX(), APit->GetWidth(), APit->GetY(), APit->GetHeight()))
        {
            DisplayRange = false;               //降防御塔的升级选择显示关闭
            for (auto defei : DefeTowerVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(defei->GetUpLeftX() == APit->GetX() && defei->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = defei->GetUpLeftX(), DisplayRangeY = defei->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }

            SelBox->CheckTower(APit->GetX(), APit->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }

    DisplayRange = false;           //取消显示防御塔攻击范围
    SelBox->SetDisplay(false);      //取消显示选择框

    update();
}

//析构释放内存
MainWindow::~MainWindow()
{
    //释放防御塔坑指针数组TowerPitVec
    for (auto it = TowerPitVec.begin(); it != TowerPitVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    //释放选择框类SelBox
    delete SelBox;
    SelBox = NULL;

    //释放防御塔父类指针数组DefeTowerVec
    for (auto it = DefeTowerVec.begin(); it != DefeTowerVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    //释放怪物数组MonsterVec
    for (auto it = MonsterVec.begin(); it != MonsterVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    delete homecoor;
}
