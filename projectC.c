#include <stdio.h>
#include <string.h>
#define Max 100
struct Location{
	char name[50];
	char address[100];
};
struct Passenger{
	char name[50];
	char phone[15];
};
struct Trip{
	char tripId[20];
	struct Location departure;
	struct Location destination;
	char date[20];
	int totalSeats;
	int bookedSeats;
};
struct Ticket{
	char ticketId[20];
	char tripId[20];
	struct Passenger passenger;
	int seatNumber;
	double price;
	int paymentStatus;
	char date[20];
};
void printMenu();
void createNewTrip(struct Trip trips[],int *a);
void updateTripInfo(struct Trip trips[], int a);
int main(){
	struct Trip trips[Max];
	int i, a = 0;
    int choice;
    char ch;
    do {
        printMenu();
        printf("nhap lua chon cua ban: ");

        ch = getchar();
        if (ch == '\n') {
            printf("vui long khong nhap phan tu rong!?\n");
            continue;
        }
        ungetc(ch, stdin);
        if (scanf("%d", &choice) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("lua chon khong hop le! vui long nhap lai.\n");
            continue;
        }
        while ((ch = getchar()) != '\n' && ch != EOF);
        switch (choice) {
            case 1:
                createNewTrip(trips,&a);
                break;
            case 2:
			updateTripInfo(trips, a);
			break;
            case 3:
                printf("Ban chon 3\n");
                break;
            case 4:
                printf("Ban chon 4\n");
                break;
            case 5:
                printf("Ban chon 5\n");
                break;
            case 6:
                printf("Ban chon 6\n");
                break;
            case 7:
                printf("Ban chon 7\n");
                break;
            case 8:
                printf("Ban chon 8\n");
                break;
            case 9:
                printf("thoat chuong trinh.\n");
                break;
            default:
            	printf("lua chon khong hop le! vui long nhap lai.\n");
            	break;
        }

    } while (choice != 9);

    return 0;
}

void printMenu() {
    printf("+------------------MENU------------------+\n");
    printf("|%-40s|\n","1. Them chuyen xe moi.");
    printf("|%-40s|\n","2. Cap nhap thong tin chuyen xe.");
    printf("|%-40s|\n","3. Dat ve.");
    printf("|%-40s|\n","4. Kiem tra tinh trang ve.");
    printf("|%-40s|\n","5. Liet ke chuyen xe.");
    printf("|%-40s|\n","6. Thanh toan ve.");
    printf("|%-40s|\n","7. Quan ly trang thai ve.");
    printf("|%-40s|\n","8. Bao cao doanh thu va thong ke ve.");
    printf("|%-40s|\n","9. Thoat chuong trinh.");
    printf("+----------------------------------------+\n");
}
int validateTrip(struct Trip *trip) {
    if (strlen(trip->tripId) == 0 ||
        strlen(trip->departure.name) == 0 ||
        strlen(trip->departure.address) == 0 ||
        strlen(trip->destination.name) == 0 ||
        strlen(trip->destination.address) == 0 ||
        strlen(trip->date) == 0 ||
        trip->totalSeats <= 0) {
        return 0;
    }
    return 1;
}
void createNewTrip(struct Trip trips[],int *a) {
    if (*a>= Max) {
        printf("Danh sach chuyen xe da day! Them that bai!\n");
        return;
    }
    struct Trip newTrip;
    printf("Nhap ma chuyen xe: ");
    scanf("%s", newTrip.tripId);
    for (int i = 0; i < *a; i++) {
        if (strcmp(trips[i].tripId, newTrip.tripId) == 0) {
            printf("Ma chuyen xe da ton tai. Them that bai!\n");
            return;
        }
    }
    printf("Nhap ten diem di: ");
    scanf(" %[^\n]", newTrip.departure.name);
    printf("Nhap dia chi diem di: ");
    scanf(" %[^\n]", newTrip.departure.address);
    printf("Nhap ten diem den: ");
    scanf(" %[^\n]", newTrip.destination.name);
    printf("Nhap dia chi diem den: ");
    scanf(" %[^\n]", newTrip.destination.address);
    printf("Nhap ngay gio chuyen: ");
    scanf(" %[^\n]", newTrip.date);
    printf("Nhap tong so ghe: ");
    scanf("%d", &newTrip.totalSeats);
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    if (!validateTrip(&newTrip)) {
        printf("Du lieu nhap vao khong hop le. Them that bai!\n");
        return;
    }
    newTrip.bookedSeats = 0;
    trips[*a] = newTrip;
    (*a)++;
    printf("Them chuyen xe thanh cong!\n");
}
void updateTripInfo(struct Trip trips[], int a) {
    if (a == 0) {
        printf("Danh sach chuyen xe trong!\n");
        return;
    }

    char tripId[20];
    printf("Nhap ma chuyen xe can cap nhat: ");
    scanf("%s", tripId);

    int found = 0;
    for (int i = 0; i < a; i++) {
        if (strcmp(trips[i].tripId, tripId) == 0) {
            found = 1;
            struct Trip *t = &trips[i];
            
            printf("Nhap thong tin moi cho chuyen xe\n");
            printf("Nhap ma chuyen xe: ");
            scanf("%s", t->tripId);

            printf("Nhap ten diem di: ");
            scanf(" %[^\n]", t->departure.name);
            printf("Nhap dia chi diem di: ");
            scanf(" %[^\n]", t->departure.address);

            printf("Nhap ten diem den: ");
            scanf(" %[^\n]", t->destination.name);
            printf("Nhap dia chi diem den: ");
            scanf(" %[^\n]", t->destination.address);

            int newTotalSeats;
            do {
                printf("Nhap tong so ghe : ", t->bookedSeats);
                scanf("%d", &newTotalSeats);
                if (newTotalSeats < t->bookedSeats) {
                    printf("Tong so ghe phai >= so ghe da dat (%d). Vui long nhap lai.\n", t->bookedSeats);
                }
            } while (newTotalSeats < t->bookedSeats);
            t->totalSeats = newTotalSeats;

            printf("Nhap ngay gio chuyen: ");
            scanf(" %[^\n]", t->date);

            printf("Cap nhat thong tin chuyen xe thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay chuyen xe voi ma %s xin cam on!\n", tripId);
    }
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
