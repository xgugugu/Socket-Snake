/*Socket Snake Server Module Sample*/

//编译参数：-shared

//头文件可自行添加
#include <bits/stdc++.h>
#include <windows.h>

//定义
#define DLL __declspec(dllexport)

using namespace std;

//API定义
namespace basic {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE), hin = GetStdHandle(STD_INPUT_HANDLE);
	void gotoxy(short x, short y) { //移动光标
		COORD coord = {x, y};
		SetConsoleCursorPosition(hout, coord);
	}
	void cursor(bool visible) { //控制光标
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(hout, &CursorInfo);
		CursorInfo.bVisible = visible;
		SetConsoleCursorInfo(hout, &CursorInfo);
	}
	void color(int ForgC, int BackC) { //设置颜色
		WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hout, wColor);
	}
	void color(int ForgC) { //设置颜色
		WORD wColor;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hout, &csbi)) {
			wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
			SetConsoleTextAttribute(hout, wColor);
		}
	}
	std::string to_string(int _int) { //int转string
		char str[1005];
		sprintf(str, "%d", _int);
		return str;
	}
	int to_int(std::string str) { //string转int
		return atoi(str.c_str());
	}
	int Rand(int a, int b) { //生成随机数
		return (rand() % (b - a + 1)) + a;
	}
}
class Snake {
	public:
		struct Node { //蛇节位置
			int x, y;
			bool operator==(Node b) {
				return x == b.x && y == b.y;
			}
		};
		vector<Node> s_snake; //蛇节位置队列
		int way, dir[4][2]; //方向
		bool online, run; //是否在线，是否为跑步状态
		int dead, length; //重生倒计时，未死亡为0
		Snake() {
			online = 1, dead = 0, run = 0;
			int _dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
			memcpy(dir, _dir, sizeof(_dir)); //初始化方向数组
			way = basic::Rand(0, 99) % 4; //取随机方向
			int X = basic::Rand(10, 190), Y = basic::Rand(10, 190); //取随机出生坐标
			length = 5; //出生长度
			Node temp_node;
			for (int i = 0; i < length; i++) { //生成初始蛇身
				temp_node.x = X;
				temp_node.y = Y;
				s_snake.insert(s_snake.begin(), temp_node);
				X += dir[way][0];
				Y += dir[way][1];
			}
		}
		void change_way(int _way) { //改变方向
			way = _way;
		}
		void grow() { //生长1格
			length = length + 1;
		}
		void shorten() { //缩短1格
			length = length - 1;
		}
		void update() { //蛇前进一次
			Node temp_node;
			temp_node.x = s_snake[0].x + dir[way][0];
			temp_node.y = s_snake[0].y + dir[way][1];
			s_snake.insert(s_snake.begin(), temp_node); //在队列首部加入蛇节
			while (s_snake.size() > length) {
				s_snake.pop_back(); //在队列尾部删去蛇节
			}
		}
		void stop() { //退出玩家
			online = 0;
		}
		Node next_coord() { //获取下一次的位置
			Node temp_node;
			temp_node.x = s_snake[0].x + dir[way][0];
			temp_node.y = s_snake[0].y + dir[way][1];
			return temp_node;
		}
		void die() { //蛇死亡
			dead = 5;
		}
		void reborn() { //重生
			dead = 0, run = 0;
			way = basic::Rand(0, 199) % 4; //取随机方向
			int X = basic::Rand(10, 190), Y = basic::Rand(10, 190); //取随机出生坐标
			length = 5; //出生长度
			s_snake.clear(); //清空长度
			Node temp_node;
			for (int i = 0; i < length; i++) { //生成初始蛇身
				temp_node.x = X;
				temp_node.y = Y;
				s_snake.insert(s_snake.begin(), temp_node);
				X += dir[way][0];
				Y += dir[way][1];
			}
		}
};
class Food { //食物类
	public:
		int x, y, color;
		Food() {
			x = basic::Rand(0, 199), y = basic::Rand(0, 199);
			color = rand() % 15 + 1;
		}
};

//内部使用的变量、函数、类定义区


extern "C" {
	//玩家id下标从1开始
	DLL vector<SOCKET> *sock = NULL; //socket列表，下标从1开始
	DLL vector<Snake> *snake = NULL; //蛇，下标从0开始
	DLL vector<Food> *food = NULL; //食物，下标从0开始
	DLL vector<string> *snake_color = NULL; //颜色，下标从0开始
	DLL vector<string> *snake_name = NULL; //名字，下标从0开始
	DLL void mod_main() { //处理游戏信息，在被加载时运行，建议循环
		//循环处理游戏信息
	}
	DLL string edit_display(string str, int id) { //在玩家显示内容生成完毕时运行，用于显示自定义内容
		//在|和>间的数字表示后面文本使用的文字颜色
                //修改字符串
		return str;
	}
	DLL void read_keydown(string input, int id) { //在收到玩家的按键信息后运行，用于自定义操作
	        //处理按键操作
	}
}
