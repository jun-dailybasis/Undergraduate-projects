
#pragma warning(disable:4996)

#include <iostream>
#include <stdio.h>
using namespace std;
#include <windows.h>//Sleep()함수 이용
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stack>
static int moveCount = 0;
static int inde = 0;


typedef struct
{
	int x;
	int y;
	int visit;
}block;
static block init;//처음 초기화 값 : 입구 
static block exitP; //출구 발견하면 저장할 좌표
int investigation(int **mazse, int x, int y);
void find_path(int **maze, int row, int col, int energy);
//void find_path(int **maze, int **maze_brain, int row, int col, int energy);
void Print(int **maze, int row, int col); //미로 출력
void scan(int **maze, int row, int col); //스캔
//block check_exit(int **maze_scan);
static int scan_count = 0;
void scan(int **maze, int row, int col){
	//printf("표시-> 가로 크기: %d 세로 크기 : %d\n", row, col);
	//printf("스캔 뿌림.\n\n");
	//printf("init.x:%d, init.y:%d\n\n", init.x, init.y);
	//getchar();
	scan_count++;
	int r = 0;//스캔 행렬 가로
	int c = 0;//스캔 행렬 세로 
	//3x3 동적할당
	static int **maze_scan; //스캔 행렬 
	//<--스캔 행렬 동적 할당-->//
	maze_scan = new int*[3];
	for (int i = 0; i < 3; ++i)
	{
		maze_scan[i]= new int[3];
	}


	//윗벽부터~ 모서리에서 꺾기까지
	if(init.x==0){ //위 첫째 줄에서 탐색
		if(init.y==col-3 || init.y==col-2 || init.y==col-4){ //첫째 줄이면서.. 모서리부분 처리
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y+1; j<=init.y+3; j++){
					if(j>=col){ maze_scan[r][c]=8;   //행렬 크기 넘어섰는지 판단하고 넘었으면 스캔 행렬에 8대입
					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);

					if(c<2) c++; //스캔 행렬 값 저장 하기위한 index처리
					if(j==init.y+3){
						r++;
						c=0;
					}
					}
					else{
						maze_scan[r][c]=maze[i][j];//넘어서지 않았다면....

						//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
						if(j==col-1&&maze[i][col-1]==0){
							//printf(" 모서리에서 윗면에서 출구찾음\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(i==0&&maze[0][j]==0){
							//printf("윗면에서 출구찾음\n");
							exitP.x=0;
							exitP.y=j;
						}
						if(c<2) c++;
						if(j==init.y+3){
							r++;
							c=0;
						}
					}
				}
			}
			init.x=3;
			init.y=col-4;
			//printf("\n이제 오른쪽면으로\n");
		}
		else{
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y+1; j<=init.y+3; j++){
					maze_scan[r][c]=maze[i][j];

					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
					if(c<2) c++;
					if(j==init.y+3){
						r++;
						c=0;
					}
					if(i==0&&maze[0][j]==0){
						//printf("윗면에서 출구찾음\n");
						exitP.x=0;
						exitP.y=j;
					}
				}
			}
			init.y= init.y+3;
		}
	}
	//오른 벽면부터~ 모서리에서 꺾기까지
	else if(init.y==col-4){
		if(init.x==row-1 || init.x==row-2 || init.x==row-3){
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y+1; j<=init.y+3; j++){
					if(i>=row){ maze_scan[r][c]=8;
					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);

					if(c<2) c++;
					if(j==init.y+3){
						r++;
						c=0;
					}
					}
					else{
						maze_scan[r][c]=maze[i][j];
						//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
						if(i==row-1&&maze[row-1][j]==0){
							//printf(" 모서리(아래)에서 출구찾음\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(j==col-1&&maze[i][col-1]==0){
							//printf(" ->모서리(옆면)에서 출구찾음\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(c<2) c++;
						if(j==init.y+3){
							r++;
							c=0;
						}
					}
				}
			}
			init.x=row-3;
			init.y=col-3;
		}
		else{
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y+1; j<=init.y+3; j++){
					maze_scan[r][c]=maze[i][j];
					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
					if(j==col-1&&maze[i][col-1]==0){
						//printf(" ->옆면에서 출구찾음\n");
						exitP.x=i;
						exitP.y=j;
					}
					if(c<2) c++;
					if(j==init.y+3){
						r++;
						c=0;
					}
				}
			}
			init.x=init.x+3;
		}
	}
	//아래면에서 ~ 모서리(5시방향)에서 꺾기까지
	else if(init.x==row-3 || init.x==row-2 || init.x==row-1){
		if(init.y==1 || init.y==2 || init.y==0){
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y-3; j<=init.y-1; j++){
					if(j<0){ maze_scan[r][c]=8;
					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
					if(c<2) c++;
					if(j==init.y-1){
						r++;
						c=0;
					}
					}
					else{
						maze_scan[r][c]=maze[i][j];
						//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
						if(i==row-1&&maze[row-1][j]==0){
							//printf(" 모서리(아래)에서 출구찾음\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(j==0&&maze[i][0]==0){
							//printf(" 모서리(왼쪽 벽)에서 출구찾음\n");
							exitP.x=i;
							exitP.y=j;
						}

						if(c<2) c++;
						if(j==init.y-1){
							r++;
							c=0;
						}
					}
				}
			}
			init.x=init.x-3;
			init.y=1;
		}
		else{
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y-3; j<=init.y-1; j++){
					maze_scan[r][c]=maze[i][j];
					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
					if(i==row-1&&maze[row-1][j]==0){
						//printf(" 아래에서 출구찾음\n");
						exitP.x=i;
						exitP.y=j;
					}
					if(c<2) c++;
					if(j==init.y-1){
						r++;
						c=0;
					}
				}
			}
			//printf("확인22");
			init.y=init.y - 3;
		}
	}
	//왼쪽 벽면 부분 스캔할꺼 
	else if(init.y==1){


		if(init.x==1 || init.x==2 ||init.x==0){
			printf("출구를찾지 못했음.");
		}
		else{
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y-3; j<=init.y-1; j++){
					if(j<0){ maze_scan[r][c]=8;
					if(c<2) c++;
					if(j==init.y-1){
						r++;
						c=0;
					}
					}
					else{
						maze_scan[r][c]=maze[i][j];
						//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);

						if(j==0&&maze[i][0]==0){
							//printf(" 모서리(왼쪽 벽)에서 출구찾음\n");
							exitP.x=i;
							exitP.y=j;
						}

						if(c<2) c++;
						if(j==init.y-1){
							r++;
							c=0;
						}
					}
				}
			}
			init.x=init.x-3;
		}
	}
	//<----스캔 기능 값 출력 확인----->//
	//   for(int i = 0; i<3; i++) {
	//      for(int j = 0; j<3; j++){
	//         printf("  %d ", maze_scan[i][j]);
	//      }
	//      printf("\n\n\n");
	//   }
	//
	//free(maze_scan);
	if(exitP.x != 100 && exitP.y !=100)
		free(maze_scan);

}
int main()
{
	FILE *ifp;

	exitP.x=100;
	exitP.y=100;
	static int row; //행의 개수
	static int col; //열의 개수
	int energy; //쥐의 에너지
	int **maze; //미로 입력받는 변수
	//int **maze_brain;//쥐가 보이는 시야를 표시하기 위한 맵
	int row_cnt = 0, col_cnt = 0; //미로의 행과 열의 개수를 새기 위한 변수
	char pan; //미로의 각 부분을 입력받기 위한 변수
	char arr[1000][1000]; //미로의 값 임시 저장 배열
	char file_name[10]; //파일명




	printf("*** 알고리즘 Term Project ***\n");
	printf("- 미로탐색 알고리즘 -\n");
	printf("파일의 이름을 입력하시오 : ");
	cin >> file_name;
	//strcpy(file_name, "Maze2.txt");
	ifp = fopen(file_name, "r"); //파일 읽기 준비

	if (ifp == NULL) //파일 업으면 에러 호출
	{
		cout << "File Open Error!!" << endl;
		exit(1);
	}
	else //파일 읽기 성공하면
	{
		while ((pan = fgetc(ifp)) != EOF) //파일 읽어오는 글자가 끝이 아닐때까지
		{
			arr[row_cnt][col_cnt] = pan; //해당 정보(벽) arr행렬에 저장

			if (pan == '\n') //'한' 라인 읽어왔으면
			{
				//다음줄 읽어올 준비 
				++row_cnt; //row++; 
				col_cnt = 0;//col(열)은 0으로
			}

			else if(pan ==' ')//파일내 공백처리
			{ }
			else// 나머지 경우는 열 +1하면서 한글자씩 읽어오는 경우
			{
				++col_cnt;
			}
		}
	}

	fclose(ifp); //파일 입력 종료3


	++row_cnt;
	row = row_cnt;
	col = col_cnt;

	//행과 열의 크기 만큼 동적할당.
	maze = new int *[row];
	//maze_brain = new int*[row];
	for (int i = 0; i < row; ++i)
	{
		maze[i] = new int[col];
		//maze_brain[i]= new int[col];
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			//maze_brain[i][j] = 1;
			if (arr[i][j] == '1')
			{
				maze[i][j] = 1;
			}
			else if (arr[i][j] == '0')
			{
				maze[i][j] = 0;
			}
		}
	}

	energy = row * col * 2   ;

	//미로가 제대로 구성이 되었는지 출력.
	cout << "row : " << row << endl; //row출력
	cout << "col : " << col << endl; //col출력
	cout << "energy : " << energy << endl; //energy출력

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << maze[i][j];

		}

		cout << endl;
	}
	Print(maze, row, col);
	cout << endl;
	//for (int i = 0; i < row; ++i)
	//{
	//   for (int j = 0; j < col; ++j)
	//   {
	//      cout << maze_brain[i][j];
	//
	//   }
	//
	//   cout << endl;
	//}

	find_path(maze, row, col, energy);

	free(maze);
	getchar();
	getchar();
	return 0;
}

void Print(int **maze, int row, int col)
{
	system("cls");

	int ch = 0;

	printf("moveCOUNT: %d\n", moveCount);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			ch = maze[i][j];

			if(ch == 0)
				printf("  ");
			else if(ch == 1)
				printf("■");
			//else if(ch == 5)
			//   printf("○");
			//else if(ch == 9)
			//   printf("◎");
			else if(ch == 2)
				printf("□");
			//최단거리의 경우
			else if(ch == 8)
				printf("☆");
		}
		printf("\n");
	}
	//printf("===========================================\n");v
}
//미로 탐색 함수 (길이 있으면 true, 없으면 false 반환)
//
int investigation(int **maze, int x, int y)
{
	int cnt = 0;
	//<--cnt변수 의미-->//
	//0이면 막혀있음(정서가 설명한 부분)
	//1이면 길이 하나다
	//2이면 길이 2개다
	//3이면 길이 3개다
	//4이면 길이 4개다(내가 지나온 거리 포함)
	//아래방향으로 길이 있으면
	if (maze[x + 1][y] == 0)
	{
		++cnt;
	}
	//위쪽 방향으로 길이 있으면
	if (maze[x - 1][y] == 0)
	{
		++cnt;
	}
	//오른쪽 방향으로 길이 있으면
	if (maze[x][y + 1] == 0)
	{
		++cnt;
	}
	// 왼쪽 방향으로 길이 있으면
	if (maze[x][y - 1] == 0)
	{
		++cnt;
	}

	return cnt;
}

//본격적으로 쥐가 길을 찾기 위해 사용되는 함수
void find_path(int **maze, int row, int col, int energy)
{
	FILE *ofp;

	ofp = fopen("output.txt", "w");

	srand(time(NULL));
	init.x=0; //스캔 기능에게 처음시작 위치 전달
	init.y=1;   //스캔 기능에게 처음시작 위치 전달
	init.visit=1;
	int mouse_x = 0, mouse_y = 1; //쥐의 현재 위치.
	int **ans_maze; //정답이 표시되는 미로.
	int **path_maze;
	stack <block> path; //쥐가 이동하는 경로를 저장하기 위한 스택.
	block cur; //현재 쥐가 있는 위치를 나타내는 구조체 변수.
	int count = 0;


	int fork_check; //갈림길이 몇 개 있는지 확인하기 위한 변수.
	int energy_zero_check = 0; //출구 찾기 전에 에너지를 다 썼는지 확인하는 변수.
	int exit_check = 0; //출구가 있는 행의 위치에 와서 봤더니 출구가 없으면 1, 있으면 0.
	int wasted_energy = 0; //소모된 에너지를 나타내는 변수.
	double mana_energy = 0;
	int r; //난수 생성.

	//탈출 경로가 표시될 미로 배열 초기화

	//---정답 미로 저장하는 회로 동적 할당--//
	ans_maze = new int*[row];
	for (int i = 0; i < row; ++i)
	{
		ans_maze[i] = new int[col];
	}

	path_maze = new int*[row]; //이전경로 동적할당
	for (int i = 0; i < row; ++i)
	{
		path_maze[i] = new int[col];
	}
	//-------------------------------------//

	//미로 -> 정답미로 값로 저장
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			ans_maze[i][j] = maze[i][j];
			path_maze[i][j] = maze[i][j];//이전경로 0으로
		}
	}

	//쥐의 처음 위치 동기화.
	cur.x = mouse_x;
	cur.y = mouse_y;
	cur.visit = 1;

	//처음 시작 위치가 존재하지 않으면...
	if (ans_maze[mouse_x][mouse_y] != 0)
	{
		cout << "입구를 찾을 수 없습니다." << endl;
		exit(1);
	}

	//쥐가 처음 시작위치에 있을때는 갈 위치가 정해져 있으므로 따로 설정.
	if ((mouse_x == 0) && (mouse_y == 1))
	{
		ans_maze[cur.x][cur.y] = 2;//일종의 빵조각을 떨어뜨려놓는 것과 같다. 이미 방문했다는 표시.
		path_maze[cur.x][cur.y] = 2;
		path.push(cur); //현재 쥐의 위치를 기록한다.
		++mouse_x; //처음에는 쥐가 무조건 앞으로만 가야한다.
		cur.x = mouse_x;
		cur.y = mouse_y;
		++wasted_energy; //에너지가 1 소모 된다.
		moveCount++;
		mana_energy+=0.1;
		//printf("마나:%.1f\n",mana_energy);
		if((mana_energy>=1)){ //마나가 10이 넘으면 바로 스캔 뿌려
			mana_energy= mana_energy-1;
			//printf("스캔 발동!!\n");
			scan(maze, row, col);
		}
	}

	//쥐의 탈출 경로 찾기!!
	while (1)
	{
		if(inde == 0){
			fork_check = 0;//갈림길 갯수 파악 하는 변수.

			//출구를 찾으면 종료.
			if (!(mouse_x == 0 && mouse_y == 1) && (mouse_x == 0 || mouse_y == 0 || mouse_x == row - 1 || mouse_y == col - 1))
				//시작 위치에 있지 않고, (0,0)||(row-1, Y)||(0,Y)||(X,0)||(X, col-1)
				//               쥐가 아래, 위, 왼쪽, 오른쪽 벽 상 에 있을 경우 = 출구찾음
			{
				path.push(cur);
				energy_zero_check = 0;
				exit_check = 0;
				break; // 스캔기능 이상유무 확인하려고 주석처리. 
			}

			//출구를 찾기 전에 에너지가 모두 소실되면 끝.
			if (energy - wasted_energy == 0)
			{
				path.push(cur);
				energy_zero_check = 1;
				break; //스캔기능 이상유무 확인하려고 주석처리
			}
			//printf("mouse_x : %d , mouse_y : %d, energy : %d\n", mouse_x, mouse_y, wasted_energy);
			fork_check = investigation(ans_maze, mouse_x, mouse_y); //갈림길 체크.
			//fork_check 0(정서가 설명한.. 무인도 해프닝)
			//1이면 길1개
			//2이면 길2개
			//3이면 길3개
			//4이면 길4개(지나온 길 포함)
			if (fork_check == 0) //길이 아예 없다.
			{
				ans_maze[mouse_x][mouse_y] = 2;
				path_maze[mouse_x][mouse_y] = 2;
				cur = path.top();
				path.pop();
				mouse_x = cur.x;
				mouse_y = cur.y;
				++wasted_energy;
				++moveCount;
				mana_energy+=0.1;
				//printf("마나:%.1f\n",mana_energy);
				if((mana_energy>=1)){
					mana_energy= mana_energy-1;
					//printf("스캔 발동!!\n");
					scan(maze, row, col);
				}
			}

			if (fork_check == 1)
				//길이 하나 존재.
			{
				if (ans_maze[mouse_x + 1][mouse_y] == 0)
					//아래쪽 행렬의 값이 0이면.. 아래쪽이 뚫렸으면..
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					//이동하기 전(현 위치) 2값으로 변경(이동한 곳이라는 의미)
					path.push(cur);//현 위치좌표 push(2로 변경된 곳)
					++mouse_x; //아래쪽으로 이동
					cur.x = mouse_x; //현위치 업데이트
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if (ans_maze[mouse_x - 1][mouse_y] == 0)
					//왼쪽 행렬의 값이 0이면.. 왼쪽 길이 뚫렸으면...
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur); //현 위치 좌표 push(2로 변경된곳)
					--mouse_x;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if (ans_maze[mouse_x][mouse_y + 1] == 0)
					//오른쪽 길이 뚫렸으면...
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					++mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if (ans_maze[mouse_x][mouse_y - 1] == 0)
					//위쪽 길이 꿇렸으면...
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					--mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}

				// 길이 있는 경우의 if문 중 하나는 통과하므로 '한칸 움직이기' 끝.
				++wasted_energy;
				moveCount++;
				mana_energy+=0.1;//
				//printf("마나:%.1f\n",mana_energy);
				if((mana_energy>=1)){
					mana_energy= mana_energy-1;
					//printf("스캔 발동!!\n");
					scan(maze, row, col);
				}

				Print(path_maze, row, col); //행렬 출력하는 함수
				//Sleep(200);
			}
			else //길이 여러 개 존재.
			{
				//r = rand() % 4 + 1; //1부터 4까지 난수 발생.
				/*************/
				int root_check[4] = { 0 };
				if (ans_maze[mouse_x + 1][mouse_y] == 0) root_check[0] = 1; //아래로 길이 있다
				if (ans_maze[mouse_x - 1][mouse_y] == 0) root_check[1] = 1; //위로 길이 있다.
				if (ans_maze[mouse_x][mouse_y + 1] == 0) root_check[2] = 1; //오른쪽 길이 있다.
				if (ans_maze[mouse_x][mouse_y - 1] == 0) root_check[3] = 1; //왼쪽 길이 있다.
				//root_check 인덱스 순으로 요약하면 -> [아래][위][오른쪽][왼쪽]
				//                              [0]   [1]   [2]    [3] 
				/*사실상 여기서 부터 랜덤 알고리즘*/
				//4길모두있는경우
				if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) {
					//상, 하, 좌, 우 다 길이 나있을 경우
					r = rand() % 4 + 1; 
				}
				//3길있는경우 r=1,2,3중 하나
				//1,2,3번길 있는경우
				else if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) {
					r = rand() % 3 + 1; 
				}
				//1,2,4번길 있는경우 r=1,2,4 중 하나
				else if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) {
					r = rand() % 4 + 1;
					while(r==3){
						r = rand() % 4 + 1;
						if(r!=3) break;
					}  
				}
				//1,3,4번길 있는경우 r=1,3,4 중 하나
				else if (root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) {
					r = rand() % 4 + 1;
					while(r==2){
						r = rand() % 4 + 1;
						if(r!=2) break;
					}  
				}
				//2,3,4번길 있는경우
				else if (root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) {
					r = rand() % 3 + 2;
				}

				//2길 있는경우
				//1,2번길 있는경우
				else if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) {
					r = rand() % 2 + 1;
				}
				//1,3번길 있는경우
				else if (root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) {
					r= rand()%3 +1;
					while(r==2){
						r = rand() % 3 + 1;
						if(r!=2) break;
					}
				}
				//1,4번길 있는경우
				else if (root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) {
					r = rand()%4 +1;
					while(r==2||r==3){
						r = rand()%4 +1;
						if(r!=2 && r!=3) break;

					}
				}
				//2,3번길 있는경우
				else if (root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) {
					r = rand()%2 +2;
				}
				//2,4번길 있는경우
				else if (root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) {
					r = rand()%4 +1;
					while(r==1||r==3){
						r = rand()%4 +1;
						if(r!=1 && r!=3) break;

					}
				}
				//3,4번길 있는경우
				else if (root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) {
					r = rand()%2 + 3;

				}

				Print(path_maze, row, col);
				//Sleep(200);
				//printf("여기까지");

				/**************/
				//방향찾아 고고
				if (r == 1) 
					//r=1이면..
				{
					if (ans_maze[mouse_x + 1][mouse_y] == 0)
						//아래로 이동하라.
					{
						ans_maze[mouse_x][mouse_y] = 2;
						path_maze[mouse_x][mouse_y] = 2;
						path.push(cur);
						++mouse_x;
						cur.x = mouse_x;
						cur.y = mouse_y;
						cur.visit = 1;
					}
				}
				else if (r == 2)
					//r=2이면..
				{
					if (ans_maze[mouse_x - 1][mouse_y] == 0)
						//위로 이동 하라..
					{
						ans_maze[mouse_x][mouse_y] = 2;
						path_maze[mouse_x][mouse_y] = 2;
						path.push(cur);
						--mouse_x;
						cur.x = mouse_x;
						cur.y = mouse_y;
						cur.visit = 1;
					}
				}
				else if (r == 3)
				{
					if (ans_maze[mouse_x][mouse_y + 1] == 0)
					{
						ans_maze[mouse_x][mouse_y] = 2;
						path_maze[mouse_x][mouse_y] = 2;
						path.push(cur);
						++mouse_y;
						cur.x = mouse_x;
						cur.y = mouse_y;
						cur.visit = 1;
					}
				}
				else if (r == 4)
				{
					if (ans_maze[mouse_x][mouse_y - 1] == 0)
					{
						ans_maze[mouse_x][mouse_y] = 2;
						path_maze[mouse_x][mouse_y] = 2;
						path.push(cur);
						--mouse_y;
						cur.x = mouse_x;
						cur.y = mouse_y;
						cur.visit = 1;
					}
				}

				++wasted_energy;
				++moveCount;
				mana_energy+=0.1;
				//printf("마나:%.1f\n",mana_energy);
				if((mana_energy>=1)){
					mana_energy= mana_energy-1;
					//printf("스캔 발동!!\n");


					scan(maze, row, col);
				}
				Print(path_maze, row, col);
				//Sleep(200);

				//printf("여기까지");
			}
			if(exitP.x !=100 && exitP.y != 100){
				getchar();
				printf("\n출구 찾아서 정지 (%d, %d)\n", exitP.x, exitP.y);
				inde = 1;
				getchar();
				for(int i = 0; i < row; i++){
					for(int j = 0; j < col; j++){
						if(ans_maze[i][j] == 2){
							ans_maze[i][j] = 0;
						}
					}
				}
			}
		}
		//여기서 부터 정서
		else{
			int temp_x = exitP.x - mouse_x;	//갈림길에서 어디로갈지 판별위함
			int temp_y = exitP.y - mouse_y;
			fork_check = 0;

			////나가는 길이 아예 없으면... 종료...
			//if(mouse_x == 0 && mouse_y == 1)
			//{
			//	not_exist_road = 1;
			//	break;
			//}

			//출구를 찾으면 종료.
			if(mouse_x == exitP.x && mouse_y == exitP.y)
			{
				path_maze[mouse_x][mouse_y] = 8;
				path.push(cur);
				energy_zero_check = 0;
				exit_check = 0;
				Print(path_maze, row, col);
				break;
			}

			//입구로옴
			if(mouse_x == 0 && mouse_y == 1)
			{
				path.push(cur);
				energy_zero_check = 0;
				exit_check = 1;
				printf("쥐가 입구로와서 종료됩니다.");
				break;
			}

			//출구를 찾기 전에 에너지가 모두 소실되면 끝.
			if(energy - wasted_energy == 0)
			{
				path.push(cur);
				energy_zero_check = 1;

				break;
			}



			fork_check = investigation(ans_maze, mouse_x, mouse_y); //갈림길 체크.

			if(fork_check == 0) //길이 아예 없다.
			{
				ans_maze[mouse_x][mouse_y] = 2;
				path_maze[mouse_x][mouse_y] = 2;
				cur = path.top();
				path.pop();

				mouse_x = cur.x;
				mouse_y = cur.y;
				++wasted_energy;
				++moveCount;
				Print(maze, row, col);

			}
			else if(fork_check == 1) //길이 하나 존재.//수정 x
			{
				if(ans_maze[mouse_x + 1][mouse_y] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					++mouse_x;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if(ans_maze[mouse_x - 1][mouse_y] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					--mouse_x;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if(ans_maze[mouse_x][mouse_y + 1] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					++mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if(ans_maze[mouse_x][mouse_y - 1] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					--mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}

				++wasted_energy;
				++moveCount;
				Print(path_maze, row, col);
			}
			else //길이 여러 개 존재.
			{
				int root_check[4] = {0};
				//길이 존재하는지 확인
				if(ans_maze[mouse_x + 1][mouse_y] == 0) root_check[0] = 1;	
				if(ans_maze[mouse_x - 1][mouse_y] == 0) root_check[1] = 1;	
				if(ans_maze[mouse_x][mouse_y + 1] == 0) root_check[2] = 1;	
				if(ans_maze[mouse_x][mouse_y - 1] == 0) root_check[3] = 1;
				//1번
				if(temp_x < 0 && temp_y < 0)
				{
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 2;
					//	}
					//	else
					//		r = 4;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 1;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 4;
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 4;	
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 1;	
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 3;
						}
						else
							r = 1;
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;				
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 4;
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}			
				}

				//2번
				else if(temp_x < 0 && temp_y ==0)
				{
					////4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 2;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else
							r = 3;
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 2;
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						r = 2;
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(mouse_y > (col * 1/2)){
							r = 1;
						}
						else
							r = 3;
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;	
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else
							r = 3;
					}				
				}
				//3번
				else if(temp_x < 0 && temp_y > 0)
				{
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 2;
					//	}
					//	else
					//		r = 3;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 3;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else{
							if(mouse_x > (row * 1/2))
								r = 2;
							else
								r = 1;
						}
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							if(mouse_y > (col * 1/2))
								r = 4;
							else
								r = 3;
						}
						else
							r = 3;					
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 3;
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else{
							if(mouse_x > (row * 1/2))
								r = 2;
							else
								r = 1;
						}
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 3;
						}
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 4;
						}
						else{
							r = 1;
						}
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 3;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;	
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}	
				}
				//4번
				else if(temp_x == 0 && temp_y < 0){
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 4;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}	
				}

				//case 5

				else if(temp_x == 0 && temp_y > 0){
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 3;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;	
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}	
				}
				//case6
				else if(temp_x > 0 && temp_y < 0){
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 1;
					//	}
					//	else
					//		r = 4;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							if(mouse_x > (row * 1/2))
								r = 2;
							else
								r = 1;
						}
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 4;
						}
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 4;
						}
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							if(mouse_y > (col * 1/2))
								r = 4;
							else
								r = 3;
						}
						else{
							r = 4;
						}
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							if(mouse_x > (row * 1/2))
								r = 2;
							else
								r = 1;
						}
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 4;
						}
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 3;
						}
						else
							r = 2;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							if(mouse_y > (col * 1/2))
								r = 4;
							else
								r = 3;
						}
						else
							r = 4;
					}	
				}
				//case7
				else if(temp_x > 0 && temp_y == 0){
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 1;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else{
							r = 3;
						}
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;	
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;	
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else{
							r = 3;
						}
					}	
				}
				//case8
				else if(temp_x > 0 && temp_y > 0){
					//4개의 길이 존재하는 경우
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 1;
					//	}
					//	else
					//		r = 3;
					//}

					////3길이 존재하는 경우
					////1,2,3번 길이 존재하는 경우
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else
							r = 3;
					}
					//1,2,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							if(mouse_x > (row * 1/2))
								r = 2;
							else
								r = 1;

						}
					}
					//1,3,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else
							r = 3;
					}
					//2,3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							if(mouse_y > (col * 1/2))
								r = 4;
							else
								r = 3;
						}
						else{
							r = 3;
						}
					}

					//2개의 길이 존재하는 경우
					//1,2번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							if(mouse_x > (row * 1/2))
								r = 2;
							else
								r = 1;
						}
					}
					//1,3번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else
							r = 3;
					}
					//1,4번 길이 존재하는 경우
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//2,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;	
					}
					//3,4번 길이 존재하는 경우
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}	
				}
				Print(path_maze, row, col);
				//Sleep(200);
			}
			if(r == 1)
			{
				if(ans_maze[mouse_x + 1][mouse_y] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					++mouse_x;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
			}
			else if(r == 2)
			{
				if(ans_maze[mouse_x - 1][mouse_y] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					--mouse_x;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
			}
			else if(r == 3)
			{
				if(ans_maze[mouse_x][mouse_y + 1] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					++mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
			}
			else if(r == 4)
			{
				if(ans_maze[mouse_x][mouse_y - 1] == 0)
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					--mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
			}

			++wasted_energy;	
			++moveCount;
			Print(path_maze, row, col);
			//Sleep(200);
			if(count ==0){
				count ++;
				ans_maze[0][2] = 1;
			}
		}	  
	}

	if (energy_zero_check == 1) //에너지가 없으면 끝.
	{	
		printf("\n에너지가 부족하여 출구를 찾지 못했습니다.\n");
	}
	else //에너지가 남아 있으면...
	{
		if (exit_check == 1)
		{
			printf("출구를 찾지 못했습니다.\n");
			fprintf(ofp, "출구를 찾지 못했습니다.\n");

			printf("시작 에너지 : %d\n",energy);
			fprintf(ofp, "시작 에너지 : %d\n", energy);

			printf("소비 에너지 : %d\n",wasted_energy);
			fprintf(ofp, "소비 에너지 : %d\n", wasted_energy);

			printf("남은 에너지 : %d\n", energy - wasted_energy);
			fprintf(ofp, "남은 에너지 : %d\n", energy - wasted_energy);
			for(int i = 0; i < row; i++){
				for(int j = 0; j < col; j++){
					ans_maze[i][j] = 0;
				}
			}
			while(1)
				{
					if(path.empty() == 1)
					{
						break;
					}

					block ms;

					ms = path.top();

					ans_maze[ms.x][ms.y] = 1;

					path.pop();
				}

				for(int i = 0 ; i < row ; ++i)
				{
					for(int j = 0 ; j < col ; ++j)
					{
						if(ans_maze[i][j] == 1)
						{
							cout << "0";
							fprintf(ofp, "0");
						}
						else
						{
							cout << " ";
							fprintf(ofp, " ");
						}
					}
					cout << endl;
					fprintf(ofp, "\n");
				}
		}
		else
		{
			
			printf("출구를 찾았습니다!!!\n");
			fprintf(ofp, "출구를 찾았습니다!!!\n");

			printf("시작 에너지 : %d\n",energy);
			fprintf(ofp, "시작 에너지 : %d\n", energy);

			printf("소비 에너지 : %d\n",wasted_energy);
			fprintf(ofp, "소비 에너지 : %d\n", wasted_energy);

			printf("남은 에너지 : %d\n", energy - wasted_energy);
			fprintf(ofp, "남은 에너지 : %d\n", energy - wasted_energy);
			for(int i = 0; i < row; i++){
				for(int j = 0; j < col; j++){
					ans_maze[i][j] = 0;
				}
			}
			while(1)
				{
					if(path.empty() == 1)
					{
						break;
					}

					block ms;

					ms = path.top();

					ans_maze[ms.x][ms.y] = 1;

					path.pop();
				}

				for(int i = 0 ; i < row ; ++i)
				{
					for(int j = 0 ; j < col ; ++j)
					{
						if(ans_maze[i][j] == 1)
						{
							cout << "0";
							fprintf(ofp, "0");
						}
						else
						{
							cout << " ";
							fprintf(ofp, " ");
						}
					}
					cout << endl;
					fprintf(ofp, "\n");
				}
		}
		free(ans_maze);
	}
}