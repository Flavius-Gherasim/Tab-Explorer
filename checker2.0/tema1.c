/*Gherasim Flavius-Sebastian 313CC*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct page {
	int id;
	char url[50];
	char *description;
};

// structura in care retin paginile
struct vec_pag {
	struct page *pagina;
} pag[51];
struct tab {
	int id;
	struct page *currentPage;
	struct stack *backwardStack;
	struct stack *forwardStack;
};

// structura stivei
struct stack {
	struct stack *next;
	struct page *pag;
};

// structura nodurilor din lista
struct tabsListnod {
	struct tab *tabul;
	struct tabsListnod *next;
	struct tabsListnod *prev;
};

// santinela
struct tabsList {
	struct tabsListnod *santinela;
};

struct browser {
	struct tab *current;
	struct tabsList list;
};

// functie de initializare a listei
void init(struct tabsList *list, struct tab **current, struct vec_pag x[],
		  int n)
{
	list->santinela = (struct tabsListnod *)malloc(sizeof(struct tabsListnod));
	list->santinela->tabul = NULL;
	list->santinela->next = list->santinela;
	list->santinela->prev = list->santinela;
	struct tabsListnod *newtab =
		(struct tabsListnod *)malloc(sizeof(struct tabsListnod));
	newtab->tabul = (struct tab *)malloc(sizeof(struct tab));
	newtab->tabul->currentPage = x[n - 1].pagina; // pagina 0
	newtab->tabul->id = 0;
	newtab->tabul->backwardStack = NULL;
	newtab->tabul->forwardStack = NULL;
	newtab->next = list->santinela;
	newtab->prev = list->santinela;
	list->santinela->next = newtab;
	list->santinela->prev = newtab;
	*current = newtab->tabul;
}

// functie de creare a unui tab nou
void newtab(struct tabsList *list, struct tab **current, int *id,
			struct vec_pag x[], int n)
{
	struct tabsListnod *newtab =
		(struct tabsListnod *)malloc(sizeof(struct tabsListnod));
	newtab->tabul = (struct tab *)malloc(sizeof(struct tab));
	newtab->tabul->currentPage = x[n - 1].pagina; // pagina 0
	newtab->tabul->id = (*id)++;
	newtab->next = list->santinela;
	newtab->prev = list->santinela->prev;
	list->santinela->prev->next = newtab;
	list->santinela->prev = newtab;
	newtab->tabul->backwardStack = NULL;
	newtab->tabul->forwardStack = NULL;
	*current = newtab->tabul;
}

// functia de print
void printList(struct tabsList *list, struct tab *current, FILE *outputfile)
{
	// gasim tabul curent
	struct tabsListnod *temp = list->santinela->next;
	while (temp->tabul != current) {
		temp = temp->next;
	}
	fprintf(outputfile, "%d ", current->id);
	temp = temp->next;
	// afisam taburile pana la tabul curent
	while (temp->tabul != current) {
		if (temp == list->santinela) {
			temp = temp->next;
			if (temp->tabul != current) {
				fprintf(outputfile, "%d ", temp->tabul->id);
				temp = temp->next;
			}
		} else {
			fprintf(outputfile, "%d ", temp->tabul->id);
			temp = temp->next;
		}
	}
	fprintf(outputfile, "\n");
	fprintf(outputfile, "%s\n", current->currentPage->description);
}

// functia de deschidere a unui tab cu un id
void open(struct tabsList *list, struct tab **current, int *id,
		  FILE *outputfile)
{
	struct tabsListnod *temp = list->santinela->next;
	while (temp != list->santinela) {
		if (temp->tabul->id == (*id)) {
			*current = temp->tabul;
			return;
			// daca am gasit tabul iesire din functie
		}
		temp = temp->next;
	}
	fprintf(outputfile, "403 Forbidden\n");
}

// functie de trecere pe urmatorul tab
void next(struct tabsList *list, struct tab **current)
{
	// gasim tabul curent
	struct tabsListnod *temp = list->santinela->next;
	while (temp->tabul != (*current)) {
		temp = temp->next;
	}
	temp = temp->next;
	if (temp == list->santinela) {
		temp = temp->next;
	}
	*current = temp->tabul;
}

// functie de trecere pe tabul anterior
void prev(struct tabsList *list, struct tab **current)
{
	// gasire tab curent
	struct tabsListnod *temp = list->santinela->next;
	while (temp->tabul != (*current)) {
		temp = temp->next;
	}
	temp = temp->prev;
	if (temp == list->santinela) {
		temp = temp->prev;
	}
	*current = temp->tabul;
}

// functie push pentru stiva
void push(struct stack **stiva, struct page *x)
{
	struct stack *newnode = (struct stack *)malloc(sizeof(struct stack));
	newnode->next = *stiva;
	newnode->pag = x;
	*stiva = newnode;
}

// functie pop pentru stiva
void pop(struct stack **stiva)
{
	if ((*stiva) == NULL) {
		return;
	}
	struct stack *temp;
	temp = (*stiva)->next;
	free(*stiva);
	(*stiva) = temp;
}

// functie afisare inversa a continutului de pe stiva
void invers(struct stack *temp, FILE *outputfile)
{
	if (!temp) {
		return;
	}
	invers(temp->next, outputfile);
	fprintf(outputfile, "%s\n", temp->pag->url);
}

// functia print history
void printh(struct tabsList *list, struct tab **current, FILE *outputfile,
			int *id)
{
	// gasire tabul cu acel id
	struct tabsListnod *temp = list->santinela->next;
	int ok = 0;
	while (temp != list->santinela) {
		if (temp->tabul->id == (*id)) {
			ok = 1;
			break;
		}
		temp = temp->next;
	}
	if (ok == 0) {
		fprintf(outputfile, "403 Forbidden\n");
		return;
	}
	struct stack *temp2 = temp->tabul->forwardStack;
	invers(temp2, outputfile);
	// afisare continut stiva forward
	fprintf(outputfile, "%s\n", temp->tabul->currentPage->url);
	// afisare continut curent
	temp2 = temp->tabul->backwardStack;
	while (temp2) {
		fprintf(outputfile, "%s\n", temp2->pag->url);
		temp2 = temp2->next;
	}
	// afisare continut stiva backward
}

// functie backward
void backward(struct tabsList *list, struct tab **current, FILE *outputfile)
{
	if (!(*current)->backwardStack) {
		fprintf(outputfile, "403 Forbidden\n");
		return;
	}
	push(&(*current)->forwardStack, (*current)->currentPage);
	// pagina actuala este introdusa in stiva forward
	(*current)->currentPage = (*current)->backwardStack->pag;
	// pagina curenta devine cea din varful stivei backward
	pop(&(*current)->backwardStack);
	// se sterge elementul din stiva backward
}

// functia forward
void forwardu(struct tabsList *list, struct tab **current, FILE *outputfile)
{
	if (!(*current)->forwardStack) {
		fprintf(outputfile, "403 Forbidden\n");
		return;
	}
	push(&(*current)->backwardStack, (*current)->currentPage);
	// pagina actuala este introdusa in stiva backward
	(*current)->currentPage = (*current)->forwardStack->pag;
	// pagina curenta devine cea din varful stivei forward
	pop(&(*current)->forwardStack);
	// se sterge elementul din stiva forward
}

// functie de free al paginilor din vectorul de pagini
void freepagini(struct vec_pag temp[], int n)
{
	for (int i = 0; i < n; i++) {
		free(temp[i].pagina->description);
		free(temp[i].pagina);
	}
}

// functie de free al stivei
void freestiva(struct stack *temp)
{
	while (temp) {
		struct stack *temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}

// functie de free al tabului
void freetab(struct tab *temp)
{
	if (!temp) {
		return;
	}
	freestiva(temp->forwardStack);
	freestiva(temp->backwardStack);
	free(temp);
}

// functia de inchidere al tabului
void close(struct tabsList *list, struct tab **current, FILE *outputfile)
{
	if ((*current)->id == 0) {
		fprintf(outputfile, "403 Forbidden\n");
		return;
	}
	// gasire tab curent
	struct tabsListnod *temp = list->santinela->next;
	while (temp->tabul != (*current)) {
		temp = temp->next;
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	*current = temp->prev->tabul;
	freetab(temp->tabul);
	free(temp);
	// eliberare de memorie
}

// functia de deschidere a unei pagini cu un id
void pageid(struct tabsList *list, struct tab **current, int n, int *id,
			struct vec_pag v[], FILE *outputfile)
{
	int i, ok = 0;
	for (i = 0; i < n; i++) {
		if (v[i].pagina->id == (*id)) {
			ok = 1;
			break;
		}
	}
	// gasire pagina
	if (ok == 0) {
		fprintf(outputfile, "403 Forbidden\n");
		return;
	}
	push(&(*current)->backwardStack, (*current)->currentPage);
	// adaugare elementul ce se afla in current in stiva backward
	(*current)->currentPage = v[i].pagina;
	// pagina curenta devine cea din vector
	freestiva((*current)->forwardStack);
	// eliberare memorie stiva forward
	(*current)->forwardStack = NULL;
}

// functie de eliberare a listei de taburi si a santinelei
void free_listataburi(struct tabsList *list)
{
	struct tabsListnod *temp = list->santinela->next;
	while (temp != list->santinela) {
		struct tabsListnod *temp2 = temp->next;
		freetab(temp->tabul);
		free(temp);
		temp = temp2;
	}
	free(list->santinela);
}

// functia main
int main(void)
{
	struct browser browserul;
	int n, m;
	int id = 1;
	char s[100];
	// deschidere fisiere
	FILE *inputfile, *outputfile;
	inputfile = fopen("tema1.in", "r");
	outputfile = fopen("tema1.out", "w");
	fscanf(inputfile, "%d", &n);
	// citire nr de pagini
	for (int i = 0; i < n; i++) {
		pag[i].pagina =
			(struct page *)malloc(sizeof(struct page)); // alocarea paginii
		fscanf(inputfile, "%d", &pag[i].pagina->id);	// citire id
		fscanf(inputfile, "%s", pag[i].pagina->url);	// citire url
		fgetc(inputfile);								// eliminare newline
		fscanf(inputfile, "%[^\n]",
			   s); // citire descrierii pana la sfarsitul liniei
		pag[i].pagina->description =
			(char *)malloc(strlen(s) + 1); // alocarea descrierii
		strcpy(pag[i].pagina->description, s);
	}
	// adaugare pe pozitia n in vector a paginii cu id 0
	pag[n].pagina = (struct page *)malloc(sizeof(struct page));
	pag[n].pagina->id = 0;
	strcpy(pag[n].pagina->url, "https://acs.pub.ro/");
	pag[n].pagina->description = malloc(strlen("Computer Science") + 1);
	strcpy(pag[n].pagina->description, "Computer Science");
	n++; // incrementare nr de pagini
	init(&browserul.list, &browserul.current, pag, n);
	// initializarea listei
	fscanf(inputfile, "%d", &m); // citirea nr de operatii
	for (int i = 0; i < m; i++) {
		fgetc(inputfile); // consumare newline
		fscanf(inputfile, "%[^\n]",
			   s); // citirea operatiei pana la finalul liniei
		int inv = 0;
		// determinarea idului in cazul operatiilor ce contin id
		for (int j = 0; j <= strlen(s) - 1; j++) {
			if (s[j] == ' ') {
				j++;
				while (s[j] >= '0' && s[j] <= '9') {
					inv = inv * 10 + (s[j] - '0');
					j++;
				}
				j--;
			}
		}
		// determinarea operatiei
		if (strcmp(s, "NEW_TAB") == 0) {
			newtab(&browserul.list, &browserul.current, &id, pag, n);
		} else if (strcmp(s, "CLOSE") == 0) {
			close(&browserul.list, &browserul.current, outputfile);
		} else if (strcmp(s, "PRINT") == 0) {
			printList(&browserul.list, browserul.current, outputfile);
		} else if (strstr(s, "OPEN")) {
			open(&browserul.list, &browserul.current, &inv, outputfile);
		} else if (strcmp(s, "NEXT") == 0) {
			next(&browserul.list, &browserul.current);
		} else if (strcmp(s, "PREV") == 0) {
			prev(&browserul.list, &browserul.current);
		} else if (strstr(s, "PAGE")) {
			pageid(&browserul.list, &browserul.current, n, &inv, pag,
				   outputfile);
		} else if (strstr(s, "PRINT_")) {
			printh(&browserul.list, &browserul.current, outputfile, &inv);
		} else if (strcmp(s, "BACKWARD") == 0) {
			backward(&browserul.list, &browserul.current, outputfile);
		} else if (strcmp(s, "FORWARD") == 0 || strcmp(s, "FORWARD ") == 0) {
			forwardu(&browserul.list, &browserul.current, outputfile);
		}
	}
	free_listataburi(&browserul.list);
	// eliberare lista
	freepagini(pag, n);
	// eliberare pagini
	fclose(inputfile);
	fclose(outputfile);
	// inchidere fisiere
	return 0;
}
