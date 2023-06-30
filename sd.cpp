#define _CRT_SECURE_NO_WARNINGS
#include"mydefine.h"
namespace DEAL {
	int col_count[9][10] = { 0 }, row_count[9][10] = { 0 }, block_count[9][10] = { 0 };
	BLFS bs[100];
	int map[9][9];
	//Ϊ�˷�ֹȫ�ֱ������ң�ʹ�������ʿռ�
}

namespace STORE {
	char store[300000000] = { 0 };
	long count = 0;
}
char out[9][9];

int getBlockNum(int x, int y) {
	//��ÿո�����һ��Ź���ĵģ����㿪ʼ����
	if (x < 0 || y < 0 || x >= 9 || y>8) return -1;
	return ((x / 3) * 3 + (y / 3));
}


bool cmp(BLFS& a, BLFS& b) {
	return a.count > b.count;
}

int produceOutputIntoTxt(int produce_num) {		//�������������������վ�
	int count = produce_num;
	int	trans_arr[9] = { 1,2,3,4,5,6,7,8,9 };	//��������������
	int cols[9] = { 0,1,2,3,4,5,6,7,8 };	//������������
	int sub;		//һ���м�ֵ��������õ�
	string table[9] = {			//����ģ��
		"912345678",
		"678912345",
		"345678912",
		"123456789",
		"789123456",
		"456789123",
		"891234567",
		"567891234",
		"234567891"
	};
	if (count <= 0 || count > 1000000) {
		cout << "please input N which>0 and <=1000000" << endl;
		return -1;
	}
	remove("./shudoku_finality.txt");
	FILE* fp = fopen("./shudoku_finality.txt", "wt");
	if (fp == NULL) {
		cout << "err" << endl;
		return -1;
	}
	STORE::count = 0;
	memset(STORE::store, 0, sizeof(STORE::store));
	do {//ǰ���еĽ���
		do {//�������н���
			do {//�������еĽ���
				do {//ǰ�˸����ֵĽ���
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							sub = (int)(table[cols[i]][j] - '0') - 1;
							//�����ɵ������վֱ����ڴ������У��ռ任ʱ��
							STORE::store[STORE::count++] = trans_arr[sub] + '0';
							if (j == 8)STORE::store[STORE::count++] = '\n';
							else STORE::store[STORE::count++] = ' ';
						}
					}
					STORE::store[STORE::count++] = '\n';
					count--;
					if (count <= 0) {
						//���ɽ�������ʼ��������һ��д���ļ�
						fwrite(STORE::store, sizeof(char), STORE::count, fp);
						cout << "over create finality" << endl;
						fclose(fp);
						return 0;
					}
				} while (next_permutation(trans_arr, trans_arr + 8));
			} while (next_permutation(cols + 6, cols + 9));
		} while (next_permutation(cols + 3, cols + 6));
	} while (next_permutation(cols + 1, cols + 3));

	cout << "over or err" << endl;
	return 0;
}

int dealQuestion(char* path) {
	char shudu[1024];
	int x, y;
	int _col[9] = { 0 }, _row[9] = { 0 }, _block[9] = { 0 };
	//�ֱ���������Լ��Ź��������������֡�����block_count[1][7]=1����ڿ��Ѿ�����7�ˡ�
	using namespace DEAL;
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		cout << "error open file,please check the question file path" << endl;
		return -1;
	}
	int soku_num = 0;
	do {
		memset(shudu, 0, sizeof(shudu));
		if (fread(shudu, sizeof(char), 163 * sizeof(char), fp) < 162) {		//��������һ������������ַ�
			if (feof(fp)) break;//�ж��Ƿ��ļ�β
			else {		//������ֹ
				cout << "error read file" << endl;
				return -1;
			}
		};
		x = 0; y = 0;

		{			//������ʼ��һЩֵ
			memset(bs, 0, sizeof(bs));
			memset(_col, 0, sizeof(_col));
			memset(_block, 0, sizeof(_block));
			memset(_row, 0, sizeof(_row));
			memset(row_count, 0, sizeof(row_count));
			memset(col_count, 0, sizeof(col_count));
			memset(block_count, 0, sizeof(block_count));
		}

		for (int i = 0; i < 162; i++) {
			if (shudu[i] == ' ' || shudu[i] == '\n') continue;
			else {
				map[x][y] = int(shudu[i] - '0');
				if (y >= 8) {
					y = 0;
					x++;
				}
				else y++;
			}
		}
		//�������ļ�ת��Ϊint�ʹ洢
		int count_bs = 0;
		int sub_map;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (map[i][j] == 0) {
					bs[count_bs].x = i;
					bs[count_bs].y = j;
					count_bs++;
				}
				else {
					sub_map = map[i][j];
					setFlag(i, j, sub_map, 1);
					_row[i]++;
					_col[j]++;
					_block[getBlockNum(i, j)]++;
				}
			}
		}

		x = 0; y = 0;
		for (int i = 0; i < count_bs; i++) {
			x = bs[i].x; y = bs[i].y;
			bs[i].count = _row[x] + _col[y] + _block[getBlockNum(x, y)];
		}//��¼�հ׸���Χ�Ѿ�ռ�õĵ㣬ռ�õ�Խ���������������ȼ�Խ�ߣ�Խ������

		sort(bs, bs + count_bs, cmp);	//���򣬰�count�ߵ�ֵ�ŵ�ǰ��

		if (dfs(0, count_bs) == false) {
			printf("error dfs\n");
			cout << "sudoku error" << soku_num << endl;
			if (soku_num >= 100) {
				printf("too much error��please check the question file\n");
				return -1;
			}//����һ�ٸ�����ֱ�ӽ���
			soku_num++;
			continue;
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				STORE::store[STORE::count++] = char(map[i][j] + '0');
				if (j == 8)STORE::store[STORE::count++] = '\n';
				else STORE::store[STORE::count++] = ' ';
			}
		}
		STORE::store[STORE::count++] = '\n';
		//����������洢����������ռ任ʱ��
	} while (!feof(fp));
	FILE* wrfp = fopen("./shudoku.txt", "wt");
	fwrite(STORE::store, sizeof(char), STORE::count, wrfp);	//��������д���ļ�
	fclose(wrfp);
	fclose(fp);
	cout << "deal" << endl;
	return 0;
}

void setFlag(int x, int y, int i, int flag) {
	DEAL::col_count[y][i] = flag;
	DEAL::row_count[x][i] = flag;
	DEAL::block_count[getBlockNum(x, y)][i] = flag;
}

int dfs(int num, int size) {
	if (num == size) {
		return true;
	}
	else {
		int x = DEAL::bs[num].x, y = DEAL::bs[num].y;
		for (int i = 1; i <= 9; i++) {
			if (judge(x, y, i)) {
				DEAL::map[x][y] = i;
				setFlag(x, y, i, 1);
				if (dfs(num + 1, size)) return true;
				setFlag(x, y, i, 0);
				DEAL::map[x][y] = 0;
			}
		}
		return false;
	}
}

bool judge(int x, int y, int i) {
	return !DEAL::col_count[y][i] && !DEAL::row_count[x][i] && !DEAL::block_count[getBlockNum(x, y)][i];
}
