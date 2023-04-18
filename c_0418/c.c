#include<stdio.h>
typedef struct {
	/**스택*/
	char* stack_c;
	int top;
	int capacity;
}stack_struct;

int is_empty(stack_struct* s) {
	return (s->top == -1);
}
int is_full(stack_struct* s) {
	return (s->top == (s->capacity - 1));
}
void push(stack_struct* s, char item) {
	if (is_full(s)) {
		s->capacity++;
		s->stack_c = realloc(s->stack_c, s->capacity * sizeof(char));
		if (s->stack_c == NULL) {
			fprintf(stderr, "NULL.\n");
		}
	}
	s->stack_c[++s->top] = item;
}
char pop(stack_struct* s) {
	if (is_empty(s)) {
		fprintf(stderr, "poppop pop을 원해.\n");
		exit(1);
	}
	else return s->stack_c[s->top--];
}
void in(stack_struct* s) {
	s->stack_c = malloc(s->capacity * sizeof(char));
	s->capacity = 0;
	s->top = -1;
}
int main(void) {
	int boolean = 1;
	while (boolean) {
		stack_struct s;
		in(&s);
		int number = 30;
		char* string = malloc(number * sizeof(char));
		
		printf("문자열을 입력하시오 : ");
		//scanf_s("%s", string,number);
		fgets(string, number, stdin);
		//fflush(stdin);
	
		for (int i = 0; ; i++) {
			char c = string[i];
			if (string[i] == '\n') break;

			switch (c) {
			case '\'':	case '\"':	case ' ':	case ',':	case '.': 
				continue;
			}
			c = tolower(c);
			push(&s, c);
		}
		stack_struct s2;
		in(&s2);
		for (int i = 0; i < s.capacity / 2; i++) {
			char c2 = pop(&s);
			push(&s2, c2);
		}
		for (int i = 0;; i++) {
			if (i == 0 && s.capacity % 2 != 0) pop(&s);

			if (s.top == -1) {
				printf("회문입니다.");
				break;
			}
			char c, c2;
			c = pop(&s);
			c2 = pop(&s2);
			if (c != c2) {
				printf("회문X.");
				break;
			}
		}
		while (1) {
			printf("\n계속 입력하시겠습니까? (YES/NO)");
			char c[4];
			scanf_s("%s", c, 4);
			_strupr_s(c,4);
			//printf("\n%s", c);
			if (strcmp(c, "YES") == 0)
				break;
			else if (strcmp(c, "NO") == 0) { boolean = 0; break; }
		}
		while (getchar() != '\n');
		free(s.stack_c);
		free(s2.stack_c);
		free(string);
	}
}