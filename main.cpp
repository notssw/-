#include"mydefine.h"
int main(int argc, char** argv) {
	if (argc == 1) {	//δ���������в�������������
		cout << "please input command in cmd line" << endl;
		return 0;
	}
	else {
		if (!strcmp(argv[1], "-c")) {
			int produce_num = atoi(argv[2]);
			//���޷�ת���������ڷǷ�����
			if (produce_num != 0) {
				int produce_num = atoi(argv[2]);
				if (produceOutputIntoTxt(produce_num) == -1) {
					cout << "�վ�����ʧ��" << endl;
					return -1;
				}
			}
			else {
				cout << "please input number after -c" << endl;
				return 0;
			}
		}
		else if (!strcmp(argv[1], "-s")) {
			if (dealQuestion(argv[2]) == -1) {
				cout << "error deal shudoku question" << endl;
				return -1;
			}
		}
		else {	//�������룬����
			cout << "input cmd error!" << endl;
			return 0;
		}
	}
}
