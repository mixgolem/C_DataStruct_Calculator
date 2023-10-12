#define _CRT_SECURE_NO_WARNINGS	//Visual C���� fopen�Լ� ��� �� ���� ������ ������� �ʱ� ���� ���. Linux, OS X������ �������� �ʾƵ� �ȴ�.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//���� ��� �Լ�
void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}



//���Ḯ��Ʋ �̿��� ����
typedef double Element;
typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
} Node;
Node* top = NULL;
//������ ����ִ��� Ȯ���ϴ� �Լ�
int is_empty() { return top == NULL; }
//���� �ʱ�ȭ �Լ�
void init_stack() { top = NULL; }
//���� ���� ����� ������ ��ȯ�ϴ� �Լ�
int size() {
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link) count++;
	return count;
}
//���� ���� ����
void push(Element e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->link = top;
	top = p;
}
//���� ��������
Element pop() {
	Node* p;
	Element e;
	if (is_empty())
		error("���� ���� ����");
	p = top;
	top = p->link;
	e = p->data;
	free(p);
	return e;
}
//���� peek����
Element peek() {
	if (is_empty())
		error("���� ���� ����");
	return top->data;
}

/*���ڿ��� �����ϱ� ���� ������ ���Ḯ��Ʈ�� �̿��� ����2
������ ���� ����� �����ϸ� ��� �ȿ� ���ڿ��� ������ �� �ְ� �Ͽ���*/
typedef struct LinkedNode2 {
	char* str;
	struct LinkedNode2* link2;
}Node2;
Node2* top2 = NULL;
int is_emptystr() { return top2 == NULL; }
void init_stackstr() { top2 = NULL; }
void pushstr(char* expr) {
	Node2* p = (Node2*)malloc(sizeof(Node2));
	p->str = expr;
	p->link2 = top2;
	top2 = p;
}
char* popstr() {
	Node2* p;
	char* str;
	if (is_emptystr())
		error("���� ���� ����");
	p = top2;
	top2 = p->link2;
	str = p->str;
	free(p);
	return str;
}





//���Ḯ��Ʈ�� �̿��� ť�� ����
typedef char* Element_queue;
typedef struct LinkedNode_queue {
	Element_queue data;
	struct LinkedNode_queue* link3;
} Node_queue;
//front�� rear�� ����
Node_queue* front = NULL, * rear = NULL;
//ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty_queue() { return front == NULL; }
//ť�� �ʱ�ȭ�ϴ� �Լ�
void init_queue() { front = rear = NULL; }
//ť ���� ����� ������ ��ȯ�ϴ� �Լ�
int size_queue() {
	Node_queue* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link3) count++;
	return count;
}
//ť ���� ����
void enqueue(Element_queue e) {
	Node_queue* p = (Node_queue*)malloc(sizeof(Node_queue));
	p->data = e;
	p->link3 = NULL;

	if (is_empty_queue()) front = rear = p;
	else {
		rear->link3 = p;
		rear = p;
	}
}
//ť ���� ����
Element_queue dequeue() {
	Node_queue* p;
	Element_queue e;
	if (is_empty_queue())
		error("ť ���� ����");
	p = front;
	front = front->link3;
	if (front == NULL) rear = NULL;
	e = p->data;
	free(p);
	return e;
}
//ť peek ����
Element_queue peek_queue() {
	if (is_empty_queue())
		error("ť ���� ����");
	return front->data;
}





/*��ȣ �˻� �Լ�
	���� 1 : ���� ��ȣ�� ������ ������ ��ȣ�� ������ ���ƾ� ��
	���� 2 : ���� ��ȣ�� ���ʿ��� ���� ���;� ��
	���� 3 : ���� �ٸ� Ÿ���� ��ȣ�� ¦�� �̷�� �ȵ�
��ȣ�� ������ ���� ��� 0�� ��ȯ
��ȣ�� ������ �ִ� ��� 1, 2, 3 ��ȯ*/
int check_matching(char expr[]) {
	int i = 0, prev;
	char ch;	//���ڿ��� �ϳ��� ���� �� ���ڸ� �����ϴ� ����

	init_stack();
	while (expr[i] != '\0') {
		ch = expr[i++];	//���ڿ��� index i ���� �о���̰�, i+1�� ����
		if (ch == '[' || ch == '{' || ch == '(')
			push(ch);	//�о���� ���ڰ� ���� ��ȣ�� ��� ���ÿ� �о���� ���� ��ȣ�� push
		else if (ch == ']' || ch == '}' || ch == ')') {
			if (is_empty())
				return 2;	//���� 2 ���� : ������ ��ȣ�� ���� ��ȣ���� ���� ����
			prev = pop();	//������ ������� ���� ���¿��� top�� �ִ� ��ȣ�� ������ prev�� ����
			if ((ch == ']' && prev != '[') || (ch == '}' && prev != '{') || (ch == ')' && prev != '(')) {
				return 3;			//���ڿ��� �дٰ� ch�� ����� ������ ��ȣ��, ���ÿ��� pop�� prev�� ���� ��ȣ�� ���� ���� ��� ���� 3 ���� : ��ȣ�� ���� ���� ����
			}
		}
	}
	if (is_empty() == 0) return 1;	//���� 1 ���� : ������ ������� �ʴ� ��� �°�ȣ�� ���ȣ�� ������ ���� �ʴ�
	return 0;	//�� ���ǿ� �ɸ��� ������ ������ ��ȣ�� ������ ������ �˸��� 0 ��ȯ
}

//�������� �켱������ ���ϴ� �Լ�. �켱������ ���� ���� ���ڰ� ũ��.
int precedence(char op) {
	switch (op) {
	case '(':case')':return 0;
	case '+':case'-':return 1;
	case '*':case'/':return 2;
	}
	return -1;
}

/*���� ǥ�� ������ ���� ǥ�� �������� ��ȯ�ϴ� �Լ�
�� �ڸ��� ���ڰ� �ƴϱ� ������ �Ǽ��� �Ǽ�, �Ǽ��� �����ڸ� ������ �� �ֵ��� ������ ���̿� ������ �߰��� �����Ѵ�.*/

void infix_to_postfix(char* expr, char* postexpr) {
	init_stack();
	while (*expr != '\0') {	//���ڿ��� ���� ������ �� ���� �ݺ�

		if (*expr >= '0' && *expr <= '9') {	//���ǹ� : �Ǽ��� �б� ���� ���ǹ�. ���ڳ� ���� ������ ���
			do {
				*postexpr++ = *expr++;	//postexpr�� expr�� ���� �����ϰ� ���� �����Ͱ� ����Ű�� ��ġ 1 �����ϸ� ���� ���ڸ� ��� ���� �� �ִ�
			} while ((*expr >= '0' && *expr <= '9') || *expr == '.');	//do-while���� �̿��� ��� postexpr�� �����Ѵ�
			*postexpr++ = ' ';	//�Ǽ��� �� ������ postexpr�� ������ �߰�
		}

		else if (*expr == '(') {	//���ǹ� : �°�ȣ�� ������ ���
			push(*expr++);	//�켱 ���ÿ� �����ϰ� expr�� ��ġ ����
		}

		else if (*expr == ')') {	//���ǹ� : ���ȣ�� ������ ���
			while (peek() != '(') {	//�°�ȣ�� ������ �� ����(�ݺ��� �ȿ��� pop�� �ϱ� ������ peek�� ����ص� ���� �ݺ����� �ʴ´�)
				*postexpr++ = pop();	//���ÿ� ����� �����ڸ� pop �ؼ� postexpr�� �����Ѵ�
				*postexpr++ = ' ';	//�����ڸ� pop �ϸ鼭 ������ ���̿� ������ �߰�
			}
			pop();	//�°�ȣ�� ���ÿ��� pop�Ѵ�
			expr++;	//��ȣ ���� �����ڸ� �� ������ ��� expr ��ġ ����
		}

		else if (*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/') {	//���ǹ� : �����ڸ� ������ ���
			while (!is_empty() && (precedence(*expr) <= precedence(peek()))) {	//������ ������� �ʰ�, expr�� �����ڰ� ���ÿ� ����� �����ں��� �켱������ ���� ���
				*postexpr++ = pop();	//���ÿ� ����Ǿ��ִ� �����ڰ� �켱������ ������ pop �ؼ� postexpr�� ���� 
				*postexpr++ = ' ';	//�� ������ ���̿� ������ �߰�
			}
			push(*expr);	//�� ������ ������ expr�� �����ڸ� ���ÿ� �߰��Ѵ�.
			expr++;	//��� �۾��� ������ expr 1 ����
		}

		else expr++; //�Ǽ�, ��ȣ, �����ڿ� ������ ���� ���� ��� �����ϰ� expr ��ġ 1 �������� ���� ���ڸ� �д´�.
	}

	while (!is_empty()) {	//���������� ���ÿ� �����ִ� �����ڵ��� pop�Ͽ� postexpr�� �߰��ϸ� ��
		*postexpr++ = pop();
		*postexpr++ = ' ';	//�� ������ ���̿� ���� �߰�
	}

	postexpr--;
	*postexpr == '\0';	//������ �����ڱ��� ��� ����ϰ� �Ǹ� ������ ���� ������ ���� �Ǵµ�, �̸� NULL�� �ٲ��ش�
}





/*���� ǥ�� ���� �Ի� �Լ�*/
double calc_postfix(char expr[]) {
	double val, val1, val2;
	int i = 0;	//expr�� ��ĵ�ϱ� ���� ����
	int j = 0;	//buffer�� ���ڸ� �Է��ϱ� ���� ����
	char buffer[100] = { '0', };	//�Ǽ��� �Է¹��� buffer, ��� ���ڸ� NULL�� �ƴ� '0'���� �ʱ�ȭ
	char c; //expr�� �� ���ھ� ��ĵ�� �� ����ϴ� ����

	init_stack();
	while (expr[i] != '\0') {	//expr�� ���� ������ �� ���� �ݺ�
		c = expr[i++];	//�켱 �� ���ھ� c�� �����Ѵ�

		if ((c >= '0' && c <= '9') || c == '.') { buffer[j++] = c; }	//���� c�� 0�� 9 ������ �����̰ų� ���� ��� �켱 ���ۿ� �����Ѵ�
		else if (c == ' ' && (expr[i - 2] >= '0' && expr[i - 2] <= '9')) {	//���� c�� �����̸� �� ������ ���ڰ� ���ڷ� ������ ����? �� �Ǽ��� ��ĵ�� �����ٴ°��� �ǹ��Ѵ�
			val = atof(buffer);	//������ ������ atof()�Լ��� �̿��� double�� ������ val�� ����
			push(val); //val�� ���ÿ� ����
			j = 0;
			memset(buffer, 0, strlen(buffer) * sizeof(char));	//���۸� ���� ����ϱ� ���� j�� 0���� �ٲٰ� memset()�Լ��� ������ ��� ������ 0���� �ʱ�ȭ
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {	//�����ڸ� ������ ��� pop 2ȸ �����ؼ� ����� ���� ���ÿ� ����
			val2 = pop();	//���� ���ÿ��� ���� ���� �ڷ� �����Ѵ�
			val1 = pop();
			switch (c) {
			case '+':push(val1 + val2); break;
			case '-':push(val1 - val2); break;
			case '*':push(val1 * val2); break;
			case '/':push(val1 / val2); break;
			}
		}
		else continue;	//�� ������ �������� ������ �ݺ����� ����Ͽ� ���� ���ڸ� ����
	}
	return pop();	//��� �ݺ��� ������ ���ÿ��� ���� ��� ����� �����ִµ�, �̸� pop�ؼ� ��� ����� ��ȯ
}



//main�Լ� ����. argument�� �Է¹޾� argv[2]=0�̸� ť�� ����� ������ ����, argv[2]=1�̸� ������ ����� ������ ����
int main(int argc, char* argv[]) {
	FILE* fp = NULL;	//���� ������ ����
	int check;	//argv[2] �� �����ϱ� ���� ����
	int i;
	char** equation_f = NULL, ** input_equation = NULL; //�Է¹��� ������ ������ �� ���� char���������� ����
	int count = 0;	//���ڿ��� �� ������ ���� ���� �Լ�

	if (argc != 3)	error("exec equation check(0 or 1)");	//argument count�� 3�� �ƴ� ���� ��ɾ �߸� �Էµ� ����̴�

	fp = fopen(argv[1], "rt");	//argument value�� �� ��°�� �Է¹��� ���� ��θ� �ؽ�Ʈ �б� ���� ����
	check = atoi(argv[2]);	//argument value�� �� ��°�� �Է¹��� ������ atoi()�Լ��� ����� ������ ��ȯ �� check�� ����

	//�Ʒ��� ���� �����͸� �����Ҵ��ϴ� �����̴�. �迭�� ������ �ʱ�ȭ�ϱ� ���� calloc()�Լ��� ����Ͽ��� 
	equation_f = (char**)calloc(sizeof(char*) * 10, sizeof(char*));
	for (i = 0; i < 10; i++)
		equation_f[i] = (char*)calloc(sizeof(char) * 256, sizeof(char));

	input_equation = (char**)calloc(sizeof(char*) * 10, sizeof(char*));
	for (i = 0; i < 10; i++)
		input_equation[i] = (char*)calloc(sizeof(char) * 256, sizeof(char));

	//���� ��ΰ� �߸��Ǿ��� ���
	if (fp == NULL)
		error("fopen is failed");

	if (check == 0) {	//0�� �ɼ��� ��� ť�� �̿��� ���� ����
		printf("calculator using queue\n");

		for (i = 0; fgets(input_equation[i], 256, fp) != NULL; i++) {	//txt���Ϸκ��� ���� �ƴ� �� ���� ���ڿ��� �� �پ� �Է¹���
			if (check_matching(input_equation[i]) != 0)	//���� ���� ��ȣ�˻縦 �����Ѵ�
				error("��ȣ �˻� ����");
			enqueue(input_equation[i]);	//������� ���ڿ��� ť�� �����ϰ�, �� ���� �Է¹޾Ҵ��� count
			count++;
		}
		for (i = 0; i < count; i++) {
			infix_to_postfix(dequeue(), equation_f[i]);	//dequeue_str()�Լ��� �� �پ� ���� ��� �� ����� ����Ѵ�.
			
			printf("Result = %lf\n", calc_postfix(equation_f[i]));
		}
	}

	else if (check == 1) {	//1�� �ɼ��� ��� ������ �̿��� ���� ����
		printf("calculator using stack\n");

		for (i = 0; fgets(input_equation[i], 256, fp) != NULL; i++) {	//txt���Ϸκ��� ���� �ƴ� �� ���� ���ڿ��� �� �پ� �Է¹���
			if (check_matching(input_equation[i]) != 0)	//���� ���� ��ȣ�˻縦 �����Ѵ�
				error("��ȣ �˻� ����");
			pushstr(input_equation[i]);	//������� ���ڿ��� ���ÿ� �����ϰ�, �� ���� �Է¹޾Ҵ��� count
			count++;
		}
		for (i = 0; i < count; i++) {
			infix_to_postfix(popstr(), equation_f[i]);	//popstr()�Լ��� �� �پ� ���� ��� �� ����� ����Ѵ�.
			printf("Result = %lf\n", calc_postfix(equation_f[i]));
		}
	}

	//�Ҵ�� �޸𸮸� ��� �����ϰ� ������ ������ �ݴ´�
	for (i = 0; i < 10; i++)
		free(equation_f[i]);
	free(equation_f);
	for (i = 0; i < 10; i++)
		free(input_equation[i]);
	free(input_equation);
	fclose(fp);

	return 0;
}