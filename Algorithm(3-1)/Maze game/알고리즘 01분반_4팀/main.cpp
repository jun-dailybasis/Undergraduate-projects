
#pragma warning(disable:4996)

#include <iostream>
#include <stdio.h>
using namespace std;
#include <windows.h>//Sleep()�Լ� �̿�
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
static block init;//ó�� �ʱ�ȭ �� : �Ա� 
static block exitP; //�ⱸ �߰��ϸ� ������ ��ǥ
int investigation(int **mazse, int x, int y);
void find_path(int **maze, int row, int col, int energy);
//void find_path(int **maze, int **maze_brain, int row, int col, int energy);
void Print(int **maze, int row, int col); //�̷� ���
void scan(int **maze, int row, int col); //��ĵ
//block check_exit(int **maze_scan);
static int scan_count = 0;
void scan(int **maze, int row, int col){
	//printf("ǥ��-> ���� ũ��: %d ���� ũ�� : %d\n", row, col);
	//printf("��ĵ �Ѹ�.\n\n");
	//printf("init.x:%d, init.y:%d\n\n", init.x, init.y);
	//getchar();
	scan_count++;
	int r = 0;//��ĵ ��� ����
	int c = 0;//��ĵ ��� ���� 
	//3x3 �����Ҵ�
	static int **maze_scan; //��ĵ ��� 
	//<--��ĵ ��� ���� �Ҵ�-->//
	maze_scan = new int*[3];
	for (int i = 0; i < 3; ++i)
	{
		maze_scan[i]= new int[3];
	}


	//��������~ �𼭸����� �������
	if(init.x==0){ //�� ù° �ٿ��� Ž��
		if(init.y==col-3 || init.y==col-2 || init.y==col-4){ //ù° ���̸鼭.. �𼭸��κ� ó��
			for(int i = init.x; i<=init.x+2; i++){
				for(int j = init.y+1; j<=init.y+3; j++){
					if(j>=col){ maze_scan[r][c]=8;   //��� ũ�� �Ѿ���� �Ǵ��ϰ� �Ѿ����� ��ĵ ��Ŀ� 8����
					//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);

					if(c<2) c++; //��ĵ ��� �� ���� �ϱ����� indexó��
					if(j==init.y+3){
						r++;
						c=0;
					}
					}
					else{
						maze_scan[r][c]=maze[i][j];//�Ѿ�� �ʾҴٸ�....

						//printf("maze_scan[%d][%d]=%d / maze[%d][%d]=%d\n", r,c,maze_scan[r][c],i,j,maze[i][j]);
						if(j==col-1&&maze[i][col-1]==0){
							//printf(" �𼭸����� ���鿡�� �ⱸã��\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(i==0&&maze[0][j]==0){
							//printf("���鿡�� �ⱸã��\n");
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
			//printf("\n���� �����ʸ�����\n");
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
						//printf("���鿡�� �ⱸã��\n");
						exitP.x=0;
						exitP.y=j;
					}
				}
			}
			init.y= init.y+3;
		}
	}
	//���� �������~ �𼭸����� �������
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
							//printf(" �𼭸�(�Ʒ�)���� �ⱸã��\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(j==col-1&&maze[i][col-1]==0){
							//printf(" ->�𼭸�(����)���� �ⱸã��\n");
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
						//printf(" ->���鿡�� �ⱸã��\n");
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
	//�Ʒ��鿡�� ~ �𼭸�(5�ù���)���� �������
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
							//printf(" �𼭸�(�Ʒ�)���� �ⱸã��\n");
							exitP.x=i;
							exitP.y=j;
						}
						if(j==0&&maze[i][0]==0){
							//printf(" �𼭸�(���� ��)���� �ⱸã��\n");
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
						//printf(" �Ʒ����� �ⱸã��\n");
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
			//printf("Ȯ��22");
			init.y=init.y - 3;
		}
	}
	//���� ���� �κ� ��ĵ�Ҳ� 
	else if(init.y==1){


		if(init.x==1 || init.x==2 ||init.x==0){
			printf("�ⱸ��ã�� ������.");
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
							//printf(" �𼭸�(���� ��)���� �ⱸã��\n");
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
	//<----��ĵ ��� �� ��� Ȯ��----->//
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
	static int row; //���� ����
	static int col; //���� ����
	int energy; //���� ������
	int **maze; //�̷� �Է¹޴� ����
	//int **maze_brain;//�㰡 ���̴� �þ߸� ǥ���ϱ� ���� ��
	int row_cnt = 0, col_cnt = 0; //�̷��� ��� ���� ������ ���� ���� ����
	char pan; //�̷��� �� �κ��� �Է¹ޱ� ���� ����
	char arr[1000][1000]; //�̷��� �� �ӽ� ���� �迭
	char file_name[10]; //���ϸ�




	printf("*** �˰��� Term Project ***\n");
	printf("- �̷�Ž�� �˰��� -\n");
	printf("������ �̸��� �Է��Ͻÿ� : ");
	cin >> file_name;
	//strcpy(file_name, "Maze2.txt");
	ifp = fopen(file_name, "r"); //���� �б� �غ�

	if (ifp == NULL) //���� ������ ���� ȣ��
	{
		cout << "File Open Error!!" << endl;
		exit(1);
	}
	else //���� �б� �����ϸ�
	{
		while ((pan = fgetc(ifp)) != EOF) //���� �о���� ���ڰ� ���� �ƴҶ�����
		{
			arr[row_cnt][col_cnt] = pan; //�ش� ����(��) arr��Ŀ� ����

			if (pan == '\n') //'��' ���� �о������
			{
				//������ �о�� �غ� 
				++row_cnt; //row++; 
				col_cnt = 0;//col(��)�� 0����
			}

			else if(pan ==' ')//���ϳ� ����ó��
			{ }
			else// ������ ���� �� +1�ϸ鼭 �ѱ��ھ� �о���� ���
			{
				++col_cnt;
			}
		}
	}

	fclose(ifp); //���� �Է� ����3


	++row_cnt;
	row = row_cnt;
	col = col_cnt;

	//��� ���� ũ�� ��ŭ �����Ҵ�.
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

	//�̷ΰ� ����� ������ �Ǿ����� ���.
	cout << "row : " << row << endl; //row���
	cout << "col : " << col << endl; //col���
	cout << "energy : " << energy << endl; //energy���

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
				printf("��");
			//else if(ch == 5)
			//   printf("��");
			//else if(ch == 9)
			//   printf("��");
			else if(ch == 2)
				printf("��");
			//�ִܰŸ��� ���
			else if(ch == 8)
				printf("��");
		}
		printf("\n");
	}
	//printf("===========================================\n");v
}
//�̷� Ž�� �Լ� (���� ������ true, ������ false ��ȯ)
//
int investigation(int **maze, int x, int y)
{
	int cnt = 0;
	//<--cnt���� �ǹ�-->//
	//0�̸� ��������(������ ������ �κ�)
	//1�̸� ���� �ϳ���
	//2�̸� ���� 2����
	//3�̸� ���� 3����
	//4�̸� ���� 4����(���� ������ �Ÿ� ����)
	//�Ʒ��������� ���� ������
	if (maze[x + 1][y] == 0)
	{
		++cnt;
	}
	//���� �������� ���� ������
	if (maze[x - 1][y] == 0)
	{
		++cnt;
	}
	//������ �������� ���� ������
	if (maze[x][y + 1] == 0)
	{
		++cnt;
	}
	// ���� �������� ���� ������
	if (maze[x][y - 1] == 0)
	{
		++cnt;
	}

	return cnt;
}

//���������� �㰡 ���� ã�� ���� ���Ǵ� �Լ�
void find_path(int **maze, int row, int col, int energy)
{
	FILE *ofp;

	ofp = fopen("output.txt", "w");

	srand(time(NULL));
	init.x=0; //��ĵ ��ɿ��� ó������ ��ġ ����
	init.y=1;   //��ĵ ��ɿ��� ó������ ��ġ ����
	init.visit=1;
	int mouse_x = 0, mouse_y = 1; //���� ���� ��ġ.
	int **ans_maze; //������ ǥ�õǴ� �̷�.
	int **path_maze;
	stack <block> path; //�㰡 �̵��ϴ� ��θ� �����ϱ� ���� ����.
	block cur; //���� �㰡 �ִ� ��ġ�� ��Ÿ���� ����ü ����.
	int count = 0;


	int fork_check; //�������� �� �� �ִ��� Ȯ���ϱ� ���� ����.
	int energy_zero_check = 0; //�ⱸ ã�� ���� �������� �� ����� Ȯ���ϴ� ����.
	int exit_check = 0; //�ⱸ�� �ִ� ���� ��ġ�� �ͼ� �ô��� �ⱸ�� ������ 1, ������ 0.
	int wasted_energy = 0; //�Ҹ�� �������� ��Ÿ���� ����.
	double mana_energy = 0;
	int r; //���� ����.

	//Ż�� ��ΰ� ǥ�õ� �̷� �迭 �ʱ�ȭ

	//---���� �̷� �����ϴ� ȸ�� ���� �Ҵ�--//
	ans_maze = new int*[row];
	for (int i = 0; i < row; ++i)
	{
		ans_maze[i] = new int[col];
	}

	path_maze = new int*[row]; //������� �����Ҵ�
	for (int i = 0; i < row; ++i)
	{
		path_maze[i] = new int[col];
	}
	//-------------------------------------//

	//�̷� -> ����̷� ���� ����
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			ans_maze[i][j] = maze[i][j];
			path_maze[i][j] = maze[i][j];//������� 0����
		}
	}

	//���� ó�� ��ġ ����ȭ.
	cur.x = mouse_x;
	cur.y = mouse_y;
	cur.visit = 1;

	//ó�� ���� ��ġ�� �������� ������...
	if (ans_maze[mouse_x][mouse_y] != 0)
	{
		cout << "�Ա��� ã�� �� �����ϴ�." << endl;
		exit(1);
	}

	//�㰡 ó�� ������ġ�� �������� �� ��ġ�� ������ �����Ƿ� ���� ����.
	if ((mouse_x == 0) && (mouse_y == 1))
	{
		ans_maze[cur.x][cur.y] = 2;//������ �������� ����߷����� �Ͱ� ����. �̹� �湮�ߴٴ� ǥ��.
		path_maze[cur.x][cur.y] = 2;
		path.push(cur); //���� ���� ��ġ�� ����Ѵ�.
		++mouse_x; //ó������ �㰡 ������ �����θ� �����Ѵ�.
		cur.x = mouse_x;
		cur.y = mouse_y;
		++wasted_energy; //�������� 1 �Ҹ� �ȴ�.
		moveCount++;
		mana_energy+=0.1;
		//printf("����:%.1f\n",mana_energy);
		if((mana_energy>=1)){ //������ 10�� ������ �ٷ� ��ĵ �ѷ�
			mana_energy= mana_energy-1;
			//printf("��ĵ �ߵ�!!\n");
			scan(maze, row, col);
		}
	}

	//���� Ż�� ��� ã��!!
	while (1)
	{
		if(inde == 0){
			fork_check = 0;//������ ���� �ľ� �ϴ� ����.

			//�ⱸ�� ã���� ����.
			if (!(mouse_x == 0 && mouse_y == 1) && (mouse_x == 0 || mouse_y == 0 || mouse_x == row - 1 || mouse_y == col - 1))
				//���� ��ġ�� ���� �ʰ�, (0,0)||(row-1, Y)||(0,Y)||(X,0)||(X, col-1)
				//               �㰡 �Ʒ�, ��, ����, ������ �� �� �� ���� ��� = �ⱸã��
			{
				path.push(cur);
				energy_zero_check = 0;
				exit_check = 0;
				break; // ��ĵ��� �̻����� Ȯ���Ϸ��� �ּ�ó��. 
			}

			//�ⱸ�� ã�� ���� �������� ��� �ҽǵǸ� ��.
			if (energy - wasted_energy == 0)
			{
				path.push(cur);
				energy_zero_check = 1;
				break; //��ĵ��� �̻����� Ȯ���Ϸ��� �ּ�ó��
			}
			//printf("mouse_x : %d , mouse_y : %d, energy : %d\n", mouse_x, mouse_y, wasted_energy);
			fork_check = investigation(ans_maze, mouse_x, mouse_y); //������ üũ.
			//fork_check 0(������ ������.. ���ε� ������)
			//1�̸� ��1��
			//2�̸� ��2��
			//3�̸� ��3��
			//4�̸� ��4��(������ �� ����)
			if (fork_check == 0) //���� �ƿ� ����.
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
				//printf("����:%.1f\n",mana_energy);
				if((mana_energy>=1)){
					mana_energy= mana_energy-1;
					//printf("��ĵ �ߵ�!!\n");
					scan(maze, row, col);
				}
			}

			if (fork_check == 1)
				//���� �ϳ� ����.
			{
				if (ans_maze[mouse_x + 1][mouse_y] == 0)
					//�Ʒ��� ����� ���� 0�̸�.. �Ʒ����� �շ�����..
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					//�̵��ϱ� ��(�� ��ġ) 2������ ����(�̵��� ���̶�� �ǹ�)
					path.push(cur);//�� ��ġ��ǥ push(2�� ����� ��)
					++mouse_x; //�Ʒ������� �̵�
					cur.x = mouse_x; //����ġ ������Ʈ
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if (ans_maze[mouse_x - 1][mouse_y] == 0)
					//���� ����� ���� 0�̸�.. ���� ���� �շ�����...
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur); //�� ��ġ ��ǥ push(2�� ����Ȱ�)
					--mouse_x;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}
				else if (ans_maze[mouse_x][mouse_y + 1] == 0)
					//������ ���� �շ�����...
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
					//���� ���� �ݷ�����...
				{
					ans_maze[mouse_x][mouse_y] = 2;
					path_maze[mouse_x][mouse_y] = 2;
					path.push(cur);
					--mouse_y;
					cur.x = mouse_x;
					cur.y = mouse_y;
					cur.visit = 1;
				}

				// ���� �ִ� ����� if�� �� �ϳ��� ����ϹǷ� '��ĭ �����̱�' ��.
				++wasted_energy;
				moveCount++;
				mana_energy+=0.1;//
				//printf("����:%.1f\n",mana_energy);
				if((mana_energy>=1)){
					mana_energy= mana_energy-1;
					//printf("��ĵ �ߵ�!!\n");
					scan(maze, row, col);
				}

				Print(path_maze, row, col); //��� ����ϴ� �Լ�
				//Sleep(200);
			}
			else //���� ���� �� ����.
			{
				//r = rand() % 4 + 1; //1���� 4���� ���� �߻�.
				/*************/
				int root_check[4] = { 0 };
				if (ans_maze[mouse_x + 1][mouse_y] == 0) root_check[0] = 1; //�Ʒ��� ���� �ִ�
				if (ans_maze[mouse_x - 1][mouse_y] == 0) root_check[1] = 1; //���� ���� �ִ�.
				if (ans_maze[mouse_x][mouse_y + 1] == 0) root_check[2] = 1; //������ ���� �ִ�.
				if (ans_maze[mouse_x][mouse_y - 1] == 0) root_check[3] = 1; //���� ���� �ִ�.
				//root_check �ε��� ������ ����ϸ� -> [�Ʒ�][��][������][����]
				//                              [0]   [1]   [2]    [3] 
				/*��ǻ� ���⼭ ���� ���� �˰���*/
				//4�����ִ°��
				if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) {
					//��, ��, ��, �� �� ���� ������ ���
					r = rand() % 4 + 1; 
				}
				//3���ִ°�� r=1,2,3�� �ϳ�
				//1,2,3���� �ִ°��
				else if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) {
					r = rand() % 3 + 1; 
				}
				//1,2,4���� �ִ°�� r=1,2,4 �� �ϳ�
				else if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) {
					r = rand() % 4 + 1;
					while(r==3){
						r = rand() % 4 + 1;
						if(r!=3) break;
					}  
				}
				//1,3,4���� �ִ°�� r=1,3,4 �� �ϳ�
				else if (root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) {
					r = rand() % 4 + 1;
					while(r==2){
						r = rand() % 4 + 1;
						if(r!=2) break;
					}  
				}
				//2,3,4���� �ִ°��
				else if (root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) {
					r = rand() % 3 + 2;
				}

				//2�� �ִ°��
				//1,2���� �ִ°��
				else if (root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) {
					r = rand() % 2 + 1;
				}
				//1,3���� �ִ°��
				else if (root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) {
					r= rand()%3 +1;
					while(r==2){
						r = rand() % 3 + 1;
						if(r!=2) break;
					}
				}
				//1,4���� �ִ°��
				else if (root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) {
					r = rand()%4 +1;
					while(r==2||r==3){
						r = rand()%4 +1;
						if(r!=2 && r!=3) break;

					}
				}
				//2,3���� �ִ°��
				else if (root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) {
					r = rand()%2 +2;
				}
				//2,4���� �ִ°��
				else if (root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) {
					r = rand()%4 +1;
					while(r==1||r==3){
						r = rand()%4 +1;
						if(r!=1 && r!=3) break;

					}
				}
				//3,4���� �ִ°��
				else if (root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) {
					r = rand()%2 + 3;

				}

				Print(path_maze, row, col);
				//Sleep(200);
				//printf("�������");

				/**************/
				//����ã�� ���
				if (r == 1) 
					//r=1�̸�..
				{
					if (ans_maze[mouse_x + 1][mouse_y] == 0)
						//�Ʒ��� �̵��϶�.
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
					//r=2�̸�..
				{
					if (ans_maze[mouse_x - 1][mouse_y] == 0)
						//���� �̵� �϶�..
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
				//printf("����:%.1f\n",mana_energy);
				if((mana_energy>=1)){
					mana_energy= mana_energy-1;
					//printf("��ĵ �ߵ�!!\n");


					scan(maze, row, col);
				}
				Print(path_maze, row, col);
				//Sleep(200);

				//printf("�������");
			}
			if(exitP.x !=100 && exitP.y != 100){
				getchar();
				printf("\n�ⱸ ã�Ƽ� ���� (%d, %d)\n", exitP.x, exitP.y);
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
		//���⼭ ���� ����
		else{
			int temp_x = exitP.x - mouse_x;	//�����濡�� ���ΰ��� �Ǻ�����
			int temp_y = exitP.y - mouse_y;
			fork_check = 0;

			////������ ���� �ƿ� ������... ����...
			//if(mouse_x == 0 && mouse_y == 1)
			//{
			//	not_exist_road = 1;
			//	break;
			//}

			//�ⱸ�� ã���� ����.
			if(mouse_x == exitP.x && mouse_y == exitP.y)
			{
				path_maze[mouse_x][mouse_y] = 8;
				path.push(cur);
				energy_zero_check = 0;
				exit_check = 0;
				Print(path_maze, row, col);
				break;
			}

			//�Ա��ο�
			if(mouse_x == 0 && mouse_y == 1)
			{
				path.push(cur);
				energy_zero_check = 0;
				exit_check = 1;
				printf("�㰡 �Ա��οͼ� ����˴ϴ�.");
				break;
			}

			//�ⱸ�� ã�� ���� �������� ��� �ҽǵǸ� ��.
			if(energy - wasted_energy == 0)
			{
				path.push(cur);
				energy_zero_check = 1;

				break;
			}



			fork_check = investigation(ans_maze, mouse_x, mouse_y); //������ üũ.

			if(fork_check == 0) //���� �ƿ� ����.
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
			else if(fork_check == 1) //���� �ϳ� ����.//���� x
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
			else //���� ���� �� ����.
			{
				int root_check[4] = {0};
				//���� �����ϴ��� Ȯ��
				if(ans_maze[mouse_x + 1][mouse_y] == 0) root_check[0] = 1;	
				if(ans_maze[mouse_x - 1][mouse_y] == 0) root_check[1] = 1;	
				if(ans_maze[mouse_x][mouse_y + 1] == 0) root_check[2] = 1;	
				if(ans_maze[mouse_x][mouse_y - 1] == 0) root_check[3] = 1;
				//1��
				if(temp_x < 0 && temp_y < 0)
				{
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 2;
					//	}
					//	else
					//		r = 4;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 1;
					}
					//1,2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 4;
					}
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}
					//2,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 4;	
					}

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 1;	
					}
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 3;
						}
						else
							r = 1;
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;				
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 4;
					}
					//3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}			
				}

				//2��
				else if(temp_x < 0 && temp_y ==0)
				{
					////4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 2;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//1,2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;
					}
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else
							r = 3;
					}
					//2,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 2;
					}

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						r = 2;
					}
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(mouse_y > (col * 1/2)){
							r = 1;
						}
						else
							r = 3;
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;	
					}
					//3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else
							r = 3;
					}				
				}
				//3��
				else if(temp_x < 0 && temp_y > 0)
				{
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 2;
					//	}
					//	else
					//		r = 3;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 3;
					}
					//1,2,4�� ���� �����ϴ� ���
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
					//1,3,4�� ���� �����ϴ� ���
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
					//2,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 3;
					}

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
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
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 3;
						}
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 4;
						}
						else{
							r = 1;
						}
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 2;
						}
						else
							r = 3;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;	
					}
					//3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}	
				}
				//4��
				else if(temp_x == 0 && temp_y < 0){
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 4;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}
					//2,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 2;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 4;
					}	
				}

				//case 5

				else if(temp_x == 0 && temp_y > 0){
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 3;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//1,2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}
					//2,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						if(mouse_x > (row * 1/2))
							r = 2;
						else
							r = 1;
					}
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 2;	
					}
					//3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 3;
					}	
				}
				//case6
				else if(temp_x > 0 && temp_y < 0){
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 1;
					//	}
					//	else
					//		r = 4;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
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
					//1,2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 4;
						}
					}
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 4;
						}
					}
					//2,3,4�� ���� �����ϴ� ���
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

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
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
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else{
							r = 4;
						}
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 3;
						}
						else
							r = 2;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;
					}
					//3,4�� ���� �����ϴ� ���
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
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	r = 1;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(mouse_y > (col * 1/2)){
							r = 4;
						}
						else{
							r = 3;
						}
					}

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 0) 
					{
						r = 1;
					}
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 1;	
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;	
					}
					//3,4�� ���� �����ϴ� ���
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
					//4���� ���� �����ϴ� ���
					//if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 1)
					//{						
					//	if(abs(temp_x) > abs(temp_y)){
					//		r = 1;
					//	}
					//	else
					//		r = 3;
					//}

					////3���� �����ϴ� ���
					////1,2,3�� ���� �����ϴ� ���
					//else 
					if(root_check[0] == 1 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else
							r = 3;
					}
					//1,2,4�� ���� �����ϴ� ���
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
					//1,3,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 1) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else
							r = 3;
					}
					//2,3,4�� ���� �����ϴ� ���
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

					//2���� ���� �����ϴ� ���
					//1,2�� ���� �����ϴ� ���
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
					//1,3�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 1 && root_check[3] == 0) 
					{
						if(abs(temp_x) > abs(temp_y)){
							r = 1;
						}
						else
							r = 3;
					}
					//1,4�� ���� �����ϴ� ���
					else if(root_check[0] == 1 && root_check[1] == 0 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 1;
					}
					//2,3�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 1 && root_check[3] == 0) 
					{
						r = 3;
					}
					//2,4�� ���� �����ϴ� ���
					else if(root_check[0] == 0 && root_check[1] == 1 && root_check[2] == 0 && root_check[3] == 1) 
					{
						r = 4;	
					}
					//3,4�� ���� �����ϴ� ���
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

	if (energy_zero_check == 1) //�������� ������ ��.
	{	
		printf("\n�������� �����Ͽ� �ⱸ�� ã�� ���߽��ϴ�.\n");
	}
	else //�������� ���� ������...
	{
		if (exit_check == 1)
		{
			printf("�ⱸ�� ã�� ���߽��ϴ�.\n");
			fprintf(ofp, "�ⱸ�� ã�� ���߽��ϴ�.\n");

			printf("���� ������ : %d\n",energy);
			fprintf(ofp, "���� ������ : %d\n", energy);

			printf("�Һ� ������ : %d\n",wasted_energy);
			fprintf(ofp, "�Һ� ������ : %d\n", wasted_energy);

			printf("���� ������ : %d\n", energy - wasted_energy);
			fprintf(ofp, "���� ������ : %d\n", energy - wasted_energy);
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
			
			printf("�ⱸ�� ã�ҽ��ϴ�!!!\n");
			fprintf(ofp, "�ⱸ�� ã�ҽ��ϴ�!!!\n");

			printf("���� ������ : %d\n",energy);
			fprintf(ofp, "���� ������ : %d\n", energy);

			printf("�Һ� ������ : %d\n",wasted_energy);
			fprintf(ofp, "�Һ� ������ : %d\n", wasted_energy);

			printf("���� ������ : %d\n", energy - wasted_energy);
			fprintf(ofp, "���� ������ : %d\n", energy - wasted_energy);
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