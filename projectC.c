#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 100
struct Location{
    char name[50];
    char address[100];
};
struct Passenger{
    char name[50];
    char phone[12];
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
};
// Danh sach chuyen xe va ve
struct Trip trips[Max];
int tripCount = 0;
struct Ticket tickets[Max];
int ticketCount = 0;
// Prototype
void printMenu();
void createNewTrip();
void hienThiTrips();
void updateTripInfo();
void bookTicket();
void checkTicketStatus();
void error(char *prompt, char *buffer, int size);
int isOnlyNumber(char *s);
int seatIsBooked(char tripId[], int seat);
void listTrips();
int main(){
    int choice;
    char ch;
    do {
        printMenu();
        printf("Nhap lua chon cua ban: ");
        ch = getchar();
        if(ch=='\n'){
            printf("Vui long khong nhap phan tu rong!\n");
            continue;
        }
        ungetc(ch, stdin);
        if(scanf("%d", &choice)!=1){
            while((ch=getchar())!='\n' && ch!=EOF);
            printf("Ki tu khong duoc nhap!Vui long nhap lai.\n");
            continue;
        }
        while((ch=getchar())!='\n' && ch!=EOF);
        switch(choice){
            case 1: createNewTrip(); break;
            case 2: updateTripInfo(); break;
            case 3: bookTicket(); break;
            case 4: checkTicketStatus(); break;
            case 5: listTrips(); break;
            case 6: printf("Ban chon 6\n"); break;
            case 7: printf("Ban chon 7\n"); break;
            case 8: printf("Ban chon 8\n"); break;
            case 9: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le! Vui long nhap lai.\n"); break;
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
        printf("Danh sach chuyen xe da day! Them that bai!\n");
        return;
    }
    struct Trip newTrip;
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
    newTrip.bookedSeats=0;
    trips[tripCount++]=newTrip;
    printf("Them chuyen xe thanh cong!\n");
}
// Hien thi danh sach chuyen xe
void hienThiTrips(){
    printf("+-------DANH SACH CHUYEN XE-------+\n");
    for(int i=0;i<tripCount;i++){
        printf("Chuyen %d:\n",i+1);
        printf("Ma: %s\n", trips[i].tripId);
        printf("Di: %s - %s\n", trips[i].departure.name,trips[i].departure.address);
        printf("Den: %s - %s\n", trips[i].destination.name,trips[i].destination.address);
        printf("Ngay: %s\n", trips[i].date);
        printf("Tong ghe: %s | Da dat: %d\n", trips[i].totalSeats,trips[i].bookedSeats);
        printf("+-------------------------------+\n");
    }
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
        error("Nhap so dien thoai (10 chu so): ", newTicket.passenger.phone,12);
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
    // Tao ticketId
    sprintf(newTicket.ticketId,"TICKET%d",ticketCount+1);
    tickets[ticketCount++]=newTicket;
    t->bookedSeats++;
    printf("Dat ve thanh cong!\n");
}
// Kiem tra tinh trang ve
void checkTicketStatus(){
    if(ticketCount==0){ printf("Chua co ve nao!\n"); return; }
    char ticketId[20];
    error("Nhap ma ve can kiem tra: ", ticketId,20);
    int found=0;
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].ticketId,ticketId)==0){
            found=1;
            printf("+------------THONG TIN VE------------+\n");
            printf("Ten hanh khach: %s\n", tickets[i].passenger.name);
            printf("SDT: %s\n", tickets[i].passenger.phone);
            for(int j=0;j<tripCount;j++){
                if(strcmp(trips[j].tripId,tickets[i].tripId)==0){
                    printf("Chuyen xe: %s\n", trips[j].tripId);
                    printf("Di: %s - %s\n", trips[j].departure.name,trips[j].departure.address);
                    printf("Den: %s - %s\n", trips[j].destination.name,trips[j].destination.address);
                    printf("Ngay: %s\n", trips[j].date);
                    break;
                }
            }
            printf("So ghe: %d\n", tickets[i].seatNumber);
            printf("Gia ve: %.0f VND\n", tickets[i].price);
            printf("Trang thai thanh toan: %s\n", tickets[i].paymentStatus ? "Da thanh toan" : "Chua thanh toan");
            printf("+-------------------------------------+\n");
            break;
        }
    }
    if(!found) printf("Khong tim thay ve voi ma %s!\n",ticketId);
}
void listTrips(){
    if(tripCount==0){
        printf("Khong co chuyen xe de hien thi!\n");
        return;
    }

    int pageSize=10;
    char input[20];
    printf("Nhap so dong / trang (mac dinh 10): ");
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
        
    printf("+--------------------DANH SACH CHUYEN XE (Trang %d/%d)---------------------+\n",pageNumber,totalPages);
    printf("|%-5s|%-10s|%-15s|%-15s|%-12s|%-10s|\n",
           "STT","TripID","Diem Di","Diem Den","Ngay","Ghe");
    printf("+-----+----------+---------------+---------------+------------+----------+\n");
    for(int i=start;i<end;i++){
        printf("|%-5d|%-10s|%-15s|%-15s|%-12s|%-10s|\n",
		i+1,trips[i].tripId,trips[i].departure.name,trips[i].destination.name,trips[i].date,trips[i].totalSeats);
    }
    printf("+------------------------------------------------------------------------+\n");
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
