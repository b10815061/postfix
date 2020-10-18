#include <iostream>

using namespace std;

bool handle_input(char* expression, int& i) {
	//handle input
		//read the input


	cin.getline(expression, 70);

	int parentphrase_flag = 0;
	// parentphrase
	 // "(" appers -> set to 1 , if its 0 , ")" shouldn't apper.
	for (; expression[i] != '\0'; i++)
	{
		//operator -> 1. operands first
		if ((expression[0]<'0' || expression[0]>'9') && expression[0] != '(') {
			cout << "invalid";
			return 0;
		}
		//operator -> 2. no operator sires
		if (i > 0) {
			if ((expression[i]<'0' || expression[i]>'9') && (expression[i] != '(')) {
				if ((expression[i - 1]<'0' || expression[i - 1]>'9') && (expression[i - 1] != ')')) {
					cout << "invalid";
					return 0;
				}
			}
		}
		if (expression[i] == '(') {
			parentphrase_flag++;
		}
		if (expression[i] == ')') {
			parentphrase_flag--;
		}
	}
	//operator -> 3. oprands last
	if ((expression[i - 1]<'0' || expression[i - 1]>'9') && expression[i - 1] != ')') {
		cout << "invalid";
		return 0;
	}

	if (parentphrase_flag !=0) {
		cout << "invalid";
		return 0;
	}
	return 1;
}



class member {
public:
	int precedence;
	char data;
};

class stack {
public:
	stack(int i) {
		length = i;
		mem = new member[length * sizeof(member)];
	};
	member* mem;
	int length;
	void push(char value) {
		if (rear + 1 > length) {
			cout << "stack overflow.";
			return;
		}
		else {
			rear++;
			mem[rear].data = value;
			if (value == '*') {
				mem[rear].precedence = 2;
			}
			else if (value == '+' || value == '-') {
				mem[rear].precedence = 3;
			}

		}
	};
	int pop(bool post=0) {
		if (rear < 0) {
			cout << "stack underflow.";
			return 0;
		}
		else {

			
			if (post) {
				int exponatial = 1;
				int result = 0;
				bool neg_flag = 0;
				rear--;
				do {
					if (mem[rear].data == '-') {
						neg_flag = 1;
						rear--;
					}
					else {
						result += (mem[rear].data - '0') * exponatial;
						mem[rear].data = '\0';
						rear--;
						exponatial *= 10;
					}
				} while (mem[rear].data != '\0'&&rear>=0);
				if (neg_flag) {
					return -result;
				}
				return result;
				
			}
			mem[rear].data = '\0';
			rear--;
			return 0;
		}
	};
	void End_Of_If() {
		while (rear >= 0) {
			pop();
		}
	};

	member current() {
		return mem[rear];
	}

	int c_rear() {
		return rear;
	}
	int rear = -1;
};




int main() {

	char* expression;
	int exp_length = 0;
	expression = (char*)calloc('A', 70 * sizeof(char));
	int flag = handle_input(expression, exp_length);
	if (!flag) {
		return 0;
	}
	// to prefix
	char* pre = (char*)malloc((exp_length + 1) * sizeof(char));
	char* post = (char*)calloc('A', (exp_length + 1) * sizeof(char));
	int postcount = 0;
	for (int i = 0; i <= exp_length + 1; i++)
	{
		pre[i] = expression[i];
	}
	//free(expression);
	pre[exp_length] = ')';
	stack a(exp_length);
	a.push('(');
	for (int i = 0; i < exp_length + 1; i++)
	{
		if (pre[i] == '(') {
			a.push('(');
		}

		else if (pre[i] == ')') {
			while (a.current().data != '(') {
				post[postcount] = a.current().data;
				postcount += 2;
				a.pop();

			}
			a.pop(); // discard '('
		}
		else if (pre[i] == '+' || pre[i] == '-' || pre[i] == '*') {
			int precedence = 0;
			if (pre[i] == '*') {
				precedence = 2;
			}
			else if (pre[i] == '+' || pre[i] == '-') {
				precedence = 3;
			}
			while (a.current().precedence <= precedence&&a.current().data!='(') {
				post[postcount] = a.current().data;
				postcount += 2;
				a.pop();

			}
			a.push(pre[i]);
		}
		else {
			post[postcount] = pre[i];
			if (pre[i + 1] < '0' || pre[i + 1] > '9') {
				postcount += 2;
			}
			else {
				postcount++;
			}
		}
	}
	while (a.rear >= 0) {
		post[postcount] = a.current().data;
		postcount++;
		a.pop();

	}

	for (int i = 0; i < postcount-1; i++)
	{
		if (post[i] == '\0') {
			cout << ' ';
		}
		else {
			cout << post[i];
		}
	}
	cout << '\n';
	//calculate
	int solution = 0;
	int opp1 = 0;
	int opp2 = 0;
	bool first = 1;
	post[postcount] = ')';
	stack b(postcount);
	for (int i = 0; post[i]!=')'; i++)
	{
		if (post[i] >= '0' && post[i] <= '9') {
			b.push(post[i]);
		}
		else if (post[i] == '\0') {
			b.push('\0');
		}
		else {
			opp1 = b.pop(1);
			opp2 = b.pop(1);
			stack c(10);
			int result ;
			int count = 0;
			bool neg_flag = 0;
			switch (post[i]) {
			case '+':
				
				result = opp2 + opp1;
				if (result < 0) {
					neg_flag = 1;
					result = -result;
				}
				if (result == 0) {
					b.push('0');
				}
				while (result > 0) {

					c.push(result % 10 + '0');
					c.push('\0');
					result /= 10;
					count++;
				}
				if (neg_flag) {
					b.push('-');
				}
				for (int g = 0; g < count; g++)
				{
					b.push(c.pop(1) + '0');
				}
				break;
			case '-':
				result = opp2 - opp1;
				if (result < 0) {
					neg_flag = 1;
					result = -result;
				}
				if (result == 0) {
					b.push('0');
				}
				while (result > 0) {

					c.push(result % 10+'0');
					c.push('\0');
					result /= 10;
					count++;
				}
				if (neg_flag) {
					b.push('-');
				}
				for (int g = 0; g < count; g++)
				{
					b.push(c.pop(1)+'0');
				}
				
				break;
			case '*':
				result = opp2 * opp1;
				if (result < 0) {
					neg_flag = 1;
					result = -result;
				}
				if (result == 0) {
					b.push('0');
				}
				while (result > 0) {

					c.push(result % 10 + '0');
					c.push('\0');
					result /= 10;
					count++;
				}
				if (neg_flag) {
					b.push('-');
				}
				for (int g = 0; g < count; g++)
				{
					b.push(c.pop(1) + '0');
				}
				break;
			}
			
			
		}
	
	}
	solution = b.pop(1);
	cout << solution <<'\n'; 
}