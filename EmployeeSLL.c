#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#define Max_Array_Name 50
#define Max_Array_Gender 10

typedef struct Employee{
  int id;
  char name[Max_Array_Name];
  char gender[Max_Array_Gender];
  int hour;
  float rate;
  float salary;
}Employee;

struct Nodetype{
  struct Employee info;
  struct Nodetype *next;
};

void initialize(struct Nodetype **plist){
  *plist = NULL;
}

struct Nodetype *GetNode(){
  struct Nodetype *p;
  p = (struct Nodetype*)malloc(sizeof(struct Nodetype));
  return p;
}

void FreeNode(struct Nodetype *p){
  free(p);
}

void CreateList(struct Nodetype **plist, int n){
  struct Nodetype *p, *ptr;
  for(int i = 0; i < n; i++){
    p = GetNode();
    if(p == NULL){
      printf("Memory allocation failed!\n");
      return;
    }

    printf("\nEnter employee %d details:\n", i + 1);
    printf("Enter Id: "); scanf("%d", &p->info.id);
    printf("Enter Name: "); scanf(" %[^\n]", p->info.name);
    printf("Enter Gender: "); scanf("%s", p->info.gender);
    printf("Enter Hour: "); scanf("%d", &p->info.hour);
    printf("Enter Rate: "); scanf("%f", &p->info.rate);

    p -> next = NULL;

    if(*plist == NULL){
      *plist = p;
    } else{
      ptr = *plist;
      while(ptr->next != NULL){
        ptr = ptr -> next;
      }
      ptr->next = p;
    }
  }
}

float calculateSalary(struct Nodetype *plist){
  struct Nodetype *p = plist;
  float total = 0.0;
  while(p != NULL){
    p -> info.salary = p -> info.rate * p -> info.hour;
    total += p -> info.salary;
    p = p -> next;
  }
  return total;
}

void traverse(struct Nodetype *plist){
  if(plist == NULL){
    printf("List is empty\n");
    return;
  }

  calculateSalary(plist);

  struct Nodetype *p = plist;
  printf("\n%-5s %-20s %-10s %-6s %-6s %-8s\n", 
    "ID", "Name", "Gender", "Hour", "Rate", "Salary");
  printf("-----------------------------------------------------------\n");

  while(p != NULL){
    printf("%-5d %-20s %-10s %-6d %-6.2f$ %-8.2f$\n",
      p->info.id,
      p->info.name,
      p->info.gender,
      p->info.hour,
      p->info.rate,
      p->info.salary);
    p = p -> next;
  }
}

int CountNode(struct Nodetype *plist){
  int count = 0;
  struct Nodetype *p = plist;

  while(p != NULL){
    count++;
    p = p -> next;
  }
  return count;
}

void search(struct Nodetype *plist, int id){
  if(plist == NULL){
    printf("List is empty!\n");
    return;
  }
  calculateSalary(plist);

  struct Nodetype *p = plist;
  int found = 0;

  while(p != NULL){
    if(p -> info.id == id){
      printf("\nEmployee found: \n");
      printf("%-5s %-20s %-10s %-6s %-6s %-8s",
        "ID", "Name", "Gender", "Hour", "Rate", "Salary");
      printf("-------------------------------------------------------------\n");
      printf("%-5d %-20s %-10s %-6d %-6.2f$ %-8.2f$",
        p -> info.id,
        p -> info.name,
        p -> info.gender,
        p -> info.hour,
        p -> info.rate,
        p -> info.salary);
        found = 1;
        break;
    }
    p = p -> next;
  }
  if(!found){
    printf("\nEmployee with ID %d not found.\n", id);
  }
}

struct Nodetype* searchPost(struct Nodetype *plist, int pos){
  int index = 0;
  struct Nodetype *p = plist;

  while(p != NULL){
    if(index == pos){
      return p;
    }
    p = p -> next;
    index++;
  }
  return NULL;
}

void sort(struct Nodetype *plist){
    if(plist == NULL || plist->next == NULL) return;

    struct Nodetype *i, *j;
    Employee temp;

    for(i = plist; i != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->info.salary < j->info.salary){
                temp = i->info;
                i->info = j->info;
                j->info = temp;
            }
        }
    }
    printf("Employees sorted by salary in descending order:\n");
    traverse(plist);
}

void insertFirst(struct Nodetype **plist){
  struct Nodetype *p = GetNode();
  if(p == NULL){
    printf("Memory allocation failed!\n");
    return;
  }
  printf("Enter Employee ID: "); scanf("%d", &p->info.id);
  printf("Enter Name: "); scanf(" %[^\n]", p->info.name);
  printf("Enter Gender: "); scanf("%s", p->info.gender);
  printf("Enter Hour: "); scanf("%d", &p->info.hour);
  printf("Enter Rate: "); scanf("%f", &p->info.rate);
  p->info.salary = p->info.hour * p->info.rate;
  p->next = *plist;
  *plist = p;
}

void insertLast(struct Nodetype **plist){
  struct Nodetype *p = GetNode();
  if(p == NULL){
    printf("Memory allocation failed!\n");
    return;
  }

  printf("Enter Employee ID: "); scanf("%d", &p->info.id);
  printf("Enter Name: "); scanf(" %[^\n]", p->info.name);
  printf("Enter Gender: "); scanf("%s", p->info.gender);
  printf("Enter Hour: "); scanf("%d", &p->info.hour);
  printf("Enter Rate: "); scanf("%f", &p->info.rate);
  p->info.salary = p->info.rate * p->info.hour;
  p->next = NULL;

  if(*plist == NULL){
    *plist = p;
  } else{
    struct Nodetype *ptr = *plist;
    while(ptr->next != NULL){
      ptr = ptr->next;
    }
    ptr->next = p;
  }
}

void insertPost(struct Nodetype **plist, int pos){
  if(pos < 0){
    printf("Invalid position!\n");
    return;
  }
  struct Nodetype *p = GetNode();
  if(p == NULL){
    printf("Memory Allocation failed!\n");
    return;
  }

  printf("Enter Employee ID: "); scanf("%d", &p->info.id);
  printf("Enter Name: "); scanf(" %[^\n]", p->info.name);
  printf("Enter Gender: "); scanf("%s", p->info.gender);
  printf("Enter Hour: "); scanf("%d", &p->info.hour);
  printf("Enter Rate: "); scanf("%f", &p->info.rate);
  p->info.salary = p->info.hour * p->info.rate;
  p->next = NULL;

  if(pos == 0){
    p->next = *plist;
    *plist = p;
    return;
  }
  struct Nodetype *ptr = *plist;
  int index = 0;

  while(ptr != NULL && index < pos - 1){
    ptr = ptr -> next;
    index++;
  }

  if(ptr == NULL){
    printf("Position is beyond list length. Insertion failed.\n");
    FreeNode(p);
    return;
  }
  p->next = ptr->next;
  ptr->next = p;
}

void deleteFirst(struct Nodetype **plist){
  if(*plist == NULL){
    printf("List is empty. Nothing to delete.\n");
    return;
  }
  struct Nodetype *ptr = *plist;
  *plist = ptr -> next;
  FreeNode(ptr);
  printf("First node deleted successfully.\n");
}

void deleteLast(struct Nodetype **plist){
  if(*plist == NULL){
    printf("List is empty. Nothing to delete.\n");
    return;
  }

  struct Nodetype *ptr = *plist;
  struct Nodetype *p = NULL;

  if(ptr->next == NULL){
    *plist = NULL;
    FreeNode(ptr);
    printf("Last Node deleted successfully.\n");
    return;
  }

  while(ptr->next != NULL){
    p = ptr;
    ptr = ptr -> next;
  }
  p->next = NULL;
  FreeNode(ptr);
  printf("Last Node deleted successfully.\n");
}


void deletePost(struct Nodetype **plist, int pos) {
    if (*plist == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    if (pos < 0) {
        printf("Invalid position.\n");
        return;
    }

    struct Nodetype *prev = NULL;
    struct Nodetype *curr = *plist;
    int index = 0;

    while (curr != NULL && index < pos) {
        prev = curr;
        curr = curr->next;
        index++;
    }

    if (curr == NULL) {
        printf("Position %d does not exist.\n", pos);
        return;
    }

    if (prev == NULL) {
        *plist = curr->next;
    } else {
        prev->next = curr->next;
    }

    FreeNode(curr);
    printf("Node at position %d deleted successfully.\n", pos);
}

void getMaxSalary(struct Nodetype *plist){
  if(plist == NULL){
    printf("List is empty!\n");
    return;
  }

  struct Nodetype *max = plist;
  struct Nodetype *p = plist->next;

  while(p != NULL){
    if(p->info.salary > max->info.salary){
      max = p;
    }
    p = p->next;
  }
  printf("\nEmployee with the highest salary:\n");
  printf("%-5s %-20s %-10s %-6s %-6s %-8s",
      "ID", "Name", "Gender", "Hour", "Rate", "Salary");
  printf("------------------------------------------------------------\n");

  printf("%-5d %-20s %-10s %-6d %-6.2f$ %-8.2f$", 
    max->info.id,
    max->info.name,
    max->info.gender,
    max->info.hour,
    max->info.rate,
    max->info.salary);
}

void writeToFile(struct Nodetype *plist, const char *filename){
  FILE *fp = fopen(filename, "wb");
  if(fp == NULL){
    printf("Error opening file for writing.\n");
    return;
  }
  struct Nodetype *p = plist;
  while(p != NULL){
    fwrite(&(p->info), sizeof(Employee), 1, fp);
    p = p->next;
  }
  fclose(fp);
  printf("Data saved to file '%s' successfully.\n", filename);
}

void readFromFile(struct Nodetype **plist, const char *filename){
  FILE *fp = fopen(filename, "rb");
  if(fp == NULL){
    printf("Error opening file for reading.\n");
    return;
  }

  initialize(plist);
  Employee tempEmp;
  struct Nodetype *p, *ptr = NULL;

  while(fread(&tempEmp, sizeof(Employee), 1, fp) == 1){
    p = GetNode();
    if(p == NULL){
      printf("Memory allocation failed while reading file.\n");
      fclose(fp);
      return;
    }
    p->info = tempEmp;
    p->next = NULL;

    if(*plist == NULL){
      *plist = p;
      ptr = p;
    } else{
      ptr->next = p;
      ptr = p;
    }
  }

  fclose(fp);
  printf("Data loaded from file '%s' successfully.\n", filename);
}

void updateById(struct Nodetype *plist, int id){
    struct Nodetype *p = plist;
    int found = 0;

    while(p != NULL){
        if(p->info.id == id){
            printf("Updating employee with ID %d:\n", id);
            printf("Enter new Name: "); scanf(" %[^\n]", p->info.name);
            printf("Enter new Gender: "); scanf("%s", p->info.gender);
            printf("Enter new Hour: "); scanf("%d", &p->info.hour);
            printf("Enter new Rate: "); scanf("%f", &p->info.rate);
            p->info.salary = p->info.hour * p->info.rate;
            found = 1;
            printf("Employee updated successfully.\n");
            break;
        }
        p = p->next;
    }

    if(!found){
        printf("Employee with ID %d not found.\n", id);
    }
}

void updateByName(struct Nodetype *plist, const char *name){
    struct Nodetype *p = plist;
    int found = 0;

    while(p != NULL){
        if(strcmp(p->info.name, name) == 0){
            printf("Updating employee with Name '%s':\n", name);
            printf("Enter new ID: "); scanf("%d", &p->info.id);
            printf("Enter new Gender: "); scanf("%s", p->info.gender);
            printf("Enter new Hour: "); scanf("%d", &p->info.hour);
            printf("Enter new Rate: "); scanf("%f", &p->info.rate);
            p->info.salary = p->info.hour * p->info.rate;
            found = 1;
            printf("Employee updated successfully.\n");
            break;
        }
        p = p->next;
    }

    if(!found){
        printf("Employee with Name '%s' not found.\n", name);
    }
}

void updateByPost(struct Nodetype *plist, int pos){
    struct Nodetype *p = plist;
    int index = 0;

    while(p != NULL){
        if(index == pos){
            printf("Updating employee at position %d:\n", pos);
            printf("Enter new ID: "); scanf("%d", &p->info.id);
            printf("Enter new Name: "); scanf(" %[^\n]", p->info.name);
            printf("Enter new Gender: "); scanf("%s", p->info.gender);
            printf("Enter new Hour: "); scanf("%d", &p->info.hour);
            printf("Enter new Rate: "); scanf("%f", &p->info.rate);
            p->info.salary = p->info.hour * p->info.rate;
            printf("Employee updated successfully.\n");
            return;
        }
        index++;
        p = p->next;
    }

    printf("No employee found at position %d.\n", pos);
}

void updateEmployee(struct Nodetype *plist){
    int method, id, pos;
    char name[Max_Array_Name];

    printf("\nChoose update method:\n");
    printf("1. Update by ID\n");
    printf("2. Update by Name\n");
    printf("3. Update by Position\n");
    printf("Enter choice: ");
    scanf("%d", &method);

    switch(method){
        case 1:
            printf("Enter ID to update: ");
            scanf("%d", &id);
            updateById(plist, id);
            break;

        case 2:
            printf("Enter Name to update: ");
            scanf(" %[^\n]", name);
            updateByName(plist, name);
            break;

        case 3:
            printf("Enter Position to update: ");
            scanf("%d", &pos);
            updateByPost(plist, pos);
            break;

        default:
            printf("Invalid choice for update method.\n");
    }
}


void showMenu(){
  printf("\n====== Employee Management System ======\n");
  printf("1. Create list\n");
  printf("2. Traverse\n");
  printf("3. Calculate and show total salary\n");
  printf("4. Count employees\n");
  printf("5. Search employee by ID\n");
  printf("6. Search employee by position\n");
  printf("7. Sort employees by salary (desc)\n");
  printf("8. Insert employee at beginning\n");
  printf("9. Insert employee at end\n");
  printf("10. Insert employee at position\n");
  printf("11. Update Employee\n");
  printf("12. Delete first employee\n");
  printf("13. Delete last employee\n");
  printf("14. Delete employee at position\n");
  printf("15. Show employee with highest salary\n");
  printf("16. Save list to file\n");
  printf("17. Load list from file\n");
  printf("0. Exit\n");
}

int main(){
    struct Nodetype *plist;
    int choice, n, id, pos;
    float total;

    initialize(&plist);

    do {
        showMenu();
        
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter number of employees to create: ");
                scanf("%d", &n);
                CreateList(&plist, n);
                break;

            case 2:
                traverse(plist);
                break;

            case 3:
                total = calculateSalary(plist);
                printf("Total salary of all employees: %.2f$\n", total);
                break;

            case 4:
                printf("Total number of employees: %d\n", CountNode(plist));
                break;

            case 5:
                printf("Enter employee ID to search: ");
                scanf("%d", &id);
                search(plist, id);
                break;

            case 6:
              calculateSalary(plist);
              printf("Enter position to search: ");
              scanf("%d", &pos);
              {
                  struct Nodetype *node = searchPost(plist, pos);
                  if(node != NULL){
                      printf("\nEmployee at position %d:\n", pos);
                      printf("%-5s %-20s %-10s %-6s %-6s %-8s\n", "ID", "Name", "Gender", "Hour", "Rate", "Salary");
                      printf("-------------------------------------------------------------\n");
                      printf("%-5d %-20s %-10s %-6d %-6.2f$ %-8.2f$\n",
                            node->info.id,
                            node->info.name,
                            node->info.gender,
                            node->info.hour,
                            node->info.rate,
                            node->info.salary);
                  } else {
                      printf("No employee found at position %d.\n", pos);
                  }
              }
              break;

            case 7:
                sort(plist);
                printf("\nEmployees sorted by salary in descending order.\n");
                break;

            case 8:
                insertFirst(&plist);
                break;

            case 9:
                insertLast(&plist);
                break;

            case 10:
                printf("Enter position to insert new employee: ");
                scanf("%d", &pos);
                insertPost(&plist, pos);
                break;
            
            case 11:
			    updateEmployee(plist);
			    break;

            case 12:
                deleteFirst(&plist);
                break;

            case 13:
                deleteLast(&plist);
                break;

            case 14:
                printf("Enter position to delete employee: ");
                scanf("%d", &pos);
                deletePost(&plist, pos);
                break;

            case 15:
                getMaxSalary(plist);
                break;
                
            case 16:
			    writeToFile(plist, "employees.dat");
			    break;
			
			case 17:
			    readFromFile(&plist, "employees.dat");
			    break;

            case 0:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while(choice != 0);

    return 0;
}
