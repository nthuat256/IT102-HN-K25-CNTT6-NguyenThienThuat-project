#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
    char totalSeats[Max];
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
    int status;
};
// Danh sach chuyen xe va ve
struct Trip trips[Max];
int tripCount = 0;
struct Ticket tickets[Max];
int ticketCount = 0;
// Prototype
void printMenu();
void error(char *prompt, char *buffer, int size);
void createNewTrip();
void hienThiTrips();
void updateTripInfo();
void bookTicket();
void checkTicket();
void ticketShow();
int isOnlyNumber(char *s);
int seatIsBooked(char tripId[], int seat);
void listTrips();
void payTicket();
void manageTicket();
int main(){
    int choice;
    initSampleTrips();
    do {
        printMenu();
        printf("Nhap lua chon cua ban: ");
        char input[20];
		fgets(input, sizeof(input), stdin);
		// Xoa ky tu xuong dong
		input[strcspn(input, "\n")] = 0;
		// Kiem tra rong hoac chi co dau cach
		int onlySpace = 1;
		for(int i = 0; i < strlen(input); i++){
			if(!isspace(input[i])){
				onlySpace = 0;
				break;
			}
		}
		if(strlen(input) == 0 || onlySpace){
		printf("Vui long khong nhap phan tu rong!\n");
		continue;
		}
		if(!isOnlyNumber(input)){
		printf("Ki tu khong duoc nhap! Vui long nhap lai.\n");
		continue;
	}
	choice = atoi(input);
    switch(choice){
	case 1: createNewTrip();break;
	case 2: updateTripInfo();break;
	case 3: bookTicket();break;
	case 4: checkTicket();break;
	case 5: listTrips();break;
	case 6: payTicket();break;
	case 7: manageTicket();break;
	case 8: printf("Ban chon 8\n");break;
	case 9: printf("Thoat chuong trinh.\n"); break;
	default: printf("Lua chon khong hop le! Vui long nhap lai.\n");break;
}
    } while(choice!=9);
    return 0;
}
void printMenu(){
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
// Ham nhap khong de trong
void error(char *prompt, char *buffer, int size){
    do{
        printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer,"\n")]=0;
        if(strlen(buffer)==0)
            printf("Khong duoc de trong! Vui long nhap lai.\n");
    } while(strlen(buffer)==0);
}
// Kiem tra chuoi chi co so
int isOnlyNumber(char *s){
    for(int i=0;i<strlen(s);i++){
        if(s[i]<'0' || s[i]>'9') return 0;
    }
    return 1;
}
// Kiem tra ghe da dat chua
int seatIsBooked(char tripId[], int seat){
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].tripId, tripId)==0 && tickets[i].seatNumber==seat)
            return 1;
    }
    return 0;
}
// Them chuyen xe moi
void createNewTrip(){
    if(tripCount>=Max){
        printf("Danh sach chuyen xe da day! Them that bai!\n");return;}
    struct Trip newTrip;
    printf("+---------THEM CHUYEN XE MOI----------+\n");
    error("Nhap ma chuyen xe: ", newTrip.tripId, 20);
    for(int i=0;i<tripCount;i++){
        if(strcmp(trips[i].tripId,newTrip.tripId)==0){
            printf("Ma chuyen xe da ton tai. Them that bai!\n");
            hienThiTrips();
            return;
        }
    }
    error("Nhap ten diem di: ", newTrip.departure.name,50);
    error("Nhap dia chi diem di: ", newTrip.departure.address,100);
    error("Nhap ten diem den: ", newTrip.destination.name,50);
    error("Nhap dia chi diem den: ", newTrip.destination.address,100);
    error("Nhap ngay gio chuyen: ", newTrip.date,20);
    do{
        error("Nhap tong so ghe: ", newTrip.totalSeats, Max);
        if(atoi(newTrip.totalSeats)<=0)
            printf("So ghe phai >0!\n");
    }while(atoi(newTrip.totalSeats)<=0);
    printf("+-------------------------------------+\n");
    newTrip.bookedSeats=0;
    trips[tripCount++]=newTrip;
    printf("Them chuyen xe thanh cong!\n");
}
// Hien thi danh sach chuyen xe
void hienThiTrips(){
    if(tripCount==0){
        printf("Khong co chuyen xe nao!\n");
        return;
    }
    printf("+------------------------------------DANH SACH CHUYEN XE------------------------------------+\n");
    printf("|%-5s|%-10s|%-15s|%-15s|%-20s|%-10s|%-10s|\n",
           "STT","TripID","Diem Di","Diem Den","Ngay","Tong ghe","Da dat");
    printf("+-------------------------------------------------------------------------------------------+\n");
    for(int i=0;i<tripCount;i++){
        printf("|%-5d|%-10s|%-15s|%-15s|%-20s|%-10s|%-10d|\n",
            i+1,trips[i].tripId,trips[i].departure.name,trips[i].destination.name,trips[i].date,trips[i].totalSeats,trips[i].bookedSeats);
    }
    printf("+-------------------------------------------------------------------------------------------+\n");
}
// Cap nhat thong tin chuyen xe
void updateTripInfo(){
    if(tripCount==0){ printf("Danh sach chuyen xe trong!\n"); return; }
    char tripId[20];
    error("Nhap ma chuyen xe can cap nhat: ", tripId, 20);
    int found=0;
    for(int i=0;i<tripCount;i++){
        if(strcmp(trips[i].tripId,tripId)==0){
            found=1;
            struct Trip *t=&trips[i];
            error("Nhap ten diem di moi: ", t->departure.name,50);
            error("Nhap dia chi diem di moi: ", t->departure.address,100);
            error("Nhap ten diem den moi: ", t->destination.name,50);
            error("Nhap dia chi diem den moi: ", t->destination.address,100);
            error("Nhap ngay gio moi: ", t->date,20);
            int newSeats;
            do{
                error("Nhap tong so ghe moi: ", t->totalSeats, Max);
                newSeats=atoi(t->totalSeats);
                if(newSeats<t->bookedSeats)
                    printf("So ghe moi phai >= so ghe da dat (%d)!\n", t->bookedSeats);
            }while(newSeats<t->bookedSeats);
            printf("Cap nhat thong tin chuyen xe thanh cong!\n");
            return;
        }
    }
    if(!found){
        printf("Khong tim thay chuyen xe voi ma %s\n", tripId);
        hienThiTrips();
    }
}
// Dat ve
void bookTicket(){
    if(tripCount==0){ printf("Chua co chuyen xe nao!\n"); return; }
    struct Ticket newTicket;
    char seatStr[10];
    error("Nhap ma chuyen xe: ", newTicket.tripId, 20);
    int foundTrip=-1;
    for(int i=0;i<tripCount;i++){
        if(strcmp(trips[i].tripId,newTicket.tripId)==0){
            foundTrip=i;
            break;
        }
    }
    if(foundTrip==-1){
        printf("Ma chuyen xe khong ton tai!\n");
        hienThiTrips();
        return;
    }
    struct Trip *t=&trips[foundTrip];
    if(atoi(t->totalSeats)<=t->bookedSeats){
        printf("Chuyen xe da het cho!\n");
        return;
    }
    error("Nhap ten hanh khach: ", newTicket.passenger.name,50);
    do{
        error("Nhap so dien thoai (10 chu so): ", newTicket.passenger.phone,15);
        if(!isOnlyNumber(newTicket.passenger.phone)||strlen(newTicket.passenger.phone)!=10)
            printf("So dien thoai phai la 10 chu so!\n");
    }while(!isOnlyNumber(newTicket.passenger.phone)||strlen(newTicket.passenger.phone)!=10);
    int seat;
    do{
        error("Nhap so ghe: ", seatStr,10);
        seat=atoi(seatStr);
        if(seat<=0 || seat>atoi(t->totalSeats))
            printf("So ghe khong hop le!\n");
        else if(seatIsBooked(newTicket.tripId,seat))
            printf("Ghe nay da duoc dat!\n");
        else break;
    }while(1);
    newTicket.seatNumber=seat;
    newTicket.price=20000;
    error("Nhap ngay dat ve: ", newTicket.date,20);
    newTicket.paymentStatus=0;
    newTicket.status = 0;
    // Tao ticketId
    sprintf(newTicket.ticketId,"TICKET%d",ticketCount+1);
    tickets[ticketCount++]=newTicket;
    t->bookedSeats++;
    printf("Dat ve thanh cong!\n");
    
}
// Kiem tra tinh trang ve
void checkTicket(){
    if(ticketCount==0){ printf("Chua co ve nao!\n"); return; }
    char ticketId[20];
    error("Nhap ma ve can kiem tra: ", ticketId,20);
    int found=0;
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].ticketId,ticketId)==0){
            found=1;
            printf("+----------- THONG TIN VE -----------+\n");
            printf("+----------------+-------------------+\n");
			printf("|%-15s|%-20s|\n","Ma ve",tickets[i].ticketId);
			printf("|%-15s|%-20s|\n","Hanh khach",tickets[i].passenger.name);
			printf("|%-15s|%-20s|\n","SDT",tickets[i].passenger.phone);
			printf("+----------------+-------------------+\n");
    for(int j=0;j<tripCount;j++){
        if(strcmp(trips[j].tripId,tickets[i].tripId)==0){
        	printf("|%-15s|%-20s|\n","Chuyen xe",trips[j].tripId);
			printf("|%-15s|%-20s|\n","Diem di",trips[j].departure.name);
			printf("|%-15s|%-20s|\n","Diem den",trips[j].destination.name);
			printf("|%-15s|%-20s|\n","Ngay",trips[j].date);
			printf("+----------------+-------------------+\n");
			break;
			}
		}
		printf("|%-15s|%-20d|\n","So ghe",tickets[i].seatNumber);
		printf("|%-15s|%-20.0f|\n","Gia ve",tickets[i].price);
		const char *tt;
		if(tickets[i].status==1) tt="Da khoa";
		else if(tickets[i].status==2) tt="Da huy";
		else tt = tickets[i].paymentStatus ? "Da thanh toan" : "Chua thanh toan";
		printf("|%-15s|%-20s|\n","Trang thai", tt);
		printf("+------------------------------------+\n");
		break;
		}
	}
	if(!found)
	printf("Khong tim thay ve voi ma %s!\n",ticketId);
	ticketShow();
	return;
}
//hien thi ve hien co 
void ticketShow(){
	printf("+---------------------DANH SACH VE-------------------------+\n");
    printf("|%-10s|%-15s|%-15s|%-15s|\n", "Ma ve", "Hanh khach", "SDT", "Trang thai");
    printf("+----------------------------------------------------------+\n");
    for(int i=0;i<ticketCount;i++){
    	if(tickets[i].status == 2) continue;
        printf("|%-10s|%-15s|%-15s|%-15s|\n",
            tickets[i].ticketId,tickets[i].passenger.name,tickets[i].passenger.phone,tickets[i].paymentStatus ? "Da thanh toan" : "Chua thanh toan");
    }
    printf("+----------------------------------------------------------+\n");
}
void listTrips(){
    if(tripCount==0){
        printf("Khong co chuyen xe de hien thi!\n");
        return;
    }
    int pageSize=10;
    char input[20];
    printf("Nhap so dong / trang : ");
    fgets(input, sizeof(input), stdin);
    if(strlen(input) > 1)
        pageSize = atoi(input);
    if(pageSize <= 0){
        printf("pageSize phai > 0!\n");
        return;
    }
    int totalPages = (tripCount + pageSize - 1) / pageSize;
    int pageNumber = 1;
    char choice;
    do{
        int start = (pageNumber - 1) * pageSize;
        int end = start + pageSize;
        if(end > tripCount) end = tripCount;
    printf("+--------------------DANH SACH CHUYEN XE (Trang %d/%d)-------------------------+\n",pageNumber,totalPages);
    printf("|%-5s|%-10s|%-15s|%-15s|%-16s|%-10s|\n",
           "STT","TripID","Diem Di","Diem Den","Ngay","Ghe");
    printf("+-----+----------+---------------+---------------+----------------+----------+\n");
    for(int i=start;i<end;i++){
        printf("|%-5d|%-10s|%-15s|%-15s|%-16s|%-10s|\n",
		i+1,trips[i].tripId,trips[i].departure.name,trips[i].destination.name,trips[i].date,trips[i].totalSeats);
    }
    printf("+----------------------------------------------------------------------------+\n");
    printf("[N] Next | [P] Previous | [Q] Thoat\n");
        printf("Chon: ");
        choice = getchar();
        while(getchar()!='\n');
        if((choice=='N' || choice=='n') && pageNumber < totalPages)
            pageNumber++;
        else if((choice=='P' || choice=='p') && pageNumber > 1)
            pageNumber--;
        else if(choice=='Q' || choice=='q')
            break;
    }while(1);
}
//thanh toan ticket
void payTicket(){
    if(ticketCount==0){
        printf("Chua co ve nao!\n");
        return;
    }
    char ticketId[20];
    error("Nhap ma ve can thanh toan: ", ticketId, 20);
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].ticketId, ticketId)==0){
            if(tickets[i].status != 0){
                printf("Khong the thanh toan. Trang thai ve: %s\n",
                    tickets[i].status==1?"Locked":"Canceled");
                return;
            }
            if(tickets[i].paymentStatus==1){
                printf("Ve nay da duoc thanh toan truoc do!\n");
                return;
            }
            tickets[i].paymentStatus = 1;
            printf("Thanh toan ve thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay ve %s!\n", ticketId);
    ticketShow();
}
void manageTicket(){
    if(ticketCount==0){
        printf("Chua co ve nao!\n");
        return;
    }
    char ticketId[20];
    error("Nhap ma ve: ", ticketId, 20);
    int found = 0;
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].ticketId, ticketId)==0){
            found = 1;
            if(tickets[i].status != 0){
                printf("Khong the thao tac. Trang thai ve: %s\n",
                    tickets[i].status==1?"Locked":"Canceled");
                return;
            }
            int exit = 0;
            do {
                printf("\n+-----QUAN LY TRANG THAI VE-----+\n");
                printf("|%-31s|\n","1. Khoa ve");
                printf("|%-31s|\n","2. Huy ve");
                printf("|%-31s|\n","3. Thoat");
                printf("+-------------------------------+\n");
                char buf[10];
                printf("Chon: ");
                fgets(buf, sizeof(buf), stdin);
                buf[strcspn(buf, "\n")] = 0;
                if(strlen(buf)==0){
                    printf("Vui long khong nhap rong!\n");
                    continue;
                }
                if(!isOnlyNumber(buf)){
                    printf("Vui long nhap so!\n");
                    continue;
                }
                int ch = atoi(buf);
                if(ch==3){ exit = 1; break; }
                if(ch!=1 && ch!=2){
                    printf("Lua chon khong hop le!\n");
                    continue;
                }

                if(ch==1){ // Khoa ve
                    if(tickets[i].paymentStatus==0){
                        printf("Khong the khoa ve chua thanh toan!\n");
                    } else {
                        tickets[i].status = 1;
                        printf("Khoa ve thanh cong!\n");
                    }
                } else if(ch==2){ // Huy ve
                    if(tickets[i].paymentStatus==1){
                        printf("Khong the huy ve da thanh toan!\n");
                    } else {
                        tickets[i].status = 2; // Canceled
                        // Giai phong ghe
                        for(int j=0;j<tripCount;j++){
                            if(strcmp(trips[j].tripId, tickets[i].tripId)==0){
                                trips[j].bookedSeats--;
                                break;
                            }
                        }
                        printf("Huy ve thanh cong!\n");
                    }
                }
            } while(!exit);

            break;
        }
    }
    if(!found){
        printf("Khong tim thay ve!\n");
        ticketShow();
    }
}
void initSampleTrips() {
    struct Trip t;
    // Chuy?n xe 1
    strcpy(t.tripId, "TX001");
    strcpy(t.departure.name, "Ha Noi");
    strcpy(t.departure.address, "Noi Bai");
    strcpy(t.destination.name, "Hai Phong");
    strcpy(t.destination.address, "Ben xe Hai Phong");
    strcpy(t.date, "2025-12-01 08:00");
    strcpy(t.totalSeats, "40");
    t.bookedSeats = 0;
    trips[tripCount++] = t;

    // Chuy?n xe 2
    strcpy(t.tripId, "TX002");
    strcpy(t.departure.name, "Ha Noi");
    strcpy(t.departure.address, "Noi Bai");
    strcpy(t.destination.name, "Thanh Hoa");
    strcpy(t.destination.address, "Ben xe Thanh Hoa");
    strcpy(t.date, "2025-12-01 09:00");
    strcpy(t.totalSeats, "35");
    t.bookedSeats = 0;
    trips[tripCount++] = t;

    // Chuy?n xe 3
    strcpy(t.tripId, "TX003");
    strcpy(t.departure.name, "Da Nang");
    strcpy(t.departure.address, "Ben xe Da Nang");
    strcpy(t.destination.name, "Quang Ngai");
    strcpy(t.destination.address, "Ben xe Quang Ngai");
    strcpy(t.date, "2025-12-02 07:30");
    strcpy(t.totalSeats, "30");
    t.bookedSeats = 0;
    trips[tripCount++] = t;

    // Chuy?n xe 4
    strcpy(t.tripId, "TX004");
    strcpy(t.departure.name, "Ho Chi Minh");
    strcpy(t.departure.address, "Ben xe Mien Dong");
    strcpy(t.destination.name, "Vung Tau");
    strcpy(t.destination.address, "Ben xe Vung Tau");
    strcpy(t.date, "2025-12-02 10:00");
    strcpy(t.totalSeats, "50");
    t.bookedSeats = 0;
    trips[tripCount++] = t;

    // Chuy?n xe 5
    strcpy(t.tripId, "TX005");
    strcpy(t.departure.name, "Can Tho");
    strcpy(t.departure.address, "Ben xe Can Tho");
    strcpy(t.destination.name, "Soc Trang");
    strcpy(t.destination.address, "Ben xe Soc Trang");
    strcpy(t.date, "2025-12-03 06:00");
    strcpy(t.totalSeats, "25");
    t.bookedSeats = 0;
    trips[tripCount++] = t;
}

